#include <vector>

class Berims
{
public:
    std::vector<int> berimBeas; //버린패들
    std::vector<int> behurod;//내가 버린거 남이 후로해간거. 버린패에서 제외필요.
    int richindex = -1;//리치했을때 위치. 없으면 -1
};