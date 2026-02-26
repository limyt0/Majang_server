#include "YakuChecker.h"
#include "../HwaryoInfo.h"
#include <iostream>
#include "Jaksadata.h"
#include "GameData.h"
#include "../hwaryo_config.h"
#ifdef YAKU_CHECKER_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif


void YakuChecker::yaku_update(std::vector<HwaryoInfo> * hwaryo_list, Jaksadata * jaksa, GameData * game_data)
{
    
    int seat_wind = jaksa->baram + 1;
    int table_wind = game_data->nowTableBaram + 1;
    int richi_type = jaksa->isRich;
    bool is_ilbal = jaksa->isIlbal;

    DEBUG_LOG("Yaku update\n");
    // 삼원패 소삼원 대삼원
    dragon_info_update(hwaryo_list);
    DEBUG_LOG("dragon updated\n");
    
    // 자풍 장풍
    wind_info_update(hwaryo_list, seat_wind, table_wind);
    DEBUG_LOG("wind updated\n");
    
    // 후로 블록수 업데이트. 슌쯔 커쯔 깡쯔를 후로 여부 구분해서 카운트 업데이트
    bcounts_update(hwaryo_list);
    DEBUG_LOG("bcounts updated\n");

    // 핑후
    pinghu_info_update(hwaryo_list, seat_wind, table_wind);
    DEBUG_LOG("pinghu updated\n");

    // 탕야오
    tangyao_info_update(hwaryo_list);
    DEBUG_LOG("tangyao updated\n");

    // 이페코, 량페코.
    peko_info_update(hwaryo_list);
    DEBUG_LOG("peko updated\n");

    // 일기통관
    ilgitonggwan_info_update(hwaryo_list);
    DEBUG_LOG("ilgitong updated\n");

    // 삼색 동순
    samdongsun_info_update(hwaryo_list);
    DEBUG_LOG("samdongsun updated\n");

    // 삼색 동각
    samdonggak_info_update(hwaryo_list);
    DEBUG_LOG("samdonggak updated\n");

    // 찬타, 준찬타, 혼노두, 청노두
    chantanodu_info_update(hwaryo_list);
    DEBUG_LOG("chantanodu updated\n");

    // 영상 창깡 해저 하저 천화 지화.
    tsumo_ron_type_depended_info_update(hwaryo_list);
    DEBUG_LOG("tsumo_ron_type_depended_info updated\n");

    // 또이또이 산안커 스안커 스안커단기 산깡즈 스깡즈
    toi_info_update(hwaryo_list);
    DEBUG_LOG("toi_ankeo_info updated\n");

    // 혼일색 청일색 자일색.
    color_info_update(hwaryo_list);
    DEBUG_LOG("color updated\n");

    // 녹일색
    nok_info_update(hwaryo_list);
    DEBUG_LOG("nok updated\n");

    // 소사희 대사희
    sushi_info_update(hwaryo_list);
    DEBUG_LOG("sushi updated\n");

    // 멘젠 쯔모
    menzen_tsumo_info_update(hwaryo_list);
    DEBUG_LOG("menzen_tsumo_info updated\n");

    // 리치, 더블리치, 일발
    rich_ilbal_info_update(hwaryo_list, richi_type, is_ilbal);
    DEBUG_LOG("rich_ilbal_info updated\n");

}
