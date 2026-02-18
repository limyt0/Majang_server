#include <vector>
#include <string>
#include "GameData.h"

class GameUserData{
public:
  int pk_id;
  std::string name;
};

class Jaksadata{
public:
    GameUserData gameuserdata;
    std::vector<int> sonTils;
    int lastTile = -1;//쯔모 혹은 론 한 마지막 패
    Berims berims;
    int isRich = 0;//0: 리치아님, 1: 일반리치, 2; 더블리치
    Baram baram = Dong;
    std::vector<HuroBlcck> hurolist;
    std::vector<AnkanBlcok> ankanList;
    std::vector<int> nukilist;
}