#pragma once
#include<string>

// Tsu type
class TsuType
{
    public:
    static const int None = 0;
    static const int Syuntsu = 1;
    static const int Meori = 2;
    static const int Keotsu = 3;
    static const int Kangtsu = 4;
    static const int Guksa = 5;
    static const int Guryeon = 6;
    static std::string Tostring(int type)
    {
        std::string str = "";
        if(type == TsuType::None){str += "None";}
        else if(type == TsuType::Syuntsu){str += "Syuntsu";}
        else if(type == TsuType::Meori){str += "Meori";}
        else if(type == TsuType::Keotsu){str += "Keotsu";}
        else if(type == TsuType::Kangtsu){str += "Kangtsu";}
        else if(type == TsuType::Guksa){str += "Guksa";}
        else if(type == TsuType::Guryeon){str += "Guryeon";}
        else {str += "(TsuType error number=" + std::to_string(type)+ ")";}
        return str;
    }
};


class PaeType
{
    public:
    static const int None = -1;
    static const int Mansu = 0;
    static const int Tongsu = 1;
    static const int Saksu = 2;
    static const int JaPae = 3;
    static const int Hwapae = 4;
    static std::string Tostring(int type)
    {
        std::string str = "";
        if(type == PaeType::None){str = "None";}
        else if(type == PaeType::Mansu){str = "Mansu";}
        else if(type == PaeType::Tongsu){str = "Tongsu";}
        else if(type == PaeType::Saksu){str = "Saksu";}
        else if(type == PaeType::JaPae){str = "JaPae";}
        else if(type == PaeType::Hwapae){str = "Hwapae";}
        else {str = "(PaeType error number="+ std::to_string(type)+ ")";}
        return str;
    }
};







class HwaryoPaeType
{
    public:
    static const int None = 0;

    // 론 - 계산 편의를 위해 홀수로.
    static const int NormalRon = 1;
    static const int Chankang = 3;
    static const int Hajeo = 5;
    static const int Ankang = 7; // 국사무쌍 전용 안깡 론
    
    // 쯔모 - 계산 편의를 위해 짝수로.
    static const int PaesanTsumo = 2;
    static const int Yeongsang = 4;
    static const int Haejeo = 6;
    static const int CheonHwa = 8;
    static const int JiHwa = 10;

    static bool is_ron(int type)
    {
        if( type % 2 == 1){return true;}
        
        return false;// None도 짝수
    }


    static std::string int_to_str(int type_int)
    {
        std::string str = "";

        // if(type_int == NormalRon){str = "NormalRon";}
        // else if(type_int == Chankang){str = "Chankang";}
        // else if(type_int == PaesanTsumo){str = "PaesanTsumo";}
        // else if(type_int == Yeongsang){str = "Yeongsang";}
        // else if(type_int == Haejeo){str = "Haejeo";}
        // else if(type_int == Hajeo){str = "Hajeo";}
        // else if(type_int == Ankang){str = "AnkangRon";}
        // else if(type_int == CheonHwa){str = "CheonHwa";}
        // else if(type_int == JiHwa){str = "JiHwa";}
        // else {str = $"type-error (value={type_int})";}

        // if(is_ron(type_int)){str += "(RON)";}
        // else{str += "(TSUMO)";}

        return str;
    }

};

struct Daegistate
{
    public:
    bool Dangi = false;
    bool Yang = false;
    bool Gan = false;
    bool Byeon = false;
    bool Syabo = false;
};