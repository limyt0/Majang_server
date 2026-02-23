#include <vector>

class Jaksadata;
class GameData;
class TenpaiInfo;

class TenpaiChecker
{
    private:
    int pae_count[38];
    void daegihubo_update(int daegipae_type);
    void pae_count_update(int id);
    void guksa_check();
    void chitoi_check();
    void Tenpai_sonpae_daegihubo_check(Jaksadata * jaksa);
    
    public:
    bool hwapae_exist = false;
    bool guksa = false;
     
    // 대기패 후보.
    std::vector<int> daegi_hubo;
    
    // 대기패 마다 텐파이 정보 리스트 - 화료를 만들수 있는 경우만 포함.
    std::vector<TenpaiInfo> TenpaiList;

    TenpaiChecker(GameData * gameData, Jaksadata * jaksa, int hwaryopae_type);
    ~TenpaiChecker();
};