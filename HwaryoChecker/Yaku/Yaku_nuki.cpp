#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "GameData/Jaksadata.h"
#include <vector>
#include "../hwaryo_config.h"
#ifdef YAKU_NUKI_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

void YakuChecker::nuki_info_update(std::vector<HwaryoInfo> * hwaryo_list, Jaksadata * jaksa)
{
    for(std::size_t i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i];
        h->scoreComponent.nuki_pansu = jaksa->nukilist.size();
    }
}