#include "HwaryoInfo.h"
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"

HwaryoInfo::HwaryoInfo(std::vector<TsuBlock> tsu_blocks_, int * pae_count_)
{
    tsu_blocks = tsu_blocks_;
    for(int i=0;i<38;i++){
        pae_count[i] = pae_count_[i];
    }

}

HwaryoInfo::~HwaryoInfo()
{

}

void HwaryoInfo::print_info(bool block, bool hwaryo_tile, bool daegi, bool yaku, bool dora)
{
    if(block)
    {
        for(int i=0;i<tsu_blocks.size();i++)
        {
            tsu_blocks[i].print_contents();
        }
    }
    
    if(hwaryo_tile)
    {
        printf("-- 마지막 화료 패 : %s %d\n", PaeType::Tostring(last_tile / 100).c_str(), (last_tile / 10) % 10);
    }
    
    if(daegi)
    {
        std::string str = "--대기 : ";
        if(daegistate.Dangi){str += "단기, ";}
        if(daegistate.Yang){str += "양면, ";}
        if(daegistate.Gan){str += "간짱, ";}
        if(daegistate.Byeon){str += "변짱, ";}
        if(daegistate.Syabo){str += "샤보, ";}
        printf("%s\n", str.c_str());
    }

    if(yaku)
    {
        YakuChecker::Print_yaku(this);
    }
    
    if(dora)
    {
        // YakuChecker.print_dora(this);
    }
}

