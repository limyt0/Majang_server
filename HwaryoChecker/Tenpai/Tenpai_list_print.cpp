#include "TenpaiChecker.h"
#include "TenpaiInfo.h"
#include <iostream>
#include "../hwaryo_config.h"
#ifdef TENPAI_CHECKER_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

void TenpaiChecker::print_daegi_list()
{

    DEBUG_LOG("텐파이 대기패 : ");
    if(!tenpai){DEBUG_LOG("(텐파이 아님)");}

    if(huriten){DEBUG_LOG("(후리텐)");}

    for(int i=0;i < TenpaiList.size();i++)
    {
        DEBUG_LOG("%d(", TenpaiList[i].last_tile);
        if(TenpaiList[i].NoYaku)
        {
            DEBUG_LOG("역없음");
        }
        else
        {
            if(TenpaiList[i].yakuman_su > 0)
            {
                DEBUG_LOG("역만%d", TenpaiList[i].yakuman_su);
            }
            else
            {
                DEBUG_LOG("%d판", TenpaiList[i].pansu);
            }
        }
        DEBUG_LOG(") ");
    }
    DEBUG_LOG("\n");
}