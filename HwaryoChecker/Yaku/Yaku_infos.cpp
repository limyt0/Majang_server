#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../Tsublock.h"
#include <vector>
#include "../Consts_hwaryo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_INFO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

// 쯔모/론 패, 대기 정보, 론 쯔모 여부 업데이트
void YakuChecker::info_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile, int type)
{
    DEBUG_LOG("YakuChecker::info_update()\n");
    // 쯔모/론 패 업데이트.
    LastTile_update(hwaryo_list, LastTile);
    // DEBUG_LOG("aa\n");
    // DEBUG_LOG("a)hwaryo_list[0].last_tile = %d\n", (*hwaryo_list)[0].last_tile); // 화료 아니면 (*hwaryo_list)[0]이 없어서 오류남

    // 쯔모/론 패가 있는 블록을 찾아서 대기 타입 정보 업데이트.
    Daegi_info_update(hwaryo_list, LastTile);
    // DEBUG_LOG("b)hwaryo_list[0].last_tile = %d\n", (*hwaryo_list)[0].last_tile);

    // 론,쯔모 여부 및 타입 - 창깡, 영상개화, 해저로월, 하저로어 포함.
    hwaryopae_type_update(hwaryo_list, type);
    // DEBUG_LOG("c)hwaryo_list[0].last_tile = %d\n", (*hwaryo_list)[0].last_tile);

}//end of function


// 쯔모/론 패 업데이트.
void YakuChecker::LastTile_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile)
{
    DEBUG_LOG("LastTile_update()\n");
    DEBUG_LOG("hwaryo_list->size() = %d\n", hwaryo_list->size());
    DEBUG_LOG("LastTile = %d", LastTile);
    // last_tile = LastTile;
    for(std::size_t i=0;i < hwaryo_list->size();i++)
    {
        DEBUG_LOG("LastTile = %d, hwaryo_list->size() = %d\n", LastTile, hwaryo_list->size());
        (*hwaryo_list)[i].last_tile = LastTile;
        DEBUG_LOG("hwaryo_list[%d].last_tile = %d\n", i, (*hwaryo_list)[i].last_tile);
    }
    DEBUG_LOG("LastTile_update() end\n");
}

// 론,쯔모 여부 및 타입 업데이트 - 창깡, 영상개화, 해저로월, 하저로어 포함.
void YakuChecker::hwaryopae_type_update(std::vector<HwaryoInfo> * hwaryo_list, int type)
{
    for(std::size_t i=0;i<hwaryo_list->size();i++)
    {
        (*hwaryo_list)[i].hwaryo_pae_type = type;
    }
}

