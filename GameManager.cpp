#include "GameManager.h"

// 스태틱 변수 초기화
GameManager* GameManager::instance = nullptr;
std::mutex GameManager::mutex_;

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
    while (server_running) {
            auto now = std::chrono::steady_clock::now();

            // 2. 활성화된 모든 게임 세션을 관리하는 리스트 순회
            for (auto& pair : games) {
                GameData* game = pair.second.get();
                // 각 게임 객체의 Update 함수만 살짝 호출
                game->Update(now); 
            }

            // 3. CPU를 쉬게 함 (예: 100ms 대기 -> 초당 10번 체크)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}