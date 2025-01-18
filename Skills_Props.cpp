#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>
#include <iostream>


//Using_Skill_Props���� ���ռ���/���ߴ��롢����ʱ״̬����ҵ�stats�����ֵ�stats����ѡ��
//�������ݴ����ѯȫ�ֱ����������б�SKILL_PROPS_LIST���SKILL_PROPS�ṹ���飩������һ��SKILL_PROPS�ṹ����
//������������ܽṹ��������Ĳ�����Ӧִ�и����������stats�������޸ĺ������
//����ֻ�ܷ���һ�������������ﷵ�ؽṹ������׵�ַ������˵�ṹ���ָ�룩
role_stats* Using_Skill_Props(bool* new_n_Round_Effect_Happpen, SKILL_PROPS * n_Round_Effect_SK, int * n_Round_Effect, int Skill_Prop_code, int state, role_stats Skill_PropsTempPlayerStatus, role_stats Skill_PropsTempOpponentStatus)
{
    SKILL_PROPS Skill_Props_Temp_PLAYER_PROPS;//��ʼ�����ߣ�����ս���д��벢����Using_Skill_Props����

    role_stats *Refreshed_Status = new role_stats[2];//��ʼ�����ĺ����ҺͶ���stats������Ҫ���ķ��ز���ֵ���Ծ��е���ʱstats/��ս���е�ȫ��stats

    Refreshed_Status[1] = Skill_PropsTempOpponentStatus;
    Refreshed_Status[0] = Skill_PropsTempPlayerStatus;

    Skill_Props_Temp_PLAYER_PROPS = SKILL_PROPS_LIST[Skill_Prop_code];//����code����SKILL_PROPS_LIST[]

    if (!Using_Skill_Props_Checker(Skill_Prop_code, state))//����ֻʹ����Using_Skill_Props_Checker��ͨ����飬����ḻ�����ڱ�ĸ߼�������ʹ��
    {
        printf("��ǰ״̬�²�����ʹ�ô˼��ܻ����\n");
        printf("����%d-��ǰ��%d\n", Skill_Props_Temp_PLAYER_PROPS.state, state);
        
        return Refreshed_Status;//���ؽ���ʼ��Ϊԭ���������������
    }

    if ((*n_Round_Effect != -1))
    {
        if (Skill_Props_Temp_PLAYER_PROPS.Fight_Times != 0)
        {
            printf("�б�ķ�ȫ�Ծּ���������Ч�У����μ����޷��ͷš���Ϊ�ͷ����۳�һ���õ��߻���ʹ�û��ᣡ\n");//��ʵ���������ø�bug
            return Refreshed_Status;
        }
        else
        {
            printf("�б�ķ�ȫ�Ծּ���������Ч�У�����ȫ�ּ�����Ȼ�ɹ��ͷţ����Ǽ��ܶ��ڴ�ǰ��ȫ�Ծּ��ܵĶ���Ĺ��������������Ĳ������ڷ�ȫ�ּ���ֹͣ��Ч�󱻻�ԭ�����������ֲ��������õ��������ڿ��־�ʹ��ȫ�ּ��ܡ�\n");
        }
    }
    if (Skill_Props_Temp_PLAYER_PROPS.Fight_Times != 0)
    {//�����������ģ���Ϊû��ƺ�����ֻ����������ָ��
        *new_n_Round_Effect_Happpen = 1;
        *n_Round_Effect = Skill_Props_Temp_PLAYER_PROPS.Fight_Times;
        *n_Round_Effect_SK = Skill_Props_Temp_PLAYER_PROPS;
    }

    if (Skill_Props_Temp_PLAYER_PROPS.object == 1)
    {
        Refreshed_Status[0].ATK = Skill_PropsTempPlayerStatus.ATK * Skill_Props_Temp_PLAYER_PROPS.Operate_ATK;
        Refreshed_Status[0].DEF = Skill_PropsTempPlayerStatus.DEF * Skill_Props_Temp_PLAYER_PROPS.Operate_DEF;
        Refreshed_Status[0].HP = Skill_PropsTempPlayerStatus.HP + Skill_Props_Temp_PLAYER_PROPS.Operate_HP;
        Refreshed_Status[0].Money = Skill_PropsTempPlayerStatus.Money + Skill_Props_Temp_PLAYER_PROPS.Operate_Money;
        printf("ʹ�ü���%s\n", Skill_Props_Temp_PLAYER_PROPS.prompt);
        logger(INFO, Skills_Props, "[Using_Skill_Props]-������Լ������ͷ�");
        Refreshed_Status[0] = StatsAlterChecker(Refreshed_Status[0]);
        return Refreshed_Status;
    }
    else if (Skill_Props_Temp_PLAYER_PROPS.object == 2)//�Ե��˲���
    {
        Refreshed_Status[1].ATK = Skill_PropsTempOpponentStatus.ATK * Skill_Props_Temp_PLAYER_PROPS.Operate_ATK;
        Refreshed_Status[1].DEF = Skill_PropsTempOpponentStatus.DEF * Skill_Props_Temp_PLAYER_PROPS.Operate_DEF;
        Refreshed_Status[1].HP = Skill_PropsTempOpponentStatus.HP + Skill_Props_Temp_PLAYER_PROPS.Operate_HP;
        Refreshed_Status[1].Money = Skill_PropsTempOpponentStatus.Money + Skill_Props_Temp_PLAYER_PROPS.Operate_Money;
        printf("ʹ�ü���%s\n", Skill_Props_Temp_PLAYER_PROPS.prompt);
        logger(INFO, Skills_Props, "[Using_Skill_Props]-����Ե��˼����ͷ�");
        Refreshed_Status[1] = StatsAlterChecker(Refreshed_Status[1]);
        return Refreshed_Status;
    }

    
    //ƥ�䴫���state��AnalyseSP���صļ������Ӧ�ļ��ܵĿ��ó���������ӽ�ҵ���ֻ���ڷ�ս��ʹ��
    //�ڱ������и��ݼ��ܵĶ������޸�
    //���ݲ��ҽ���������󣬷���һ��stats���������ڶԾ���ʱʹ�ã���Ϊս���п��õĵ��߶��ǽ��ڶԾ�����Ч�ģ����߸���ԭ�е�stats
    return Refreshed_Status;//���ص���һ��stats�ṹ���飨ָ�룩����Ӧ�Լ��Ͷ���
}

