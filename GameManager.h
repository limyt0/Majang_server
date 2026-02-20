#include <chrono>
#include <mutex>
#include <map>
#include <memory>
#include <thread>
#include <vector>
#include "GameData/GameData.h"
#include "GameData/GameUserData.h"

//class GameData;
//class GameUserData;

class GameManager
{
private: 
    static GameManager* instance;
    static std::mutex mutex_;
    static const int serverPort = 2345;
    int server_fd;

    std::map<int, std::unique_ptr<GameData>> games;
    //static std::mutex update_mutex;
    std::vector<std::shared_ptr<GameUserData>> users;
    GameManager(){};
    ~GameManager(){};


public:
    bool server_running = true;
    static GameManager* GetInstance(){
        std::lock_guard<std::mutex> lock(mutex_);
        if(instance == nullptr)
        {
            instance = new GameManager();
        }
        return instance;
    };
    
    void ServerSoketInit();
    void AcceptClientUpdate();
    void HandleUser(int client_fd);
    void CreateGame(int roomId);

    void UpdateAll();

    void AddUser(int id);
    void RemoveUser(int id);
};