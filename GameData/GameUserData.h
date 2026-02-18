#include <vector>
#include "GameData.h"

class GameUserData{
public:
  int pk_id;
  std::string name;
}

class Jaksadata{
public:
    GameUserData gameuserdata;
    vector<int> sonTils;
    int lastTile = -1;//쯔모 혹은 론 한 마지막 패
    Berims berims;
    int isRich = 0;//0: 리치아님, 1: 일반리치, 2; 더블리치
    Baram baram = Baram.Dong;
    vector<HuroBlcck> hurolist;
    vector<AnkanBlcok> ankanList;
    vector<int> nukilist;
}