role_stats StatsAlterChecker(role_stats unCheckedStats)//����޸ĺ��stats�ǲ����ں���Χ���������ֵ��Χ��[0,1](��ʵ��Ӧ����0�����ǻ���ĳЩ���ԣ�ò��Ҳ�ܴ��һ����˺������߰��������һ���޵�NPCҲ��
{
    
    role_stats CheckedStats = unCheckedStats;
    if (CheckedStats.ATK < 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-��⵽��ATK�Ĳ������޸ģ�ֵ<0����������Ϊ0");
        CheckedStats.ATK = 0;
    }
    if (CheckedStats.DEF < 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-��⵽��DEF�Ĳ������޸ģ�ֵ<0����������Ϊ0");
        CheckedStats.DEF = 0;
    }
    if (CheckedStats.DEF > 1)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-��⵽��DEF�Ĳ������޸ģ�ֵ>1����������Ϊ1");
        CheckedStats.DEF = 1;
    }
    if (CheckedStats.HP <= 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-��⵽��HP�Ĳ������޸ģ�ֵ<0����������Ϊ0");
        CheckedStats.HP = 1;
    }
    if (CheckedStats.Money < 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-��⵽��Money�Ĳ������޸ģ�ֵ<0����������Ϊ0");
        CheckedStats.Money = 0;
    }
    return CheckedStats;
}

bool isPositiveInt(const char* str, int* result) {//���������������ַ����������֣�ֱ����ȡ��
    const char* start = str;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            // �ҵ��������еĿ�ʼ
            const char* end = str;
            while (isdigit((unsigned char)*end)) {
                end++;
            }
            // ����ת��Ϊ����
            char* endPtr;
            long num = strtol(str, &endPtr, 10);
            if (num > 0 && endPtr == end && num <= INT_MAX) {
                *result = (int)num;
                return true;
            }
            str = end;
        }
        else {
            str++;
        }
    }
    return false;
}

