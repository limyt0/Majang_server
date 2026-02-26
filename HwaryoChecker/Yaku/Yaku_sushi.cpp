#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef YAKU_SUSHI_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 소사희 대사희
void YakuChecker::sushi_info_update(std::vector<HwaryoInfo> * hwaryo_list)
{

    for(std::size_t i_=0;i_<hwaryo_list->size();i_++)
    {
        int _count = 0; //동남서북 다 있는지
        int men_count = 0;//동남서북 멘쯔 카운트
        HwaryoInfo * h = &(*hwaryo_list)[i_];
        for(std::size_t j_=0;j_<h->tsu_blocks.size();j_++)
        {
            TsuBlock b = h->tsu_blocks[j_];
            if(b.pae_type == PaeType::JaPae)
            {
                if(b.number == 1)
                {
                    _count++;
                    if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                    {
                        men_count++;
                    }
                }
                else if(b.number == 2)
                {
                    _count++;
                    if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                    {
                        men_count++;
                    }
                }
                else if(b.number == 3)
                {
                    _count++;
                    if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                    {
                        men_count++;
                    }
                }
                else if(b.number == 4)
                {
                    _count++;
                    if(b.tsu_type == TsuType::Keotsu || b.tsu_type == TsuType::Kangtsu)
                    {
                        men_count++;
                    }
                }
            }

        }//end of loop
        if(men_count == 4)
        {
            // 동남서북 모두 커쯔나 깡쯔인 경우
            h->yakumansate.dae_sushi = true;
        }
        else if(men_count == 3 && _count == 4)
        {
            // 동남서북 중 3개가 커쯔나 깡쯔이고, 동남서북 4종류 모두 있는 상태로 화료시.
            h->yakumansate.so_sushi = true;
        }

    }//end of loop
}