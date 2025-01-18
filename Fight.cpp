#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>


// �����ı���ɫΪָ���� RGB ֵ
void setTextColorRGB(int r, int g, int b) {
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}
//ս�������������¿ո�ֹͣ���������»س�ѡ����
float progress_bar() {
    int progress = 0;
    int max_progress = 100;
    float current_value = 0.0;
    float increment = 0.04;
    clearInputBuffer();//���������
    while (1) {
        // ��յ�ǰ��
        printf("\r");
        for (int i = 0; i < 80; i++) {
            printf(" ");
        }
        printf("\r");

        // ��ӡ������
        printf("��");
        for (int i = 0; i < progress; i++) {
            // ���ݽ���������ɫ
            int r = (i * 255) / max_progress;
            int g = 255 - (i * 255) / max_progress;
            int b = 0; // ������ɫΪ0
            setTextColorRGB(r, g, b);
            printf("��");
        }
        for (int i = progress; i < max_progress; i++) {
            printf(" ");
        }
        printf("\x1b[0m��"); // ������ɫ

        // ���½��Ⱥ���ֵ
        progress = (int)(current_value * max_progress);
        current_value += increment;
        if (current_value > 1.0) {
            current_value = 0.0;
        }

        // ����������
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                printf("\n�����ٷֱ�: %.2f\n", current_value);
                return current_value + 0.5;//��������ָ��0.5-1.5
            }
            else if (ch == 13)
            {
                printf("\nѡ����ʹ�ü��ܻ���ߣ�\n");
                return -1.0;//fight���жϷ���ֵ�������-1��ʼ������ز���
            }
        }

        // �����ӳ�
        Sleep(10); // 100����
    }
}
// ��ʾ��ɫѪ���ĺ���
void displayHealthBar(int maxHealth, int currentHealth, const char* characterName, int align) {
    const int barLength = 25; // Ѫ���ܳ���Ϊ25�������ַ�
    int filledBlocks = (currentHealth * barLength) / maxHealth; // ���㵱ǰѪ����Ӧ�ķ�����
    int emptyBlocks = barLength - filledBlocks; // ����ʣ��ķ�����

    // ��ӡѪ����Ϣ�ͽ�ɫ����
    if (align == 1) { // �Ҷ���
        printf("%*s", 75, ""); // ��Ѫ����Ϣǰ��ӡ�ո���ʵ���Ҷ��룬�������̨���Ϊ50
    }
    printf("%s: %d/%d\n", characterName, currentHealth, maxHealth);

    // ��ӡѪ��
    if (align == 1) { // �Ҷ���
        printf("%*s", 100 - barLength, ""); // ��Ѫ��ǰ��ӡ�ո���ʵ���Ҷ���
    }
    setTextColorRGB(255, 0, 0); // ����Ѫ����ɫΪ��ɫ
    for (int i = 0; i < filledBlocks; i++) {
        printf("��"); // ��ӡ��ɫ�����ʾ��ǰѪ��
    }
    setTextColorRGB(255, 255, 255); // ����ʣ�ಿ����ɫΪ��ɫ
    for (int i = 0; i < emptyBlocks; i++) {
        printf("��"); // ��ӡ��ɫ�����ʾʣ��Ѫ��
    }
    printf("\x1b[0m"); // ������ɫ
    printf("\n");
}




