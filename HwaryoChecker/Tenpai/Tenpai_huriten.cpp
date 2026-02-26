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

// 만통삭1~9및자패 종류별 버린패 false로 초기화
void TenpaiChecker::huri_init()
{
    for(int i=0;i<38;i++)
    {
        huri[i] = false;
    }
}

// 버린패 정보를 huri array에 업데이트.
void TenpaiChecker::berim_huri_update(Jaksadata * jaksa)
{
    auto berims = std::move(jaksa->berims).get();
    
    for(std::size_t i=0;i < berims->berimBeas.size();i++)
    {
        // 버린 패.
        int index = berims->berimBeas[i]/10;
        if(index < 38)
        {
            huri[index] = true;
            DEBUG_LOG("[HURITEN] 버림패 %d\n", berims->berimBeas[i]);
        }

        // 버린패 남이 후로해간 패.
        index = berims->behurod[i]/10;
        if(index < 38)
        {
            huri[index] = true;
            DEBUG_LOG("[HURITEN] 버림패 후로된거 %d\n", berims->behurod[i]);
        }
    }
}

// 대기패 중에 버린패가 있는지를 확인하고 후리텐 여부 업데이트.
void TenpaiChecker::daegi_huriten_update()
{
    for(std::size_t i=0;i<TenpaiList.size();i++)
    {
        if(huri[TenpaiList[i].last_tile/10])
        {
            huriten = true;
        }
    }
}

void TenpaiChecker::print_huri_array()
{
#ifdef TENPAI_HURITEN_DEBUG
#else
    printf("[HURITEN] ");
    for(int i=1;i<=9;i++){
        if(huri[i]){printf("1");}
        else{printf("0");}
    }
    printf(" ");
    for(int i=11;i<=19;i++){
        if(huri[i]){printf("1");}
        else{printf("0");}
    }
    printf(" ");
    for(int i=21;i<=29;i++){
        if(huri[i]){printf("1");}
        else{printf("0");}
    }
    printf(" ");
    for(int i=31;i<=37;i++){
        if(huri[i]){printf("1");}
        else{printf("0");}
    }
    printf("\n");

#endif

}