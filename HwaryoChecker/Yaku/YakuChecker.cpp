#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include <iostream>

void YakuChecker::Yaku_update(HwaryoInfo * hwaryo_list, int seat_wind, int table_wind, int richi_ilbal_type)
{
    printf("Yaku update\n");
    // // 삼원패 소삼원 대삼원
    // dragon_info_update(hwaryo_list);
    
    // // 자풍 장풍
    // wind_info_update(hwaryo_list, seat_wind, table_wind);
    
    // // 후로 블록수 업데이트. 슌쯔 커쯔 깡쯔를 후로 여부 구분해서 카운트 업데이트
    // bcounts_update(hwaryo_list)

    // // 핑후
    // pinghu_info_update(hwaryo_list, seat_wind, table_wind);

    // // 탕야오
    // tangyao_info_update(hwaryo_list);

    // // 이페코, 량페코.
    // peko_info_update(hwaryo_list);

    // // 일기통관
    // ilgitonggwan_info_update(hwaryo_list);

    // // 삼색 동순
    // samdongsun_info_update(hwaryo_list);

    // // 삼색 동각
    // samdonggak_info_update(hwaryo_list);

    // // 찬타, 준찬타, 혼노두, 청노두
    // chantanodu_info_update(hwaryo_list);

    // // 영상 창깡 해저 하저 천화 지화.
    // tsumo_ron_type_depended_info_update(hwaryo_list);
    
    // // 또이또이 산안커 스안커 스안커단기 산깡즈 스깡즈
    // toi_info_update(hwaryo_list);

    // // 혼일색 청일색 자일색.
    // color_info_update(hwaryo_list);

    // // 녹일색
    // nok_info_update(hwaryo_list);

    // // 소사희 대사희
    // sushi_info_update(hwaryo_list);

    // // 멘젠 쯔모
    // menzen_tsumo_info_update(hwaryo_list);

    // // 리치, 더블리치, 일발
    // rich_ilbal_info_update(hwaryo_list, int richi_ilbal_type);

}



// static void YakuChecker::guksa(std::vector<HwaryoInfo> * hwaryo_list,  int * pae_count, int last_tile, int hwaryo_tile_type)
// {
//     int sum = 0;
//     bool guksa_possible = true;
    
//     if (pae_count[1] > 0){sum += pae_count[1];}else{guksa_possible = false;}
//     if (pae_count[9] > 0){sum += pae_count[9];}else{guksa_possible = false;}
//     if (pae_count[11] > 0){sum += pae_count[11];}else{guksa_possible = false;}
//     if (pae_count[19] > 0){sum += pae_count[19];}else{guksa_possible = false;}
//     if (pae_count[21] > 0){sum += pae_count[21];}else{guksa_possible = false;}
//     if (pae_count[29] > 0){sum += pae_count[29];}else{guksa_possible = false;}

//     for(int i = 31; i <= 37; i++)
//     {
//         if (pae_count[i] > 0){sum += pae_count[i];}
//         else{guksa_possible = false;}
//     }

//     if(sum == 14 && guksa_possible)
//     {           
//         TsuBlock tsuBlock;// = new TsuBlock();
//         std::vector<TsuBlock> tsu_blocks;// = new std::vector<TsuBlock>();
//         tsuBlock.tsu_type = TsuType.Guksa;

//         tsu_blocks.push_back(tsuBlock);
//         HwaryoInfo h(&tsu_blocks, pae_count);
//         if (pae_count[last_tile / 10] == 2)
//         {
//             printf("guksa 13 updating...");
//             h.yakumansate.guksa_13 = true;
//             h.hwaryo_pae_type = hwaryo_pae_type;
//             h.last_tile = last_tile;
//             if(hwaryo_pae_type == HwaryoPaeType.CheonHwa)
//             {h.yakumansate.cheonhwa = true;}
//             else if(hwaryo_pae_type == HwaryoPaeType.JiHwa)
//             {h.yakumansate.jihwa = true;}
            
//         }
//         else
//         {
//             printf("guksa updating...");
//             h.yakumansate.guksa = true;
//             h.daegistate.Dangi = true;
//             h.hwaryo_pae_type = hwaryo_pae_type;
//             h.last_tile = last_tile;
//             if(hwaryo_pae_type == HwaryoPaeType.CheonHwa)
//             {h.yakumansate.cheonhwa = true;}
//             else if(hwaryo_pae_type == HwaryoPaeType.JiHwa)
//             {h.yakumansate.jihwa = true;}
//         }
//         hwaryo_list.push_back(h);
//     }
// }
