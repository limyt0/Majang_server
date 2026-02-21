#include "HwaryoChecker.h"
#include "Jaksadata.h"
#include <iostream>
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"
#include "GameData.h"
#include "Enums.h"

HwaryoChecker::HwaryoChecker(GameData * game_data, Jaksadata * jaksa, int hwaryopae_type){

    printf("화료체크 시작\n");

    // 손패에서 화료 형태를 체크.
    Hwaryo_check_sonpae(jaksa, hwaryopae_type);

    printf("손패 화료 형태 체크 완료\n");
 
    // 쯔모패, 대기 정보 업데이트
    YakuChecker::info_update(&hwaryo_list, jaksa->lastTile, hwaryopae_type);

    printf("쯔모패, 대기 정보 업데이트 완료\n");
    // for(int i=0;i<hwaryo_list.size();i++)
    // {
    //     hwaryo_list[i].print_info();
    // }

    if(!gu) // 국사무쌍, 구련보등이 아닌경우에만 추가적인 역체크
    {
        // 후로 안깡 정보 추가, (빼기 정보도 추가해야함)
        HuroAnkan_To_TsuBlock(jaksa);

        // 다양한 역 정보 업데이트
        YakuChecker::yaku_update(&hwaryo_list, jaksa, game_data);

        // 도라, 뒷도라, 적도라 정보를 화료 리스트에 업데이트.
        YakuChecker::dora_info_update(&hwaryo_list, jaksa, game_data);
    }

    // 역만 및 판수 업데이트 - 국사무쌍, 구련보등 포함.
    YakuChecker::yaku_su_update(&hwaryo_list);

    int count = 0;
    if (hwaryo_list.size() > 0)
    {   
        
        printf("화료성공.!!\n");
        for(int i=0;i<hwaryo_list.size();i++)
        {
            count++;
            printf("화료 %d ----------------- start\n", count);
            // printf("hwaryo pae : {HwaryoPaeType.int_to_str(hwaryoInfo.hwaryo_pae_type)}");
            hwaryo_list[i].print_info(true, true, true, true, true);
            printf("화료 %d ----------------- end\n", count);
        }

    }
    else
    {
        printf("화료 실패.\n");
    }

}

HwaryoChecker::~HwaryoChecker()
{

}



