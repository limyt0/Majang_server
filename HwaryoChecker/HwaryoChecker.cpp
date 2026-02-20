#include "HwaryoChecker.h"
#include "Jaksadata.h"
#include <iostream>
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"

HwaryoChecker::HwaryoChecker(Jaksadata * jaksa, int hwaryopae_type){

    printf("화료체크 시작\n");

    // 손패에서 화료 형태를 체크.
    Hwaryo_check_sonpae(jaksa, hwaryopae_type);
 
    // 쯔모패, 대기 정보 업데이트
    YakuChecker::info_update(&hwaryo_list, jaksa->lastTile, hwaryopae_type);

    printf("쯔모패, 대기 정보 업데이트 이후\n");
    for(int i=0;i<hwaryo_list.size();i++)
    {
        hwaryo_list[i].print_info();
    }

}

HwaryoChecker::~HwaryoChecker()
{

}



