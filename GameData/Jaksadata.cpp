#include "Jaksadata.h"
#include <algorithm>

Jaksadata::Jaksadata()
{
    isSort = false;
}
Jaksadata::~Jaksadata()
{
    
}

void Jaksadata:: SonPeaSort()    
{
    if(isSort)
    {
        sort(sonTils.begin(), sonTils.end());
    }
}