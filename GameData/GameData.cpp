#include "GameData.h"
#include "Jaksadata.h"
#include <algorithm>
#include <random>
#include <iostream>
//#include <crono>
#include "../Consts.h"
#include "Peas.pb.h"
#include "GameUserData.h"
#include <sys/socket.h>
#include <arpa/inet.h>

GameData::GameData()
{
    
  
    //InitGame();
    //jaksas.insert(new Jaksadata());
}

void GameData::InitGame()
{
    peasan = {10, 20, 30, 40, 50, 60, 70, 80, 90,
                10, 20, 30, 40, 50, 60, 70, 80, 90,
                10, 20, 30, 40, 50, 60, 70, 80, 90,
                10, 20, 30, 40, 55, 60, 70, 80, 90,
                110, 120, 130, 140, 150, 160, 170, 180, 190,
                110, 120, 130, 140, 150, 160, 170, 180, 190,
                110, 120, 130, 140, 150, 160, 170, 180, 190,
                110, 120, 130, 140, 155, 160, 170, 180, 190,
                210, 220, 230, 240, 250, 260, 270, 280, 290,
                210, 220, 230, 240, 250, 260, 270, 280, 290,
                210, 220, 230, 240, 250, 260, 270, 280, 290,
                210, 220, 230, 240, 255, 260, 270, 280, 290,
                310, 320, 330, 340, 350, 360, 370,
                310, 320, 330, 340, 350, 360, 370,
                310, 320, 330, 340, 350, 360, 370,
                310, 320, 330, 340, 350, 360, 370,
                410, 420, 430, 440, 450, 460, 470, 480
        };
    std::cerr << "InitGame!"<< std::endl;

    //방 들어왔다는 메시지 여기 뿌려야 할 듯.
    Suffle();
    RandomDongNamSeoBuk();
    for(int i = 0;i<4;i++)
    {
        std::cerr << "Baepae1"<< std::endl;
        Baepae(jaksas[i].get(), i);
        
    }
    phases = DrawAfter;
    std::cerr << "-------배패 완료----------"<< std::endl;

}


GameData::~GameData()
{

}
void GameData::SetGame(Baram baram,int guk, int bonJang)
{
    nowTableBaram = baram;
    nowGuk = guk;
    nowBonJang = bonJang;
}
 

void GameData::Suffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(peasan.begin(), peasan.end(), g);
}

void GameData::RandomDongNamSeoBuk()
{
    //printf("test1\n");
    //std::vector<int> indices = {0, 1, 2, 3};
    //std::random_device rd;
    //std::mt19937 g(rd());
    //std::shuffle(indices.begin(), indices.end(), g);

    jaksas[0]->baram = Dong;
    jaksas[1]->baram = Nam;
    jaksas[2]->baram = Seo;
    jaksas[3]->baram = Buk;
}

void GameData::SetWangPae()
{
    int wangstart = PeasanLen - WangPaeLen;
    int dora_start = wangstart;
    int dora_end = wangstart + WangDoraLen - 1;
    int ys_start = wangstart + WangDoraLen;
    int ys_end = PeasanLen - 1;
    int count = 0;
    // for (int i = dora_start; i <= dora_end; i++) {
    //     if (i % 2 == 0)
    //     {
    //         doras_ura[count] = peasan[i];
    //     }
    //     else { 
    //         doras_omote[count] = peasan[i];
            
    //         count++;
    //     }
    // }
    count = 0;
    int wanglast = wangpae.size() - 1;
    for (int i = ys_start; i <= ys_end; i++) {
        int tilenum = peasan.back();
        wangpae[wanglast - count] = tilenum;
        peasan.pop_back();
        count++;
    }
    //첫번째 도라 열기
    SetDoraPae();
}

