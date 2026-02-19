#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../Tsublock.h"
#include <vector>
#include "../Consts_hwaryo.h"
// #include 

void YakuChecker::guksa(std::vector<HwaryoInfo> * hwaryo_list,  int * pae_count, int last_tile, int hwaryo_pae_type)
{
    int sum = 0;
    bool guksa_possible = true;
    
    if (pae_count[1] > 0){sum += pae_count[1];}else{guksa_possible = false;}
    if (pae_count[9] > 0){sum += pae_count[9];}else{guksa_possible = false;}
    if (pae_count[11] > 0){sum += pae_count[11];}else{guksa_possible = false;}
    if (pae_count[19] > 0){sum += pae_count[19];}else{guksa_possible = false;}
    if (pae_count[21] > 0){sum += pae_count[21];}else{guksa_possible = false;}
    if (pae_count[29] > 0){sum += pae_count[29];}else{guksa_possible = false;}

    for(int i = 31; i <= 37; i++)
    {
        if (pae_count[i] > 0){sum += pae_count[i];}
        else{guksa_possible = false;}
    }

    if(sum == 14 && guksa_possible)
    {   
        // printf("(guksa) sum == 14\n");
        TsuBlock tsuBlock;// = new TsuBlock();
        std::vector<TsuBlock> tsu_blocks;// = new std::vector<TsuBlock>();
        tsuBlock.tsu_type = TsuType::Guksa;

        tsu_blocks.push_back(tsuBlock);
        HwaryoInfo h(tsu_blocks.data(), pae_count);
        if (pae_count[last_tile / 10] == 2)
        {
            printf("guksa 13 updating...\n");
            h.yakumansate.guksa_13 = true;
            h.hwaryo_pae_type = hwaryo_pae_type;
            h.last_tile = last_tile;
            if(hwaryo_pae_type == HwaryoPaeType::CheonHwa)
            {h.yakumansate.cheonhwa = true;}
            else if(hwaryo_pae_type == HwaryoPaeType::JiHwa)
            {h.yakumansate.jihwa = true;}
            
        }
        else
        {
            printf("guksa updating...\n");
            h.yakumansate.guksa = true;
            h.daegistate.Dangi = true;
            h.hwaryo_pae_type = hwaryo_pae_type;
            h.last_tile = last_tile;
            if(hwaryo_pae_type == HwaryoPaeType::CheonHwa)
            {h.yakumansate.cheonhwa = true;}
            else if(hwaryo_pae_type == HwaryoPaeType::JiHwa)
            {h.yakumansate.jihwa = true;}
        }
        hwaryo_list->push_back(h);
    }
}
