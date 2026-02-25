#include <vector>

class Jaksadata;
class GameData;
class TenpaiInfo;

class TenpaiChecker
{
    private:
    int pae_count[38];
    bool huri[38];// 버린패. 후리텐 체크용.
    
    // ---- 후리텐을 잘못 이해해서 있었던 변수 ---
    // bool syabo_huriten[38]; // 샤보 후리텐
    // bool yang_huriten[38]; // 양면에 의한 후리텐. 로직상 bound error를 피하기위해서 31~37영역도 정의.

    void daegihubo_update(int daegipae_type);
    void pae_count_update(int id);
    void guksa_check();
    void chitoi_check();
    void Tenpai_sonpae_daegihubo_check(Jaksadata * jaksa);

    void huri_init();// 버린패 false로 초기화
    void berim_huri_update(Jaksadata * jaksa);
    void daegi_huriten_update();

    // ---- 후리텐을 잘못 이해해서 있었던 함수 ---
    // void coupled_huriten_update();
    // void guksa13_daegi_huriten_update();
    // void guryeon9_daegi_huriten_update();
    // void syabo_huriten_update();
    // void yang_huriten_update();

    void print_huri_array();
    
    public:
    bool hwapae_exist = false;
    bool guksa = false;
    bool tenpai = false;//텐파이 여부
    bool huriten = false;//후리텐여부.

    // 대기패 후보.
    std::vector<int> daegi_hubo;
    
    // 대기패 마다 텐파이 정보 리스트 - 화료를 만들수 있는 경우만 포함.
    std::vector<TenpaiInfo> TenpaiList;
    void print_daegi_list();


    TenpaiChecker(GameData * gameData, Jaksadata * jaksa, int hwaryopae_type);
    ~TenpaiChecker();
};