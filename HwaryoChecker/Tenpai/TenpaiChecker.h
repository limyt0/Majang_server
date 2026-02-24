#include <vector>

class Jaksadata;
class GameData;
class TenpaiInfo;

class TenpaiChecker
{
    private:
    int pae_count[38];
    bool huriten[38];// 패 종류별 후리텐
    void daegihubo_update(int daegipae_type);
    void pae_count_update(int id);
    void guksa_check();
    void chitoi_check();
    void Tenpai_sonpae_daegihubo_check(Jaksadata * jaksa);

    void huriten_init();
    void berim_huriten_update(Jaksadata * jaksa);
    void daegi_huriten_update();
    void coupled_huriten_update();
    
    public:
    bool hwapae_exist = false;
    bool guksa = false;
     
    // 대기패 후보.
    std::vector<int> daegi_hubo;
    
    // 대기패 마다 텐파이 정보 리스트 - 화료를 만들수 있는 경우만 포함.
    std::vector<TenpaiInfo> TenpaiList;
    void print_daegi_list();


    TenpaiChecker(GameData * gameData, Jaksadata * jaksa, int hwaryopae_type);
    ~TenpaiChecker();
};