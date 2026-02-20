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
        int paetype = last_tile / 100;
        int num = (last_tile / 10) % 10;
        printf("-- 마지막 화료 패 : ("); 
        if(paetype == PaeType::JaPae){
            if (num == 1){printf(" 東 ");}
            if (num == 2){printf(" 南 ");}
            if (num == 3){printf(" 西 ");}
            if (num == 4){printf(" 北 ");}
            if (num == 5){printf(" 白 ");}
            if (num == 6){printf(" 發 ");}
            if (num == 7){printf(" 中 ");}
        }
        else{
            printf(PaeType::Tostring(paetype).c_str());
            printf(" %d", num);
        }
        printf(")\n");
        
    }
    
    if(daegi)
    {
        std::string str = "대기 : ";
        if(daegistate.Dangi){str += "단기 ";}
        if(daegistate.Yang){str += "양면 ";}
        if(daegistate.Gan){str += "간짱 ";}
        if(daegistate.Byeon){str += "변짱 ";}
        if(daegistate.Syabo){str += "샤보 ";}
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