int AnalyseSP(const char* SPmessage)
{

    int SPcode = 0;
    if (isPositiveInt(SPmessage, &SPcode)) {
        logger(INFO, Skills_Props, "[AnalyseSP]-ƥ�䵽�����룺");
        char spcode[5];//֧����λ���ļ�����
        sprintf_s(spcode, "%d", SPcode);
        logger(INFO, Skills_Props, spcode);
        if (SPcode == 0)//0���ܲ��������������ڳ�ʼ����ɫ�����б��
        {
            return -1;
        }
        else
        {
            return SPcode;
        }
    }
    else {
        logger(WARN, Skills_Props, "[AnalyseSP]-û���ҵ������е������ͼ����룬����ʹ�����Ľ�����䣺");
        logger(INFO, Skills_Props, SPmessage);
    }

    

    //���������ַ���û�����֣���ִ������Ĳ��ҡ��ⲻ�����������

    if (//��д�����������кܶ����Ӧ�ʵģ����������Ӹ���Ļ������ܾ�ֻ���ú����ˡ���Ϊ����ͨ���ļ���ȡ���ܣ��������ӣ�����������벻�����޶�
        //��˵�ܲ��ܰ���ʾ��Ҳд��txt������
        strstr(SPmessage, "һ����") ||
        strstr(SPmessage, "����һ") ||
        strstr(SPmessage, "������ʯ") ||
        strstr(SPmessage, "jrps")

        )
    {
        
        SPcode = 1;
    }
    //���������Ҫ�����ļ��ܻ���Ҫʹ�õĵ��ߣ����ؼ�����
    //ս���С�ս���ⶼ���������
    else
    {
        SPcode = -1;
        logger(WARN, Skills_Props, "[AnalyseSP]-û���ҵ������еļ���");
        printf("û���ҵ������еļ���\n");
        return -1;
    }
    logger(INFO, Skills_Props, "[AnalyseSP]-���Ľ����ɹ����ҵ������еļ���");
    logger(WARN, Skills_Props, "[AnalyseSP] - ���Ľ������ܲ�֧�ִ�������ܻ���ߣ�����ʹ�ü��ܴ��룬��ǰ���õļ������б������ѡ����ʱ����#h����ȡ");
    printf("���Ľ������ܲ�֧�ִ�������ܻ���ߣ�����ʹ�ü��ܴ��룬��ǰ���õļ������б������ѡ����ʱ����#h����ȡ\n");//�һ�ûд����������Ƕ๦�ܵģ����ݵ���״̬��ս���в�ѯ���ǿ�����ս���еġ��Լ�ӵ�еĵ��ߣ���ս��ʱ�������еģ�������ֱ��ȫ���غ���Ҳ�У�
    return SPcode;
}

int Using_Skill_Props_Checker(int Skill_Prop_code, int state)//ֻ��飬����������������Ǹ����Ծ����Ѿ�ʹ�ù��ü��ܣ����Ǹ����⣬��Ϊ�ڷǶԾ��в�����������
{
    if (Skill_Prop_code == -1)//-1��ASP�Ĵ����룺δ�ҵ���Ӧ����
    {
        printf("δƥ�䵽����ļ�������Ϣ\n");
        return -1;//-1����δ���ҵ�����
    }
    if (SKILL_PROPS_LIST[Skill_Prop_code].state == state)
        if (Skill_Prop_code == PLAYER.SKILL[0])//�ȼ�鼼��
            if (PLAYER.SKILL[1])//����0����ͨ��������������ֻ��0��1����Ҳ������������ˣ����Զ������ > 1�����������úܶ�Σ�����ֱ��=-1
            {
                logger(INFO, Skills_Props, "[Using_Skill_Props_Checker]-����ʹ�ü��ͨ��");
                PLAYER.SKILL[1] = 0;//����Ͳ���ս���д�������ʱ�����ˡ�
                return 1;//�����ǿ��ü���
            }
            else
            {
                printf("�Ծ����Ѿ�ʹ�ù��ü��ܣ�\n");
                logger(INFO, Skills_Props, "[Using_Skill_Props_Checker]-����ʹ�ü�鲻ͨ������Ϊ���ܿ��ô���Ϊ0");
                return 0;
            }
        else//�������ڲ���������Ե����б���ɲ�����
        {
            for (int i = 0; i < 100; i++)
            {
                if ((PLAYER.PROPS[i][0] == Skill_Prop_code) && (PLAYER.PROPS[i][1] > 0))//���ҵ�������Ե����б��е�ָ������
                {
                    PLAYER.PROPS[i][1] -= 1;
                    return 2;//�����ǿ��õ���
                }
            }
            printf("ѡ��ĵ���ʣ����ô���Ϊ0��\n");
            return 0;
        }
    else
    {
        logger(INFO, Skills_Props, "[Using_Skill_Props]-�ܾ��������ļ��ܷ���������Ϊ״̬��鲻ͨ��");
        return 0;
    }
}

