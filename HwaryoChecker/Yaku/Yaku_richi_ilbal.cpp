#include "YakuChecker.h"
#include "../HwaryoInfo.h"
// 리치, 더블 리치, 일발
// 주의 : 영상개화는 일발 동시적용 안됨
// (창깡은 일발 동시적용 됨.)

//           |  Normal | ilbal
// -----------------------------
// not richi |    0    |   3
// -----------------------------
//  riched   |    1    |   4
// -----------------------------
//  double   |    2    |   5

void YakuChecker::rich_ilbal_info_update(std::vector<HwaryoInfo> * hwaryo_list, int richi_ilbal_type)
{
    for(int i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        if (richi_ilbal_type % 3 == 1)
        {
            h->yakustate.richi = true;
        }
        else if (richi_ilbal_type % 3 == 2)
        {
            h->yakustate.double_richi = true;
        }

        if (richi_ilbal_type / 3 == 1)
        {
            h->yakustate.ilbal = true;
        }
        
    }
}
