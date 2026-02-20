#include "YakuChecker.h"
#include "../HwaryoInfo.h"
// 리치, 더블 리치, 일발
// 주의 : 영상개화는 일발 동시적용 안됨
// (창깡은 일발 동시적용 됨.)


void YakuChecker::rich_ilbal_info_update(std::vector<HwaryoInfo> * hwaryo_list, int richi_type, bool is_ilbal)
{
    for(int i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        if(richi_type == RichiType::Richied)
        {
            h->yakustate.richi = true;
        }
        else if(richi_type == RichiType::Double_Richied)
        {
            h->yakustate.double_richi = true;
        }

        if (is_ilbal)
        {
            h->yakustate.ilbal = true;
        }
        
    }
}
