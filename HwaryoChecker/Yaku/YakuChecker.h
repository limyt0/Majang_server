#include <vector>
class HwaryoInfo;
class GameData;
class Jaksadata;

class YakuChecker
{
    private:
    
    static void LastTile_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile);
    static void Daegi_info_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile);
    static void hwaryopae_type_update(std::vector<HwaryoInfo> * hwaryo_list, int type);

    public:
    // 쯔모/론 패, 대기 정보, 론 쯔모 여부 업데이트
    static void info_update(std::vector<HwaryoInfo> * hwaryo_list, int LastTile, int type);

    static void Print_yaku(HwaryoInfo *);

    // 다양한 역을 체크해서 정보 업데이트
    static void yaku_update(std::vector<HwaryoInfo> * hwaryo_list, Jaksadata * jaksa, GameData * game_data);

    // 삼원패 소삼원 대삼원
    static void dragon_info_update(std::vector<HwaryoInfo> * hwaryo_list);
    
    // 자풍 장풍
    static void wind_info_update(std::vector<HwaryoInfo> * hwaryo_list, int seat_wind, int table_wind);
    
    // 후로 블록수 업데이트. 슌쯔 커쯔 깡쯔를 후로 여부 구분해서 카운트 업데이트
    static void bcounts_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 핑후
    static void pinghu_info_update(std::vector<HwaryoInfo> * hwaryo_list, int seat_wind, int table_wind);

    // 탕야오
    static void tangyao_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 이페코, 량페코.
    static void peko_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 일기통관
    static void ilgitonggwan_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 삼색 동순
    static void samdongsun_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 삼색 동각
    static void samdonggak_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 찬타, 준찬타, 혼노두, 청노두
    static void chantanodu_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 영상 창깡 해저 하저 천화 지화.
    static void tsumo_ron_type_depended_info_update(std::vector<HwaryoInfo> * hwaryo_list);
    
    // 또이또이 산안커 스안커 스안커단기 산깡즈 스깡즈
    static void toi_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 혼일색 청일색 자일색.
    static void color_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 녹일색
    static void nok_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 소사희 대사희
    static void sushi_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 멘젠 쯔모
    static void menzen_tsumo_info_update(std::vector<HwaryoInfo> * hwaryo_list);

    // 리치, 더블리치, 일발
    static void rich_ilbal_info_update(std::vector<HwaryoInfo> * hwaryo_list, int richi_type, bool is_ilbal);

    // 국사무쌍
    static void guksa(std::vector<HwaryoInfo> * ,  int * , int , int );

    // 구련보등
    static void guryeon(std::vector<HwaryoInfo> * , int* , int , int );

    // 치또이쯔
    static void chitoitsu_checker(std::vector<HwaryoInfo> *, int *, bool *);

    // 도라
    static void dora_info_update(std::vector<HwaryoInfo> *, Jaksadata *, GameData *);

    // 판수 계산
    static void yaku_su_update(std::vector<HwaryoInfo> *hwaryo_list);
};