#include "Consts_hwaryo.h"
#include "HwaryoChecker.h"
#include <string>
#include <iostream>
// 화료 체커 보조 함수 모음.

void HwaryoChecker::pae_count_update(int id)
{
    int pae_type = id/100;
    int index = id / 10;
    if (pae_type == PaeType::Hwapae)
    {
        hwapae_exist = true;
    }
    else
    {
        pae_count[index] += 1;
        // printf("(paecount)%d updated!\n", index);
    }

}

int HwaryoChecker::get_meori_type()
{
    int mansu_count_sum = array_sum(pae_count, 1, 9);
    int tongsu_count_sum = array_sum(pae_count, 11, 19);
    int saksu_count_sum = array_sum(pae_count, 21, 29);
    int japae_count_sum = array_sum(pae_count, 31, 37);

    bool m0 = false;if(mansu_count_sum %3 == 0){m0 = true;}
    bool t0 = false;if(tongsu_count_sum %3 == 0){t0 = true;}
    bool s0 = false;if(saksu_count_sum %3 == 0){s0 = true;}
    bool j0 = false;if(japae_count_sum %3 == 0){j0 = true;}

    bool m2 = false;if(mansu_count_sum %3 == 2){m2 = true;}
    bool t2 = false;if(tongsu_count_sum %3 == 2){t2 = true;}
    bool s2 = false;if(saksu_count_sum %3 == 2){s2 = true;}
    bool j2 = false;if(japae_count_sum %3 == 2){j2 = true;}
    if(m2 && t0 && s0 && j0){return PaeType::Mansu;}
    if(m0 && t2 && s0 && j0){return PaeType::Tongsu;}
    if(m0 && t0 && s2 && j0){return PaeType::Saksu;}
    if(m0 && t0 && s0 && j2){return PaeType::JaPae;}

    return PaeType::None;

}

int HwaryoChecker::array_sum(int * ints, int start_index, int last_index)
{
    int sum = 0;
    for(int i = start_index; i <= last_index; i++)
    {
        sum += ints[i];
    }
    return sum;
}


// 자패 머리 업데이트.
// pae_count와 tsu_blocks(List)업데이트
void HwaryoChecker::japae_meori_update(int pae_type)
{
    int index = 0;
    if(pae_type == PaeType::JaPae)
    {
        for(int i = 31; i <= 37; i++)
        {
            if(pae_count[i] == 2)
            {
                index = i % 10;
                pae_count[i] = 0;
                break;
            }
        }
    }

    TsuBlock tsuBlock;
    tsuBlock.number = index;
    tsuBlock.pae_type = pae_type;
    tsuBlock.tsu_type = TsuType::Meori;

    printf("머리 update - pae_type : %d, index : %d\n",pae_type,index);

    tsu_blocks.push_back(tsuBlock);
}


void HwaryoChecker::print_blocks()
{
    for(int i=0;i<tsu_blocks.size();i++){
        tsu_blocks[i].print_contents();
    }
}

void HwaryoChecker::print_tsu_blocks(std::vector<TsuBlock> b)
{
    for(int i=0;i<b.size();i++)
    {
        b[i].print_contents();
    }
}

// 자패 커쯔 체크.
// pae_count와 tsu_blocks(List)업데이트
void HwaryoChecker::japae_keotsu_update()
{
    for(int i = 31; i <= 37; i++)
    {
        if(pae_count[i] == 0)
        {
            continue;
        }else if(pae_count[i] == 3)
        {
            // pae_count와 tsu_blocks(List)업데이트
            pae_count[i] = 0;
            TsuBlock tsuBlock;
            tsuBlock.number = i % 10;
            tsuBlock.pae_type = PaeType::JaPae;
            tsuBlock.tsu_type = TsuType::Keotsu;

            tsu_blocks.push_back(tsuBlock);

        }
        else
        {   
            // 머리를 제외한 자패가 0개나 3개가 아니면 화료 불가
            printf("화료불가. pae_count[%d]의 값이 %d임. (0 이나 3이 되어야 함.)\n", i, pae_count[i]);
            japa_keotsu_break = true;
            break;
        }
    }
}


int HwaryoChecker::get_smallest_index(int * p_count)
{
    int index = 30;
    for(int i = 1; i < 30; i++)
    {
        if(p_count[i] > 0)
        {
            index = i;
            break;
        }
    }
    return index;
}


