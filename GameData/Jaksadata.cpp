#include "GameData.h"
#include "Jaksadata.h"
#include <algorithm>
#include "PeaAndBlock/Berims.h"
#include "PeaAndBlock/HuroBlock.h"
#include "PeaAndBlock/AnkanBlock.h"

Jaksadata::Jaksadata()
{
    isSort = false;
    auto berims = std::make_unique<Berims>();

}
Jaksadata::~Jaksadata()
{
    
}

void Jaksadata:: SonPeaSort()    
{
    if(isSort)
    {
        sort(sonTils.begin(), sonTils.end());
    }
}

//패를 먹음
void Jaksadata::Tsumo(int tileId)
{
    lastTile = tileId;
    //먹은 직후 패산쯔모, 영상, 해저, 천화, 지화.-> 쯔모화료체크 및 안깡/가깡/빼기 가능 여부 체크+_버림패별 텐파이체크, 버림별 후리텐 및 갯수체크, 구종구패 체크
}

void Jaksadata::Berim(int index, bool isRich)
{
    int target = sonTils[index];
    berims->berimBeas.push_back(target);
    if(isRich) berims->richindex = berims->berimBeas.size();
    sonTils.erase(sonTils.begin()+index);
    sonTils.push_back(lastTile);
}