#include"functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <commdlg.h>



int last_f = -1;//��ʼ��ȫ�ֱ���
int STORY_LINE_CODE = 0;//ָʾ���ǵڼ��׾���

role_stats OPPONENT;
SKILL_PROPS  SKILL_PROPS_LIST[MAX_SKILLS];//ȫ�ֱ�����ʼ��һ��Ҫ�ں����ⲿ
int skill_count = 0;//������ڼ��ص�ʱ����loader��ˢ��

Story_Line STORY_LINES[MAX_STORY_LINES];//������
int story_count = 0; // ��ǰ��������

Save PLAYER_SAVE;
role_stats PLAYER = PLAYER_SAVE.Player_Stats;
int save_count = 0;



// ����һ�������������ļ�·����������ļ�̫���ˣ�������
wchar_t* SelectFile() {
    OPENFILENAME ofn;
    wchar_t szFile[260] = { 0 }; // ʹ�ÿ��ַ�����
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // ����GetOpenFileName���������ļ�ѡ��Ի���
    if (GetOpenFileName(&ofn) == TRUE) {
        // ��̬�����ڴ����洢�ļ�·��
        wchar_t* filePath = (wchar_t*)malloc((wcslen(ofn.lpstrFile) + 1) * sizeof(wchar_t));
        if (filePath != NULL) {
            // ʹ�ð�ȫ���������ַ���
            wcscpy_s(filePath, wcslen(ofn.lpstrFile) + 1, ofn.lpstrFile);
            return filePath;
        }
    }

    // ���û��ѡ���ļ�������ڴ�ʧ�ܣ�����NULL
    return NULL;
}


