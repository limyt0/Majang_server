#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_CHANTANODU_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf("[DEBUG] %s", fmt , ##__VA_ARGS__)    
#endif

// 찬타 준찬타 혼노두 청노두
void YakuChecker::chantanodu_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(std::size_t i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];

        int japae_b_count = 0; // 자패 블록 카운트
        int su_chan_b_count = 0; // 123 789 999 111 99 11
        int su_nodu_b_count = 0; // 999 111 99 11
        bool chanta_fail = false; // 나머지 경우.
        
        for(std::size_t j_=0;j_<h->tsu_blocks.size();j_++)
        {   
            TsuBlock b = h->tsu_blocks[j_];
            
            if(b.pae_type == PaeType::JaPae)
            {// 자패인 경우
                japae_b_count++;
            }
            else
            {// 수패인 경우.
                if(b.tsu_type == TsuType::Meori || b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                {   

                    // 수패인 경우, 머리/커쯔/깡쯔는 1이나 9로 이루어져야함.
                    if(b.number == 1 || b.number == 9)
                    {
                        su_chan_b_count++;
                        su_nodu_b_count++;
                    }
                    else{
                        // 수패 머리/커쯔/깡쯔인 경우,
                        // 1이나 9가 아니면 (준)찬타/(혼/청)노두 불가.
                        chanta_fail = true;
                        break;
                    }
                    
                }
                else if(b.tsu_type == TsuType::Syuntsu)
                {
                    // 슌쯔는 123이나 789여야 함.
                    if(b.number == 1 || b.number == 7)
                    {
                        su_chan_b_count++;
                    }
                    else
                    {// 슌쯔가 123이나 789가 아닌 경우 찬타불가
                        chanta_fail = true;
                        break;
                    }
                }
            }

        }//end of loop

        //찬타/준찬타/혼노두/청노두 불가 미리 체크
        if(chanta_fail){
            h->yakustate.chanta = false;
            h->yakustate.junchanta = false;
            h->yakustate.honnodu = false;
            h->yakumansate.cheongnodu = false;
            continue;
        }

        // 이 지점에서 123/789 111/999 11/99 또는 자패만 있다는 것이 보장되어야 함.
        // 123/789 111/999 11/99 블록이 적어도 하나는 있어야 함.
        if(su_chan_b_count> 0)
        {
            if(japae_b_count > 0)
            {// 자패 블록이 있는 경우 준찬타, 청노두 불가.

                if (su_nodu_b_count == su_chan_b_count)
                {// 자패가 있고, 수패는 111/999 11/99만 있는 경우 -> 혼노두
                    h->yakustate.chanta = false;   
                    h->yakustate.junchanta = false;
                    h->yakustate.honnodu = true;
                    h->yakumansate.cheongnodu = false;
                }
                else
                {// 자패가 있고, 그외 -> 찬타
                    h->yakustate.chanta = true;   
                    h->yakustate.junchanta = false;
                    h->yakustate.honnodu = false;
                    h->yakumansate.cheongnodu = false;
                }

            }
            else
            {// 자패 블록이 없는 경우 준찬타 or 청노두
                if (su_nodu_b_count == su_chan_b_count)
                {// 자패가 있고, 수패는 111/999 11/99만 있는 경우 -> 청노두
                    h->yakustate.chanta = false;   
                    h->yakustate.junchanta = false;
                    h->yakustate.honnodu = false;
                    h->yakumansate.cheongnodu = true;
                }
                else
                {// 자패가 있고, 그외 -> 준찬타
                    h->yakustate.chanta = false;   
                    h->yakustate.junchanta = true;
                    h->yakustate.honnodu = false;
                    h->yakumansate.cheongnodu = false;
                }
            }
        }

    }//end of loop
}