void GameData::Baepae(Jaksadata* jaksa, int index)
{
    if (jaksa == nullptr) {
        std::cerr << "Fatal Error: jaksa pointer is NULL at index " << index << std::endl;       
        return;
    }
    for(int i = 0;i<TsumoLen;i++)
    {
        int tilenum = peasan.back();
        int a =  jaksa->sonTils.size();

        jaksa->sonTils.push_back(tilenum);
        
        peasan.pop_back();
    }
        peas::GamePacket packet;
        peas::BeaPea* beapea = packet.mutable_bea_pea();
        beapea->set_roomid(1);
        beapea->set_jaksaindex(index);
        for(int tile : jaksa->sonTils) {
            beapea->add_sonpeas(tile);
        }
        std::string sendBuffer;
        packet.SerializeToString(&sendBuffer);

        // [중요] 1. 헤더 생성 (데이터 크기)
        uint32_t dataSize = static_cast<uint32_t>(sendBuffer.size());
        uint32_t networkSize = htonl(dataSize); // 네트워크 바이트 순서로 변환

        // [중요] 2. 헤더 먼저 전송
        send(jaksa->gameuserdata->pk_id, reinterpret_cast<char*>(&networkSize), sizeof(networkSize), 0);
        
        std::cerr << "sendBuffer.size(): " << sendBuffer.size() << std::endl;
        ssize_t bytes_sent = send(jaksa->gameuserdata->pk_id, sendBuffer.data(), sendBuffer.size(), 0);
        if (bytes_sent == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // 논블로킹 소켓에서 버퍼가 가득 참. 잠시 대기 후 재시도 또는 오류 처리
                // 여기서는 간단하게 다시 시도하지 않고 오류 메시지 출력
                std::cerr << "Warning: Send buffer full, message might not have been sent immediately." << std::endl;
            } else {
                std::cerr << "Error sending data (errno: " << errno << ")." << std::endl;
                return; // 전송 오류 시 루프 종료
            }
        }
}

// 도라 열기
void GameData::SetDoraPae()
{
    int count = doras_omote.size()* 2;
    doras_omote.push_back(wangpae[count]);
    doras_omote.push_back(wangpae[count+1]);
}

void GameData::Update(std::chrono::steady_clock::time_point now) 
{
    std::chrono::duration<double> elapsed = now - last_tick;
    double deltaTime = elapsed.count();
    
    //std::cerr << "---DrawAfter 호출!" << std::endl;
    
    
    if(phases == DrawAfter)
    {
        turnTimer -= deltaTime;
        if(turnTimer <= 0 ) //누군가 버리면 0초로 만들기
        {   
            //시간 지나면 자동으로 버리고 버림after로 상태 변환
            phases = berimAfter;
            //PassTurn();
        }
    }else if(phases == berimAfter)
    {
        //std::cerr << "---berimAfter 호출!" << std::endl;
        huroTimer -= deltaTime;
        if(huroTimer <= 0 )//스킵시 바로 0초로 만들어야 함.
        {   
            //시간 지나면 그냥 스킵
            phases = berimAfter;
            nowTurnJaksaIndex = (nowTurnJaksaIndex + 1) % 4;
            PassTurn();
            
        }
    }


    last_tick = now;
}

void GameData::PassTurn()
{      
    int tsumoTile = peasan.back();
    peasan.pop_back();
    jaksas[nowTurnJaksaIndex]->Tsumo(tsumoTile);
    //호출하면 됨.
    std::string test12 = "";
    int size = jaksas[nowTurnJaksaIndex]->sonTils.size();
    for(int i = 0;i<size;i++)
    {
        std::string k = std::to_string(jaksas[nowTurnJaksaIndex]->sonTils[i])+" ";
        //std::cerr << jaksas[nowTurnJaksaIndex]->sonTils[i]<< std::endl;
        test12.append(k);
    }
    test12.append(std::to_string(jaksas[nowTurnJaksaIndex]->lastTile));
    
    //std::cerr << nowTurnJaksaIndex<< "차례" << test12<< std::endl;


    //차례 넘기고
    turnTimer = turnTime;
    huroTimer = huroTime;
}