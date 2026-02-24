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

    DEBUG_LOG("[Tenpaichecker] 손패만으로 텐파이 여부를 체크하고 대기패 후보를 저장.\n");
    // 손패만으로 텐파이 여부를 체크하고 대기패 후보를 저장.
    Tenpai_sonpae_daegihubo_check(jaksa);
    print_huriten_array();///TODO


    DEBUG_LOG("[Tenpaichecker] 패 종류별 후리텐 여부 false로 초기화.\n");
    // 패 종류별 후리텐 여부 false로 초기화
    huriten_init();
    print_huriten_array();///TODO

    DEBUG_LOG("[Tenpaichecker] 버림패 기반으로 패종류별 후리텐 정보 업데이트.\n");
    // 버림패 기반으로 패종류별 후리텐 정보 업데이트
    berim_huriten_update(jaksa);
    print_huriten_array();
    // int hwaryopae_type = 2;// 1론 2쯔모

    DEBUG_LOG("--------텐파이 체크!!-----------\n");
    DEBUG_LOG("대기패 후보 :");
    for(int i=0;i<daegi_hubo.size();i++)
    {
        DEBUG_LOG(" %d",daegi_hubo[i]);
        jaksa->lastTile = daegi_hubo[i];
    }
    DEBUG_LOG("\n");
    print_huriten_array();

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
            tenpai = true;
            TenpaiInfo tenpai_info(&hwaryoChecker, dagipae);
            TenpaiList.push_back(tenpai_info);
            DEBUG_LOG("텐파이 업데이트\n");
            
        }
        DEBUG_LOG("텐파이체크(%d) 끝-------------(대기 후보 :%d)\n", i, daegi_hubo[i]);
    }

    print_huriten_array();
    jaksa->lastTile = last_tile_saved;

    DEBUG_LOG("[텐파이체커] 대기패 후리텐 업데이트\n");
    daegi_huriten_update();

    DEBUG_LOG("[텐파이체커] 대기패 리스트\n");
    print_daegi_list();

}//end of Constructor

TenpaiChecker::~TenpaiChecker(){}