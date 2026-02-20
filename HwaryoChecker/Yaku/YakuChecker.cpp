#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include <iostream>

void YakuChecker::yaku_update(std::vector<HwaryoInfo> * hwaryo_list, int seat_wind, int table_wind, int richi_ilbal_type)
{
    printf("Yaku update\n");
    // 삼원패 소삼원 대삼원
    dragon_info_update(hwaryo_list);
    
    // 자풍 장풍
    wind_info_update(hwaryo_list, seat_wind, table_wind);
    
    // 후로 블록수 업데이트. 슌쯔 커쯔 깡쯔를 후로 여부 구분해서 카운트 업데이트
    bcounts_update(hwaryo_list);

    // 핑후
    pinghu_info_update(hwaryo_list, seat_wind, table_wind);

    // 탕야오
    tangyao_info_update(hwaryo_list);

    // 이페코, 량페코.
    peko_info_update(hwaryo_list);

    // 일기통관
    ilgitonggwan_info_update(hwaryo_list);

    // 삼색 동순
    samdongsun_info_update(hwaryo_list);

    // 삼색 동각
    samdonggak_info_update(hwaryo_list);

    // 찬타, 준찬타, 혼노두, 청노두
    chantanodu_info_update(hwaryo_list);

    // 영상 창깡 해저 하저 천화 지화.
    tsumo_ron_type_depended_info_update(hwaryo_list);
    
    // 또이또이 산안커 스안커 스안커단기 산깡즈 스깡즈
    toi_info_update(hwaryo_list);

    // 혼일색 청일색 자일색.
    color_info_update(hwaryo_list);

    // 녹일색
    nok_info_update(hwaryo_list);

    // 소사희 대사희
    sushi_info_update(hwaryo_list);

    // 멘젠 쯔모
    menzen_tsumo_info_update(hwaryo_list);

    // 리치, 더블리치, 일발
    rich_ilbal_info_update(hwaryo_list, richi_ilbal_type);

}

 void YakuChecker::Print_yaku(HwaryoInfo * h)
    {

        // if(h->scoreComponent.yakuman_su > 0)
        {
            int i = 0;
            printf("- 역만 리스트\n");
            if(h->yakumansate.daesamwon){i++;printf("%d. 대삼원\n", i);}
            if(h->yakumansate.cheongnodu){i++;printf("%d. 청노두\n", i);}
            if(h->yakumansate.su_ankeo){i++;printf("%d. 스안커\n", i);}
            if(h->yakumansate.su_ankeo_dangi){i++;printf("%d. 스안커단기\n", i);}

            if(h->yakumansate.su_kangz){i++;printf("%d. 스깡쯔\n", i);}
            if(h->yakumansate.ja_il){i++;printf("%d. 자일색\n", i);}

            if(h->yakumansate.guksa){i++;printf("%d. 국사무쌍\n", i);}
            if(h->yakumansate.guksa_13){i++;printf("%d. 국사무쌍13면대기\n", i);}

            if(h->yakumansate.cheonhwa){i++;printf("%d. 천화\n", i);}
            if(h->yakumansate.jihwa){i++;printf("%d. 지화\n", i);}

            if(h->yakumansate.guryeon){i++;printf("%d. 구련보등\n", i);}
            if(h->yakumansate.sun_guryeon){i++;printf("%d. 순정구련보등\n", i);}

            if(h->yakumansate.nok_il){i++;printf("%d. 녹일색\n", i);}

            if(h->yakumansate.so_sushi){i++;printf("%d. 소사희\n", i);}
            if(h->yakumansate.dae_sushi){i++;printf("%d. 대사희\n", i);}
            
            // int yakuman_su = h->scoreComponent.yakuman_su;
            // if(yakuman_su == 1){printf("역만\n");}
            // else if(yakuman_su == 2){printf("더블(2배) 역만\n");}
            // else if(yakuman_su == 3){printf("트리플(3배) 역만\n");}
            // else if(yakuman_su == 4){printf("4배 역만\n");}
            // else if(yakuman_su == 5){printf("5배 역만\n");}
            // else if(yakuman_su == 6){printf("6배 역만\n");}
            // else if{printf("역만 오류, (yakuman_su = %d)\n", yakuman_su);}
        }
        // else
        {
  
            // // if(h->scoreComponent.pansu == 0)
            // {
            //     printf("역없음!\n");
            // }
            // else
            {
                int i = 0;
                printf("- 역 목록\n");
                int p = 0;// 판내림 
                if(h->bCounts.huro > 0){p = 1;}//후로시 판내림 처리

                // 1판역
                if(h->yakustate.richi){i++;         printf("%d. 리치     1 판\n",i);}
                if(h->yakustate.ilbal){i++;         printf("%d. 일발     1 판\n",i);}
                // if(h->doraCount.dora > 0){i++;      printf("{i}. 도라          {mentsuInfo.doraCount.dora} pan\n");}
                // if(h->doraCount.ura_dora > 0){i++;  printf("{i}. 뒷도라        {mentsuInfo.doraCount.ura_dora} pan\n");}
                // if(h->doraCount.aka_dora > 0){i++;  printf("{i}. 적도라        {mentsuInfo.doraCount.aka_dora} pan\n");}
                if(h->yakustate.pinghu){i++;        printf("%d. 핑후      1 판\n",i);}
                if(h->yakustate.tangyao){i++;       printf("%d. 탕야오    1 판\n",i);}
                if(h->yakustate.White){i++;         printf("%d. 백        1 판\n",i);}
                if(h->yakustate.Green){i++;         printf("%d. 발        1 판\n",i);}
                if(h->yakustate.Red){i++;           printf("%d. 중        1 판\n",i);}
                if(h->yakustate.seat){i++;          printf("%d. 자풍      1 판\n",i);}
                if(h->yakustate.table){i++;         printf("%d. 장풍      1 판\n",i);}
                if(h->yakustate.ipeko){i++;         printf("%d. 이페코    1 판\n",i);}
                if(h->yakustate.menzen_tsumo){i++;  printf("%d. 멘젠쯔모  1 판\n",i);}
                if(h->yakustate.yeongsang){i++;     printf("%d. 영상개화  1 판\n",i);}
                if(h->yakustate.haejeo){i++;        printf("%d. 해저로월  1 판\n",i);}
                if(h->yakustate.hajeo){i++;         printf("%d. 하저로어  1 판\n",i);}
                if(h->yakustate.changkang){i++;     printf("%d. 창깡      1 판\n",i);}
                
                // 2판역
                if(h->yakustate.chitoitsu){i++;     printf("%d. 치또이쯔  2 판\n",i);}
                if(h->yakustate.double_richi){i++;  printf("%d. 더블리치  2 판\n",i);}
                if(h->yakustate.ilgitonggwan){i++;  printf("%d. 일기통관  %d 판\n",i, 2-p);}
                if(h->yakustate.samdongsun){i++;    printf("%d. 삼색동순  %d 판\n",i, 2-p);}
                if(h->yakustate.samdonggak){i++;    printf("%d. 삼색동각  2 판\n",i);}
                if(h->yakustate.chanta){i++;        printf("%d. 찬타      %d 판\n",i, 2-p);}
                if(h->yakustate.honnodu){i++;       printf("%d. 혼노두    2 판\n",i);}
                if(h->yakustate.sosamwon){i++;      printf("%d. 소삼원    2 판\n",i);}
                if(h->yakustate.toitoi){i++;        printf("%d. 또이또이  2 판\n",i);}
                if(h->yakustate.san_ankeo){i++;     printf("%d. 산안커    2 판\n",i);}
                if(h->yakustate.san_kangz){i++;     printf("%d. 산깡쯔    2 판\n",i);}

                // 3판역
                if(h->yakustate.hon_il){i++;        printf("%d. 혼일색    %d 판\n",i, 3-p);}
                if(h->yakustate.junchanta){i++;     printf("%d. 준찬타    %d 판\n",i, 3-p);}
                if(h->yakustate.ryangpeko){i++;     printf("%d. 량페코    3 판\n",i);}

                // 6판역
                if(h->yakustate.cheong_il){i++;     printf("%d. 청일색    %d 판\n",i, 6-p);}
                // int total_pansu = mentsuInfo.scoreComponent.pansu + mentsuInfo.scoreComponent.dora_pansu;
                // printf("총 %d 판\n", total_pansu);
            }
        }
    }//end of function