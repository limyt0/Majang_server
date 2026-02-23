#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_TSUMO_RON_DEP_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 영상 창깡 해저 하저 천화 지화. + 멘젠 쯔모


// 영상 창깡 해저 하저 천화 지화.
void YakuChecker::tsumo_ron_type_depended_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    // 영상개화, 창깡, 해저로월, 하저로어, 천화, 지화
    for(int i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        if(h->hwaryo_pae_type == HwaryoPaeType::NormalRon){break;}
        else if(h->hwaryo_pae_type == HwaryoPaeType::PaesanTsumo){break;}
        else if(h->hwaryo_pae_type == HwaryoPaeType::Yeongsang)
        {
            h->yakustate.yeongsang = true;
        }
        else if(h->hwaryo_pae_type == HwaryoPaeType::Hajeo)
        {
            h->yakustate.hajeo = true;   
        }
        else if(h->hwaryo_pae_type == HwaryoPaeType::Haejeo)
        {
            h->yakustate.haejeo = true;   
        }
        else if(h->hwaryo_pae_type == HwaryoPaeType::Chankang)
        {
            h->yakustate.changkang = true;
        }
        else if(h->hwaryo_pae_type == HwaryoPaeType::CheonHwa)
        {
            h->yakumansate.cheonhwa = true;
        }
        else if(h->hwaryo_pae_type == HwaryoPaeType::JiHwa)
        {
            h->yakumansate.jihwa = true;
        }
    }
}

// 멘젠 쯔모
void YakuChecker::menzen_tsumo_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(int i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        if (HwaryoPaeType::is_ron(h->hwaryo_pae_type))
        {
            // 론인 경우 멘젠 쯔모 불가.
            break;
        }
        else if(h->bCounts.huro == 0)
        {
            // 후로 없이 쯔모해서 화료한 경우
            h->yakustate.menzen_tsumo = true;
        }
    }
}