#include "TenpaiInfo.h"
#include "../HwaryoInfo.h"
#include "../HwaryoChecker.h"
#include "../hwaryo_config.h"
#ifdef TENPAI_INFO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif


// 역이 있는 텐파이의 경우 화료 정보 추가
TenpaiInfo::TenpaiInfo(HwaryoChecker * hwaryoChecekr, int LastTile)
{
    last_tile = LastTile;//대기패.
    // int best_yakuman_su = 0;
    int i_ym = 0;
    // int best_pansu = 0;
    int i_y = 0;

    // 블록 형태 경우의 수 별로 추가
    for(std::size_t i=0;i< hwaryoChecekr->hwaryo_list.size();i++)
    {
        HwaryoInfo * h = &hwaryoChecekr->hwaryo_list[i];
        
        // 블록 형태 정보
        // TenpaiBlock_list t;
        // for(int j=0;j < h->tsu_blocks.size();j++)
        // {
        //     t.tsu_blocks.push_back(h->tsu_blocks[j]);
        // }

        // // 대기 정보.(양면, 사보만)
        // yang = yang || h->daegistate.Yang;
        // syabo = syabo || h->daegistate.Syabo;
        
        // n배 역만
        if(yakuman_su < h->scoreComponent.yakuman_su)
        {
            yakuman_su = h->scoreComponent.yakuman_su;
            i_ym = i;
        }
        
        // 판수.
        if(h->scoreComponent.pansu > 0){
            int h_total_pansu = h->scoreComponent.pansu;
            h_total_pansu += h->scoreComponent.dora_pansu;
            if(pansu < h_total_pansu)
            {
                pansu = h_total_pansu;
                i_y = i;
            }
        }
        
        // 역 정보


        // tenpaiBlock_list.push_back(t);
    }

    if(yakuman_su > 0)
    {   
        // 역만이 있는 경우.
        HwaryoInfo * h = &hwaryoChecekr->hwaryo_list[i_ym];
        yakumansate = h->yakumansate;
    }
    else
    {   
        // 역만이 아닌 경우
        HwaryoInfo * h = &hwaryoChecekr->hwaryo_list[i_y];
        if(pansu == 0){NoYaku = true;}
        else{yakustate = h->yakustate;}
    }

}

TenpaiInfo::~TenpaiInfo(){}