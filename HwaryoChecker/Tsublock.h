#pragma once

class TsuBlock
{
    public:
    int number = 0;
    int pae_type;//만수, 통수, 삭수, 자패
    int tsu_type;//슌쯔, 머리, 커쯔, 깡쯔.
    bool huro = false;
    TsuBlock();
    ~TsuBlock();

    void print_contents();
};
