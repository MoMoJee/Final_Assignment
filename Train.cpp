#include"functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <commdlg.h>
#include <time.h>
#include<math.h>

int train()
{
    while (1)
    {
    Start_Train:

        int difficulty;
        char* monster_name = { NULL };

        int train_cc_menu_arr[MAX_BUTTONS] = { -1 };
        const char* train_cc_menu_buttons[MAX_BUTTONS] =
        {
            "�˳�",
            "C��",
            "B��",
            "A��",
            "S��",
            "AUVR��",
        };
        const char* train_introduction[MAX_BUTTONS] = {
        NULL,
        "��ͨС����",
        "�м�С����",
        "�߼�����",
        "�������",
        "AUVR��������û��"
        };

        difficulty = menu(6, "ѵ����", train_cc_menu_arr, train_cc_menu_buttons, train_introduction);
        if (difficulty == 0)
        {
            printf("�´�������\n");
            break;
        }

        role_stats monster = generate_monster_stats(difficulty);

        int reward_gold = calculate_reward_gold(monster, difficulty);
        monster.Money = reward_gold;
        
        monster_name = generate_monster_name();
        const char* const_monster_name = monster_name;
        strcpy_s(monster.Name, const_monster_name);

        printf("���ɵĹ������֣� %s\n", monster.Name);
        printf("�������� %d\n", monster.ATK);
        printf("����ֵ�� %d\n", monster.HP);
        printf("�������� %.8f\n", monster.DEF);
        printf("���ܸù���ɻ�õĽ�ҽ����� %d\n", monster.Money);

        SKILL_PROPS reward_stats = calculate_reward_stats(monster);
        printf("���ܸù���ɻ�õ�����������\n");
        printf("=======================================\n");
        printf("�Թ������Ĳ�����*%.8f\n", reward_stats.Operate_ATK);
        printf("������ֵ�Ĳ�����+%d\n", reward_stats.Operate_HP);
        printf("�Է������Ĳ�����*%.8f\n", reward_stats.Operate_DEF);
        printf("=======================================\n");



        printf("ȷ��Ҫ��ʼս����\n");
        printf("�����������������\n");
        while (!_kbhit()) {}
        int cc_menu_arr[MAX_BUTTONS] = { -1 };//ʹ��Ĭ�Ϸ�������
        const char* cc_menu_buttons[MAX_BUTTONS] =
        {
            "ȡ��",
            "ȷ��"
        };
        const char* introduction[MAX_BUTTONS] = { NULL };
        if (!(menu(2, "ȷ��Ҫ��ʼս����", cc_menu_arr, cc_menu_buttons, introduction) == 1))
        {
            goto Start_Train;
        }

        OPPONENT = monster;
        if (fight())
        {
            PLAYER.Money += OPPONENT.Money;
            printf("��ʤ���ˣ�������%d����Һ�����������", OPPONENT.Money);
            //bool useless = 0;
            //PLAYER = Using_Skill_Props(&useless)
            //��������ˣ��鷳
            PLAYER.ATK *= reward_stats.Operate_ATK;
            PLAYER.DEF *= reward_stats.Operate_DEF;
            PLAYER.HP += reward_stats.Operate_HP;
            printf("�����������������\n");
            while (!_kbhit()) {}
        }
        else
        {
            printf("ûʵ���ͱ���\n");
            printf("�����������������\n");
            while (!_kbhit()) {}
        }
    }
    return 0;
}



// �����Ѷ����ɹ�������
role_stats generate_monster_stats(int difficulty)
{
    difficulty *= 5;
    role_stats monster;
    srand(time(NULL)); // ��ʼ�����������

    // �����Ѷ����ù�������Χ
    int min_atk = difficulty * 10;
    int max_atk = difficulty * 20;
    monster.ATK = rand() % (max_atk - min_atk + 1) + min_atk;

    // �����Ѷ���������ֵ��Χ
    int min_hp = difficulty * 50;
    int max_hp = difficulty * 100;
    monster.HP = rand() % (max_hp - min_hp + 1) + min_hp;

    // �����Ѷ����÷�������Χ���Ѷ�Խ�ߣ�������Խ��
    float min_def = 1.0 - (0.04 * difficulty);
    float max_def = 1.0 - (0.01 * difficulty);
    if (min_def <= 0) min_def = 0.000001; // ��ֹ������С��0
    if (max_def <= 0) max_def = 0.000001;
    monster.DEF = (float)(rand() % 100) / 100.0 * (max_def - min_def) + min_def;

    return monster;
}

