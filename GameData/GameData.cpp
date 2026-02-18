#include "GameData.h"
#include "Jaksadata.h"
#include <algorithm>
#include <random>
#include <iostream>
//#include <crono>
#include "../Consts.h"

GameData::GameData()
{
    peasan = {10, 20, 30, 40, 50, 60, 70, 80, 90,
                10, 20, 30, 40, 50, 60, 70, 80, 90,
                10, 20, 30, 40, 50, 60, 70, 80, 90,
                10, 20, 30, 40, 55, 60, 70, 80, 90,
                110, 120, 130, 140, 150, 160, 170, 180, 190,
                110, 120, 130, 140, 150, 160, 170, 180, 190,
                110, 120, 130, 140, 150, 160, 170, 180, 190,
                110, 120, 130, 140, 155, 160, 170, 180, 190,
                210, 220, 230, 240, 250, 260, 270, 280, 290,
                210, 220, 230, 240, 250, 260, 270, 280, 290,
                210, 220, 230, 240, 250, 260, 270, 280, 290,
                210, 220, 230, 240, 255, 260, 270, 280, 290,
                310, 320, 330, 340, 350, 360, 370,
                310, 320, 330, 340, 350, 360, 370,
                310, 320, 330, 340, 350, 360, 370,
                310, 320, 330, 340, 350, 360, 370,
                410, 420, 430, 440, 450, 460, 470, 480
        };
    for(int i = 0;i<4;i++)
    {
        jaksas.push_back(std::make_unique<Jaksadata>());
    }
    InitGame();
    //jaksas.insert(new Jaksadata());
}

void GameData::InitGame()
{
    Suffle();
 
    RandomDongNamSeoBuk();
    for(int i = 0;i<4;i++)
    {
        Baepae(jaksas[i].get());
    }

}


GameData::~GameData()
{

}
void GameData::SetGame(Baram baram,int guk, int bonJang)
{
    nowTableBaram = baram;
    nowGuk = guk;
    nowBonJang = bonJang;
}
 

void GameData::Suffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(peasan.begin(), peasan.end(), g);
}

void GameData::RandomDongNamSeoBuk()
{
    //printf("test1\n");
    std::vector<int> indices = {0, 1, 2, 3};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    jaksas[0]->baram = Dong;
    jaksas[1]->baram = Nam;
    jaksas[2]->baram = Seo;
    jaksas[3]->baram = Buk;
}

void GameData::SetWangPae()
{
    int wangstart = PeasanLen - WangPaeLen;
    int dora_start = wangstart;
    int dora_end = wangstart + WangDoraLen - 1;
    int ys_start = wangstart + WangDoraLen;
    int ys_end = PeasanLen - 1;
    int count = 0;
    // for (int i = dora_start; i <= dora_end; i++) {
    //     if (i % 2 == 0)
    //     {
    //         doras_ura[count] = peasan[i];
    //     }
    //     else { 
    //         doras_omote[count] = peasan[i];
            
    //         count++;
    //     }
    // }
    count = 0;
    int wanglast = wangpae.size() - 1;
    for (int i = ys_start; i <= ys_end; i++) {
        int tilenum = peasan.back();
        wangpae[wanglast - count] = tilenum;
        peasan.pop_back();
        count++;
    }
    //첫번째 도라 열기
    SetDoraPae();
}

void GameData::Baepae(Jaksadata* jaksa)
{
    for(int i = 0;i<TsumoLen;i++)
    {
        int tilenum = peasan.back();
        jaksa->sonTils.push_back(tilenum);
        peasan.pop_back();
    }

}

// 도라 열기
void GameData::SetDoraPae()
{
    int count = doras_omote.size()* 2;
    doras_omote.push_back(wangpae[count]);
    doras_omote.push_back(wangpae[count+1]);
}

void GameData::Update(std::chrono::steady_clock::time_point now) 
{
    // if (!this->is_waiting_input) return;

    // // 흐른 시간 계산
    // auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - this->last_turn_time);

    // if (duration.count() >= 3) {
    //     this->AutoNextTurn(); // 3초 경과 시 로직 실행
    // }
}