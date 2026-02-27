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
        DEBUG_LOG("치또이쯔 25부\n");
        return;
    }

    //
    if(HwaryoPaeType::is_ron(hwaryo_pae_type))
    {// 론인 경우

    }
    else// 쯔모인 경우
    {
        if(yakustate.pinghu)
        {   // 핑후 쯔모인 경우 20부 고정.
            DEBUG_LOG("핑후 - 기본 20부\n");
            scoreComponent.busu = 20;
            return;
        }
        DEBUG_LOG("쯔모 +2부\n");
    }




    scoreComponent.busu = 20;
    DEBUG_LOG("기본 20부\n");

    // 대기에 따른 부수.
    if(daegistate.Yang){DEBUG_LOG("양면대기 +0부\n");}
    // if(daegistate.Dangi || ){}


    // 블록별 부수
    for(std::size_t i=0;i<tsu_blocks.size();i++)
    {
        if(tsu_blocks[i].tsu_type == TsuType::Meori)
        {   // 머리(또이츠)
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
        // else if()
        // {

        // }
        // else if(){

        // }
    }

    //
    if(HwaryoPaeType::is_ron(hwaryo_pae_type))
    {// 론인 경우
    }
    else// 쯔모인 경우
    {
        if(yakustate.pinghu)
        {   // 핑후인 경우 20부 고정.
            DEBUG_LOG("핑후 - 기본 20부\n");
            scoreComponent.busu = 20;
            return;
        }
        DEBUG_LOG("쯔모 +2부\n");
    }

}
