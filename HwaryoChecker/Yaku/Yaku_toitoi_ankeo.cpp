#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_TOITOI_ANKEO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 또이또이 산안커 스안커 스안커단기 산깡즈, 스깡즈

// 또이또이 : 커쯔/깡쯔 상관 X
// 산안커 스안커 스안커단기 - 커쯔만 가능
// 산깡즈, 스깡즈. - 깡쯔만 가능.
void YakuChecker::toi_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(std::size_t i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];

        int toi_count = h->bCounts.keot + h->bCounts.kang;
        int ankeo = h->bCounts.keot - h->bCounts.huro_keot;
        int ankang = h->bCounts.kang - h->bCounts.huro_kang;
        ankeo += ankang;

        DEBUG_LOG("커쯔 : %d, 깡쯔 %d \n", h->bCounts.keot, h->bCounts.kang);
        DEBUG_LOG("후로 커쯔 : %d, 후로 깡쯔 %d\n", h->bCounts.huro_keot, h->bCounts.huro_kang);
        DEBUG_LOG("안커 수 : %d \n", ankeo);
        
        if(ankeo >= 3)
        {
            
            if( HwaryoPaeType::is_ron(h->hwaryo_pae_type) )
            {   // 론인 경우 - 대기패가 안커로 될 수 없음.
                // DEBUG_LOG("론인 경우 - 대기패가 안커로 될 수 없음. \n");

                if (h->daegistate.Syabo)
                {
                    // 론 화료일 때, 샤보대기일 경우 대기패가 안커 아님
                    // DEBUG_LOG("론 화료일 때, 샤보대기일 경우 대기패가 안커 아님. \n");
                    if(ankeo == 4){h->yakustate.san_ankeo = true;}
                }
                else
                {
                    // 론 화료일 때, 샤보대기가 아닌경우.
                    // DEBUG_LOG("론 화료일 때, 샤보대기가 아닌경우. \n");
                    if(ankeo == 3){h->yakustate.san_ankeo = true;}
                    if(ankeo == 4){
                        
                        if(h->daegistate.Dangi)// 스안커 단기
                        {h->yakumansate.su_ankeo_dangi = true;}
                        else // 그외 스안커
                        {h->yakumansate.su_ankeo = true;}
                    }
                }                    
            }
            else 
            {   // 쯔모인 경우 - 대기패도 안커가 될 수 있음
                if(ankeo == 3){h->yakustate.san_ankeo = true;}
                if(ankeo == 4)
                {       
                    if(h->daegistate.Dangi)// 스안커 단기
                    {h->yakumansate.su_ankeo_dangi = true;}
                    else // 그외 스안커
                    {h->yakumansate.su_ankeo = true;}
                }
            }

        }
        else if(h->bCounts.kang== 3)
        {
            h->yakustate.san_kangz = true;
        }
        else if(h->bCounts.kang == 4)
        {
            h->yakumansate.su_kangz = true;
        }
        else if(toi_count == 4)
        {   // 상위역이 아닌 경우, 또이또이 체크
            h->yakustate.toitoi = true;
        }

    }
}