//���Ҽ�������props�б��е�λ��
int findPropIndex(int target) {
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][0] == target) {
            return i; // �ҵ�ƥ�������������
        }
    }
    return -1; // û���ҵ�ƥ�������������-1
}

//����PLAYER.PROPS����ĺ�����ÿ��ִ�����PLAYER.PROPS�Ĳ���������
void cleanAndOrganizeProps() {
    int temp[100][2]; // ������ʱ�洢����������
    int count = 0;          // ���ڼ�¼������������Ч����
    int found;              // ���ڱ���Ƿ��ҵ��ظ�����

    // �������飬��鲢���õ�һ������Ϊ0
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][1] == 0) {
            PLAYER.PROPS[i][0] = 0;
        }
    }

    // �������飬����һ�����ֲ�Ϊ0����Ų��ǰ�棬���ϲ��ظ�����
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][0] != 0) {
            found = 0;
            // ����Ƿ��Ѵ��ڸñ���
            for (int j = 0; j < count; j++) {
                if (temp[j][0] == PLAYER.PROPS[i][0]) {
                    temp[j][1] += PLAYER.PROPS[i][1]; // �ϲ�����
                    found = 1;
                    break;
                }
            }
            // ���δ�ҵ�����ӵ���ʱ����
            if (!found) {
                temp[count][0] = PLAYER.PROPS[i][0];
                temp[count][1] = PLAYER.PROPS[i][1];
                count++;
            }
        }
    }

    // �����������鸴�ƻ�ԭ����
    for (int i = 0; i < count; i++) {
        PLAYER.PROPS[i][0] = temp[i][0];
        PLAYER.PROPS[i][1] = temp[i][1];
    }

    // ��ʣ���������Ϊ0
    for (int i = count; i < 100; i++) {
        PLAYER.PROPS[i][0] = 0;
        PLAYER.PROPS[i][1] = 0;
    }
}


int Choose_My_Skill()
{
    int skpr_num_buttons = 0;
    int skpr_num_buttons_arr[MAX_BUTTONS];
    char* skpr_num_buttons_buttons[MAX_BUTTONS] = {};
    for (int i = 1400; i < 1499; i++) {
        if (SKILL_PROPS_LIST[i].prompt[0] != '\0')
        {
            skpr_num_buttons_arr[skpr_num_buttons] = i;
            skpr_num_buttons_buttons[skpr_num_buttons] = SKILL_PROPS_LIST[i].prompt;
            if ((PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] < 5) && (i >= 1410))// ��5��֮ǰֻ��ѡǰ10������
            {
                skpr_num_buttons_arr[skpr_num_buttons] = -i;
            }
            skpr_num_buttons += 1;
        }
    }
    const char* skpr_num_buttons_buttons_const[MAX_BUTTONS];
    for (int i = 0; i < skpr_num_buttons; i++)
    {
        skpr_num_buttons_buttons_const[i] = skpr_num_buttons_buttons[i];
    }
    const char* introduction[MAX_BUTTONS] = {
    NULL
    };
    int choice = menu(skpr_num_buttons, "�����б�", skpr_num_buttons_arr, skpr_num_buttons_buttons_const, introduction, 2);
    if (choice == -10999)
    {
        return 0;
    }
    PLAYER.SKILL[0] = choice;
    PLAYER.SKILL[1] = 1;
    PLAYER_SAVE.Player_Stats = PLAYER;
    SaveSaveFile(&PLAYER_SAVE, &save_count);
    printf("��ѡ���˼��� %s װ�ص���ļ��ܲ��У�������������ܵ���ϸ�������۸���ԣ�����ͷţ�\n", SKILL_PROPS_LIST[choice].prompt);
    displayDetail(choice);
    return 0;
}