int fight(int *last_time_HP)//һ����������̣�Ĭ�Ϸ��ص�����Ӯ�Ĳ���ֵ��last_time_HP�������ضԾֽ���ʱ��ҵ�ʣ��Ѫ����
{
    role_stats FightTempPlayerStats = PLAYER;
    role_stats FightTempOpponentStats = OPPONENT;//��Ϊ���ܻ��ڶԾ��ڸ���stats���Ծֽ�����ָ�������������ʱ�洢��Using_Skill_Props�����Ĳ����������������ʱ����

    int ROUND = 1;
    int state = 2;

    int n_Round_Effect = -1;//ָʾ��Щn�غ���Ч�ļ��ܡ�����n�غ���Ч���ܻ�ˢ�¼��������ڼ���������󣬶�˫����statsִ�з������
    bool new_n_Round_Effect_Happpen = 0;//ָʾ�Ƿ������µ�n�غ�ʽ���ܵ��߲���
    SKILL_PROPS n_Round_Effect_SK;//���ڴ洢������ܣ��������
    role_stats n_Round_Effect_FightTempPlayerStats = PLAYER;//�����洢n�غ���Ч���ܵĶϵ���Ϣ���ضϵ�ʱ������ֵ���û���SPR�����ķ�ʽ�������ѻغ��д��µ�Ѫ�ӻ�ȥ��������ֵ�͹�����������ϵ㣬��Ȼ�����޼᲻��ͨ��*99999�����������ļ�飬���ѷ���ֵ��Ϊ1.�ٻ��ݵĻ����ǳ���99999������𲻵�����
    role_stats n_Round_Effect_FightTempOpponentStats = OPPONENT;
    
    displayHealthBar(PLAYER.HP, FightTempPlayerStats.HP, FightTempPlayerStats.Name, 0);//��ӡ��ʼʱ˫��Ѫ��
    displayHealthBar(OPPONENT.HP, FightTempOpponentStats.HP, FightTempOpponentStats.Name, 1);//1�����Ҷ���

    while (1)
    {
        printf("===================================��%d�غ�===================================\n",ROUND);
        Sleep(2000);
        float ATTACK;
        float charged_value = progress_bar();
        if (charged_value < 0)
        {
            int code;
            char SPmessage[101] = { '\0' };
            printf("������Ҫ�����ļ������ƻ���룬���롰h��������ʾ��ǰ���õļ��ܣ�");
            fflush(stdin);
            scanf_s("%s", SPmessage, 101);
            const char* pSPmessage = SPmessage;

            //��ʾ���ü���
            if (strstr(pSPmessage, "h"))
            {
                printf("======================��ǰ���õĵ���====================\n");
                for (int i = 0; i < 100; i++) {
                    if (PLAYER.PROPS[i][0] != 0 || PLAYER.PROPS[i][1] != 0) {
                        if (SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].state == state)
                        {
                            printf("��� %d:\t\t %s\tʣ��%d��\n", PLAYER.PROPS[i][0], SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].prompt, PLAYER.PROPS[i][1]);
                        }
                    }
                }
                printf("======================��ǰ���õļ���====================\n");
                if (PLAYER.SKILL[1])
                {
                    printf("��� %d\t%s\n", PLAYER.SKILL[0], SKILL_PROPS_LIST[PLAYER.SKILL[0]].prompt);
                }
                printf("============================================================\n");
                continue;
            }

            //�������ͷ�
            {
                role_stats* FightTempPlayer_OpponentStatsList = Using_Skill_Props(&new_n_Round_Effect_Happpen, &n_Round_Effect_SK, &n_Round_Effect,AnalyseSP(pSPmessage), state, FightTempPlayerStats, FightTempOpponentStats);//2����ս����
                if (!new_n_Round_Effect_Happpen)//���µ�n�غ��ͼ�����Ч�����ﱣ��һ��״̬�ϵ㡣���ڸ����������е���һ����ɵģ�����������߼���ÿ�ֶ��ϵ㣬���������Ϳ�ʼ���ϵ�
                {
                    n_Round_Effect_FightTempPlayerStats = FightTempPlayerStats;
                    n_Round_Effect_FightTempOpponentStats = FightTempOpponentStats;
                }
                FightTempPlayerStats = FightTempPlayer_OpponentStatsList[0];//USP�������ص��ǽṹ�����ָ�룬��ĵ�һ������ң��ڶ����Ƕ���
                FightTempOpponentStats = FightTempPlayer_OpponentStatsList[1];//�ȴ���һ���µĽṹ�������ڴ洢USP�ķ��أ�����Ҫ�������Ρ��ֲ�����µģ���ʡ�ڴ�
            }
            continue;
        }
        ATTACK = FightTempOpponentStats.DEF * FightTempPlayerStats.ATK * charged_value;

        FightTempOpponentStats.HP = FightTempOpponentStats.HP + 0.5 - ATTACK;
        printf("��Ե��˲�����%f���˺������˵�ǰѪ����%d\n\n", ATTACK, FightTempOpponentStats.HP);
        
        displayHealthBar(OPPONENT.HP, FightTempOpponentStats.HP, FightTempOpponentStats.Name, 1);//1�����Ҷ���
        if (FightTempOpponentStats.HP <= 0)//��������
        {
            printf("����ս�ܣ���ʤ���ˣ�\n");
            printf("=============================================================================\n");
            PLAYER.SKILL[1] = 1;
            cleanAndOrganizeProps();

            if (last_time_HP != nullptr)
            {
                *last_time_HP = FightTempPlayerStats.HP;
            }
            printf("�����������\n");
            while (!_kbhit()) {}
            return 1;
        }
        // ��ʼ�������������
        //srand((unsigned int)time(NULL));
        // ����һ������ 0.0 �� 1.0 ֮������������
        Sleep(2000);
        float randomFloat = (float)rand() / RAND_MAX;
        ATTACK = FightTempOpponentStats.ATK * FightTempPlayerStats.DEF * (randomFloat + 0.5);//�ֵ�����ֵ���
        FightTempPlayerStats.HP = FightTempPlayerStats.HP + 0.5 - ATTACK;//��������
        printf("���˶��������%f���˺����㵱ǰѪ����%d\n\n", ATTACK, FightTempPlayerStats.HP);
        displayHealthBar(PLAYER.HP, FightTempPlayerStats.HP, FightTempPlayerStats.Name, 0);
        if (FightTempPlayerStats.HP <= 0)//�������
        {
            printf("�㱻�����ˣ�\n");
            printf("=============================================================================\n");
            PLAYER.SKILL[1] = 1;
            cleanAndOrganizeProps();
            printf("�����������\n");
            while (!_kbhit()) {}
            return 0;
        }
        printf("=============================================================================\n");
        ROUND += 1;

        if (n_Round_Effect > 0)//ÿ�ֺ����һ����������
        {
            n_Round_Effect -= 1;
        }
        if (n_Round_Effect == 0)
        {//�����߼�
            if (n_Round_Effect_SK.object == 1)
            {
                FightTempPlayerStats.HP -= n_Round_Effect_SK.Operate_HP;
                FightTempPlayerStats.ATK = n_Round_Effect_FightTempPlayerStats.ATK;
                FightTempPlayerStats.DEF = n_Round_Effect_FightTempPlayerStats.DEF;
            }
            else//==2
            {
                FightTempOpponentStats.HP -= n_Round_Effect_SK.Operate_HP;
                FightTempOpponentStats.ATK = n_Round_Effect_FightTempOpponentStats.ATK;
                FightTempOpponentStats.DEF = n_Round_Effect_FightTempOpponentStats.DEF;
            }
            printf("��n�غ��͵��߻��ܵĽ����ѽ����\n��Ч������ʧ��\n");
            n_Round_Effect = -1;
            new_n_Round_Effect_Happpen = 0;//0ָʾû���µĻغϼ��ܣ���ʱ����Ķϵ��ȡ�����
        }//һ�������С�߼������Կ����������������ͣ�ʹ洢����
    }



    return 1;
}