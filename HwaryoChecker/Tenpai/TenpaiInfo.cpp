#include "TenpaiInfo.h"
#include "../HwaryoInfo.h"
#include "../hwaryo_config.h"
#ifdef TENPAI_INFO_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)    
#endif

// 기본 생성자 : 역없음 텐파이에서 사용.
TenpaiInfo::TenpaiInfo(){}

// 역이 있는 텐파이의 경우 화료 정보 추가
TenpaiInfo::TenpaiInfo(HwaryoInfo * hwaryo_info)
{
    last_tile = hwaryo_info->last_tile;// 대기패.
    // huriten = false; // 후리텐여부.
    // NoYaku = false; // 역없음여부.
    
    // 해석가능한 역 중에서 판수가 가장 높은 역 정보 저장
    // HwaryoInfo hwaryo_info;

    // 0 역만 아님 | 1 역만 | 2 더블역만 | 3 트리플 역만 ...
    yakuman_su = hwaryo_info->scoreComponent.yakuman_su;

    // 판수
    pansu +=  hwaryo_info->scoreComponent.pansu;
    pansu +=  hwaryo_info->scoreComponent.dora_pansu;
    
    // 여러 역 상태.
    yakustate = hwaryo_info->yakustate;
    
    // 역만 상태.
    yakumansate = hwaryo_info->yakumansate;
}

TenpaiInfo::~TenpaiInfo(){}