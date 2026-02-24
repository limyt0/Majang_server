#include "TenpaiChecker.h"
#include "TenpaiInfo.h"
#include "GameData/Jaksadata.h"
#include "GameData/PeaAndBlock/Berims.h"
#include "../HwaryoChecker.h"
#include <iostream>
#include "../hwaryo_config.h"
#ifdef TENPAI_HURITEN_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

// 패 종류별 후리텐 여부 false로 초기화
void TenpaiChecker::huriten_init()
{
    for(int i=0;i<38;i++)
    {
        huriten[38] = false;
    }
}

// 버림패 기반으로 패종류별 후리텐 정보 업데이트
void TenpaiChecker::berim_huriten_update(Jaksadata * jaksa)
{
    auto berims = std::move(jaksa->berims).get();
    
    for(int i=0;i < berims->berimBeas.size();i++)
    {
        // 버린 패 후리텐.
        int index = berims->berimBeas[i]/10;
        if(index < 38){huriten[index] = true;}

        // 버린패 남이 후로해간 패 후리텐.
        index = berims->behurod[i]/10;
        if(index < 38){huriten[index] = true;}
    }
}

// 후리텐 정보를 텐파이 대기패 정보에 추가.
void TenpaiChecker::daegi_huriten_update()
{
    for(int i=0;i<TenpaiList.size();i++)
    {
        if(huriten[TenpaiList[i].last_tile/10])
        {
            TenpaiList[i].huriten = true;
            DEBUG_LOG("[HURITEN] 후리텐 대기패 %d\n", TenpaiList[i].last_tile);
        }
    }

}


// 버림패 정보 기반 양면/샤보대기 국사13면, 순정 구련보등 9면 대기 후리텐
void TenpaiChecker::coupled_huriten_update()
{

}

