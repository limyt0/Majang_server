#include <string>

class GameUserData{
public:
  int pk_id;
  std::string name;
  GameUserData(int id, std::string n): pk_id(id), name(n)
  {
    
  }
};
