#include <vector>
#include "Enums.h"
#include <memory>

class GameUserData;
class Berims;
class HuroBlock;
class AnkanBlock;
class GameData;

class Jaksadata{
public:
    GameUserData* gameuserdata;
    std::vector<int> sonTils;
    int lastTile = -1;//쯔모 혹은 론 한 마지막 패
    std::unique_ptr<Berims> berims;
    int isRich = 0;//0: 리치아님, 1: 일반리치, 2; 더블리치
    Baram baram;// = Dong;
    std::vector<std::unique_ptr<HuroBlock>> hurolist;
    std::vector<std::unique_ptr<AnkanBlock>> ankanList;
    std::vector<int> nukilist;
    bool isSort;

    Jaksadata();
    ~Jaksadata();
    void SonPeaSort();
    void Tsumo(int tileId);
    void Berim(int index, bool isRich);
};