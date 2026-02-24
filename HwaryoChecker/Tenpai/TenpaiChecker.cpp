#include <vector>
#include "TenpaiChecker.h"
#include "GameData/Jaksadata.h"
#include "GameData/GameData.h"
#include <iostream>
#include "TenpaiInfo.h"
#include "../HwaryoChecker.h"
#include "../hwaryo_config.h"
#ifdef TENPAI_CHECKER_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

TenpaiChecker::TenpaiChecker(GameData * gameData, Jaksadata * jaksa, int hwaryopae_type)
{
    // 손패만으로 텐파이 여부를 체크하고 대기패 후보를 저장.
    Tenpai_sonpae_daegihubo_check(jaksa);

    // 패 종류별 후리텐 여부 false로 초기화
    huriten_init();

    // 버림패 기반으로 패종류별 후리텐 정보 업데이트
    berim_huriten_update(jaksa);

    // int hwaryopae_type = 2;// 1론 2쯔모

    DEBUG_LOG("--------텐파이 체크!!-----------\n");
    DEBUG_LOG("대기패 후보 :");
    for(int i=0;i<daegi_hubo.size();i++)
    {
        DEBUG_LOG(" %d",daegi_hubo[i]);
        jaksa->lastTile = daegi_hubo[i];
    }
    DEBUG_LOG("\n");
    int last_tile_saved = jaksa->lastTile;
    for(int i=0;i<daegi_hubo.size();i++)
    {
        jaksa->lastTile = daegi_hubo[i];
        DEBUG_LOG("텐파이체크(%d) 시작-----------(대기 후보 :%d)\n", i, daegi_hubo[i]);
        HwaryoChecker hwaryoChecker(gameData, jaksa, hwaryopae_type);

        if(hwaryoChecker.hwaryo_list.size()  == 0)
        {
            DEBUG_LOG("(텐파이 아님.)\n");
        }
        else
        {
            int dagipae = daegi_hubo[i];
            DEBUG_LOG("텐파이됨.\n");
            TenpaiInfo tenpai_info(&hwaryoChecker, dagipae);
            TenpaiList.push_back(tenpai_info);
            DEBUG_LOG("텐파이 업데이트\n");
            
        }
        DEBUG_LOG("텐파이체크(%d) 끝-------------(대기 후보 :%d)\n", i, daegi_hubo[i]);
    }

    jaksa->lastTile = last_tile_saved;
    print_daegi_list();

    // daegi_huriten_update();

}//end of Constructor

TenpaiChecker::~TenpaiChecker(){}