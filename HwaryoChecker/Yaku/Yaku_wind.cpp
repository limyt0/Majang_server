#include "YakuChecker.h"
#include "../HwaryoInfo.h"
// #include <iostream>
#include "../hwaryo_config.h"
#ifdef YAKU_WIND_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif


// 자풍 장풍 체크 // 동 남 서 북 1 2 3 4로 가정.
void YakuChecker::wind_info_update(std::vector<HwaryoInfo> * hwaryo_list, int seat_wind, int table_wind)
{
    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i];
        for(int j=0;j<h->tsu_blocks.size();j++)
        {   
            TsuBlock b = h->tsu_blocks[j];
            // 자패 중에서
            if(b.pae_type == PaeType::JaPae)
            {   
                // 커쯔나 깡쯔.
                if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                {
                    if(b.number == seat_wind){h->yakustate.seat = true;}
                    if(b.number == table_wind){h->yakustate.table = true;}
                    
                }
            }
        }//end of loop
    }//end of loop
}//end of function