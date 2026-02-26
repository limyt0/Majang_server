#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include <iostream>
#include "../hwaryo_config.h"
#ifdef YAKU_DRAGON_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

// 백발중 관련 역.
// 삼원패 체크 - 각 1판. 소삼원 대삼원도 여기서 체크.
void YakuChecker::dragon_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    // (350 백)(360 발)(370 중)
    for(std::size_t i=0;i<hwaryo_list->size();i++)
    {
        // 삼원패 머리
        bool dragon_meori[3] = {false, false, false};

        HwaryoInfo * h = &(*hwaryo_list)[i];
        for(std::size_t j=0;j<h->tsu_blocks.size();j++)
        {   
            TsuBlock b = h->tsu_blocks[j];
            // 자패 중에서, 
            if(b.pae_type == PaeType::JaPae)
            {   
                // 커쯔나 깡쯔.
                if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                {
                    // 백발중
                    if(b.number == 5){h->yakustate.White = true;}
                    else if(b.number == 6){h->yakustate.Green = true;}
                    else if(b.number == 7){h->yakustate.Red = true;}
                }
                else if(b.tsu_type == TsuType::Meori)
                {
                    if(b.number == 5){dragon_meori[0] = true;}
                    else if(b.number == 6){dragon_meori[1] = true;}
                    else if(b.number == 7){dragon_meori[2] = true;}
                }
            }
        }//end of loop

        // 소삼원 대삼원 체크
        if(h->yakustate.White && h->yakustate.Green && h->yakustate.Red){ h->yakumansate.daesamwon = true;}
        else if(h->yakustate.White && h->yakustate.Green && dragon_meori[2]){ h->yakustate.sosamwon = true;}
        else if(h->yakustate.White && dragon_meori[1] && h->yakustate.Red ){ h->yakustate.sosamwon = true;}
        else if(dragon_meori[0] && h->yakustate.Green && h->yakustate.Red ){ h->yakustate.sosamwon = true;}


    }//end of loop
}//end of function