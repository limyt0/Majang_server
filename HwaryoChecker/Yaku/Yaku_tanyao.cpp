#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_TANYAO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 탕야오
void YakuChecker::tangyao_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
        for(int i=0;i<hwaryo_list->size();i++)
        {
            HwaryoInfo * h = &(*hwaryo_list)[i];
            for(int j=0;j<h->tsu_blocks.size();j++)
            {
                TsuBlock b = h->tsu_blocks[j];
                // 자패가 하나라도 있으면 탕야오 불가
                if(b.pae_type == PaeType::JaPae){h->yakustate.tangyao = false;break;}
                
                // 1 9가 있으면 탕야오 불가, 머리 슌쯔 커쯔 깡쯔 상관없음
                if(b.number == 1 || b.number == 9)
                {
                    h->yakustate.tangyao = false;break;
                }
                else if(b.tsu_type == TsuType::Syuntsu && b.number == 7)
                {  // 슌쯔 789의 경우 슌쯔라는 정보화 첫 숫자 7을 저장해놓음. 예외처리.
                    h->yakustate.tangyao = false;break;
                }
                // 모든 블록을 순회하고 break안되면 탕야오.
                h->yakustate.tangyao = true;
            }//end of loop
        }//end of loop
}