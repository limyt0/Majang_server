#include "Tsublock.h"
#include <string>
#include <iostream>
#include "hwaryo_config.h"

#ifdef TSU_BLOCK_DEBUG
    #define DEBUG_LOG(fmt, ...)
#else
    #define DEBUG_LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)
#endif



TsuBlock::TsuBlock()
{

}

TsuBlock::~TsuBlock()
{
    
}

void TsuBlock::print_contents()
{
    std::string str = "";
    if(pae_type == PaeType::JaPae)
    {
        std::string s = "";
        std::string n = std::to_string(number);
        if(number == 1){s += "東";}
        else if(number == 2){s += "南";}
        else if(number == 3){s += "西";}
        else if(number == 4){s += "北";}
        else if(number == 5){s += "白";}
        else if(number == 6){s += "發";}
        else if(number == 7){s += "中";}
        else{s +="?(" + std::to_string(number) +")";}

        if(tsu_type == TsuType::Meori){str += "(자패"+s+")  ("+n+n+")   - 머리";}
        else if(tsu_type == TsuType::Keotsu){str += "(자패"+s+")  ("+n+n+n+")  - 커쯔";}
        else if(tsu_type == TsuType::Kangtsu){str += "(자패"+s+")  ("+n+n+n+n+") - 깡쯔";}
        else if(tsu_type == TsuType::Syuntsu){str += "(자패+"+s+")  (error)  - 슌쯔 ";}
        else if(tsu_type == TsuType::None){str += "(자패"+s+") - tsutype None error";}
        else {str += "(자패) - error, tsu_type value is " + tsu_type;}
    }
    else
    {
        std::string n = std::to_string(number);
        std::string pae_type_str = PaeType::Tostring(pae_type);

        if(tsu_type == TsuType::Meori){str += "("+pae_type_str+"패)  ("+n+n+")   - 머리";}
        else if(tsu_type == TsuType::Keotsu){str += "("+pae_type_str+"패)  ("+n+n+n+")  - 커쯔";}
        else if(tsu_type == TsuType::Kangtsu){str += "("+pae_type_str+"패)  ("+n+n+n+n+") - 깡쯔";}
        else if(tsu_type == TsuType::Syuntsu){str += "("+pae_type_str+"패)  ("+n+std::to_string(number+1)+std::to_string(number+2)+")  - 슌쯔";}
        else if(tsu_type == TsuType::Guksa){str += "(국사무쌍)";}
        else if(tsu_type == TsuType::Guryeon){str += "(구련보등)";}
        else if(tsu_type == TsuType::None){str += "("+pae_type_str+") - Tsutype None error";}
        else {str += "("+pae_type_str+") - error, tsu_type value is " + std::to_string(tsu_type);}
    }
    if(huro){ str += " - 후로\n";}
    else{ str += " - 멘젠\n";}
    DEBUG_LOG(str.c_str());
}
