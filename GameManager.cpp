#include "GameManager.h"
//#include "GameData/GameUserData.h"
//#include "GameData/GameData.h"
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
// 스태틱 변수 초기화
GameManager* GameManager::instance = nullptr;
std::mutex GameManager::mutex_;
//std::mutex GameManager::update_mutex;



void GameManager::ServerSoketInit()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, SOMAXCONN);
}

void GameManager::AcceptClientUpdate()
{
    while(server_running)
    {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if(client_fd>0)
        {
            AddUser(client_fd);
        }
    }
}

//삭제할 때 
void GameManager::HandleUser(int client_fd) {
    char buffer[1024];
    while (true) {
        int len = recv(client_fd, buffer, sizeof(buffer), 0);
        if (len <= 0) { // 접속 끊김 감지 (0: 정상 종료, -1: 에러)
            break; 
        }
        // 메시지 처리...
    }
    
    // 여기서 제거 로직 실행
    RemoveUser(client_fd); 
    close(client_fd);
}

void GameManager::CreateGame(int roomId)
{
        games[roomId] = std::make_unique<GameData>();
        games[roomId]->InitGame();
        //games[roomId]->;
}

void GameManager::UpdateAll()
{
    //printf("a1");
    while (server_running) {
             auto now = std::chrono::steady_clock::now();
            {
                std::lock_guard<std::mutex> lock(mutex_);
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

void GameManager::AddUser(int id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::string str = std::to_string(id)+"사람";
    auto newUser = std::make_shared<GameUserData>(id, str);
    users.push_back(newUser);

}

void GameManager::RemoveUser(int id)
{
    //
    //std::lock_guard<std::mutex> lock(mutex_);
    // users.erase(std::remove_if(users.begin(), users.end(), 
    // [id](const std::shared_ptr<GameUserData>& u ){ return u->pk_id == id; }), 
    // users.end());
}