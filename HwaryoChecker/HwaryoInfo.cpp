#include "HwaryoInfo.h"
#include "Consts_hwaryo.h"

HwaryoInfo::HwaryoInfo(TsuBlock * tsu_blocks_, int * pae_count_)
{
    tsu_blocks = tsu_blocks_;
    // pae_count_.CopyTo(pae_count, 0);
    for(int i=0;i<38;i++){
        pae_count[i] = pae_count_[i];
    }

    daegistate = new Daegistate();
}

HwaryoInfo::~HwaryoInfo(){
    delete daegistate;
}

void HwaryoInfo::print_info()
{
    
}