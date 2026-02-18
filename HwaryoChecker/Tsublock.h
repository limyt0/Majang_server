
class TsuBlock
{
    public:
    int number = 0;
    int pae_type = NonePae;//만수, 통수, 삭수, 자패
    int tsu_type = NoneTsu;//슌쯔, 머리, 커쯔, 깡쯔.
    bool huro = false;

    void print_contents();
};
