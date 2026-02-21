#include "HwaryoChecker.h"
#include "GameData/Jaksadata.h"
// #include "Jaksadata.h"
#include <vector>
#include "GameData/PeaAndBlock/HuroBlock.h"
#include "GameData/PeaAndBlock/AnkanBlock.h"
// #include <iostream>
// #include "Consts_hwaryo.h"
// #include "Yaku/YakuChecker.h"
// #include "GameData.h"
// #include "Enums.h"
void To_TsuBlock(std::vector<HwaryoInfo> * hwaryo_list, std::vector<int> block);

// HuroBlock 및 AnkanBlock을 TsuBlock으로 변환.
void HwaryoChecker::HuroAnkan_To_TsuBlock(Jaksadata * jaksa)
{

    printf("후로블록을 TsuBlock으로 변환.\n");

    int huro_size = jaksa->hurolist.size();
    printf("huro_size %d\n",huro_size);
        
    // 후로블록을 TsuBlock으로 변환.
    for(int i=0;i<huro_size;i++)
    {
        printf("a%d\n",i);
        // break;
        auto v = jaksa->hurolist[i].get();
        // auto v = std::move(jaksa->hurolist[i]);

        printf("b%d\n",i);
        

        To_TsuBlock(&hwaryo_list, v->tiles);
        // auto v = jaksa->hurolist[i];
        // To_TsuBlock(&hwaryo_list, v.tiles);
    
        printf("c%d\n",i);
        
    }

    printf("안깡블록을 TsuBlock으로 변환.\n");
    // 안깡블록을 TsuBlock으로 변환.
    for(int i=0;i<jaksa->ankanList.size();i++)
    {
        auto v = std::move(jaksa->ankanList[i]).get();
        To_TsuBlock(&hwaryo_list, v->tiles);
        // auto v = jaksa->ankanList[i];
        // To_TsuBlock(&hwaryo_list, v.tiles);
    }

    printf("후로 안깡 완료.\n");
}

void To_TsuBlock(std::vector<HwaryoInfo> * hwaryo_list, std::vector<int> block)
{
    printf("To_TsuBlock1\n");
    TsuBlock tsuBlock;

    int block_len = block.size();
    int min = 900;
    bool toi = false;//커쯔나 깡쯔

    printf("To_TsuBlock2\n");
    int block_size = block.size();
    printf("Block size = %d\n", block_size);

    if(block.size() > 4){printf("Block size error size is %d\n", block_size);}

    for(int i=0;i < block_size;i++)
    {
        printf("(%d)", i);

        int id = block[i];

        printf("id= %d, ", id);
        printf("min = %d, ", min);

        if(id == min){toi = true;printf("toi true");}
        else if(id < min){min = id;printf("toi false");}

        printf("\n");


    }

    printf("To_TsuBlock3\n");

    tsuBlock.number = (min/10) % 10;
    tsuBlock.pae_type = min/100;
    if (toi)
    {   //커쯔나 깡쯔
        if(block_len == 4)
        {
            tsuBlock.tsu_type = TsuType::Kangtsu;
            tsuBlock.huro = true;
        }
        else if (block_len == 3)
        {
            tsuBlock.tsu_type = TsuType::Keotsu;
            tsuBlock.huro = true;
        }
    }
    else
    {   // 슌쯔
        tsuBlock.tsu_type = TsuType::Syuntsu;
        tsuBlock.huro = true;
    }
    printf("To_TsuBlock4\n");

    // 화료리스트에 업데이트
    for(int i=0;i<hwaryo_list->size();i++)
    {
        (*hwaryo_list)[i].tsu_blocks.push_back(tsuBlock);
    }
}
