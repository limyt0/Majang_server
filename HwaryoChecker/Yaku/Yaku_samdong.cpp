#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_SAMDONG_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

 // 삼색 동순
void YakuChecker::samdongsun_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(std::size_t i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        
        // 슌쯔가 3개 미만인 경우 삼색동순 불가능
        if(h->bCounts.syun < 3)
        {
            h->yakustate.samdongsun = false;
            continue;
        }
        
        // 슌쯔 3장에서 가장 앞번호의 패id/10 (예 : 만수 345 -> 3, 통수 567 -> 15)
        int syuns[4]; // 4개 블록 중 menzen_syn_count 갯수만큼만 사용.

        int index = 0;
        for(std::size_t j=0;j<h->tsu_blocks.size();j++)
        {

            TsuBlock b = h->tsu_blocks[j];
            // 슌쯔인 경우만 처리.
            if(b.tsu_type == TsuType::Syuntsu)
            {
                syuns[index] = b.pae_type*10 + b.number;
                DEBUG_LOG("(samdong checking)syuns[%d]=%d\n",index,syuns[index]);
                index++;
            }
        }
        
        bool two_same_num = false; // 같은 숫자 슌쯔 2개 이상 인지 먼저 확인
        int target = 0; // 같은 숫자가 나온 숫자.

        for(int i = 0; i < index - 1; i++)
        {
            for(int j = i+1; j < index; j++)
            {
                DEBUG_LOG("(samdong checking)(%d,%d)=(%d,%d)",i,j,syuns[i],syuns[j]);
                if(syuns[i] % 10 == syuns[j] % 10)
                {
                    two_same_num = true;
                    target = syuns[i] % 10;
                }
            }
        }

        // 만수 통수 삭수 존재 여부 확인용.
        bool type_exist[3] = {false, false, false};

        // 같은 숫자(target)로 슌쯔가 두 개 이상인 경우.
        if (two_same_num)
        {
            // 타겟 번호를 확인.
            for(int i = 0; i < index; i++)
            {
                // DebugLog.log($"(samdong checking)(target={target}){syuns[i]}");
                if(syuns[i] % 10 == target)
                {
                    int type = syuns[i]/10;
                    type_exist[type] = true;
                }
            }
        }

        // 같은 숫자(target)로 슌쯔가 두 개 이상있고, 해당 숫자에서 만 통 삭 다 있는 경우.
        if(type_exist[PaeType::Mansu] && type_exist[PaeType::Tongsu] && type_exist[PaeType::Saksu])
        {
            h->yakustate.samdongsun = true;
        }
        else
        {
            h->yakustate.samdongsun = false;
        }

    }//end of loop

}//end of function


// 삼색 동각
void YakuChecker::samdonggak_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{
    for(std::size_t i_=0;i_<hwaryo_list->size();i_++)
    {
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        
        // 커쯔(깡쯔)가 3개 미만인 경우 삼색동각 불가능
        int k_len = h->bCounts.keot + h->bCounts.kang;
        if(k_len < 3)
        {
            h->yakustate.samdonggak = false;
            continue;
        }
        
        // 커쯔(깡쯔)의 패 id/10
        int k[4]; // 4개의 블록 중 k_len 갯수까지만 사용.
        int index = 0;
        for(std::size_t j=0;j < h->tsu_blocks.size();j++)
        {
            TsuBlock b = h->tsu_blocks[j];
            // 자패인 경우는 넘어감.
            if(b.pae_type == PaeType::JaPae){continue;}

            // 커쯔(깡쯔)인 경우만 처리.
            if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
            {
                k[index] = b.pae_type*10 + b.number;
                DEBUG_LOG("(samdong_K checking) k[%d]=%d\n", index, k[index]);
                index++;
            }
        }
        
        bool two_same_num = false; // 같은 숫자 커쯔(깡쯔) 2개 이상 인지 먼저 확인
        int target = 0; // 같은 숫자가 나온 숫자.

        for(int i = 0; i < index - 1; i++)
        {
            for(int j = i+1; j < index; j++)
            {
                if(k[i] % 10 == k[j] % 10)
                {
                    two_same_num = true;
                    target = k[i] % 10;
                }
            }
        }

        // 만수 통수 삭수 존재 여부 확인용.
        bool type_exist[3] = {false, false, false};

        // 같은 숫자(target)로 커쯔(깡쯔)가 두 개 이상인 경우.
        if (two_same_num)
        {
            // 타겟 번호를 확인.
            for(int i = 0; i < index; i++)
            {
                if(k[i] % 10 == target)
                {
                    int type = k[i]/10;

                    type_exist[type] = true;
                }
            }
        }

        // 같은 숫자(target)로 커쯔(깡쯔)가 두 개 이상있고, 해당 숫자에서 만 통 삭 다 있는 경우.
        if(type_exist[PaeType::Mansu] && type_exist[PaeType::Tongsu] && type_exist[PaeType::Saksu])
        {
            h->yakustate.samdonggak = true;
        }
        else
        {
            h->yakustate.samdonggak = false;
        }

    }//end of loop
}//end of function