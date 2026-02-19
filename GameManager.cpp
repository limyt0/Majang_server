#include "GameManager.h"

// 스태틱 변수 초기화
GameManager* GameManager::instance = nullptr;
std::mutex GameManager::mutex_;
//std::mutex GameManager::update_mutex;

GameManager::GameManager() 
{
    
}

void GameManager::CreateGame(int roomId)
{
        games[roomId] = std::make_unique<GameData>();
        //games[roomId]->;
}

void GameManager::UpdateAll()
{
    //printf("a1");
    while (server_running) {
             auto now = std::chrono::steady_clock::now();
            {
                //std::lock_guard<std::mutex> lock(update_mutex);
                for (auto& pair : games) {
                    
                    GameData* game = pair.second.get();
                    if(game)
                    {
                        game->Update(now); 
                    }
                    
                }
            }
            // 3. CPU를 쉬게 함 (예: 100ms 대기 -> 초당 10번 체크)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}