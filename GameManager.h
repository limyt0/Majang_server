#include <chrono>
#include <mutex>
#include <map>
#include <memory>
#include "GameData/GameData.h"
#include <thread>

class GameManager
{
private: 
    static GameManager* instance;
    static std::mutex mutex_;
    std::map<int, std::unique_ptr<GameData>> games;
    bool server_running = true;
    GameManager();
public:
    static GameManager* GetInstance(){
        std::lock_guard<std::mutex> lock(mutex_);
        if(instance == nullptr)
        {
            instance = new GameManager();
        }
        return instance;
    };
   

    void CreateGame(int roomId);

    void UpdateAll();
};