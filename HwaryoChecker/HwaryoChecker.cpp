#include "HwaryoChecker.h"
#include "Jaksadata.h"
#include <iostream>
#include "Consts_hwaryo.h"
#include "Yaku/YakuChecker.h"

HwaryoChecker::HwaryoChecker(Jaksadata * jaksa, int hwaryopae_type){

    printf("test11\n");

    sonTil = &jaksa->sonTils[0];

    int last_tile = jaksa->lastTile;

    // 손패 갯수 -> 값이 1, 4, 7, 10, 13 만 가능해야 함.
    int sonTil_len = jaksa->sonTils.size();

    // tsu_blocks = new std::vector<TsuBlock>();
    // hwaryo_list = new std::vector<HwaryoInfo>();
    // pae_count = new int[38];
    for(int i=0;i<38;i++){
        pae_count[i] = 0;
    }

    for(int i = 0; i < sonTil_len; i++){
        pae_count_update(sonTil[i]);
    }
        
    pae_count_update(last_tile);

    // 화패가 있는 경우 화료 안됨. 바로 리턴.
    if(hwapae_exist){return;}

    printf("guksa check srart\n");
    // 국사무쌍 체크 (바로 리턴)
    YakuChecker::guksa(&hwaryo_list, pae_count, last_tile, hwaryopae_type);
    if(hwaryo_list.size() > 0){gu = true;return;}
    printf("guksa check end\n");

    printf("guryeon check srart\n");
    // 구련보등 체크 (바로 리턴) - 청일색의 상위역이지만 로직 편의상 여기서 먼저 체크.
    YakuChecker::guryeon(&hwaryo_list, pae_count, last_tile, hwaryopae_type);
    if(hwaryo_list.size() > 0){gu = true;return;}
    printf("guryeon check end\n");

    // 치또이쯔 체크 
    // 량페코로 해석될 수 있는 부분은 뒤에서 체크.
    // 뒤에 있는 자패 커쯔 체크 로직 때문에 먼저 체크하고 bool chitoi = true로 변경해야함.
    YakuChecker::chitoitsu_checker(&hwaryo_list, pae_count, &chitoi);


}

HwaryoChecker::~HwaryoChecker()
{

}


void HwaryoChecker::pae_count_update(int id)
{
    int pae_type = id/100;
    int index = id / 10;
    if (pae_type == PaeType::Hwapae)
    {
        hwapae_exist = true;
    }
    else
    {
        pae_count[index] += 1;
        // printf("(paecount)%d updated!\n", index);
    }

}
