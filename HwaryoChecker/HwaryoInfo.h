#pragma once
#include <vector>
#include "Yaku/YakuState.h"
#include "Consts_hwaryo.h"
#include "Tsublock.h"

// class TsuBlock;
// struct Daegistate;

class HwaryoInfo
{
    public :
    std::vector<TsuBlock> tsu_blocks;
    int pae_count[38];
    bool block_possible = false;

    // 쯔모패 대기 상태.
    Daegistate daegistate;
    int last_tile = 0;
    int hwaryo_pae_type = 0;

    BCounts bCounts;

    // 여러 역 상태.
    YakuState yakustate;
    // 역만 상태.
    YakumanState yakumansate;

    // 도라 정보 (도라, 뒷도라, 적도라)
    DoraCount doraCount;

    // n배 역만상태, 판수, 부수, 오야여부
    // ScoreComponent scoreComponent = new ScoreComponent();

    HwaryoInfo(std::vector<TsuBlock> tsu_blocks_, int * pae_count_);
    ~HwaryoInfo();
    void print_info(bool block, bool hwaryo_tile, bool daegi, bool yaku, bool dora);
    
};
