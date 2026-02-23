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
        HwaryoChecker hwaryoChecekr(gameData, jaksa, hwaryopae_type);

        int max_pansu = 0;
        int max_yakuman_su = 0;
        int y_j = 0;
        int ym_j = 0;
        
        for(int j=0;j<hwaryoChecekr.hwaryo_list.size();j++)
        {
            int yakuman_su = hwaryoChecekr.hwaryo_list[j].scoreComponent.yakuman_su;
            int pansu = hwaryoChecekr.hwaryo_list[j].scoreComponent.pansu;
            if(yakuman_su > max_yakuman_su)
            {
                max_yakuman_su = yakuman_su;
                ym_j = j;
            }
            else if(pansu > max_pansu)
            {
                max_pansu = pansu;
                y_j = j;
            }
        }

        if(hwaryoChecekr.hwaryo_list.size()  == 0)
        {
            DEBUG_LOG("(텐파이 아님.)\n");
            // 텐파이 아님.
        }
        else if(max_yakuman_su > 0)
        {
            //역만
            DEBUG_LOG("역만 텐파이 수[%d] = %d\n", ym_j, max_yakuman_su);
            TenpaiInfo tenpai_info(&hwaryoChecekr.hwaryo_list[ym_j]);
            TenpaiList.push_back(tenpai_info);
            DEBUG_LOG("역만 텐파이 업데이트\n");

        }
        else
        {
            if(max_pansu > 0){
                DEBUG_LOG("텐파이[%d]= %d판\n",y_j, max_pansu);
                TenpaiInfo tenpai_info(&hwaryoChecekr.hwaryo_list[y_j]);
                TenpaiList.push_back(tenpai_info);
                DEBUG_LOG("텐파이 업데이트\n");
            }
            else{
                //역없음
                TenpaiInfo tenpai_info;
                TenpaiList.push_back(tenpai_info);
                tenpai_info.NoYaku = true;
                tenpai_info.last_tile = daegi_hubo[i];
                DEBUG_LOG("역없음 텐파이 업데이트\n");
            }
        }
        DEBUG_LOG("텐파이체크(%d) 끝-------------(대기 후보 :%d)\n", i, daegi_hubo[i]);
    }

    jaksa->lastTile = last_tile_saved;
    print_daegi_list();

}//end of Constructor

TenpaiChecker::~TenpaiChecker(){}