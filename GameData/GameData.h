//#include <string>
#include <vector>
//#include "GameUserData.h"

class Jaksadata;

enum Baram
{
    Dong = 0,
    Nam = 1,
    Seo = 2,
    Buk = 3
};


class GameData{
public:
  int nowTurnJaksaIndex = 0;//현재 누구 차례인지
  std::vector<Jaksadata*> jaksas; //참가 작사들. 들어간 순서대로 차례임
  int Oyaindex = 0; // 현재 동이 누구인지
  Baram nowTableBaram = Dong;//현재 장풍
  std::vector<int> peasan; //패산 정보
  std::vector<int> wangpae; //도라표시패, 도라표시패아래, 영상패.(고정)
  std::vector<int> doras_omote; //앞 도라들 열릴때마다 추가
  std::vector<int> doras_ura;//뒷도라들 열릴때 마다 추가
  bool isLastTurn;//마지막 차례 체크해서 해저/하저체크용
  bool isSunOneturn;//순정 1순인지 체크해서 천화/지화 체크용.+ 더블리치 체크용+사풍연타+구종구패
  bool isFourKangs; //사깡여부 체크S
  int remainTiles; //남은 패산 패 갯수
};

// class Constants
// {
//     public const int TsumoLen = 13;
//     public const int WangPaeLen = 14;
//     public const int PeasanLen = 144;
//     public const int WangDoraLen = 10;
//     public const int YeongSangLen = 4;
// }



//후로 한덩어리
class HuroBlcck {
public:
    float startpos;//배치하는 시작 위치
    std::vector<int> tiles;
    int index;//몇번째를 옆으로 꺾을 것인가
};
class AnkanBlcok { 
public:
    float startpos;
    std::vector<int> tiles;
};

class Berims
{
public:
    std::vector<int> berimBeas; //버린패들
    std::vector<int> behurod;//내가 버린거 남이 후로해간거. 버린패에서 제외필요.
    int richindex = -1;//리치했을때 위치 없으면 -1
};
