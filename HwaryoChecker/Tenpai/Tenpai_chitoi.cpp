#include "TenpaiChecker.h"
#include <iostream>
// 또이쯔 갯수가 6개면 치또이쯔 텐파이.
// 겹칠 수 있는 량페코 텐파이 여부는 이미 체크되었다고 가정.
void TenpaiChecker::chitoi_check()
{
    int toitsu_count = 0;
    int daegi_index = 0;
    for(int i = 1; i <= 37; i++)
    {
        if(pae_count[i] == 2)
        {
            toitsu_count++;
        }
        else if(pae_count[i] == 1)
        {
            daegi_index = i;
        }
    }

    // 치또이쯔 텐파이 or 량페코 텐파이인 경우
    if(toitsu_count == 6)
    {
        // 이미 대기후보에 있으면 추가하지 않음.
        bool need_add = true;

        for(int i=0;i<daegi_hubo.size();i++)
        {
            if(daegi_hubo[i]/10 == daegi_index){need_add = false;}
        }
        
        // 이미 대기패 후보에 있으면 추가하지 않음.
        // 그 외 추가해야하는 경우에는 추가.
        if(need_add){
            printf("-----------daegi_pae type --- = %d chitoi\n", daegi_index);
            daegi_hubo.push_back(daegi_index*10);
        }
    }

}