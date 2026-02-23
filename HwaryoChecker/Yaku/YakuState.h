#pragma once

struct YakuState
{
    // 1판 - 도라는 따로 체크
    bool richi = false; // 리치
    bool ilbal = false; // 일발
    bool pinghu = false; // 핑후
    bool tangyao = false; // 탕야오
    bool White = false; // 백
    bool Green = false; // 발
    bool Red = false; // 중
    bool seat = false; // 자풍
    bool table = false; // 장풍
    bool ipeko = false; // 이페코
    bool menzen_tsumo = false; // 멘젠쯔모
    bool yeongsang = false; // 영상개화
    bool changkang = false; // 창깡
    bool haejeo = false; // 해저로월
    bool hajeo = false; // 하저로어

    // 2판
    bool chitoitsu = false; // 치또이쯔
    bool double_richi = false; // 더블리치
    bool ilgitonggwan = false; // 일기통관 - 판내림
    bool samdongsun = false; // 삼색동순 - 판내림
    bool samdonggak = false; // 삼색동각 (판내림 없음주의)
    bool chanta = false; // 찬타 - 판내림
    bool honnodu = false; // 혼노두
    bool sosamwon = false; // 소삼원
    bool toitoi = false; // 또이또이
    bool san_ankeo = false; // 산안커
    bool san_kangz = false; // 산깡쯔

    // 3판
    bool hon_il = false; // 혼일색 - 판내림
    bool junchanta =false; // 준찬타 - 판내림
    bool ryangpeko = false; // 량페코

    // 6판
    bool cheong_il = false; // 청일색 - 판내림

};


struct YakumanState
{
    // 역만 - (헤아림(카조에) 역만 제외)
    bool guksa = false; // 국사무쌍
    bool cheonhwa = false; // 천화
    bool jihwa = false; // 지화
    bool guryeon = false; // 구련보등
    bool nok_il = false; // 녹일색
    bool daesamwon = false; // 대삼원
    bool so_sushi = false; // 소사희
    bool cheongnodu = false; // 청노두
    bool ja_il = false; // 자일색
    bool su_ankeo = false; // 스안커
    bool su_kangz = false; // 스깡쯔
    
    // 더블 역만
    bool guksa_13 = false; // 국사무쌍 13면 대기
    bool sun_guryeon = false; // 순정구련보등
    bool dae_sushi = false; // 대사희
    bool su_ankeo_dangi = false; // 스안커 단기
};