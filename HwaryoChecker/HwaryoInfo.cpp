#include "HwaryoInfo.h"
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"
#include "hwaryo_config.h"
#ifdef HWARYO_INFO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)   
#endif

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
        DEBUG_LOG("-- 마지막 화료 패 : ("); 
        if(paetype == PaeType::JaPae){
            if (num == 1){DEBUG_LOG(" 東 ");}
            if (num == 2){DEBUG_LOG(" 南 ");}
            if (num == 3){DEBUG_LOG(" 西 ");}
            if (num == 4){DEBUG_LOG(" 北 ");}
            if (num == 5){DEBUG_LOG(" 白 ");}
            if (num == 6){DEBUG_LOG(" 發 ");}
            if (num == 7){DEBUG_LOG(" 中 ");}
        }
        else{
            DEBUG_LOG(PaeType::Tostring(paetype).c_str());
            DEBUG_LOG(" %d", num);
        }
        DEBUG_LOG(")\n");
        
    }
    
    if(daegi)
    {
        std::string str = "대기 : ";
        if(daegistate.Dangi){str += "단기 ";}
        if(daegistate.Yang){str += "양면 ";}
        if(daegistate.Gan){str += "간짱 ";}
        if(daegistate.Byeon){str += "변짱 ";}
        if(daegistate.Syabo){str += "샤보 ";}
        DEBUG_LOG("%s\n", str.c_str());
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

