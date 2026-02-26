#include "HwaryoChecker.h"
#include "Jaksadata.h"
#include <iostream>
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"
#include "hwaryo_config.h"

#ifdef HWARYO_CHECK_SONPAE_DEBUG
    #define DEBUG_LOG(fmt, ...)
    #define DEBUG_BLOCKS()
    #define DEBUG_TSU_BLOCKS(X)
    // #define DEBUG_CONTENTS()
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)   
    #define DEBUG_BLOCKS() print_blocks()
    #define DEBUG_TSU_BLOCKS(X) print_tsu_blocks(X)
    // #define DEBUG_CONTENTS() print_contents()
#endif

// 순수 손패만으로 화료 형태를 체크하기 위한 함수.
// 남은 머리하나와 몸통으로 구성되었는지(3 3 3 3 2형태)
// 후로를 뺀 손패 형태가 (2)/(3 2)/(3 3 2)/(3 3 3 2)인 경우에도 손패만으로 체크 가능.
// 화료 형태가 갖춰진 목록을 hwaryo_list 변수에 저장함. (여러 가지로 해석될수 있는 경우 전부 다)
// 멘젠으로만 가능한 국사무쌍, 구련보등, 치또이쯔도 여기서 미리 체크 (핑후는 풍패 정보때문에 따로 체크)
void HwaryoChecker::Hwaryo_check_sonpae(Jaksadata * jaksa, int hwaryopae_type, int last_tile){
    
    sonTil = &jaksa->sonTils[0];

    // int last_tile = jaksa->lastTile;

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

    DEBUG_LOG("국사무쌍 체크 시작\n");
    // 국사무쌍 체크 (바로 리턴)
    YakuChecker::guksa(&hwaryo_list, pae_count, last_tile, hwaryopae_type);
    if(hwaryo_list.size() > 0){gu = true;return;}
    DEBUG_LOG("국사무쌍 체크 끝\n");

    DEBUG_LOG("구련보등 체크 시작\n");
    // 구련보등 체크 (바로 리턴) - 청일색의 상위역이지만 로직 편의상 여기서 먼저 체크.
    YakuChecker::guryeon(&hwaryo_list, pae_count, last_tile, hwaryopae_type);
    if(hwaryo_list.size() > 0){gu = true;return;}
    DEBUG_LOG("구련보등 체크 끝\n");

    // 치또이쯔 체크 
    // 량페코로 해석될 수 있는 부분은 뒤에서 체크.
    // 뒤에 있는 자패 커쯔 체크 로직 때문에 먼저 체크하고 bool chitoi = true로 변경해야함.
    YakuChecker::chitoitsu_checker(&hwaryo_list, pae_count, &chitoi);

    // 머리 위치 확인. mod3 == 2가 되는 위치에 머리가 있어야 함
    // 자패, 수패, 없음, 2개 이상
    int meori_type = get_meori_type();

    // 머리 유형에 따라 분기.
    if(meori_type == PaeType::None && !chitoi){DEBUG_LOG("머리 없음!\n") ;return;}
    else if(meori_type == PaeType::JaPae)
    { // 자패 머리인 경우. 머리 후보가 1개만 있는 것이 보장됨
        japae_meori_update(meori_type);
        DEBUG_LOG("자패 머리 업데이트됨.\n");
        DEBUG_BLOCKS();

        japae_keotsu_update();
        DEBUG_LOG("자패 커쯔 업데이트됨.\n");
        DEBUG_BLOCKS();


        // 커쯔가 안되는 경우가 치또이쯔일 수도 있음.
        // 자패 커쯔 체크 중에 화료 불가능한 경우
        if (japa_keotsu_break){DEBUG_LOG("(자패 커쯔 체크 도중 화료불가 확인됨.)\n");}
        else
        {
            int ja_pae_count[38];
            for(int i=0;i<38;i++){ja_pae_count[i] = pae_count[i];}
            HwaryoInfo hwaryoInfo(tsu_blocks, ja_pae_count);
            block_check(hwaryoInfo);

        }
        DEBUG_LOG("손패 블록 체크 완료.\n");

    }
    else if(meori_type == PaeType::Mansu || 
        meori_type == PaeType::Tongsu || meori_type == PaeType::Saksu)
    {   // 수패 머리인 경우.
        DEBUG_LOG("수패 머리\n");
        
        // 자패 머리를 'tsu_blocks'에 업데이트(나중에 머리 별로 따로 복사해줘야함.)
        japae_keotsu_update();
        DEBUG_LOG("자패 커쯔 업데이트됨.\n");
        DEBUG_BLOCKS();

        // // 머리후보의 숫자 후보들를 반환.
        std::vector<int> meori_hubo = get_supae_meorihubo(meori_type);
        for(int i=0;i<meori_hubo.size();i++)
        {
            
            int meori_hubo_su = meori_hubo[i];

            DEBUG_LOG("수패 머리 ----- 후보 %d\n", meori_hubo_su);

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
            
            DEBUG_LOG("su_tsuBlocks------------------start\n");
            DEBUG_TSU_BLOCKS(su_tsuBlocks);
            DEBUG_LOG("su_tsuBlocks------------------end\n");

            // pae_count에 머리 업데이트 
            int pae_count_su[38];
            for(int i=0;i<38;i++){pae_count_su[i] = pae_count[i];}
            pae_count_su[meori_type*10 + meori_hubo_su] -= 2;
            DEBUG_LOG("머리 후보 업데이트!! - type = %d, num = %d.", meori_type, meori_hubo_su);
            DEBUG_LOG("Count %d", pae_count_su[meori_type*10 + meori_hubo_su]+2);
            DEBUG_LOG("->%d\n", pae_count_su[meori_type*10 + meori_hubo_su]);

            DEBUG_LOG("수패 머리 업데이트됨.");
#ifdef HWARYO_CHECK_SONPAE_DEBUG
#else
            tsuBlock_su.print_contents();
#endif

            japae_keotsu_update();
            DEBUG_LOG("자패 커쯔 업데이트됨\n");
#ifdef HWARYO_CHECK_SONPAE_DEBUG
#else
            tsuBlock_su.print_contents();
#endif

            // 커쯔가 안되는 경우가 치또이쯔일 수도 있음.
            // 자패 커쯔 체크 중에 화료 불가능한 경우
            if (japa_keotsu_break){DEBUG_LOG("자패 커쯔 체크 도중 화료 불가 확인되었음.\n");}
            else
            {
                HwaryoInfo hwaryoInfo(su_tsuBlocks, pae_count_su);
                block_check(hwaryoInfo);
            }
            DEBUG_LOG("손패 블록 체크 완료.\n");
        }
        
    }

    // DEBUG_LOG("last tile ------ %d\n", last_tile);

}