// 재귀적으로 블록 체크
void HwaryoChecker::block_check(HwaryoInfo hwaryo_info)
{
    int counts[38];
    for(int i=0;i<38;i++){counts[i] = hwaryo_info.pae_count[i];}
    // mentsu_info.pae_count.CopyTo(counts, 0);
    bool keotsu_possible = false;
    bool syuntsu_possible = false;
    int c_index = get_smallest_index(hwaryo_info.pae_count);

    int num = c_index % 10;
    int pae_type = c_index/10;

    printf("블록 체크중 %d\n", c_index);

    //자패만 있는 경우 예외처리.
    if(c_index >= 30){
        if(pae_sum(counts) == 0)
        {
            hwaryo_info.block_possible = true;
            hwaryo_list.push_back(hwaryo_info);
            hwaryo_info.print_info();
            return;
        }    
        
        return;
    }


    std::string str = "";
    if (pae_type == PaeType::Mansu){str += "만수 ";}
    else if(pae_type == PaeType::Tongsu){str += "통수 ";;}
    else if(pae_type == PaeType::Saksu){str += "삭수 ";;}
    for(int j = 1; j <= 9; j++)
    {
        str += std::to_string(counts[pae_type*10 + j]);
        str += " ";
    }
    printf("%s\n", str.c_str());
    // DebugLog.log(str);


    //커쯔 후보인지 확인
    if(counts[c_index] >= 3){keotsu_possible = true;}
    //슌쯔 후보인지 확인
    if(counts[c_index] > 0 && counts[c_index+1] > 0 && counts[c_index+2] > 0){syuntsu_possible = true;}

    //커쯔도 안되고 슌쯔도 안되는 경우 블록 불가
    if(!keotsu_possible && !syuntsu_possible){
        hwaryo_info.block_possible = true;
        printf("(%d) - 블록 불가능 확인됨.\n", c_index);
        return ;
    }


    if (keotsu_possible)
    {   
        HwaryoInfo k_hwaryo_info(hwaryo_info.tsu_blocks, hwaryo_info.pae_count);
        // 커쯔 패 업데이트
        k_hwaryo_info.pae_count[c_index] = 0;
        TsuBlock keotsu_block;
        keotsu_block.number = num;
        keotsu_block.pae_type = pae_type;
        keotsu_block.tsu_type = TsuType::Keotsu;
        k_hwaryo_info.tsu_blocks.push_back(keotsu_block);

        if(pae_sum(k_hwaryo_info.pae_count) == 0)
        {
            k_hwaryo_info.block_possible = true;
            hwaryo_list.push_back(k_hwaryo_info);
            k_hwaryo_info.print_info();
            return ;
        }

        // 재귀적으로 블록 체크.
        block_check(k_hwaryo_info);
                    
    }


    if (syuntsu_possible)
    {
        HwaryoInfo s_hwaryo_info(hwaryo_info.tsu_blocks, hwaryo_info.pae_count);
        // 슌쯔 패 업데이트
        s_hwaryo_info.pae_count[c_index] -= 1;
        s_hwaryo_info.pae_count[c_index + 1] -= 1;
        s_hwaryo_info.pae_count[c_index + 2] -= 1;
        TsuBlock syuntsu_block;
        syuntsu_block.number = num;
        syuntsu_block.pae_type = pae_type;
        syuntsu_block.tsu_type = TsuType::Syuntsu;
        s_hwaryo_info.tsu_blocks.push_back(syuntsu_block);

        if(pae_sum(s_hwaryo_info.pae_count) == 0)
        {
            s_hwaryo_info.block_possible = true;
            hwaryo_list.push_back(s_hwaryo_info);
            s_hwaryo_info.print_info();
            return ;
        }

        // 재귀적으로 블록 체크.
        block_check(s_hwaryo_info);
    }


    return ;
}

int HwaryoChecker::pae_sum(int * pae_count)
{   
    int sum = 0;
    for(int i = 1; i < 30; i++)
    {
        sum += pae_count[i];
    }

    return sum;
}

std::vector<int> HwaryoChecker::get_supae_meorihubo(int type)
{
    std::vector<int> meori_hubo;
    for(int i = 1; i <= 9; i++)
    {
        int c_index = type*10 + i;
        if(pae_count[c_index] >= 2)
        {
            meori_hubo.push_back(i);
        }
    }

    return meori_hubo;
}


// void HwaryoChecker::print_blocks_list()
// {
//     IEnumerator<HwaryoInfo> iterator = hwaryo_list.GetEnumerator();
//     int i =0;
//     while(iterator.MoveNext())
//     {
//         i++;
//         DebugLog.log($"----- block {i}");
//         iterator.Current.print_info();
//     }
// }