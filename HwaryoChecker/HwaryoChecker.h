#include <vector>
#include "HwaryoInfo.h"
#include "Tsublock.h"

class Jaksadata;
class HwaryoInfo;
class TsuBlock;
class GameData;

class HwaryoChecker
{
    public:
    int * sonTil;
    // int sonTil_len_;
    std::vector<TsuBlock> tsu_blocks;
    std::vector<HwaryoInfo> hwaryo_list;

    int pae_count[38];
    bool gu = false;// 국사무쌍/구련보등 우선 체크
    bool hwapae_exist = false;
    bool japa_keotsu_break = false;
    bool chitoi = false;

    HwaryoChecker(GameData * game_data, Jaksadata * jaksa, int hwaryopae_type);
    ~HwaryoChecker();

    // 손패에서 화료형태가 나오는지 체크
    void Hwaryo_check_sonpae(Jaksadata * jaksa, int hwaryopae_type);

    // 손패 화료 형태 체크 이후 후로/안깡 블록을 추가
    void HuroAnkan_To_TsuBlock(Jaksadata * jaksa);
    
    // 보조 함수.
    void print_tsu_blocks(std::vector<TsuBlock> b);
    std::vector<int> get_supae_meorihubo(int type);
    void block_check(HwaryoInfo );
    int get_smallest_index(int * pae_count_0);
    int pae_sum(int * pae_count);
    void print_blocks();
    void print_blocks_list();
    void japae_keotsu_update();
    void japae_meori_update(int pae_type);
    int get_meori_type();
    int array_sum(int * ints, int start_index, int last_index);
    void pae_count_update(int id);

};