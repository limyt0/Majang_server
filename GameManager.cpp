#include "GameManager.h"
//#include "GameData/GameUserData.h"
//#include "GameData/GameData.h"
#include <string.h>
#include <sys/socket.h>
//#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>
#include "GameData/Jaksadata.h"
#include "GameData/PeaAndBlock/Berims.h"
#include "GameData/PeaAndBlock/HuroBlock.h"
#include "GameData/PeaAndBlock/AnkanBlock.h"
#include <iostream>


GameManager* GameManager::instance = nullptr;
std::mutex GameManager::mutex_;


void GameManager::ServerSoketInit()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    //int opt = 1;
    //setsockopt(server_fd, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(opt));
    
    if(server_fd == -1)
    {
         std::cerr << "소켓 생성 실패" << std::endl;
         return;
    }else{
        std::cerr << "소켓 생성 성공!" << std::endl;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)))
    {
        std::cerr << "바인드 실패" << std::endl;
        return;
    }else{
         std::cerr << "바인드 성공!" << std::endl;
    }
    listen(server_fd, SOMAXCONN);
}

void GameManager::AcceptClientUpdate()
{
    while(server_running)
    {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if(client_fd>0)
        {
            std::cerr << "user 입장!: " << client_fd << std::endl;

            AddUser(client_fd);
        }
        if(usersqueue.size() >= 4)
        {
            int index = games.size();
            CreateGame(index);
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
    std::cerr << "4명 모였다! 방만들기 시작!: " << std::endl;
        games[roomId] = std::make_unique<GameData>();
        for(int i = 0;i<4;i++)
        {

            auto jaksa = std::make_unique<Jaksadata>();
            jaksa->gameuserdata = usersqueue.front();
            usersqueue.pop();
            games[roomId]->jaksas.push_back(std::move(jaksa));
        }
        games[roomId]->InitGame();
        server_running = true;
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
    usersqueue.push(newUser);

}

void GameManager::RemoveUser(int id)
{
    //
    //std::lock_guard<std::mutex> lock(mutex_);
    // users.erase(std::remove_if(users.begin(), users.end(), 
    // [id](const std::shared_ptr<GameUserData>& u ){ return u->pk_id == id; }), 
    // users.end());
}