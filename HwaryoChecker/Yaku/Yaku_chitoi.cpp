#include "YakuChecker.h"
#include "../Consts_hwaryo.h"
#include "../Tsublock.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_CHITOI_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
//치또이쯔

void YakuChecker::chitoitsu_checker(std::vector<HwaryoInfo> * hwaryo_list, int * pae_count, bool * chitoi)
{
    std::vector<TsuBlock> tsu_blocks;
    int meori_count = 0;
    for(int i = 1; i < 38; i++)
    {
        if(pae_count[i] == 0)
        {
            continue;
        }
        else if(pae_count[i] == 2)
        {
            TsuBlock tsuBlock;
            tsuBlock.number = i % 10;
            tsuBlock.pae_type = i/10;
            tsuBlock.tsu_type = TsuType::Meori;
            tsu_blocks.push_back(tsuBlock);

            meori_count++;
            if(meori_count == 7){break;}
        }
        else
        {
            break;
        }
    }
    
    if (meori_count == 7)
    {
        HwaryoInfo HwaryoInfo(tsu_blocks, pae_count);
        HwaryoInfo.yakustate.chitoitsu = true;
        hwaryo_list->push_back(HwaryoInfo);
        *chitoi = true;
        
    }
    else
    {
    }

}//end of function.