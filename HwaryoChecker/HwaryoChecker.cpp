#include "HwaryoChecker.h"
#include "Jaksadata.h"
#include <iostream>
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"
#include "GameData.h"
#include "Enums.h"
#include "hwaryo_config.h"

#ifdef HWARYO_CHECKER_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif


HwaryoChecker::HwaryoChecker(GameData * game_data, Jaksadata * jaksa, int hwaryopae_type, int last_tile){

    DEBUG_LOG("화료체크 시작\n");

    // 손패에서 화료 형태를 체크.
    Hwaryo_check_sonpae(jaksa, hwaryopae_type, last_tile);

    DEBUG_LOG("손패 화료 형태 체크 완료\n");
 
    // 마지막패, 대기 정보 업데이트
    YakuChecker::info_update(&hwaryo_list, last_tile, hwaryopae_type);

    DEBUG_LOG("마지막패, 대기 정보 업데이트 완료\n");
    // for(int i=0;i<hwaryo_list.size();i++)
    // {
    //     hwaryo_list[i].print_info();
    // }

    if(!gu) // 국사무쌍, 구련보등이 아닌경우에만 추가적인 역체크
    {
        // 후로 안깡 정보 추가
        HuroAnkan_To_TsuBlock(jaksa);

        // 다양한 역 정보 업데이트
        YakuChecker::yaku_update(&hwaryo_list, jaksa, game_data);

        // 빼기 수를 세서 화료정보에 업데이트.
        YakuChecker::nuki_info_update(&hwaryo_list, jaksa);

        // 도라, 뒷도라, 적도라 정보를 화료 리스트에 업데이트.
        YakuChecker::dora_info_update(&hwaryo_list, jaksa, game_data, last_tile);
    }

    // 역만 및 판수 업데이트 - 국사무쌍, 구련보등 포함.
    YakuChecker::yaku_su_update(&hwaryo_list);

    int count = 0;
    if (hwaryo_list.size() > 0)
    {   
        
        DEBUG_LOG("화료성공.!!\n");
        for(std::size_t i=0;i<hwaryo_list.size();i++)
        {
            count++;
            DEBUG_LOG("화료 %d ----------------- start\n", count);
            // printf("hwaryo pae : {HwaryoPaeType.int_to_str(hwaryoInfo.hwaryo_pae_type)}");
            hwaryo_list[i].print_info(true, true, true, true, true);
            DEBUG_LOG("화료 %d ----------------- end\n", count);
        }

    }
    else
    {
        DEBUG_LOG("화료 실패.\n");
    }

}

HwaryoChecker::~HwaryoChecker()
{

}



