#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../Consts_hwaryo.h"
#include "GameData/GameData.h"
#include "GameData/Jaksadata.h"
#include "GameData/PeaAndBlock/HuroBlock.h"
#include "GameData/PeaAndBlock/AnkanBlock.h"
#include <vector>
#include "../hwaryo_config.h"
#ifdef YAKU_DORA_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

// DoraCount Sum(DoraCount a, DoraCount b);
void dora_count_from_vector(DoraCount * doraCount, GameData * game_data, std::vector<int> tiles);
void dora_count_update_from_int(DoraCount * doraCount, GameData * game_data, int target);
int counting_dora(std::vector<int> dora, int target);
void dora_info_add(std::vector<HwaryoInfo> * hwaryo_list, DoraCount dora_count);
void DoraCount_print(DoraCount * doraCount);

// 앞도라, 뒷도라, 적도라 정보를 화료 리스트에 업데이트.
// 손패 후로 안깡 모두 체크
void YakuChecker::dora_info_update(std::vector<HwaryoInfo> * hwaryo_list, Jaksadata * jaksa, GameData * game_data, int last_tile)
{
   
    DoraCount doraCount;

    DEBUG_LOG("1");DoraCount_print(&doraCount);
    // 마지막 화료패 한 장 체크
    dora_count_update_from_int(&doraCount, game_data, last_tile);
    
    DEBUG_LOG("2");DoraCount_print(&doraCount);
    // 손패 체크
    dora_count_from_vector(&doraCount, game_data, jaksa->sonTils);
    

    DEBUG_LOG("3");DoraCount_print(&doraCount);
    // 후로블록 체크
    for(int i=0;i<jaksa->hurolist.size();i++)
    {
        auto v = std::move(jaksa->hurolist[i]).get();
        dora_count_from_vector(&doraCount, game_data, v->tiles);
        // auto v = jaksa->hurolist[i];
        // dora_count_from_vector(&doraCount, game_data, v.tiles);
    }
    
    DEBUG_LOG("4");DoraCount_print(&doraCount);
    // 안깡블록 체크
    for(int i=0;i<jaksa->ankanList.size();i++)
    {
        auto v = std::move(jaksa->ankanList[i]).get();
        dora_count_from_vector(&doraCount, game_data, v->tiles);
        // auto v = jaksa->ankanList[i];
        // dora_count_from_vector(&doraCount, game_data, v.tiles);
    }

    DEBUG_LOG("5");DoraCount_print(&doraCount);
    // 화료정보에 추가.
    dora_info_add(hwaryo_list, doraCount);

}

void dora_count_from_vector(DoraCount * doraCount, GameData * game_data, std::vector<int> tiles)
{
    for(int i = 0; i < tiles.size(); i++)
    {
        int target = tiles[i];
        dora_count_update_from_int(doraCount, game_data, target);
    }
}

void dora_count_update_from_int(DoraCount * doraCount, GameData * game_data, int target)
{

    if(target % 10 == 5)
    {
        doraCount->aka_dora += 1;
    }
    doraCount->omote_dora += counting_dora(game_data->doras_omote, target);
    doraCount->ura_dora += counting_dora(game_data->doras_ura, target);
}

int counting_dora(std::vector<int> dora, int target)
{
    int result = 0;
    for(int i=0;i<dora.size();i++)
    {
        if(target/10 == dora[i] / 10)
        {
            result +=1;
        }
    }

    return result;
}


void dora_info_add(std::vector<HwaryoInfo> * hwaryo_list, DoraCount dora_count)
{
    for(int i=0;i<hwaryo_list->size();i++)
    {

        HwaryoInfo * h = &(*hwaryo_list)[i];

        DEBUG_LOG("a.");
        DoraCount_print(&h->doraCount);

        h->doraCount.omote_dora = dora_count.omote_dora;
        h->doraCount.ura_dora = dora_count.ura_dora;
        h->doraCount.aka_dora = dora_count.aka_dora;

        DEBUG_LOG("b.");
        DoraCount_print(&h->doraCount);
    }
}

void DoraCount_print(DoraCount * doraCount)
{
    DEBUG_LOG("(앞도라 %d)",doraCount->omote_dora);
    DEBUG_LOG("(뒷도라 %d)",doraCount->ura_dora);
    DEBUG_LOG("(적도라 %d)\n",doraCount->aka_dora);
}
// DoraCount Sum(DoraCount a, DoraCount b)
// {
//     DoraCount result;
//     {
//         result.omote_dora = a.doromote_doraa + b.omote_dora,
//         result.ura_dora = a.ura_dora + b.ura_dora,
//         result.aka_dora = a.aka_dora + b.aka_dora
//     };

//     return result;
// }