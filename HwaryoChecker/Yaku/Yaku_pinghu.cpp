#include "YakuChecker.h"
#include "../HwaryoInfo.h"

// 핑후
void YakuChecker::pinghu_info_update(std::vector<HwaryoInfo> * hwaryo_list, int seat_wind, int table_wind)
{
    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i];
        
        // 후로시 핑후 불가.
        if(h->bCounts.huro > 0){h->yakustate.pinghu = false;continue;}

        // 슌쯔 블록 갯수가 4개 미만인 경우 핑후 불가
        if(h->bCounts.syun < 4){h->yakustate.pinghu = false;continue;}

        // 양면대기가 아닌 경우 핑후 불가.
        if(!h->daegistate.Yang){h->yakustate.pinghu = false;continue;}

        for(int j=0;j<h->tsu_blocks.size();j++)
        {
            TsuBlock b = h->tsu_blocks[j];
            if(b.tsu_type == TsuType::Meori)
            {
                if(b.pae_type == PaeType::JaPae)
                {   
                    if(b.number > 4)
                    {   //삼원패 머리 핑후 불가
                        h->yakustate.pinghu = false;break;
                    }
                    else if(b.number == seat_wind || b.number == table_wind)
                    {   //자풍 장풍패 머리는 핑후 불가
                        h->yakustate.pinghu = false;break;
                    
                    }
                    else
                    {   // 나머지 머리는 핑후 가능. 슌쯔 4개 체크는 이미 함.
                            h->yakustate.pinghu = true;break;
                    }
                }
                else
                {   // 나머지 머리는 핑후 가능. 슌쯔 4개 체크는 이미 함.
                        h->yakustate.pinghu = true;break;
                }
            }
        }//end of loop
    }//end of loop
}