// #include<iostream>
#include<string>

// Tsu type
enum TsuType{
    NoneTsu,
    Syuntsu,
    Meori,
    Keotsu,
    Kangtsu,
    Guksa,
    Guryeon,
};

static std::string Tostring(TsuType type)
{
    std::string str = "";
    if(type == NoneTsu){str += "None";}
    else if(type == Syuntsu){str += "Syuntsu";}
    else if(type == Meori){str += "Meori";}
    else if(type == Keotsu){str += "Keotsu";}
    else if(type == Kangtsu){str += "Kangtsu";}
    else if(type == Guksa){str += "Guksa";}
    else if(type == Guryeon){str += "Guryeon";}
    else {str += "(TsuType error number=" + std::to_string(type)+ ")";}
    return str;
}

enum PaeType
{
    NonePae = -1,
    Mansu = 0,
    Tongsu = 1,
    Saksu = 2,
    JaPae = 3,
    Hwapae = 4
};


static std::string Tostring(PaeType type)
{
    std::string str = "";
    if(type == NonePae){str = "None";}
    else if(type == Mansu){str = "Mansu";}
    else if(type == Tongsu){str = "Tongsu";}
    else if(type == Saksu){str = "Saksu";}
    else if(type == JaPae){str = "JaPae";}
    else if(type == Hwapae){str = "Hwapae";}
    else {str = "(PaeType error number="+ std::to_string(type)+ ")";}
    return str;
}




