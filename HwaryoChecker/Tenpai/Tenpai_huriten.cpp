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
        huriten[i] = false;
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
        if(index < 38)
        {
            huriten[index] = true;
            DEBUG_LOG("[HURITEN] 버림패 %d\n", berims->berimBeas[i]);
        }

        // 버린패 남이 후로해간 패 후리텐.
        index = berims->behurod[i]/10;
        if(index < 38)
        {
            huriten[index] = true;
            DEBUG_LOG("[HURITEN] 버림패 후로된거 %d\n", berims->behurod[i]);
        }
    }
}

// 후리텐 정보를 텐파이 대기패 정보에 추가.
void TenpaiChecker::daegi_huriten_update()
{
    if(!tenpai){DEBUG_LOG("[HURITEN] 텐파이가 아니라서 후리텐 정보를 추가하지 않음.\n");;}

    // 국사 13면 후리텐 처리
    guksa13_daegi_huriten_update();

    //순정 구련보등 9면 대기 후리텐
    guryeon9_daegi_huriten_update();

    DEBUG_LOG("[HURITEN] 후리텐 정보를 텐파이 대기패 정보에 추가\n");
    for(int i=0;i<TenpaiList.size();i++)
    {
        if(huriten[TenpaiList[i].last_tile/10])
        {
            TenpaiList[i].huriten = true;
            DEBUG_LOG("[HURITEN] 후리텐 대기패 %d\n", TenpaiList[i].last_tile);
        }
    }

}

// 버림패 정보 기반 양면/샤보대기
void TenpaiChecker::coupled_huriten_update()
{

}

// 순정구련보등 9면 대기
void TenpaiChecker::guryeon9_daegi_huriten_update()
{

    DEBUG_LOG("[HURITEN] 순정구련보등 9면대기 후리텐 체크\n");
    if(TenpaiList[0].yakumansate.sun_guryeon){
        int type = (TenpaiList[0].last_tile/100)*10;//만통삭 0 10 20
        if(huriten[type+1] || huriten[type+2] || huriten[type+3] ||
           huriten[type+4] || huriten[type+5] || huriten[type+6] ||
           huriten[type+7] || huriten[type+8] || huriten[type+9])
        {
            print_huriten_array();
            DEBUG_LOG("[HURITEN] 순정구련보등 9면대기 후리텐\n");
            huriten[type+1] =true;huriten[type+2]=true;huriten[type+3]=true;
            huriten[type+4] =true;huriten[type+5]=true;huriten[type+6]=true;
            huriten[type+7] =true;huriten[type+8]=true;huriten[type+9]=true;
            print_huriten_array();
        }
    }
}


// 국사 13면 대기 후리텐
void TenpaiChecker::guksa13_daegi_huriten_update()
{
    DEBUG_LOG("[HURITEN] 국사무쌍 13면대기 후리텐 체크\n");
    // if(!guksa)
    // {
    //     DEBUG_LOG("[HURITEN] 국사무쌍 아님\n");
    //     return;
    // }
    // DEBUG_LOG("[HURITEN] 국사무쌍 후리텐\n");

    // 13면 대기인 경우만 하나라도 후리텐이면 나머지도 후리텐.
    if(TenpaiList[0].yakumansate.guksa_13)
    {
        DEBUG_LOG("[HURITEN] 국사무쌍 13면 후리텐\n");
        print_huriten_array();
        if(huriten[1] || huriten[9] ||
            huriten[11] || huriten[19] ||
            huriten[21] || huriten[29] ||
            huriten[31] || huriten[32] ||
            huriten[33] || huriten[34] ||
            huriten[35] || huriten[36] ||
            huriten[37] )
        {
            // 13면 대기인 경우만 -> 하나라도 후리텐이면 나머지도 후리텐.
            DEBUG_LOG("[HURITEN] 13면 대기인 경우 하나라도 후리텐이면 나머지도 후리텐.\n");
            huriten[1] = true;huriten[9] = true;
            huriten[11] = true;huriten[19] = true;
            huriten[21] = true;huriten[29] = true;
            huriten[31] = true;huriten[32] = true;
            huriten[33] = true;huriten[34] = true;
            huriten[35] = true;huriten[36] = true;
            huriten[37] = true;
            print_huriten_array();
        }
    }
}


void TenpaiChecker::print_huriten_array()
{
#ifdef TENPAI_HURITEN_DEBUG
#else
    printf("[HURITEN] ");
    for(int i=1;i<=9;i++){
        if(huriten[i]){printf("1");}
        else{printf("0");}
    }
    printf(" ");
    for(int i=11;i<=19;i++){
        if(huriten[i]){printf("1");}
        else{printf("0");}
    }
    printf(" ");
    for(int i=21;i<=29;i++){
        if(huriten[i]){printf("1");}
        else{printf("0");}
    }
    printf(" ");
    for(int i=31;i<=37;i++){
        if(huriten[i]){printf("1");}
        else{printf("0");}
    }
    printf("\n");

#endif

}