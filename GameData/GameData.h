#include <string>
#include <vector>
#include "Enums.h"
#include <memory>
#include <chrono>

class Jaksadata;

class GameData{
public:
  int nowTurnJaksaIndex = 0;//현재 누구 차례인지
  std::vector<std::unique_ptr<Jaksadata>> jaksas; //참가 작사들. 들어간 순서대로 차례임
  int Oyaindex = 0; // 현재 동이 누구인지
  Baram nowTableBaram = Dong;//현재 장풍
  int nowGuk = 0;//몇국
  int nowBonJang = 0;//본장
  std::vector<int> peasan; //패산 정보
  std::vector<int> wangpae; //도라표시패, 도라표시패아래, 영상패.(고정)
  std::vector<int> doras_omote; //앞 도라들 열릴때마다 추가
  std::vector<int> doras_ura;//뒷도라들 열릴때 마다 추가
  bool isLastTurn;//마지막 차례 체크해서 해저/하저체크용
  bool isSunOneturn;//순정 1순인지 체크해서 천화/지화 체크용.+ 더블리치 체크용+사풍연타+구종구패
  bool isFourKangs; //사깡여부 체크S
  int remainTiles; //남은 패산 패 갯수
  std::chrono::steady_clock::time_point last_tick;
  double waitingTime = 3;
  double waitingTimer = waitingTime;
  double turnTime = 3;
  double turnTimer = turnTime;
  double huroTime = 3;
  double huroTimer = huroTime;
  GamePhases phases;

    GameData();
    ~GameData();
    void InitGame();
    void SetGame(Baram baram,int guk, int bonjang);
    void Suffle();
    void RandomDongNamSeoBuk();
    void SetWangPae();
    void Baepae(Jaksadata* jaksa, int index);
    void SetDoraPae();
    void Update(std::chrono::steady_clock::time_point now);
    void PassTurn();
};

