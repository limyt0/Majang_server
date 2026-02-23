#include "TenpaiChecker.h"

// 국사 텐파이 체크
void TenpaiChecker::guksa_check()
{
    int count = 0;
    int indx[13] = {1,9,11,19,21,29,31,32,33,34,35,36,37};

    int daegi_guksa = 0;

    for(int i = 0; i < 13; i++)
    {
        if(pae_count[indx[i]] == 0)
        {
            daegi_guksa = indx[i];
        }
        else if(pae_count[indx[i]] == 1)
        {
            count++;
        }
        else if (pae_count[indx[i]] == 2)
        {
            count++;
        }
    }

    if(count == 12)
    {   // 국사무쌍
        daegi_hubo.push_back(daegi_guksa*10);
        guksa = true;
    }
    else if(count == 13)
    {  // 국사무쌍 13면대기
        for(int i = 0; i < 13; i++)
        {
            daegi_hubo.push_back(indx[i]*10);
            guksa = true;
        }
    }

}