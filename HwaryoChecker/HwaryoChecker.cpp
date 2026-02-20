#include "HwaryoChecker.h"
#include "Jaksadata.h"
#include <iostream>
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"

HwaryoChecker::HwaryoChecker(Jaksadata * jaksa, int hwaryopae_type){

    printf("화료체크 시작\n");

    sonTil = &jaksa->sonTils[0];

    int last_tile = jaksa->lastTile;

    // 손패 갯수 -> 값이 1, 4, 7, 10, 13 만 가능해야 함.
    int sonTil_len = jaksa->sonTils.size();

    // tsu_blocks = new std::vector<TsuBlock>();
    // hwaryo_list = new std::vector<HwaryoInfo>();
    // pae_count = new int[38];
    for(int i=0;i<38;i++){
        pae_count[i] = 0;
    }

    for(int i = 0; i < sonTil_len; i++){
        pae_count_update(sonTil[i]);
    }
        
    pae_count_update(last_tile);

    // 화패가 있는 경우 화료 안됨. 바로 리턴.
    if(hwapae_exist){return;}

    printf("국사무쌍 체크 시작\n");
    // 국사무쌍 체크 (바로 리턴)
    YakuChecker::guksa(&hwaryo_list, pae_count, last_tile, hwaryopae_type);
    if(hwaryo_list.size() > 0){gu = true;return;}
    printf("국사무쌍 체크 끝\n");

    printf("구련보등 체크 시작\n");
    // 구련보등 체크 (바로 리턴) - 청일색의 상위역이지만 로직 편의상 여기서 먼저 체크.
    YakuChecker::guryeon(&hwaryo_list, pae_count, last_tile, hwaryopae_type);
    if(hwaryo_list.size() > 0){gu = true;return;}
    printf("구련보등 체크 끝\n");

    // 치또이쯔 체크 
    // 량페코로 해석될 수 있는 부분은 뒤에서 체크.
    // 뒤에 있는 자패 커쯔 체크 로직 때문에 먼저 체크하고 bool chitoi = true로 변경해야함.
    YakuChecker::chitoitsu_checker(&hwaryo_list, pae_count, &chitoi);

    // 머리 위치 확인. mod3 == 2가 되는 위치에 머리가 있어야 함
    // 자패, 수패, 없음, 2개 이상
    int meori_type = get_meori_type();

    // 머리 유형에 따라 분기.
    if(meori_type == PaeType::None && !chitoi){printf("머리 없음!\n") ;return;}
    else if(meori_type == PaeType::JaPae)
    { // 자패 머리인 경우. 머리 후보가 1개만 있는 것이 보장됨
        japae_meori_update(meori_type);
        printf("자패 머리 업데이트됨.\n");
        print_blocks();

        japae_keotsu_update();
        printf("자패 커쯔 업데이트됨.\n");
        print_blocks();

        // 커쯔가 안되는 경우가 치또이쯔일 수도 있음.
        // 자패 커쯔 체크 중에 화료 불가능한 경우
        if (japa_keotsu_break){printf("(자패 커쯔 체크 도중 화료불가 확인됨.)\n");}
        else
        {
            int ja_pae_count[38];
            for(int i=0;i<38;i++){ja_pae_count[i] = pae_count[i];}
            HwaryoInfo hwaryoInfo(tsu_blocks, ja_pae_count);
            block_check(hwaryoInfo);

        }

    }
    else if(meori_type == PaeType::Mansu || 
        meori_type == PaeType::Tongsu || meori_type == PaeType::Saksu)
    {   // 수패 머리인 경우.
        printf("수패 머리\n");
        
        // 자패 머리를 'tsu_blocks'에 업데이트(나중에 머리 별로 따로 복사해줘야함.)
        japae_keotsu_update();
        printf("자패 커쯔 업데이트됨.\n");
        print_blocks();

        // // 머리후보의 숫자 후보들를 반환.
        std::vector<int> meori_hubo = get_supae_meorihubo(meori_type);
        for(int i=0;i<meori_hubo.size();i++)
        {
            
            int meori_hubo_su = meori_hubo[i];

            printf("수패 머리 ----- 후보 %d\n", meori_hubo_su);

            // tsu_block에 머리 업데이트.
            std::vector<TsuBlock> su_tsuBlocks;
            TsuBlock tsuBlock_su;
            tsuBlock_su.number = meori_hubo_su;
            tsuBlock_su.pae_type = meori_type;
            tsuBlock_su.tsu_type = TsuType::Meori;
            su_tsuBlocks.push_back(tsuBlock_su);

            // tsu_block에 자패 커쯔 업데이트 ('tsu_blocks'에 저장된 것을 복사)
            for (int i=0;i<tsu_blocks.size();i++)
            {
                su_tsuBlocks.push_back(tsu_blocks[i]);
            }
            
            printf("su_tsuBlocks------------------start\n");
            print_tsu_blocks(su_tsuBlocks);
            printf("su_tsuBlocks------------------end\n");

            // pae_count에 머리 업데이트 
            int pae_count_su[38];
            for(int i=0;i<38;i++){pae_count_su[i] = pae_count[i];}
            pae_count_su[meori_type*10 + meori_hubo_su] -= 2;
            printf("머리 후보 업데이트!! - type = %d, num = %d.", meori_type, meori_hubo_su);
            printf("Count %d", pae_count_su[meori_type*10 + meori_hubo_su]+2);
            printf("->%d\n", pae_count_su[meori_type*10 + meori_hubo_su]);

            printf("수패 머리 업데이트됨.");
            tsuBlock_su.print_contents();

            japae_keotsu_update();
            printf("자패 커쯔 업데이트됨\n");
            tsuBlock_su.print_contents();


            // 커쯔가 안되는 경우가 치또이쯔일 수도 있음.
            // 자패 커쯔 체크 중에 화료 불가능한 경우
            if (japa_keotsu_break){printf("자패 커쯔 체크 도중 화료 불가 확인되었음.\n");}
            else
            {
                HwaryoInfo hwaryoInfo(su_tsuBlocks, pae_count_su);
                block_check(hwaryoInfo);
            }
        }
        
    }

    printf("last tile ------ %d\n", last_tile);
    // // 쯔모패, 대기 정보 업데이트
    YakuChecker::info_update(hwaryo_list, last_tile, hwaryopae_type);

}

HwaryoChecker::~HwaryoChecker()
{

}