int main()
{
Start_Main:

	char cmd[401] = { '\0' };
	int state = 0;
    bool success_load = 0;

    if (LoadSkillsPropsFile(SKILL_PROPS_LIST, &skill_count))
    {
        printf("����������б��ļ�����ɹ�\n");
    }
    if (skill_count == 0)
    {
        SKILL_PROPS_LIST[0] =
        {
            "��Ч����",
            0,
            1,
            1,
            0,
            1,//1����ȫ��������0����ȫ����
            0,
            0,
            0,
            "����һ����Ч����"
        };
        SKILL_PROPS_LIST[1] =
        {
            "������ʯ��ʹ�ú�������Ѫ������20��",
            2,
            1,
            1,
            20,
            1,
            0,
            0,
            0,
            "������ʯ���ü����ڷ�սʱʹ�ã���������Ѫ��"
        };
        SKILL_PROPS_LIST[2] =
        {
            "�޼᲻�ݣ����غ϶�ս�к��ӶԷ��Ļ��ף�",//���޵еĹ���
            2,
            2,
            1,
            0,
            99999,
            0,
            3,
            0,
            "�޼᲻�ݣ�ս���У�ʹ�ú󱾻غ϶�ս�к��ӶԷ��Ļ���"
        };
        skill_count = 3;
        printf("����������б��ļ�Ϊ�գ���д��Ĭ��ֵ����Ҫɾ�ģ���ͨ���������ù���ִ��\n");
        if (!SaveSkillsPropsFile(SKILL_PROPS_LIST, &skill_count))
        {
            printf("����������б��ļ�����ʧ��!\n");
        }
        else
        {
            printf("����������б��ļ��ѱ���ΪĬ��ֵ����Ҫɾ�ģ���ͨ���������ù���ִ��\n");
        }
    }

    if (LoadStoryLinesFile(STORY_LINES, &story_count))
    {
        printf("�����ļ�����ɹ�\n");
    }
    if (story_count == 0)
    {
        // ��ʼ���ṹ��
        //ע���������Ӯ���ֻ�ǽ�����SkillProps�ṹ���ʽ�������Ǵ洢�ھ����ļ���ģ�Ҳ�����ü��ܶ�ȡ�����������б���
        STORY_LINES[0] =//���Ǹ����ֽ̳�
        {
            "���ֽ̳�",
            "���⣬����һ�����ֽ̳�",
            {
                "����С��",
                10,
                100,
                1.0,
                0,
                0,
                0
            },//��ʼ����������
            {
                "��ϲ��ͨ�����ֽ̳̣�",
                1,
                1,
                1.01,
                1,
                0.99,
                100,
                0,
                0,
                "ͨ�����̵ֽ̳ļӳ�"
            },//��ʼ��ʤ�����
            {
                "��ʧ���ˣ����ִ��㶼�����ˣ�������",
                1,
                1,
                1.0,
                0,
                1.0,
                9,
                0,
                0,
                "���ֽ̳�ʧ�ܵĽ��"
            },//��ʼ��ʧ�ܺ��
            1000,
            0
        };

        story_count = 1;
        printf("�����б��ļ�Ϊ�գ���д��Ĭ��ֵ����Ҫɾ�ģ���ͨ���������ù���ִ��\n");
        if (!SaveStoryLinesFile(STORY_LINES, &story_count))
        {
            printf("�����ļ�����ʧ��!\n");
        }
        else
        {
            printf("�����ļ��ѱ���ΪĬ��ֵ����Ҫɾ�ģ���ͨ���������ù���ִ��\n");
        }
    }

    const wchar_t* default_save_filePath = L"classic_save.dat";
    if (LoadSaveFile(&PLAYER_SAVE, &save_count, default_save_filePath))
    {
        printf("Ĭ�ϴ浵�ļ�����ɹ�\n");
        success_load = 1;

    }

    Sleep(1500);
    cleanAndOrganizeProps();
    int main_menu_arr[MAX_BUTTONS] = { 0,1,2,3,-1 };
    if (!success_load)
    {
        main_menu_arr[2] = -1;
    }
    const char* main_menu_buttons[MAX_BUTTONS] =
    {
        "�˳���Ϸ",
        "��ʼ����Ϸ",
        "������Ϸ",
        "���ļ�ѡ��浵",
        "��Ϸ����"
    };
    const char* main_menu_introduction[MAX_BUTTONS] = {
    NULL,
    "��ԭʼ�浵�������е�Ĭ�ϴ浵�ļ���classic_save.dot��",
    "���Ͼ���Ϸ����ġ�classic_save.dot��Ĭ�ϴ浵�ļ���ʼ",
    "�˲����Ḳ��ԭ�е�Ĭ�ϴ浵�ļ���",
    "�һ�ûд",
    NULL
    };

    int main_code = menu(5, "����̨", main_menu_arr, main_menu_buttons, main_menu_introduction, 1);

    switch (main_code)
    {
    case 0:// �˳�
        exit(1);
        break;
    case 1:// ����Ϸ
        // �������ɹ����ٴ�ȷ��
        if (success_load)
        {
            printf("ȷ��Ҫɾ��ԭ�д浵��\n");
            int cc_menu_arr[MAX_BUTTONS] = { -1 };//ʹ��Ĭ�Ϸ�������
            const char* cc_menu_buttons[MAX_BUTTONS] =
            {
                "ȡ��",
                "ȷ��"
            };
            const char* introduction[MAX_BUTTONS] = { NULL };
            if (!(menu(2, "ȷ��Ҫɾ��ԭ�д浵��", cc_menu_arr, cc_menu_buttons, introduction) == 1))
            {
                goto Start_Main;
            }
        }

        // ��ʼ���ṹ��
        PLAYER_SAVE =//0�浵
        {
            {
            "Player",
            20,
            100,
            1,
            0,
            {1400,1},
            {{0,0}}
            },
            {0}
        };
        
        save_count = 1;

        cleanAndOrganizeProps();

        {
            char input_name[101]; // ʹ���ַ�����������ַ�ָ������

            // ������뻺����
            rewind(stdin);
            printf("���Լ�������ְɣ�100���ַ����ڣ���");
            // ʹ�� scanf_s ʱ��ȷ���ṩ��������С
            scanf_s("%s", input_name, (unsigned)_countof(input_name));

            // ֱ��ʹ�� input_name������Ҫ�����ָ��ת��
            const char* const_input_name = input_name;

            // ʹ�� strcpy_s ��ȫ�ظ����ַ���
            strcpy_s(PLAYER_SAVE.Player_Stats.Name, 101, const_input_name);
            PLAYER = PLAYER_SAVE.Player_Stats;
        }

        printf("�浵�б��ļ���д��Ĭ��ֵ\n");
        if (!SaveSaveFile(&PLAYER_SAVE, &save_count))
        {
            printf("�浵�ļ�����ʧ��!\n");
        }
        else
        {
            printf("�浵�ļ��ѱ���ΪĬ��ֵ\n");
        }
        // ��������/����

        break;
    case 2:
        // ��Ϊǰ���Ѿ����غ��ˣ�����ֱ�Ӽ�������
        break;
    case 3:
    {//wchar_t* filePath����case��ǩ�ڲ���ʼ���ģ������Ҫ�������޶��������򡣹�ʺ��C����
        wchar_t* filePath = SelectFile();
        if (filePath != NULL) {
            setlocale(LC_ALL, "");
            wprintf(L"Selected file: %ls\n", filePath);
            if (LoadSaveFile(&PLAYER_SAVE, &save_count, filePath))
            {
                printf("ָ���浵�ļ�����ɹ�\n");
                success_load = 1;
                free(filePath); // �ͷ�Ϊ�ļ�����̬������ڴ�
            }
            else
            {
                printf("ָ���浵�ļ��������\n");
                success_load = 1;
                free(filePath); // �ͷ�Ϊ�ļ�����̬������ڴ�
                goto Start_Main;
            }
            
        }
        else {
            wprintf(L"No file selected.\n");
            goto Start_Main;
        }
    }
        break;
    case 4:
        break;
    default:
        break;
    }

    PLAYER = PLAYER_SAVE.Player_Stats;
	while (1)
	{
		//fflush(stdin);
		//scanf_s("%s", cmd, 401);
		//const char *cmdinput = cmd;
		//logger(INFO, Main, "�����������յ����������");
		//logger(INFO, Main, cmdinput);
		//logger(INFO, Main, "==========================");
        const char* cmdinput = "ber";// ȡ���ˣ��������øĴ���
		Console_Command(cmdinput, state, last_f);
	}
	

}