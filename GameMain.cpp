#include"functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <commdlg.h>



int last_f = -1;//初始化全局变量
int STORY_LINE_CODE = 0;//指示这是第几套剧情

role_stats OPPONENT;
SKILL_PROPS  SKILL_PROPS_LIST[MAX_SKILLS];//全局变量初始化一定要在函数外部
int skill_count = 0;//这个，在加载的时候在loader会刷新

Story_Line STORY_LINES[MAX_STORY_LINES];//剧情组
int story_count = 0; // 当前剧情数量

Save PLAYER_SAVE;
role_stats PLAYER = PLAYER_SAVE.Player_Stats;
int save_count = 0;



// 定义一个函数，返回文件路径。这个分文件太烦了，不做了
wchar_t* SelectFile() {
    OPENFILENAME ofn;
    wchar_t szFile[260] = { 0 }; // 使用宽字符数组
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

    // 调用GetOpenFileName函数弹出文件选择对话框
    if (GetOpenFileName(&ofn) == TRUE) {
        // 动态分配内存来存储文件路径
        wchar_t* filePath = (wchar_t*)malloc((wcslen(ofn.lpstrFile) + 1) * sizeof(wchar_t));
        if (filePath != NULL) {
            // 使用安全函数复制字符串
            wcscpy_s(filePath, wcslen(ofn.lpstrFile) + 1, ofn.lpstrFile);
            return filePath;
        }
    }

    // 如果没有选择文件或分配内存失败，返回NULL
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
        printf("技能与道具列表文件载入成功\n");
    }
    if (skill_count == 0)
    {
        SKILL_PROPS_LIST[0] =
        {
            "无效技能",
            0,
            1,
            1,
            0,
            1,//1是完全不防御，0是完全防御
            0,
            0,
            0,
            "这是一个无效技能"
        };
        SKILL_PROPS_LIST[1] =
        {
            "坚如磐石！使用后中自身血量增加20！",
            2,
            1,
            1,
            20,
            1,
            0,
            0,
            0,
            "坚如磐石，该技能在非战时使用，可以增加血量"
        };
        SKILL_PROPS_LIST[2] =
        {
            "无坚不摧！本回合对战中忽视对方的护甲！",//好无敌的功能
            2,
            2,
            1,
            0,
            99999,
            0,
            3,
            0,
            "无坚不摧，战斗中，使用后本回合对战中忽视对方的护甲"
        };
        skill_count = 3;
        printf("技能与道具列表文件为空，已写入默认值，若要删改，请通过程序内置功能执行\n");
        if (!SaveSkillsPropsFile(SKILL_PROPS_LIST, &skill_count))
        {
            printf("技能与道具列表文件保存失败!\n");
        }
        else
        {
            printf("技能与道具列表文件已保存为默认值，若要删改，请通过程序内置功能执行\n");
        }
    }

    if (LoadStoryLinesFile(STORY_LINES, &story_count))
    {
        printf("剧情文件载入成功\n");
    }
    if (story_count == 0)
    {
        // 初始化结构体
        //注意里面的输赢后果只是借用了SkillProps结构体格式，本身是存储在剧情文件里的，也不会让技能读取器读到技能列表里
        STORY_LINES[0] =//这是个新手教程
        {
            "新手教程",
            "如题，这是一个新手教程",
            {
                "新手小怪",
                10,
                100,
                1.0,
                0,
                0,
                0
            },//初始化敌人属性
            {
                "恭喜你通过新手教程！",
                1,
                1,
                1.01,
                1,
                0.99,
                100,
                0,
                0,
                "通过新手教程的加成"
            },//初始化胜利后果
            {
                "你失败了，新手村你都过不了？还得练",
                1,
                1,
                1.0,
                0,
                1.0,
                9,
                0,
                0,
                "新手教程失败的结果"
            },//初始化失败后果
            1000,
            0
        };

        story_count = 1;
        printf("剧情列表文件为空，已写入默认值，若要删改，请通过程序内置功能执行\n");
        if (!SaveStoryLinesFile(STORY_LINES, &story_count))
        {
            printf("剧情文件保存失败!\n");
        }
        else
        {
            printf("剧情文件已保存为默认值，若要删改，请通过程序内置功能执行\n");
        }
    }

    const wchar_t* default_save_filePath = L"classic_save.dat";
    if (LoadSaveFile(&PLAYER_SAVE, &save_count, default_save_filePath))
    {
        printf("默认存档文件载入成功\n");
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
        "退出游戏",
        "开始新游戏",
        "继续游戏",
        "从文件选择存档",
        "游戏介绍"
    };
    const char* main_menu_introduction[MAX_BUTTONS] = {
    NULL,
    "用原始存档覆盖已有的默认存档文件“classic_save.dot”",
    "从上局游戏保存的“classic_save.dot”默认存档文件开始",
    "此操作会覆盖原有的默认存档文件！",
    "我还没写",
    NULL
    };

    int main_code = menu(5, "启动台", main_menu_arr, main_menu_buttons, main_menu_introduction, 1);

    switch (main_code)
    {
    case 0:// 退出
        exit(1);
        break;
    case 1:// 新游戏
        // 如果载入成功，再次确认
        if (success_load)
        {
            printf("确定要删除原有存档吗？\n");
            int cc_menu_arr[MAX_BUTTONS] = { -1 };//使用默认返回索引
            const char* cc_menu_buttons[MAX_BUTTONS] =
            {
                "取消",
                "确定"
            };
            const char* introduction[MAX_BUTTONS] = { NULL };
            if (!(menu(2, "确定要删除原有存档吗？", cc_menu_arr, cc_menu_buttons, introduction) == 1))
            {
                goto Start_Main;
            }
        }

        // 初始化结构体
        PLAYER_SAVE =//0存档
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
            char input_name[101]; // 使用字符数组而不是字符指针数组

            // 清空输入缓冲区
            rewind(stdin);
            printf("给自己起个名字吧（100个字符以内）：");
            // 使用 scanf_s 时，确保提供缓冲区大小
            scanf_s("%s", input_name, (unsigned)_countof(input_name));

            // 直接使用 input_name，不需要额外的指针转换
            const char* const_input_name = input_name;

            // 使用 strcpy_s 安全地复制字符串
            strcpy_s(PLAYER_SAVE.Player_Stats.Name, 101, const_input_name);
            PLAYER = PLAYER_SAVE.Player_Stats;
        }

        printf("存档列表文件已写入默认值\n");
        if (!SaveSaveFile(&PLAYER_SAVE, &save_count))
        {
            printf("存档文件保存失败!\n");
        }
        else
        {
            printf("存档文件已保存为默认值\n");
        }
        // 开场动画/介绍

        break;
    case 2:
        // 因为前面已经加载好了，所以直接继续即可
        break;
    case 3:
    {//wchar_t* filePath是在case标签内部初始化的，因此需要大括号限定其作用域。狗屎的C语言
        wchar_t* filePath = SelectFile();
        if (filePath != NULL) {
            setlocale(LC_ALL, "");
            wprintf(L"Selected file: %ls\n", filePath);
            if (LoadSaveFile(&PLAYER_SAVE, &save_count, filePath))
            {
                printf("指定存档文件载入成功\n");
                success_load = 1;
                free(filePath); // 释放为文件名动态分配的内存
            }
            else
            {
                printf("指定存档文件载入错误！\n");
                success_load = 1;
                free(filePath); // 释放为文件名动态分配的内存
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
		//logger(INFO, Main, "————接收到命令————");
		//logger(INFO, Main, cmdinput);
		//logger(INFO, Main, "==========================");
        const char* cmdinput = "ber";// 取缔了，但我懒得改代码
		Console_Command(cmdinput, state, last_f);
	}
	

}