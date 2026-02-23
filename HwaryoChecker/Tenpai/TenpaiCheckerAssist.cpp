#include <vector>
#include "TenpaiChecker.h"
#include "../Consts_hwaryo.h"
#include <iostream>
#include "../hwaryo_config.h"
#ifdef TENPAI_CHECKER_ASSIST_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

void TenpaiChecker::daegihubo_update(int daegipae_type)
{
    DEBUG_LOG("daegihubo_update\n");
    if(daegipae_type == PaeType::JaPae)
    {
        DEBUG_LOG("대기패 타입 : 자패\n");
        // 대기패가 자패인 경우 - 자패 머리 단기 혹은 자패 사보대기
        for(int i = 31; i < 38; i++)
        {
            if(pae_count[i] == 1 || pae_count[i] == 2)
            {
                DEBUG_LOG("대기패 추가 %d\n", i*10);
                daegi_hubo.push_back(i*10);
            }
        }
    }
    else
    {
        DEBUG_LOG("대기패 타입 = %d\n", daegipae_type);
        // 대기패가 수패인 경우
        int offset = daegipae_type*10;
        int start = offset + 2;
        int end = offset + 8;
        bool hubo[10] = {false, false,false,false, false,false,false, false,false,false};//편의상 10개로
        
        DEBUG_LOG("checking syun\n");
        // 슌쯔 후보. (123 234 345 456 567 789)
        for(int i = start; i <= end; i++)
        {
            DEBUG_LOG("--checking %d\n",i);
            // 대기패는 4개에서 더 넣으면 안됨.
            if(pae_count[i -1] > 0 && pae_count[i] > 0 && pae_count[i+1] !=4)
            {
                hubo[i%10 + 1] = true;
                DEBUG_LOG("hubo %d\n", i%10 + 1);
            }
            if(pae_count[i -1] > 0 && pae_count[i] != 4 && pae_count[i+1] > 0)
            {
                hubo[i%10] = true;
                DEBUG_LOG("hubo %d\n",i%10);
            }
            if(pae_count[i -1] != 4 && pae_count[i] > 0 && pae_count[i+1] > 0)
            {
                hubo[i%10 - 1] = true;
                DEBUG_LOG("hubo %d\n", i%10 - 1);

            }
        }

        start = offset + 1;
        end = offset + 9;
        DEBUG_LOG("checking k m\n");
        // 커쯔 or 머리 후보
        for(int i = start; i <= end; i++)
        {
            // DebugLog.log($"--checking {i}");
            if(pae_count[i] > 0 && pae_count[i] < 4)
            {
                hubo[i%10] = true;
            }
        }

        DEBUG_LOG("hubo list update\n");
        // 대기패 후보 리스트 업데이트.
        for(int i = 1; i <= 9; i++)
        {
            if (hubo[i])
            {
                int target = daegipae_type*100 + i*10;
                daegi_hubo.push_back(target);
                // DebugLog.log($"daegipae add {target}"); 
            }
        }

    }
}


void TenpaiChecker::pae_count_update(int id)
{
    // Pae pea = new Pae();
    int pae_type = id/100;
    int index = id / 10;
    if (pae_type == PaeType::Hwapae)
    {
        hwapae_exist = true;
    }
    else
    {
        pae_count[index] += 1;        
    }
}