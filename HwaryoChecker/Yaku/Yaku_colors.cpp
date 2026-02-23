#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../Tsublock.h"
#include <vector>
#include "../Consts_hwaryo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_COLORS_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 혼일색 청일색 자일색. 구련보등 순정구련보등, 녹일색

// 혼일색 청일색 자일색.
void YakuChecker::color_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    DEBUG_LOG("color_info_update()\n");
    for(int i_=0;i_<hwaryo_list->size();i_++)
    {
        DEBUG_LOG("(i=%d)\n",  i_);

        HwaryoInfo * h = &(*hwaryo_list)[i_];
        bool type_exist[4] = {false, false, false, false};// 만통삭/자패

        for(int j_=0;j_<h->tsu_blocks.size();j_++)
        {
            DEBUG_LOG("(--) (i=%d, j=%d)\n",i_,  j_);
            TsuBlock b = h->tsu_blocks[j_];
            type_exist[b.pae_type] = true;
        }

        DEBUG_LOG("(i=%d) if condition...\n",  i_);

        if (!type_exist[0] && !type_exist[1] && !type_exist[2])
        {
            h->yakumansate.ja_il = true;
        }
        else if(type_exist[0] && !type_exist[1] && !type_exist[2])
        {
            if(type_exist[PaeType::JaPae]){h->yakustate.hon_il = true;}
            else{h->yakustate.cheong_il = true;}
        }
        else if(!type_exist[0] && type_exist[1] && !type_exist[2])
        {
            if(type_exist[PaeType::JaPae]){h->yakustate.hon_il = true;}
            else{h->yakustate.cheong_il = true;}
        }
        else if(!type_exist[0] && !type_exist[1] && type_exist[2])
        {
            if(type_exist[PaeType::JaPae]){h->yakustate.hon_il = true;}
            else{h->yakustate.cheong_il = true;}
        }

        DEBUG_LOG("(i=%d) if condition...end\n",  i_);

    }
    DEBUG_LOG("color_info_update() function end\n");

}

// 구련보등 순정구련보등
// 청일색의 상위역이지만, 로직 편의상 따로 체크
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

// 녹일색 - 청일색/혼일색 체크를 먼저 했다고 가정.
void YakuChecker::nok_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{

    for(int i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];

        // 청일색이나 혼일색 체크된게 아니면 녹일색 불가능.
        if (!h->yakustate.cheong_il && !h->yakustate.hon_il)
        {return;}

        bool nok_possible = true;
        
        for(int j_=0;j_<h->tsu_blocks.size();j_++)
        {

            TsuBlock b = h->tsu_blocks[j_];
            if(b.pae_type == PaeType::JaPae)
            {
                DEBUG_LOG("(녹일색 체크) - 자패 확인..\n");

                // 자패가 발이 아닌 경우 녹일색 불가능
                if(b.number != 6)
                {
                    DEBUG_LOG("(녹일색체크) 자패가 '發'이 아님.\n");
                    return;
                }
            }
            else if(b.pae_type == PaeType::Saksu)
            {   // 수패는 삭수만 가능
                DEBUG_LOG("(녹일색체크) - 삭수 블록 -- \n");
                DEBUG_LOG(TsuType::Tostring(b.tsu_type).c_str());
                DEBUG_LOG(" %d\n", b.number);
                if(b.tsu_type == TsuType::Syuntsu)
                {   
                    DEBUG_LOG("(녹일색체크) - 슌쯔 확인 중\n");
                    // 슌쯔는 2/3/4만 가능
                    if(b.number != 2)
                    {
                        DEBUG_LOG("(녹일색체크) - 슌쯔가 234가 아님.\n");
                        // return이 아닌 break으로 처리.
                        // 화료 해석이 2가지 이상 있을수 있음.
                        // (예 222/333/444 == 234/234/234)
                        nok_possible = false;
                        break;
                    }

                }
                else
                {   // 머리 커쯔 깡쯔 23468만 가능, 1579는 불가능.
                    if(b.number == 1 || b.number == 5 || b.number == 7 || b.number == 9)
                    {
                        return;
                    }
                }
            }
            else{
                // 다른 종류 패가 있으면 녹일색 불가능.
                return;
            }
            
        }//end of loop
        if(nok_possible){h->yakumansate.nok_il = true;}

    }//end of loop
}