int daegi_state_sum(Daegistate * daegistate);
// 쯔모/론 패가 있는 블록을 찾아서 대기 타입 정보 업데이트.
// 대기타입이 여러가지로 해석될 수 있으면 블록별로 저장.
void YakuChecker::Daegi_info_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile)
{
    int LastTile_type = LastTile /100;
    int LastTile_num = (LastTile / 10 ) % 10;

    for(std::size_t i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &((*hwaryo_list)[i]);
        for(std::size_t j=0;j<h->tsu_blocks.size();j++)
        {
            TsuBlock b = h->tsu_blocks[j];
            if(b.pae_type == LastTile_type)
            {
                int tsu_type = b.tsu_type;
                int tsu_num = b.number;
                if (tsu_type == TsuType::Meori){if(tsu_num == LastTile_num){h->daegistate.Dangi = true;}}
                else if (tsu_type == TsuType::Syuntsu)
                {
                    if(tsu_num == LastTile_num)
                    {
                        if(LastTile_num == 7){h->daegistate.Byeon = true;}
                        else{h->daegistate.Yang = true;}
                    }
                    else if(tsu_num + 1 == LastTile_num)
                    {
                        h->daegistate.Gan = true;
                    }
                    else if(tsu_num + 2 == LastTile_num)
                    {
                        if(LastTile_num == 3){h->daegistate.Byeon = true;}
                        else{h->daegistate.Yang = true;}                            
                    }
                }else if (tsu_type == TsuType::Keotsu)
                {
                    if(tsu_num == LastTile_num)
                    {
                        h->daegistate.Syabo = true;
                    }
                }
            }
        }// end of loop
    }// end of loop


    // 같은 패에 대한 대기 타입이 여러가지인 경우 해석을 분리(부수 계산에 필요하지만, 핑후 계산 전에 해야함.).
    std::vector<HwaryoInfo> h_other_daegi;// 다른 대기타입 해석을 저장할 변수
    for(std::size_t i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &((*hwaryo_list)[i]);

        // 대기타입이 몇종류로 해석될 수 있는지
        int daegi_type_count = daegi_state_sum(&h->daegistate);
        if(daegi_type_count <= 1){continue;} // 대기 해석 2개이상인 경우만 처리

        // 양면 대기
        if(h->daegistate.Yang){
            h->daegistate.Yang = false;
            HwaryoInfo h_other_daegi_0(h->tsu_blocks, h->pae_count, h->hwaryo_pae_type);
            h_other_daegi_0.last_tile = h->last_tile;
            h_other_daegi_0.daegistate.Yang = true;
            h_other_daegi_0.daegistate.Syabo = false;
            h_other_daegi_0.daegistate.Gan = false;
            h_other_daegi_0.daegistate.Byeon = false;
            h_other_daegi_0.daegistate.Dangi = false;
            h_other_daegi.push_back(h_other_daegi_0);
        }
        daegi_type_count = daegi_state_sum(&h->daegistate);
        if(daegi_type_count <= 1){continue;} // 대기 해석 2개이상인 경우만 처리

        // 샤보대기
        if(h->daegistate.Syabo)
        {   h->daegistate.Syabo = false;
            HwaryoInfo h_other_daegi_0(h->tsu_blocks, h->pae_count, h->hwaryo_pae_type);
            h_other_daegi_0.last_tile = h->last_tile;
            h_other_daegi_0.daegistate.Yang = false;
            h_other_daegi_0.daegistate.Syabo = true;
            h_other_daegi_0.daegistate.Gan = false;
            h_other_daegi_0.daegistate.Byeon = false;
            h_other_daegi_0.daegistate.Dangi = false;
            h_other_daegi.push_back(h_other_daegi_0);
        }
        daegi_type_count = daegi_state_sum(&h->daegistate);
        if(daegi_type_count <= 1){continue;} // 대기 해석 2개이상인 경우만 처리

        // 간짱대기
        if(h->daegistate.Gan)
        {   h->daegistate.Gan = false;
            HwaryoInfo h_other_daegi_0(h->tsu_blocks, h->pae_count, h->hwaryo_pae_type);
            h_other_daegi_0.last_tile = h->last_tile;
            h_other_daegi_0.daegistate.Yang = false;
            h_other_daegi_0.daegistate.Syabo = false;
            h_other_daegi_0.daegistate.Gan = true;
            h_other_daegi_0.daegistate.Byeon = false;
            h_other_daegi_0.daegistate.Dangi = false;
            h_other_daegi.push_back(h_other_daegi_0);
        }
        daegi_type_count = daegi_state_sum(&h->daegistate);
        if(daegi_type_count <= 1){continue;} // 대기 해석 2개이상인 경우만 처리

        // 변짱 대기
        if(h->daegistate.Byeon)
        {   h->daegistate.Byeon = false;
            HwaryoInfo h_other_daegi_0(h->tsu_blocks, h->pae_count, h->hwaryo_pae_type);
            h_other_daegi_0.last_tile = h->last_tile;
            h_other_daegi_0.daegistate.Yang = false;
            h_other_daegi_0.daegistate.Syabo = false;
            h_other_daegi_0.daegistate.Gan = false;
            h_other_daegi_0.daegistate.Byeon = true;
            h_other_daegi_0.daegistate.Dangi = false;
            h_other_daegi.push_back(h_other_daegi_0);
            
        }
        // 여기까지 오면 대기 해석 1개만 남음.
        // daegi_type_count = daegi_state_sum(&h->daegistate);
        // if(daegi_type_count <= 1){continue;} // 대기 해석 2개이상인 경우만 처리

        // // 단기 대기
        // if(h->daegistate.Dangi)
        // {   h->daegistate.Dangi = false;
        //     HwaryoInfo h_other_daegi_0(h->tsu_blocks, h->pae_count, h->hwaryo_pae_type);
        //     h_other_daegi_0.last_tile = h->last_tile;
        //     h_other_daegi_0.daegistate.Yang = false;
        //     h_other_daegi_0.daegistate.Syabo = false;
        //     h_other_daegi_0.daegistate.Gan = false;
        //     h_other_daegi_0.daegistate.Byeon = false;
        //     h_other_daegi_0.daegistate.Dangi = true;
        //     h_other_daegi.push_back(h_other_daegi_0);
        // }
        
    }//end of loop

    // 화료 리스트에 추가.
    for(std::size_t i=0;i<h_other_daegi.size();i++)
    {
        hwaryo_list->push_back(h_other_daegi[i]);
    }


}//end of function

int daegi_state_sum(Daegistate * daegistate){
    int daegi_type_num =0;
    if(daegistate->Yang){daegi_type_num++;}
    if(daegistate->Syabo){daegi_type_num++;}
    if(daegistate->Gan){daegi_type_num++;}
    if(daegistate->Byeon){daegi_type_num++;}
    if(daegistate->Dangi){daegi_type_num++;}
    return daegi_type_num;
}


// 후로 카운트 업데이트, 슌쯔 수, 커쯔 깡쯔 후로 여부 구분해서 카운트 업데이트
void YakuChecker::bcounts_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(std::size_t i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &((*hwaryo_list)[i]);
        for(std::size_t j=0;j<h->tsu_blocks.size();j++)
        {   
            TsuBlock b = h->tsu_blocks[j];
            
            if(b.tsu_type == TsuType::Syuntsu)
            {
                h->bCounts.syun += 1;
                // DEBUG_LOG("슌쯔 %d, 후로 슌쯔 \n", h->bCounts.syun, h->bCounts.huro_syun);
                if (b.huro){
                    h->bCounts.huro += 1;
                    h->bCounts.huro_syun += 1;
                    // DEBUG_LOG("(후로)슌쯔 %d, 후로 슌쯔 \n", h->bCounts.syun, h->bCounts.huro_syun);
                }
                // DEBUG_LOG("-> 슌쯔 %d, 후로 슌쯔 \n", h->bCounts.syun, h->bCounts.huro_syun);
            }
            else if(b.tsu_type == TsuType::Keotsu)
            {
                h->bCounts.keot += 1;
                // DEBUG_LOG("커쯔 %d, 후로 커쯔 \n", h->bCounts.syun, h->bCounts.huro_syun);

                if (b.huro){
                    h->bCounts.huro += 1;
                    h->bCounts.huro_keot += 1;
                }   
            }
            else if(b.tsu_type == TsuType::Kangtsu)
            {
                h->bCounts.kang += 1;
                if (b.huro){
                    h->bCounts.huro += 1;
                    h->bCounts.huro_kang += 1;
                }   
            }

        }
    }
}