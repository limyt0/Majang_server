#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../Tsublock.h"
#include <vector>
#include "../Consts_hwaryo.h"
// 혼일색 청일색 자일색. 구련보등 순정구련보등, 녹일색


void YakuChecker::guryeon(std::vector<HwaryoInfo> * hwaryo_list, int* pae_count_, int hwaryo_pae, int hwaryo_pae_type)
{
    // // 자패가 있는 경우 불가.
    // // 이걸 미리 체크 안하면 아래로직에서 바운드 에러날수 있음.
    if(hwaryo_pae > 300){return;} 

    int offset = (hwaryo_pae/100)*10;
    int hwaryo_pae_index = hwaryo_pae/10;
    int sum = 0;
    
    // // 구련보등 체크.
    if(pae_count_[offset + 1] < 3){return;}
    else{sum += pae_count_[offset + 1];}
    
    if(pae_count_[offset + 9] < 3){return;}
    else{sum += pae_count_[offset + 9];}
    
    int start_index = offset + 2;
    int end_index = offset + 8;
    for(int i = start_index;i<=end_index; i++)
    {
        if(pae_count_[i] < 1){return;}
        else{sum += pae_count_[i];}
    }

    if(sum == 14){}
    else{return;}


    // 순정 구련보등 체크.
    bool sun_guryeon = true;
    int pae_count[38];
    for(int i = 0;i<38;i++){pae_count[i] = 0;}
    
    // 복사해서 사용.
    for(int i = 1; i <= 37; i++)
    {
        pae_count[i] = pae_count_[i];
    }
    pae_count[hwaryo_pae_index] -= 1;// 화료패 제외한 확인
    if(pae_count[offset + 1] < 3){sun_guryeon = false;}
    if(pae_count[offset + 9] < 3){sun_guryeon = false;}
    for(int i = start_index;i<=end_index; i++)
    {
        if(pae_count[i] < 1){sun_guryeon = false;}
    }

    TsuBlock tsuBlock;
    std::vector<TsuBlock> tsu_blocks;
    tsuBlock.tsu_type = TsuType::Guryeon;
    tsu_blocks.push_back(tsuBlock);
    HwaryoInfo h(tsu_blocks, pae_count);
    if (sun_guryeon)
    {
        h.yakumansate.sun_guryeon = true;
        h.hwaryo_pae_type = hwaryo_pae_type;
        h.last_tile = hwaryo_pae;
        if(hwaryo_pae_type == HwaryoPaeType::CheonHwa)
        {h.yakumansate.cheonhwa = true;}
        else if(hwaryo_pae_type == HwaryoPaeType::JiHwa)
        {h.yakumansate.jihwa = true;}
    }
    else
    {
        h.yakumansate.guryeon = true;
        h.hwaryo_pae_type = hwaryo_pae_type;
        h.last_tile = hwaryo_pae;
        if(hwaryo_pae_type == HwaryoPaeType::CheonHwa)
        {h.yakumansate.cheonhwa = true;}
        else if(hwaryo_pae_type == HwaryoPaeType::JiHwa)
        {h.yakumansate.jihwa = true;}
    }

    hwaryo_list->push_back(h);

}