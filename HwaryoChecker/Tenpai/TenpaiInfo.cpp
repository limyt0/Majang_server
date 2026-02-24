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
    int best_yakuman_su = 0;int i_ym = 0;
    int best_pansu = 0;int i_y = 0;

    // 블록 형태 경우의 수 별로 추가
    for(int i=0;i< hwaryoChecekr->hwaryo_list.size();i++)
    {
        HwaryoInfo * h = &hwaryoChecekr->hwaryo_list[i];
        
        // 블록 형태 정보
        TenpaiBlock_list t;
        for(int j=0;j < h->tsu_blocks.size();j++)
        {
            t.tsu_blocks.push_back(h->tsu_blocks[j]);
        }
        // 대기 정보.(양면, 사보, 단기, 간짱, 변짱)
        t.daegistate = h->daegistate;
        
        // n배 역만
        t.yakuman_su = h->scoreComponent.yakuman_su;
        if(t.yakuman_su > best_yakuman_su)
        {
            best_yakuman_su = t.yakuman_su;
            i_ym = i;
        }
        
        // 판수.
        t.pansu = h->scoreComponent.pansu;
        if(t.pansu > 0){t.pansu += h->scoreComponent.dora_pansu;}
        if(t.pansu > best_pansu)
        {
            best_pansu = t.pansu;
            i_y = i;
        }
        
        // 역 정보
        t.yakustate = h->yakustate;
        t.yakumansate = h->yakumansate;

        tenpaiBlock_list.push_back(t);
    }

    if(best_yakuman_su > 0)
    {   // 역만이 있는 경우.
        best = &tenpaiBlock_list[i_ym];
    }
    else
    {   // 역만이 아닌 경우
        best = &tenpaiBlock_list[i_y];
        if(best_pansu == 0)
        {
            NoYaku = true;
        }
    }

}

TenpaiInfo::~TenpaiInfo(){}