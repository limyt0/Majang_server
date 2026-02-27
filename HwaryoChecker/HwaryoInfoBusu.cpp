#include "HwaryoInfo.h"
#include "hwaryo_config.h"
#ifdef HWARYO_INFO_BUSU_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 부수 계산
void HwaryoInfo::Busu(int seat_wind, int table_wind){

    // 치또이쯔 25부 고정
    if(yakustate.chitoitsu)
    {   scoreComponent.busu = 25;
        DEBUG_LOG("치또이쯔 25부 고정\n");
        return;
    }

    // 론/쯔모 여부
    bool is_ron_ = HwaryoPaeType::is_ron(hwaryo_pae_type);

    // 핑후 + 쯔모 20부 고정
    if(!is_ron_ && yakustate.pinghu)
    {
        DEBUG_LOG("핑후+쯔모 - 기본 20부 고정\n");
        scoreComponent.busu = 20;
        return;
    }

    scoreComponent.busu = 20;
    DEBUG_LOG("기본 20부\n");

    // 대기에 따른 부수.
    if(daegistate.Yang){DEBUG_LOG("양면대기 +0부\n");}
    if(daegistate.Syabo){DEBUG_LOG("샤보대기 +0부\n");}
    if(daegistate.Gan){scoreComponent.busu += 2;DEBUG_LOG("간짱대기 +2부\n");}
    if(daegistate.Byeon){scoreComponent.busu += 2;DEBUG_LOG("변짱대기 +2부\n");}
    if(daegistate.Dangi){scoreComponent.busu += 2;DEBUG_LOG("단기대기 +2부\n");}

    // 블록별 부수
    for(std::size_t i=0;i<tsu_blocks.size();i++)
    {
#ifdef HWARYO_INFO_BUSU_DEBUG
#else        
        tsu_blocks[i].print_contents();DEBUG_LOG("- ");
#endif
        if(tsu_blocks[i].tsu_type == TsuType::Meori)
        {// 머리(또이츠)

            if(tsu_blocks[i].pae_type == PaeType::JaPae)
            {
                if(tsu_blocks[i].number == 5)
                {scoreComponent.busu += 2;DEBUG_LOG("백 머리 +2부\n");}
                else if(tsu_blocks[i].number == 6)
                {scoreComponent.busu += 2;DEBUG_LOG("발 머리 +2부\n");}
                else if(tsu_blocks[i].number == 7)
                {scoreComponent.busu += 2;DEBUG_LOG("중 머리 +2부\n");}
                else if(tsu_blocks[i].number == seat_wind)
                {
                    if(tsu_blocks[i].number == table_wind)
                    {scoreComponent.busu += 4;DEBUG_LOG("연풍 머리 +4부\n");}
                    else
                    {scoreComponent.busu += 2;DEBUG_LOG("자풍 머리 +2부\n");}
                }
                else if(tsu_blocks[i].number == table_wind)
                {scoreComponent.busu += 2;DEBUG_LOG("장풍 머리 +2부\n");}
                else
                {DEBUG_LOG("객풍 머리 +0부\n");}
            }
            else{DEBUG_LOG("수패 머리 +0부\n");}
        }
        else if(tsu_blocks[i].tsu_type == TsuType::Syuntsu)
        {//슌쯔
            DEBUG_LOG("슌쯔 +0부\n");
        }
        else if(tsu_blocks[i].tsu_type == TsuType::Keotsu)
        {// 커쯔
            // 후로된 커쯔 or 론으로 먹은 마지막패로 만든 커쯔는 밍커
            bool ming = false;
            if(tsu_blocks[i].huro){ming = true;}
            else if(is_ron_ && (tsu_blocks[i].number == ((last_tile/10)%10)))
            {ming = true;}

            // 자패 or 수패 1 9는 요구패
            bool yogu = false;
            if(tsu_blocks[i].pae_type == PaeType::JaPae){yogu = true;}
            else if(tsu_blocks[i].number == 1){yogu = true;}
            else if(tsu_blocks[i].number == 9){yogu = true;}
            
            if(ming)
            {// 밍커
                if(yogu)
                {// 요구패 밍커 4부
                    scoreComponent.busu += 4;
                    DEBUG_LOG("요구패 밍커 +4부\n");
                }
                else
                {// 중장패 밍커 2부
                    scoreComponent.busu += 2;
                    DEBUG_LOG("중장패 밍커 +2부\n");
                }
            }
            else
            {// 안커
                if(yogu)
                {// 요구패 안커 8부
                    scoreComponent.busu += 8;
                    DEBUG_LOG("요구패 안커 +8부\n");
                }
                else
                {// 중장패 안커 4부
                    scoreComponent.busu += 4;
                    DEBUG_LOG("중장패 안커 +4부\n");
                }
            }
        }
        else if(tsu_blocks[i].tsu_type == TsuType::Kangtsu)
        {
            // 후로된 커쯔 or 론으로 먹은 마지막패로 만든 커쯔는 밍커
            bool ming = false;
            if(tsu_blocks[i].huro){ming = true;}
            else if(is_ron_ && (tsu_blocks[i].number == ((last_tile/10)%10)))
            {ming = true;}

            // 자패 or 수패 1 9는 요구패
            bool yogu = false;
            if(tsu_blocks[i].pae_type == PaeType::JaPae){yogu = true;}
            else if(tsu_blocks[i].number == 1){yogu = true;}
            else if(tsu_blocks[i].number == 9){yogu = true;}
            
            if(ming)
            {// 밍깡
                if(yogu)
                {// 요구패 밍깡 16부
                    scoreComponent.busu += 16;
                    DEBUG_LOG("요구패 밍깡 +16부\n");
                }
                else
                {// 중장패 밍깡 8부
                    scoreComponent.busu += 8;
                    DEBUG_LOG("중장패 밍깡 +8부\n");
                }
            }
            else
            {// 안깡
                if(yogu)
                {// 요구패 안깡 32부
                    scoreComponent.busu += 32;
                    DEBUG_LOG("요구패 밍깡 +32부\n");
                }               
                else
                {// 중장패 밍깡 16부
                    scoreComponent.busu += 16;
                    DEBUG_LOG("중장패 밍깡 +16부\n");
                }
            }
        }// end of condition
    }// end of loop

    // 멘젠/비멘젠 론/쯔모에 따른 부수
    if(is_ron_)
    {// 론인 경우
        if(bCounts.huro > 0)
        {// 비멘젠론.
            DEBUG_LOG("비멘젠론 +0부\n");
            if(scoreComponent.busu < 30)
            {
                scoreComponent.busu = 30;
                DEBUG_LOG("비멘젠론 최소 30부 보장 적용.\n");
            }
        }
        else
        {// 멘젠 론
            scoreComponent.busu += 10;
            DEBUG_LOG("멘젠론 +10부\n");
        }
    }
    else// 쯔모인 경우
    {
        scoreComponent.busu += 2;   
        DEBUG_LOG("쯔모 +2부\n");
    }

    DEBUG_LOG("올림 적용 전 %d부\n", scoreComponent.busu);
    if(scoreComponent.busu%10 != 0)
    {
        int chunk = 10 + (10 - scoreComponent.busu)%10;
        DEBUG_LOG("chunk = %d\n", chunk);
        scoreComponent.busu += chunk;
    }
    DEBUG_LOG("올림 적용 후 %d부\n", scoreComponent.busu);
}
