#include <vector>
#include "TenpaiChecker.h"
#include "GameData/Jaksadata.h"
#include <iostream>
#include "../hwaryo_config.h"
#ifdef TENPAI_SONPAE_CHECK_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif
// 텐파이 유형
// 1. 국사 무쌍 머리 대기
// 2. 국사 무쌍 13면 대기
// 3. (2 2 2 2 2 2 1) 치또이쯔
// 4. (3 3 3 3 1) 머리 단기 대기 -> 1이 한개.
//  -> 만/통/삭/자패(mod 3) 하나만 1이어야 함.
// 5. (3 3 3 2 2) 양면, 변짱, 간짱, 샤보 대기
//  5-1. -> 만/통/삭/자패(mod 3) (2 2 0 0) - 2가 2개 - 둘중 하나가 머리여야 함.
//  5-1. -> 만/통/삭/자패(mod 3) (1 0 0 0) - 1이 1개 - 머리가 1에 있어야 함.

void TenpaiChecker::Tenpai_sonpae_daegihubo_check(Jaksadata * jaksa)
{
    for(int i=0;i<38;i++){pae_count[i] = 0;}

    int sonpae_len = jaksa->sonTils.size();

    for(int i = 0; i < sonpae_len; i++){
        pae_count_update(jaksa->sonTils[i]);
    }

    // 화패가 있는 경우 텐파이 불가.
    if(hwapae_exist){return;}

    // 국사무쌍 예외 처리 먼저 해야 함.
    // 국사 무쌍 따로 체크해야 하는 이유.
    // 1. 만.통.삭.자.(3 2 2 7) 화료 시
    //    1-1. 만.통.삭.자.(2 2 2 7) 텐파이 = (2 2 2 1)
    //    1-2. 만.통.삭.자.(3 1 2 7) 텐파이 = (0 1 2 1)
    //    1-3. 만.통.삭.자.(3 2 2 6) 텐파이 = (0 2 2 0) -> 0 부분에 화료패있음.
    // 2. 만.통.삭.자.(2 2 2 8) 화료 시
    //    2-1. 만.통.삭.자.(1 2 2 8) 텐파이 = (1 2 2 2)
    //    2-1. 만.통.삭.자.(2 2 2 7) 텐파이 = (2 2 2 1)
    guksa_check();
    if(guksa){return;}// 국사무쌍 or 국사무쌍13면대기 -> 바로 리턴.
    
    // 치또이쯔 텐파이이의 경우, 먼저 처리하지 않고, 뒤에서 처리
    // (량페코 + 치또이쯔) -> 량페코로 해석하는 경우 주의.
    
    int type_wise_count[4] = {0,0,0,0};
    // 만.통.삭.자패 각각 몇장씩 있는지 저장.
    for(int i = 0; i < sonpae_len; i++)
    {
        int pae_type = jaksa->sonTils[i]/100;
        type_wise_count[pae_type] += 1;
    }

    DEBUG_LOG("type_wise count ");
    DEBUG_LOG("%d ", type_wise_count[0]);
    DEBUG_LOG("%d ", type_wise_count[1]);
    DEBUG_LOG("%d ", type_wise_count[2]);
    DEBUG_LOG("%d\n", type_wise_count[3]);
    
    int mod3_count[3] = {0,0,0};
    // 3으로 나눈 나머지가 몇개씩 있는지 확인.
    for(int i = 0; i < 4; i++)
    {
        mod3_count[type_wise_count[i] % 3] += 1;
        DEBUG_LOG("mod3_count[%d] += 1\n", type_wise_count[i] % 3);
        DEBUG_LOG("(checking)mod 3 count %d %d %d\n", mod3_count[0], mod3_count[1], mod3_count[2]);
    }
    DEBUG_LOG("mod 3 count %d %d %d\n", mod3_count[0], mod3_count[1], mod3_count[2]);

    if(mod3_count[1] == 1 && mod3_count[0] == 3)
    {
        // 둘 중 하나.
        // 1. 머리 단기 텐파이 후보인 경우
        // 2. 완성된 머리와 대기패가 같은 패유형(만.통.삭.자)인 경우
        //      (완성머리(2) + 샤보/간짱/변짱/양면(2) = 1(mod 3))
        // 즉, 갯수가 1(mod3)인 패유형(만.통.삭.자)에 대기패가 있어야 함.
        
        // 대기패 유형(만.통.삭.자) 확인.
        for(int i = 0; i < 4; i++)
        {
            if(type_wise_count[i] % 3 == 1){
                // i == 대기패 유형(만.통.삭.자.)
                DEBUG_LOG("-----------daegi_pae type --- = %d(1 mod 3)\n", i);
                daegihubo_update(i);
            }
        }
        
    }
    else if(mod3_count[2] == 2 &&  mod3_count[0] == 2)
    {
        // 완성된 머리와 대기패가 다른 패유형(만.통.삭.자)
        // 갯수가 2(mod2)인 패유형에 대기패가 있어야 함.
                    // 대기패 유형(만.통.삭.자) 확인.
        for(int i = 0; i < 4; i++)
        {
            if(type_wise_count[i] % 3 == 2){
                // i == 대기패 유형(만.통.삭.자.)
                DEBUG_LOG("-----------daegi_pae type --- = %d(2 mod 3)\n", i);
                daegihubo_update(i);
            }
        }
    }
    
    // 치또이쯔를 체크하고 업데이트.
    chitoi_check();

    // std::string hubo_string = "";
    // foreach(int d in daegi_hubo)
    DEBUG_LOG("대기 후보 - ");
    for(std::size_t i=0;i< daegi_hubo.size();i++)
    {
        // hubo_string += $" {d}";
        DEBUG_LOG(" %d", daegi_hubo[i]);
    }
    DEBUG_LOG("\n");
}