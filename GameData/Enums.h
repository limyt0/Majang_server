#pragma once

enum Baram
{
    Dong = 0,
    Nam = 1,
    Seo = 2,
    Buk = 3
};

enum GamePhases
{
    Waiting,//게임 시작 기다림 
    DrawAfter, //누군가 패 쯔모한 직후
    berimAfter //누군가 버린 직후
};