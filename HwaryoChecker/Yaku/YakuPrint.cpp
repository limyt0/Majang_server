#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include <iostream>
// #include "Jaksadata.h"
// #include "GameData.h"
#include "../hwaryo_config.h"
#ifdef YAKU_PRINT_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

void YakuChecker::Print_yaku(HwaryoInfo * h)
{
#ifdef YAKU_PRINT_DEBUG
#else
            
    if(h->scoreComponent.yakuman_su > 0)
    {
        int i = 0;
        DEBUG_LOG("- 역만 리스트\n");
        if(h->yakumansate.daesamwon){i++;DEBUG_LOG("%d. 대삼원\n", i);}
        if(h->yakumansate.cheongnodu){i++;DEBUG_LOG("%d. 청노두\n", i);}
        if(h->yakumansate.su_ankeo){i++;DEBUG_LOG("%d. 스안커\n", i);}
        if(h->yakumansate.su_ankeo_dangi){i++;DEBUG_LOG("%d. 스안커단기\n", i);}

        if(h->yakumansate.su_kangz){i++;DEBUG_LOG("%d. 스깡쯔\n", i);}
        if(h->yakumansate.ja_il){i++;DEBUG_LOG("%d. 자일색\n", i);}

        if(h->yakumansate.guksa){i++;DEBUG_LOG("%d. 국사무쌍\n", i);}
        if(h->yakumansate.guksa_13){i++;DEBUG_LOG("%d. 국사무쌍13면대기\n", i);}

        if(h->yakumansate.cheonhwa){i++;DEBUG_LOG("%d. 천화\n", i);}
        if(h->yakumansate.jihwa){i++;DEBUG_LOG("%d. 지화\n", i);}

        if(h->yakumansate.guryeon){i++;DEBUG_LOG("%d. 구련보등\n", i);}
        if(h->yakumansate.sun_guryeon){i++;DEBUG_LOG("%d. 순정구련보등\n", i);}

        if(h->yakumansate.nok_il){i++;DEBUG_LOG("%d. 녹일색\n", i);}

        if(h->yakumansate.so_sushi){i++;DEBUG_LOG("%d. 소사희\n", i);}
        if(h->yakumansate.dae_sushi){i++;DEBUG_LOG("%d. 대사희\n", i);}
        
        int yakuman_su = h->scoreComponent.yakuman_su;
        if(yakuman_su == 1){DEBUG_LOG("역만\n");}
        else if(yakuman_su == 2){DEBUG_LOG("더블(2배) 역만\n");}
        else if(yakuman_su == 3){DEBUG_LOG("트리플(3배) 역만\n");}
        else if(yakuman_su == 4){DEBUG_LOG("4배 역만\n");}
        else if(yakuman_su == 5){DEBUG_LOG("5배 역만\n");}
        else if(yakuman_su == 6){DEBUG_LOG("6배 역만\n");}
        else {DEBUG_LOG("역만 오류, (yakuman_su = %d)\n", yakuman_su);}
    }
    else
    {

        if(h->scoreComponent.pansu == 0)
        {
            DEBUG_LOG("역없음!\n");
        }
        else
        {
            int i = 0;
            DEBUG_LOG("- 역 목록\n");
            int p = 0;// 판내림 
            if(h->bCounts.huro > 0){p = 1;}//후로시 판내림 처리
            
            // 1판역
            if(h->yakustate.richi){i++;         DEBUG_LOG("%d. 리치      1 판\n",i);}
            if(h->yakustate.ilbal){i++;         DEBUG_LOG("%d. 일발      1 판\n",i);}
            if(h->doraCount.omote_dora > 0){i++;DEBUG_LOG("%d. 도라      %d 판\n",i,h->doraCount.omote_dora);}
            if(h->doraCount.ura_dora > 0){i++;  DEBUG_LOG("%d. 뒷도라    %d 판\n",i,h->doraCount.ura_dora);}
            if(h->doraCount.aka_dora > 0){i++;  DEBUG_LOG("%d. 적도라    %d 판\n",i,h->doraCount.aka_dora);}
            if(h->scoreComponent.nuki_pansu > 0){i++;  DEBUG_LOG("%d. 빼기      %d 판\n",i,h->scoreComponent.nuki_pansu);}
            if(h->yakustate.pinghu){i++;        DEBUG_LOG("%d. 핑후      1 판\n",i);}
            if(h->yakustate.tangyao){i++;       DEBUG_LOG("%d. 탕야오    1 판\n",i);}
            if(h->yakustate.White){i++;         DEBUG_LOG("%d. 백        1 판\n",i);}
            if(h->yakustate.Green){i++;         DEBUG_LOG("%d. 발        1 판\n",i);}
            if(h->yakustate.Red){i++;           DEBUG_LOG("%d. 중        1 판\n",i);}
            if(h->yakustate.seat){i++;          DEBUG_LOG("%d. 자풍      1 판\n",i);}
            if(h->yakustate.table){i++;         DEBUG_LOG("%d. 장풍      1 판\n",i);}
            if(h->yakustate.ipeko){i++;         DEBUG_LOG("%d. 이페코    1 판\n",i);}
            if(h->yakustate.menzen_tsumo){i++;  DEBUG_LOG("%d. 멘젠쯔모  1 판\n",i);}
            if(h->yakustate.yeongsang){i++;     DEBUG_LOG("%d. 영상개화  1 판\n",i);}
            if(h->yakustate.haejeo){i++;        DEBUG_LOG("%d. 해저로월  1 판\n",i);}
            if(h->yakustate.hajeo){i++;         DEBUG_LOG("%d. 하저로어  1 판\n",i);}
            if(h->yakustate.changkang){i++;     DEBUG_LOG("%d. 창깡      1 판\n",i);}
            
            // 2판역
            if(h->yakustate.chitoitsu){i++;     DEBUG_LOG("%d. 치또이쯔  2 판\n",i);}
            if(h->yakustate.double_richi){i++;  DEBUG_LOG("%d. 더블리치  2 판\n",i);}
            if(h->yakustate.ilgitonggwan){i++;  DEBUG_LOG("%d. 일기통관  %d 판\n",i, 2-p);}
            if(h->yakustate.samdongsun){i++;    DEBUG_LOG("%d. 삼색동순  %d 판\n",i, 2-p);}
            if(h->yakustate.samdonggak){i++;    DEBUG_LOG("%d. 삼색동각  2 판\n",i);}
            if(h->yakustate.chanta){i++;        DEBUG_LOG("%d. 찬타      %d 판\n",i, 2-p);}
            if(h->yakustate.honnodu){i++;       DEBUG_LOG("%d. 혼노두    2 판\n",i);}
            if(h->yakustate.sosamwon){i++;      DEBUG_LOG("%d. 소삼원    2 판\n",i);}
            if(h->yakustate.toitoi){i++;        DEBUG_LOG("%d. 또이또이  2 판\n",i);}
            if(h->yakustate.san_ankeo){i++;     DEBUG_LOG("%d. 산안커    2 판\n",i);}
            if(h->yakustate.san_kangz){i++;     DEBUG_LOG("%d. 산깡쯔    2 판\n",i);}

            // 3판역
            if(h->yakustate.hon_il){i++;        DEBUG_LOG("%d. 혼일색    %d 판\n",i, 3-p);}
            if(h->yakustate.junchanta){i++;     DEBUG_LOG("%d. 준찬타    %d 판\n",i, 3-p);}
            if(h->yakustate.ryangpeko){i++;     DEBUG_LOG("%d. 량페코    3 판\n",i);}

            // 6판역
            if(h->yakustate.cheong_il){i++;     DEBUG_LOG("%d. 청일색    %d 판\n",i, 6-p);}
            int total_pansu = h->scoreComponent.pansu;
            total_pansu += h->scoreComponent.dora_pansu;
            total_pansu += h->scoreComponent.nuki_pansu;
            DEBUG_LOG("총 %d 판\n", total_pansu);
        }
    }
#endif
}//end of function