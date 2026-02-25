#include "../Yaku/YakuState.h"
#include "../Consts_hwaryo.h"
#include "../Tsublock.h"
#include <vector>

class HwaryoChecker;
class TenpaiBlock_list;

class TenpaiInfo
{
    public:

    int last_tile = 0;    // 대기패.
    bool huriten = false; // 후리텐여부.
    bool NoYaku = false; // 역없음여부.

    bool yang = false; // 양면대기 여부 - 후리텐 체크용.
    bool syabo = false; // 샤보대기 여부 - 후리텐 체크용.

    int yakuman_su = 0; // 0 역만 아님 | 1 역만 | 2 더블역만 | 3 트리플 역만 ...
    int pansu = 0; // 판수
    // 여러 역 상태.
    YakuState yakustate;
    // 역만 상태.
    YakumanState yakumansate;
    // // 같은 대기패에 대한 블록형태 경우의 수.
    // std::vector<TenpaiBlock_list> tenpaiBlock_list;
    // // 블록 형태중 제일 판수가 높은 블록형태
    // TenpaiBlock_list * best;

    // TenpaiInfo();
    TenpaiInfo(HwaryoChecker * hwaryoChecker, int daegi_pae);
    ~TenpaiInfo();

};

// class TenpaiBlock_list
// {
//     public:
//     std::vector<TsuBlock> tsu_blocks;
//     Daegistate daegistate;

//     int yakuman_su = 0; // 0 역만 아님 | 1 역만 | 2 더블역만 | 3 트리플 역만 ...
//     int pansu = 0; // 판수
//     // 여러 역 상태.
//     YakuState yakustate;
//     // 역만 상태.
//     YakumanState yakumansate;
// };