// ���ݹ������Ժ��Ѷȼ��㽱���������
int calculate_reward_gold(struct role_stats monster, int difficulty)
{
    difficulty *= 5;
    // ������ҽ������Ѷȳ�����
    int base_gold = difficulty * 100;

    // ���ݹ��������ӽ�ҽ���
    int atk_bonus_gold = monster.ATK * 2;

    // ��������ֵ���ӽ�ҽ���
    int hp_bonus_gold = monster.HP / 2;

    // ������Խ�ͣ���������Խǿ������ҽ���Խ��
    int def_bonus_gold = (int)(100/ monster.DEF);

    // �ܽ�ҽ���Ϊ������֮��
    int total_gold = base_gold + atk_bonus_gold + hp_bonus_gold + def_bonus_gold;

    return total_gold;
}

// ���Ĵʿ�
const char* word_library[][10] = {
    {"����", "��˪", "��ɳ", "��ѩ", "����", "���", "ľӰ", "ˮ��", "��", "��ʯ"},
    {"����", "��Х", "��Ծ", "����", "�Ǳ�", "����", "����", "ӥ��", "ʨ��", "��̤"},
    {"Ӱ��", "צ��", "��չ", "�Ǵ�", "�ۼ�", "���", "βɨ", "��̤", "����", "�ĺ�"},
    {"����", "С��", "����", "����", "����", "��С", "�ֶ�", "�ݹ�", "����", "����"},
    {"ħӰ", "����", "����", "����", "���", "����", "��ʹ", "����", "ʥ��", "аħ"},
    {"��ڤ", "��ҹ", "����", "����", "���", "����", "����", "ů��", "ʪ��", "����"},
    {"ɽ��", "����", "�Ӵ�", "����", "��ˮ", "Ϫ��", "Ͽ��", "�嶥", "���", "�±�"},
    {"�籩", "��¶", "����", "����", "�ƺ�", "����", "˪��", "ѩ��", "����", "����"},
    {"���", "��ƽ", "�ճ�", "����", "�ǳ�", "����", "����", "��˹", "����", "����"},
    {"�Ϲ�", "�½�", "���", "����", "ǰ��", "����", "����", "����", "�Ϸ�", "����"}
};

// ������ɹ�������
char* generate_monster_name()
{
    char name[101] = { 0 }; // ��̬���飬���ڴ洢���ɵ�����
    int word_count = sizeof(word_library) / sizeof(word_library[0]); // �ʿ��д��������
    int max_words_per_name = 50 / word_count; // ÿ������������ʹ�õĴ������Ա�֤���ֳ��Ȳ�����50������

    srand(time(NULL)); // ��ʼ�����������

    // ���ѡ����鲢ƴ������
    for (int i = 0; i < word_count; ++i)
    {
        int word_index = rand() % 5; // ���ѡ��ÿ�������е�һ����
        strncat_s(name, word_library[word_count - i - 1][word_index], 2); // ��ѡ�еĴ�׷�ӵ������У�ע��ÿ������ռ2���ֽ�
        if (strlen(name) >= 50 * 2) // ������ֳ��Ƚӽ����ƣ�ֹͣƴ��
            break;
    }

    return name;
}

SKILL_PROPS calculate_reward_stats(role_stats monster)
{
    SKILL_PROPS reward_stats;
    reward_stats.Operate_ATK = fmin(2.0, ((float)(monster.ATK) / (float)(PLAYER.ATK)));
    if (reward_stats.Operate_ATK < 1)
    {
        reward_stats.Operate_ATK = 1;
    }
    reward_stats.Operate_DEF = fmax(0.8, (monster.DEF / PLAYER.DEF));
    if (reward_stats.Operate_DEF > 1)  
    {
        reward_stats.Operate_DEF = 1;
    }
    reward_stats.Operate_HP = fmin(50, (monster.HP - PLAYER.HP)/2);
    if (reward_stats.Operate_HP < 0)
    {
        reward_stats.Operate_HP = 0;
    }
    reward_stats.Fight_Times = 0;
    reward_stats.object = 1;
    reward_stats.state = 1;
    reward_stats.Operate_Money = 0;
    reward_stats.Price = 0;
    strcpy_s(reward_stats.prompt, "[Train]�Ļ�ʤ����");

    return reward_stats;
}