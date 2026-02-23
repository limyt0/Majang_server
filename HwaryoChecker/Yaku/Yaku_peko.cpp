#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_PEKO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

// 이페코 량페코
void YakuChecker::peko_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i];
        int menzen_syn_count = h->bCounts.syun - h->bCounts.huro_syun;

        // 슌쯔 블록 갯수가 2개 미만인 경우 이페코/량페코 불가
        if(menzen_syn_count < 2){
            h->yakustate.ipeko = false;
            continue;
        }

        // 슌쯔 3장에서 가장 앞번호의 패id/10 (예 : 만수 345 -> 3, 통수 567 -> 15)
        int syuns[4]; // 4개 블록 중 menzen_syn_count 갯수만큼만 사용.

        int pekko_count = 0;
        int index = 0;
        for(int j=0;j<h->tsu_blocks.size();j++)
        {   
            TsuBlock b = h->tsu_blocks[j];
            // 후로된 블록은 체크안함.
            if(b.huro){continue;}
            
            // 슌쯔 블록만 체크.
            if(b.tsu_type == TsuType::Syuntsu){

                // 수패 id 리스트를 업데이트.
                syuns[index] = b.pae_type*10 + b.number;
                DEBUG_LOG("(peko_checking)syuns[%d] = %d\n",index, syuns[index] );
                index++;
            }
            else {continue;}
        }
        
        for(int j = 0; j < index - 1; j++)
        {
            for(int k = j+1; k < index; k++)
            {
                if(syuns[j] == syuns[k])
                {
                    pekko_count++;
                    DEBUG_LOG("(%d,%d)pekko count = %d\n", j, k, pekko_count);
                }
            }
        }

        DEBUG_LOG("pekko count = %d\n", pekko_count);

        if(pekko_count == 0)
        {
            h->yakustate.ipeko = false;
            h->yakustate.ryangpeko = false;
        }
        else if(pekko_count == 1){
            h->yakustate.ipeko = true;
            h->yakustate.ryangpeko = false;
        }
        else if(pekko_count == 2){
            h->yakustate.ipeko = false;
            h->yakustate.ryangpeko = true;
        }

    }// end of loop
}