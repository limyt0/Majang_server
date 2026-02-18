#include <vector>

class Jaksadata;
class HwaryoInfo;

class HwaryoChecker
{
    public:
    int * sonTil;
    // int sonTil_len_;
    std::vector<int> tsu_blocks;
    std::vector<int> hwaryo_list;

    int pae_count[38];
    bool guksa = false;
    bool hwapae_exist = false;
    bool japa_keotsu_break = false;
    bool chitoi = false;

    HwaryoChecker(Jaksadata * jaksa, int hwaryopae_type);
    ~HwaryoChecker();
    void print_tsu_blocks(std::vector<int> * b);
    std::vector<int> * get_supae_meorihubo(int * pae_count_0, int type);
    void mentsu_check(HwaryoInfo * mentsu_info);
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