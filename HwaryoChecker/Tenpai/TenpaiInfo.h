#include "../Yaku/YakuState.h"

class HwaryoInfo;

class TenpaiInfo
{
    public:

    int last_tile = 0;    // 대기패.
    bool huriten = false; // 후리텐여부.
    bool NoYaku = false; // 역없음여부.
    
    // 해석가능한 역 중에서 판수가 가장 높은 역 정보 저장
    // HwaryoInfo hwaryo_info;
    int yakuman_su = 0; // 0 역만 아님 | 1 역만 | 2 더블역만 | 3 트리플 역만 ...
    int pansu = 0; // 판수
    // 여러 역 상태.
    YakuState yakustate;
    // 역만 상태.
    YakumanState yakumansate;

    TenpaiInfo();
    TenpaiInfo(HwaryoInfo * hwaryo_info);
    ~TenpaiInfo();

};