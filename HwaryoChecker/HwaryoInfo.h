#include <vector>

class HwaryoInfo
{
    public :
    std::vector<int> tsu_blocks;
    int pae_count[38];
    bool block_possible = false;

    // 쯔모패 대기 상태.
    // Daegistate daegistate = new Daegistate();
    int tsumopae = 0;
    int hwaryo_pae_type = 0;

    // 삼원패 역 정보
    // public YakuHai yakuHai = new YakuHai();

    // BCounts bCounts = new BCounts();
    // public int huro_count = 0;

    // 여러 역 상태.
    // Yakustate yakustate = new Yakustate();
    // 역만 상태.
    // Yakumansate yakumansate = new Yakumansate();

    // 도라 정보 (도라, 뒷도라, 적도라)
    // DoraCount doraCount = new DoraCount();

    // n배 역만상태, 판수, 부수, 오야여부
    // ScoreComponent scoreComponent = new ScoreComponent();

    HwaryoInfo(std::vector<int> * tsu_blocks_, int * pae_count_);
    void print_info();
    
};
