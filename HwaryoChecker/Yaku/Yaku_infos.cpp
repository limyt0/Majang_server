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
    for(int i=0;i < hwaryo_list->size();i++)
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
    for(int i=0;i<hwaryo_list->size();i++)
    {
        (*hwaryo_list)[i].hwaryo_pae_type = type;
    }
}


// 쯔모/론 패가 있는 블록을 찾아서 대기 타입 정보 업데이트.
// 대기타입이 여러가지로 해석될 수 있으면 블록별로 저장.
void YakuChecker::Daegi_info_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile)
{
    int LastTile_type = LastTile /100;
    int LastTile_num = (LastTile / 10 ) % 10;

    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &((*hwaryo_list)[i]);
        for(int j=0;j<h->tsu_blocks.size();j++)
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
}//end of function

// 후로 카운트 업데이트, 슌쯔 수, 커쯔 깡쯔 후로 여부 구분해서 카운트 업데이트
void YakuChecker::bcounts_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(int i=0;i<hwaryo_list->size();i++)
    {
        HwaryoInfo * h = &((*hwaryo_list)[i]);
        for(int j=0;j<h->tsu_blocks.size();j++)
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