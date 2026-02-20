#include "YakuChecker.h"
#include "../HwaryoInfo.h"

// 일기통관
void YakuChecker::ilgitonggwan_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i];

        // 슌쯔 블록 갯수가 3개 미만인 경우 일기통관 불가
        if(h->bCounts.syun < 3)
        {
            h->yakustate.ilgitonggwan = false;
            continue;
        }
        
        // 슌쯔 123/456/789 세 가지 덩어리 체크용.
        bool man[3] = {false, false, false};
        bool tong[3] = {false, false, false};
        bool sak[3] = {false, false, false};
        for(int j=0;j<h->tsu_blocks.size();j++)
        {   
            TsuBlock b = h->tsu_blocks[j];
            // 슌쯔 블록만 체크.
            if(b.tsu_type == TsuType::Syuntsu)
            {
                // 123/456/789 인 경우만 처리.
                if(b.pae_type == PaeType::Mansu)
                {
                    if(b.number == 1)man[0] = true;
                    else if(b.number == 4)man[1] = true;
                    else if(b.number == 7)man[2] = true;
                }
                else if(b.pae_type == PaeType::Tongsu)
                {
                    if(b.number == 1)tong[0] = true;
                    else if(b.number == 4)tong[1] = true;
                    else if(b.number == 7)tong[2] = true;
                }
                else if(b.pae_type == PaeType::Saksu)
                {
                    if(b.number == 1)sak[0] = true;
                    else if(b.number == 4)sak[1] = true;
                    else if(b.number == 7)sak[2] = true;    
                }
            }
        }//end of loop
        if(man[0] && man[1] && man[2]){h->yakustate.ilgitonggwan = true;}
        else if(tong[0] && tong[1] && tong[2]){h->yakustate.ilgitonggwan = true;}
        else if(sak[0] && sak[1] && sak[2]){h->yakustate.ilgitonggwan = true;}
        else {h->yakustate.ilgitonggwan = false;}

    }//end of loop
}