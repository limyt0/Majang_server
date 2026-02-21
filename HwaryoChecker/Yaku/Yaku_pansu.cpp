#include "YakuChecker.h"
#include "../HwaryoInfo.h"
// 판수 계산용. - 역만/2~6배 역만 계산.
// 상위역 체크 및 역만 시 일반역 계산에서 제외하기 위한 처리.


void YakuChecker::yaku_su_update(std::vector<HwaryoInfo> *hwaryo_list)
{
    // 1. n배 역만 정보 업데이트.
    //     (0 역만 아님 | 1 역만 | 2 더블역만 | 3 트리플 역만)
    // 2. 판수 업데이트
    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i];
        // h->scoreComponent.yakuman_su = 0;
        printf("(yaku_su_update) yakuman---\n");
        // 역만
        if (h->yakumansate.guksa){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.cheonhwa){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.jihwa){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.guryeon){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.nok_il){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.daesamwon){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.so_sushi){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.cheongnodu){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.ja_il){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.su_ankeo){h->scoreComponent.yakuman_su +=1;}
        if (h->yakumansate.su_kangz){h->scoreComponent.yakuman_su +=1;}
        // 더블 역만
        if (h->yakumansate.guksa_13){h->scoreComponent.yakuman_su +=2;}
        if (h->yakumansate.sun_guryeon){h->scoreComponent.yakuman_su +=2;}
        if (h->yakumansate.dae_sushi){h->scoreComponent.yakuman_su +=2;}
        if (h->yakumansate.su_ankeo_dangi){h->scoreComponent.yakuman_su +=2;}
        
        // 역만이 있는 경우 판수계산 안함.
        if(h->scoreComponent.yakuman_su > 0){continue;}

        printf("(yaku_su_update) yaku---\n");
    
        // 1판역
        if (h->yakustate.richi){h->scoreComponent.pansu +=1;}  //리치
        if (h->yakustate.ilbal){h->scoreComponent.pansu +=1;}  //일발
        if (h->yakustate.pinghu){h->scoreComponent.pansu +=1;} //핑후
        if (h->yakustate.tangyao){h->scoreComponent.pansu +=1;}//탕야오
        if (h->yakustate.White){h->scoreComponent.pansu +=1;}  //백
        if (h->yakustate.Green){h->scoreComponent.pansu +=1;}  //발
        if (h->yakustate.Red){h->scoreComponent.pansu +=1;}    //중
        if (h->yakustate.seat){h->scoreComponent.pansu +=1;}   //자풍
        if (h->yakustate.table){h->scoreComponent.pansu +=1;}  //장풍
        if (h->yakustate.ipeko){h->scoreComponent.pansu +=1;}  //이페코
        if (h->yakustate.menzen_tsumo){h->scoreComponent.pansu +=1;}//멘젠쯔모
        if (h->yakustate.yeongsang){h->scoreComponent.pansu +=1;}//영상개화
        if (h->yakustate.haejeo){h->scoreComponent.pansu +=1;}   //해저로월
        if (h->yakustate.hajeo){h->scoreComponent.pansu +=1;}    //하저로어
        if (h->yakustate.changkang){h->scoreComponent.pansu +=1;}//창깡

        int p = 0;// 판내림용 변수
        if(h->bCounts.huro > 0){p = 1;}// 후로시 판내림

        // 2판역
        if (h->yakustate.chitoitsu){h->scoreComponent.pansu +=2;}  //치또이쯔
        if (h->yakustate.double_richi){h->scoreComponent.pansu +=2;} //더블리치
        if (h->yakustate.ilgitonggwan){h->scoreComponent.pansu +=2-p;}//일기통관 - 판내림
        if (h->yakustate.samdongsun){h->scoreComponent.pansu +=2-p;} //삼색동순 - 판내림
        if (h->yakustate.samdonggak){h->scoreComponent.pansu +=2;} //삼색동각(판내림없음주의)
        if (h->yakustate.chanta){h->scoreComponent.pansu += 2-p;} //찬타 - 판내림
        if (h->yakustate.honnodu){h->scoreComponent.pansu +=2;}  //혼노두
        if (h->yakustate.sosamwon){h->scoreComponent.pansu +=2;} //소삼원
        if (h->yakustate.toitoi){h->scoreComponent.pansu +=2;}   //또이또이 
        if (h->yakustate.san_ankeo){h->scoreComponent.pansu +=2;}//산안커
        if (h->yakustate.san_kangz){h->scoreComponent.pansu +=2;}//산깡쯔

        // 3판역
        if (h->yakustate.hon_il){h->scoreComponent.pansu +=3-p;}   //혼일색 - 판내림
        if (h->yakustate.junchanta){h->scoreComponent.pansu +=3-p;}//준찬타 - 판내림
        if (h->yakustate.san_kangz){h->scoreComponent.pansu +=3;}  //량페코

        // 6판역
        if (h->yakustate.cheong_il){h->scoreComponent.pansu +=6-p;}//청일색 - 판내림

        h->scoreComponent.dora_pansu += h->doraCount.omote_dora;
        h->scoreComponent.dora_pansu += h->doraCount.ura_dora;
        h->scoreComponent.dora_pansu += h->doraCount.aka_dora;
    }//end of loop

}//end of function