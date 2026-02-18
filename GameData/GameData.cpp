#include "GameData.h"
#include <algorithm>
#include <random>

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
    InitGame();
    //jaksas.insert(new Jaksadata());
}

void GameData::InitGame()
{
    Suffle();
}

GameData::~GameData()
{

}
void GameData::Suffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(peasan.begin(), peasan.end(), g);
}

void GameData::RandomDongNamSeoBuk()
{
    
}

void GameData::SetWangPae()
{

}

void GameData::Baepae(Jaksadata* jaksa)
{
    
}