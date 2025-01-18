#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>
#include<math.h>




void createStoryLine() {
    if (!develop_mode)
    {
        printf("�ù��ܽ��޿�����ʹ�ã�\n");
        return;
    }
    int index;
    printf("==========================================\n");
    printf("������Ҫд�����ţ�1-%d����", MAX_STORY_LINES);
    scanf_s("%d", &index);
    index--; // ���û���������ת��Ϊ������������0��ʼ��

    if (index < 0 || index >= MAX_STORY_LINES) {
        printf("��ų�����Χ��\n");
        return;
    }

    if ((STORY_LINES[index].Name != "�����õĹؿ�") && (STORY_LINES[index].Name[0] != '0')) {
        printf("��λ���ѱ�ռ�ã���ѡ������λ�á�\n");
        /*return;*/
    }

    printf("������������ƣ����100���ַ�����");
    getchar(); // ����������еĻ��з�
    fgets(STORY_LINES[index].Name, 101, stdin);
    STORY_LINES[index].Name[strcspn(STORY_LINES[index].Name, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

    printf("�����������ܣ����400���ַ�����");
    //getchar(); // ����������еĻ��з�
    fgets(STORY_LINES[index].Introduction, 401, stdin);
    STORY_LINES[index].Introduction[strcspn(STORY_LINES[index].Introduction, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

    printf("������������֣����100���ַ�����");
    //getchar(); // ����������еĻ��з�
    fgets(STORY_LINES[index].Opponent_Stats.Name, 101, stdin);
    STORY_LINES[index].Opponent_Stats.Name[strcspn(STORY_LINES[index].Opponent_Stats.Name, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

    printf("��������ֵ�HP��");
    scanf_s("%d", &STORY_LINES[index].Opponent_Stats.HP);
    printf("��������ֵ�ATK��");
    scanf_s("%d", &STORY_LINES[index].Opponent_Stats.ATK);
    printf("��������ֵ�DEF��");
    scanf_s("%f", &STORY_LINES[index].Opponent_Stats.DEF);

    STORY_LINES[index].Opponent_Stats.Money = 0;
    *STORY_LINES[index].Opponent_Stats.SKILL = { 0 };
    **STORY_LINES[index].Opponent_Stats.PROPS = { 0 };//����û�õ�����ֵҲ��ʼ����




    // ����ʤ�����
    printf("������ʤ�������ʾ��Ϣ��");
    getchar(); // ����������еĻ��з�
    fgets(STORY_LINES[index].Win_Consequence.prompt, 101, stdin);
    STORY_LINES[index].Win_Consequence.prompt[strcspn(STORY_LINES[index].Win_Consequence.prompt, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

    printf("������ʤ����Ĺ������������ٷֱȣ���");
    scanf_s("%f", &STORY_LINES[index].Win_Consequence.Operate_ATK);

    printf("������ʤ�����Ѫ�������ޣ�������");
    scanf_s("%d", &STORY_LINES[index].Win_Consequence.Operate_HP);

    printf("������ʤ����ķ������������ٷֱȣ���");
    scanf_s("%f", &STORY_LINES[index].Win_Consequence.Operate_DEF);

    printf("������ʤ����Ľ�Ǯ������");
    scanf_s("%d", &STORY_LINES[index].Win_Consequence.Operate_Money);

    STORY_LINES[index].Win_Consequence.Fight_Times = 0;
    STORY_LINES[index].Win_Consequence.object = 1;
    STORY_LINES[index].Win_Consequence.state = 1;
    STORY_LINES[index].Win_Consequence.Price = 0;
    *STORY_LINES[index].Win_Consequence.Introduction = { '\0' };//����û�õ����ݳ�ʼ��һ��


    // ����ʧ�ܺ��
    printf("������ʧ�ܺ����ʾ��Ϣ��");
    getchar(); // ����������еĻ��з�
    fgets(STORY_LINES[index].Lose_Consequence.prompt, 101, stdin);
    STORY_LINES[index].Lose_Consequence.prompt[strcspn(STORY_LINES[index].Lose_Consequence.prompt, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

    printf("������ʧ�ܺ�Ĺ������������ٷֱȣ���");
    scanf_s("%f", &STORY_LINES[index].Lose_Consequence.Operate_ATK);

    printf("������ʧ�ܺ��Ѫ�������ޣ�������");
    scanf_s("%d", &STORY_LINES[index].Lose_Consequence.Operate_HP);

    printf("������ʧ�ܺ�ķ������������ٷֱȣ���");
    scanf_s("%f", &STORY_LINES[index].Lose_Consequence.Operate_DEF);

    printf("������ʧ�ܺ�Ľ�Ǯ������");
    scanf_s("%d", &STORY_LINES[index].Lose_Consequence.Operate_Money);

    STORY_LINES[index].Lose_Consequence.Fight_Times = 0;
    STORY_LINES[index].Lose_Consequence.object = 1;
    STORY_LINES[index].Lose_Consequence.state = 1;
    STORY_LINES[index].Lose_Consequence.Price = 0;
    *STORY_LINES[index].Lose_Consequence.Introduction = { '\0' };//����û�õ����ݳ�ʼ��һ��


    printf("������ʤ�������ļ���/���ߴ��룺");
    scanf_s("%d", &STORY_LINES[index].Win_Award_Code);

    printf("�������Ƿ�����ظ���0��ʾ�����ظ���1��ʾֻ����һ�Σ�-1��ʾ�����棩��");
    scanf_s("%d", &STORY_LINES[index].Repeatable);

    printf("�����Ѵ�����д�뵽��� %d��\n", index + 1);
    story_count = (story_count > index + 1) ? story_count : (index + 1); // ���¾�������
    printf("==========================================\n");
    if (!SaveStoryLinesFile(STORY_LINES, &story_count))
    {
        printf("�����ļ�����ʧ��!\n");
    }
    else
    {
        printf("�����ļ��Ѹ���\n");
    }
    printf("�����������\n");
    while (!_kbhit()) {}
}

void displayBriefStoryLines() {
    printf("��ǰ�ؿ�������Ϣ��\n");
    printf("==========================================\n");
    for (int i = 0; i < story_count; i++) {
        if (STORY_LINES[i].Name[0] != '\0')
        {
            printf("��ţ�%d\n", i + 1);
            printf("���ƣ�%s\n", STORY_LINES[i].Name);
            printf("�Ƿ�����ظ���%s\n", STORY_LINES[i].Repeatable ? "��" : "��");//Ҫ�ġ����и�-1
            printf("----------------\n");
            Sleep(100);
        }
    }
    printf("==========================================\n�����������\n");
    while (!_kbhit()) {}
}

void displayDetailedStoryLine() {
    int index;
    printf("������Ҫ�鿴��ϸ��Ϣ�Ĺؿ����루1-%d����", story_count);
    scanf_s("%d", &index);
    index--; // ���û�����ı���ת��Ϊ������������0��ʼ��

    if (index < 0 || index >= story_count) {
        printf("���볬����Χ��\n");
        return;
    }
    if (STORY_LINES[index].Name[0] == '\0')
    {
        printf("�ô�����Ϊ�գ�\n");
        return;
    }
    printf("==========================================\n");
    printf("�ؿ����ƣ�%s\n", STORY_LINES[index].Name);
    printf("���ܣ�%s\n", STORY_LINES[index].Introduction);
    printf("�������ԣ�HP=%d, ATK=%d, DEF=%f\n",
        STORY_LINES[index].Opponent_Stats.HP,
        STORY_LINES[index].Opponent_Stats.ATK,
        STORY_LINES[index].Opponent_Stats.DEF);
    Sleep(500);
    // ��ʾʤ�����
    printf("----------------\n");
    printf("ʤ��������\n");
    printf("��ʾ��Ϣ��%s\n", STORY_LINES[index].Win_Consequence.prompt);
    printf("�������������ٷֱȣ���*%.2f\n", STORY_LINES[index].Win_Consequence.Operate_ATK);
    printf("Ѫ�������ޣ������� +%d\n", STORY_LINES[index].Win_Consequence.Operate_HP);
    printf("�������������ٷֱȣ���*%.2f\n", STORY_LINES[index].Win_Consequence.Operate_DEF);
    printf("��Ǯ������ +%d\n", STORY_LINES[index].Win_Consequence.Operate_Money);
    printf("----------------\n");
    Sleep(500);
    // ��ʾʧ�ܺ��
    printf("----------------\n");
    printf("ʧ�ܺ����\n");
    printf("��ʾ��Ϣ��%s\n", STORY_LINES[index].Lose_Consequence.prompt);
    printf("�������������ٷֱȣ���*%.2f\n", STORY_LINES[index].Lose_Consequence.Operate_ATK);
    printf("Ѫ�������ޣ������� +%d\n", STORY_LINES[index].Lose_Consequence.Operate_HP);
    printf("�������������ٷֱȣ���*%.2f\n", STORY_LINES[index].Lose_Consequence.Operate_DEF);
    printf("��Ǯ������ +%d\n", STORY_LINES[index].Lose_Consequence.Operate_Money);
    printf("----------------\n");

    printf("ʤ�������Ĵ��룺%d\n����Ľ�����\n", STORY_LINES[index].Win_Award_Code);
    displayDetail(STORY_LINES[index].Win_Award_Code);
    printf("�Ƿ�����ظ���%s\n", STORY_LINES[index].Repeatable ? "��" : "��");
    printf("==========================================\n�����������\n");
    while (!_kbhit()) {}
}

void deleteStoryLine() {
    if (!develop_mode)
    {
        printf("�ù��ܽ��޿�����ʹ�ã�\n");
        return;
    }
    int index;
    printf("������Ҫɾ���Ĺؿ����루1-%d����", story_count);
    scanf_s("%d", &index);
    index--; // ���û�����ı���ת��Ϊ������������0��ʼ��

    if (index < 0 || index >= story_count) {
        printf("���볬����Χ��\n");
        return;
    }

    // ��ʼ���ṹ��
    STORY_LINES[index] =
    {
        "�����õĹؿ�",//��ʼ���ؿ���
        "�����õĹؿ�����",//��ʼ���ؿ�����
        {
            {'\0'},
            0,
            0,
            1.0,
            0,
            0,
            0
        },//��ʼ����������
        {
            "��Ч����",
            0,
            1,
            1,
            0,
            1,
            0,
            0,
            0,
            "����һ����Ч����"
        },//��ʼ��ʤ�����
        {
            "��Ч����",
            0,
            1,
            1,
            0,
            1,
            0,
            0,
            0,
            "����һ����Ч����"
        },//��ʼ��ʧ�ܺ��
        0,
        -1//-1ָʾ������
    };
    Sleep(500);
    printf("�ؿ���ɾ������ʼ����\n");
    if (!SaveStoryLinesFile(STORY_LINES, &story_count))
    {
        printf("�����ļ�����ʧ��!\n");
    }
    else
    {
        printf("�����ļ��Ѹ���\n");
    }
    printf("�����������\n");
    while (!_kbhit()) {}
}

void storyLineControl() {
    int command;

    while (1) {
        //Sleep(1500);
        //rewind(stdin);
        //printf("\n����鿴�봴���������������\n");
        //printf("1. �鿴�ؿ�������Ϣ\n");
        //printf("2. �鿴�ؿ���ϸ��Ϣ\n");
        //printf("3. ɾ���ؿ�\n");
        //printf("4. �����¹ؿ�\n");
        //printf("5. �˳�\n");
        //scanf_s("%d", &command);
        int slc_menu_arr[MAX_BUTTONS] = { -1 };
        const char* slc_menu_button[MAX_BUTTONS] =
        { "�˳�",
            "�鿴�ؿ�������Ϣ",
            "�鿴�ؿ���ϸ��Ϣ",
            "ɾ���ؿ�",
            "�����¹ؿ�"
        };
        const char* introduction[MAX_BUTTONS] = {
        NULL
        };
        command = menu(5, "����鿴�봴����", slc_menu_arr, slc_menu_button, introduction);

        switch (command) {
        case 1:
            displayBriefStoryLines();
            break;
        case 2:
            displayDetailedStoryLine();
            break;
        case 3:
            deleteStoryLine();
            break;
        case 4:
            createStoryLine();
            break;
        case 0:
            printf("�˳�����\n");
            return;
        default:
            printf("��Ч�����\n");
        }
    }
}

int StoryLineModeControl()
{
    //չʾ���п��õľ���ؿ�
    int story_list[MAX_STORY_LINES];
    char* level_buttons[MAX_STORY_LINES];
    char* introduction[MAX_BUTTONS];
    int story_line_real_count = 0;
    for (int i = 0; i < story_count; i++)
    {
        if (STORY_LINES[i].Name[0] != '\0')
        {

            level_buttons[story_line_real_count] = STORY_LINES[i].Name;
            introduction[story_line_real_count] = STORY_LINES[i].Introduction;
            
            if (PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] >= 99)
            {
                story_list[story_line_real_count] = i;// 99����ȫ��ͨ��
            }
            else
            {
                if (i <= PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE])
                {
                    if (STORY_LINES[i].Repeatable == 0 || (i == PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE]))
                    {
                        story_list[story_line_real_count] = i;
                    }
                    else
                    {
                        story_list[story_line_real_count] = -1;
                    }
                }
                else
                {
                    story_list[story_line_real_count] = -1;// û�浽���治��
                }
            }
            story_line_real_count += 1;
        }

    }
    const char* const_level_buttons[MAX_STORY_LINES];
    const char* const_introduction[MAX_BUTTONS];
    for (int i = 0; i < story_count; i++)
    {
        const_level_buttons[i] = level_buttons[i];
        const_introduction[i] = introduction[i];
    }

    // ѡ��ؿ�������
    int story_choice = menu(story_count, "�ؿ�ѡ��", story_list, const_level_buttons, const_introduction,1);

    if (story_choice != -10999)// menu������ESC��
    {
        OPPONENT = STORY_LINES[story_choice].Opponent_Stats;
        if (fight())//��Ӯ��
        {
            SKILL_PROPS Story_Line_Win_Consequence = STORY_LINES[story_choice].Win_Consequence;

            // ��ȡ����
            PLAYER.PROPS[99][0] = STORY_LINES[story_choice].Win_Award_Code;
            PLAYER.PROPS[99][1] = 1;
            cleanAndOrganizeProps();

            PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] = fmax(PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE], story_choice + 1);// �����������һλ,������Ѿ�����ģ���Ϊ0

            //role_stats Refreshed_Status;
            if (Story_Line_Win_Consequence.object == 1)
            {
                PLAYER.ATK = PLAYER.ATK * Story_Line_Win_Consequence.Operate_ATK;
                PLAYER.DEF = PLAYER.DEF * Story_Line_Win_Consequence.Operate_DEF;
                PLAYER.HP = PLAYER.HP + Story_Line_Win_Consequence.Operate_HP;
                PLAYER.Money = PLAYER.Money + Story_Line_Win_Consequence.Operate_Money;
                printf("%s\n�������������\n", Story_Line_Win_Consequence.prompt);
                clearInputBuffer();
                while (!_kbhit()) {}
            }
            PLAYER_SAVE.Player_Stats = PLAYER;
            int save_count = 1;
            if (!SaveSaveFile(&PLAYER_SAVE, &save_count))
            {
                printf("�浵�ļ�����ʧ��!\n");
            }
            else
            {
                printf("�浵�ļ��ѱ���\n");
            }
            return 0;

        }
        else// ����
        {
            SKILL_PROPS Story_Line_Lose_Consequence = STORY_LINES[story_choice].Lose_Consequence;

            //role_stats Refreshed_Status;

            if (Story_Line_Lose_Consequence.object == 1)
            {
                PLAYER.ATK = PLAYER.ATK * Story_Line_Lose_Consequence.Operate_ATK;
                PLAYER.DEF = PLAYER.DEF * Story_Line_Lose_Consequence.Operate_DEF;
                PLAYER.HP = PLAYER.HP + Story_Line_Lose_Consequence.Operate_HP;
                PLAYER.Money = PLAYER.Money + Story_Line_Lose_Consequence.Operate_Money;
                printf("%s\n�������������\n", Story_Line_Lose_Consequence.prompt);
                clearInputBuffer();
                while (!_kbhit()) {}
            }
            PLAYER_SAVE.Player_Stats = PLAYER;
            int save_count = 1;
            if (!SaveSaveFile(&PLAYER_SAVE, &save_count))
            {
                printf("�浵�ļ�����ʧ��!\n");
            }
            else
            {
                printf("�浵�ļ��ѱ���\n");
            }
            return 0;
        }
        
    }
    else// �˳��ź�
    {
        return 0;
    }
        


    
}