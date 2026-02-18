#include <vector>
#include "Enums.h"

class GameUserData;
class Berims;
class HuroBlock;
class AnkanBlock;

class Jaksadata{
public:
    GameUserData* gameuserdata;
    std::vector<int> sonTils;
    int lastTile = -1;//쯔모 혹은 론 한 마지막 패
    Berims* berims;
    int isRich = 0;//0: 리치아님, 1: 일반리치, 2; 더블리치
    Baram baram;// = Dong;
    std::vector<HuroBlock*> hurolist;
    std::vector<AnkanBlock*> ankanList;
    std::vector<int> nukilist;

    Jaksadata();
    ~Jaksadata();
};