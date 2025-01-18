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
        printf("该功能仅限开发者使用！\n");
        return;
    }
    int index;
    printf("==========================================\n");
    printf("请输入要写入的序号（1-%d）：", MAX_STORY_LINES);
    scanf_s("%d", &index);
    index--; // 将用户输入的序号转换为数组索引（从0开始）

    if (index < 0 || index >= MAX_STORY_LINES) {
        printf("序号超出范围！\n");
        return;
    }

    if ((STORY_LINES[index].Name != "待设置的关卡") && (STORY_LINES[index].Name[0] != '0')) {
        printf("该位置已被占用，请选择其他位置。\n");
        /*return;*/
    }

    printf("请输入剧情名称（最多100个字符）：");
    getchar(); // 清除缓冲区中的换行符
    fgets(STORY_LINES[index].Name, 101, stdin);
    STORY_LINES[index].Name[strcspn(STORY_LINES[index].Name, "\n")] = '\0'; // 去除末尾的换行符

    printf("请输入剧情介绍（最多400个字符）：");
    //getchar(); // 清除缓冲区中的换行符
    fgets(STORY_LINES[index].Introduction, 401, stdin);
    STORY_LINES[index].Introduction[strcspn(STORY_LINES[index].Introduction, "\n")] = '\0'; // 去除末尾的换行符

    printf("请输入对手名字（最多100个字符）：");
    //getchar(); // 清除缓冲区中的换行符
    fgets(STORY_LINES[index].Opponent_Stats.Name, 101, stdin);
    STORY_LINES[index].Opponent_Stats.Name[strcspn(STORY_LINES[index].Opponent_Stats.Name, "\n")] = '\0'; // 去除末尾的换行符

    printf("请输入对手的HP：");
    scanf_s("%d", &STORY_LINES[index].Opponent_Stats.HP);
    printf("请输入对手的ATK：");
    scanf_s("%d", &STORY_LINES[index].Opponent_Stats.ATK);
    printf("请输入对手的DEF：");
    scanf_s("%f", &STORY_LINES[index].Opponent_Stats.DEF);

    STORY_LINES[index].Opponent_Stats.Money = 0;
    *STORY_LINES[index].Opponent_Stats.SKILL = { 0 };
    **STORY_LINES[index].Opponent_Stats.PROPS = { 0 };//几个没用的属性值也初始化了




    // 设置胜利后果
    printf("请输入胜利后的提示信息：");
    getchar(); // 清除缓冲区中的换行符
    fgets(STORY_LINES[index].Win_Consequence.prompt, 101, stdin);
    STORY_LINES[index].Win_Consequence.prompt[strcspn(STORY_LINES[index].Win_Consequence.prompt, "\n")] = '\0'; // 去除末尾的换行符

    printf("请输入胜利后的攻击力操作（百分比）：");
    scanf_s("%f", &STORY_LINES[index].Win_Consequence.Operate_ATK);

    printf("请输入胜利后的血量（上限）操作：");
    scanf_s("%d", &STORY_LINES[index].Win_Consequence.Operate_HP);

    printf("请输入胜利后的防御力操作（百分比）：");
    scanf_s("%f", &STORY_LINES[index].Win_Consequence.Operate_DEF);

    printf("请输入胜利后的金钱操作：");
    scanf_s("%d", &STORY_LINES[index].Win_Consequence.Operate_Money);

    STORY_LINES[index].Win_Consequence.Fight_Times = 0;
    STORY_LINES[index].Win_Consequence.object = 1;
    STORY_LINES[index].Win_Consequence.state = 1;
    STORY_LINES[index].Win_Consequence.Price = 0;
    *STORY_LINES[index].Win_Consequence.Introduction = { '\0' };//几个没用的数据初始化一下


    // 设置失败后果
    printf("请输入失败后的提示信息：");
    getchar(); // 清除缓冲区中的换行符
    fgets(STORY_LINES[index].Lose_Consequence.prompt, 101, stdin);
    STORY_LINES[index].Lose_Consequence.prompt[strcspn(STORY_LINES[index].Lose_Consequence.prompt, "\n")] = '\0'; // 去除末尾的换行符

    printf("请输入失败后的攻击力操作（百分比）：");
    scanf_s("%f", &STORY_LINES[index].Lose_Consequence.Operate_ATK);

    printf("请输入失败后的血量（上限）操作：");
    scanf_s("%d", &STORY_LINES[index].Lose_Consequence.Operate_HP);

    printf("请输入失败后的防御力操作（百分比）：");
    scanf_s("%f", &STORY_LINES[index].Lose_Consequence.Operate_DEF);

    printf("请输入失败后的金钱操作：");
    scanf_s("%d", &STORY_LINES[index].Lose_Consequence.Operate_Money);

    STORY_LINES[index].Lose_Consequence.Fight_Times = 0;
    STORY_LINES[index].Lose_Consequence.object = 1;
    STORY_LINES[index].Lose_Consequence.state = 1;
    STORY_LINES[index].Lose_Consequence.Price = 0;
    *STORY_LINES[index].Lose_Consequence.Introduction = { '\0' };//几个没用的数据初始化一下


    printf("请输入胜利奖励的技能/道具代码：");
    scanf_s("%d", &STORY_LINES[index].Win_Award_Code);

    printf("请输入是否可以重复（0表示可以重复，1表示只能玩一次，-1表示不可玩）：");
    scanf_s("%d", &STORY_LINES[index].Repeatable);

    printf("剧情已创建并写入到序号 %d。\n", index + 1);
    story_count = (story_count > index + 1) ? story_count : (index + 1); // 更新剧情数量
    printf("==========================================\n");
    if (!SaveStoryLinesFile(STORY_LINES, &story_count))
    {
        printf("剧情文件保存失败!\n");
    }
    else
    {
        printf("剧情文件已更新\n");
    }
    printf("按任意键继续\n");
    while (!_kbhit()) {}
}

void displayBriefStoryLines() {
    printf("当前关卡简略信息：\n");
    printf("==========================================\n");
    for (int i = 0; i < story_count; i++) {
        if (STORY_LINES[i].Name[0] != '\0')
        {
            printf("序号：%d\n", i + 1);
            printf("名称：%s\n", STORY_LINES[i].Name);
            printf("是否可以重复：%s\n", STORY_LINES[i].Repeatable ? "否" : "是");//要改。，有个-1
            printf("----------------\n");
            Sleep(100);
        }
    }
    printf("==========================================\n按任意键继续\n");
    while (!_kbhit()) {}
}

void displayDetailedStoryLine() {
    int index;
    printf("请输入要查看详细信息的关卡编码（1-%d）：", story_count);
    scanf_s("%d", &index);
    index--; // 将用户输入的编码转换为数组索引（从0开始）

    if (index < 0 || index >= story_count) {
        printf("编码超出范围！\n");
        return;
    }
    if (STORY_LINES[index].Name[0] == '\0')
    {
        printf("该处剧情为空！\n");
        return;
    }
    printf("==========================================\n");
    printf("关卡名称：%s\n", STORY_LINES[index].Name);
    printf("介绍：%s\n", STORY_LINES[index].Introduction);
    printf("对手属性：HP=%d, ATK=%d, DEF=%f\n",
        STORY_LINES[index].Opponent_Stats.HP,
        STORY_LINES[index].Opponent_Stats.ATK,
        STORY_LINES[index].Opponent_Stats.DEF);
    Sleep(500);
    // 显示胜利后果
    printf("----------------\n");
    printf("胜利奖励：\n");
    printf("提示信息：%s\n", STORY_LINES[index].Win_Consequence.prompt);
    printf("攻击力操作（百分比）：*%.2f\n", STORY_LINES[index].Win_Consequence.Operate_ATK);
    printf("血量（上限）操作： +%d\n", STORY_LINES[index].Win_Consequence.Operate_HP);
    printf("防御力操作（百分比）：*%.2f\n", STORY_LINES[index].Win_Consequence.Operate_DEF);
    printf("金钱操作： +%d\n", STORY_LINES[index].Win_Consequence.Operate_Money);
    printf("----------------\n");
    Sleep(500);
    // 显示失败后果
    printf("----------------\n");
    printf("失败后果：\n");
    printf("提示信息：%s\n", STORY_LINES[index].Lose_Consequence.prompt);
    printf("攻击力操作（百分比）：*%.2f\n", STORY_LINES[index].Lose_Consequence.Operate_ATK);
    printf("血量（上限）操作： +%d\n", STORY_LINES[index].Lose_Consequence.Operate_HP);
    printf("防御力操作（百分比）：*%.2f\n", STORY_LINES[index].Lose_Consequence.Operate_DEF);
    printf("金钱操作： +%d\n", STORY_LINES[index].Lose_Consequence.Operate_Money);
    printf("----------------\n");

    printf("胜利奖励的代码：%d\n具体的奖励：\n", STORY_LINES[index].Win_Award_Code);
    displayDetail(STORY_LINES[index].Win_Award_Code);
    printf("是否可以重复：%s\n", STORY_LINES[index].Repeatable ? "否" : "是");
    printf("==========================================\n按任意键继续\n");
    while (!_kbhit()) {}
}

void deleteStoryLine() {
    if (!develop_mode)
    {
        printf("该功能仅限开发者使用！\n");
        return;
    }
    int index;
    printf("请输入要删除的关卡编码（1-%d）：", story_count);
    scanf_s("%d", &index);
    index--; // 将用户输入的编码转换为数组索引（从0开始）

    if (index < 0 || index >= story_count) {
        printf("编码超出范围！\n");
        return;
    }

    // 初始化结构体
    STORY_LINES[index] =
    {
        "待设置的关卡",//初始化关卡名
        "待设置的关卡介绍",//初始化关卡介绍
        {
            {'\0'},
            0,
            0,
            1.0,
            0,
            0,
            0
        },//初始化敌人属性
        {
            "无效操作",
            0,
            1,
            1,
            0,
            1,
            0,
            0,
            0,
            "这是一个无效操作"
        },//初始化胜利后果
        {
            "无效操作",
            0,
            1,
            1,
            0,
            1,
            0,
            0,
            0,
            "这是一个无效操作"
        },//初始化失败后果
        0,
        -1//-1指示不可用
    };
    Sleep(500);
    printf("关卡已删除并初始化！\n");
    if (!SaveStoryLinesFile(STORY_LINES, &story_count))
    {
        printf("剧情文件保存失败!\n");
    }
    else
    {
        printf("剧情文件已更新\n");
    }
    printf("按任意键继续\n");
    while (!_kbhit()) {}
}

void storyLineControl() {
    int command;

    while (1) {
        //Sleep(1500);
        //rewind(stdin);
        //printf("\n剧情查看与创建器：请输入命令：\n");
        //printf("1. 查看关卡简略信息\n");
        //printf("2. 查看关卡详细信息\n");
        //printf("3. 删除关卡\n");
        //printf("4. 创建新关卡\n");
        //printf("5. 退出\n");
        //scanf_s("%d", &command);
        int slc_menu_arr[MAX_BUTTONS] = { -1 };
        const char* slc_menu_button[MAX_BUTTONS] =
        { "退出",
            "查看关卡简略信息",
            "查看关卡详细信息",
            "删除关卡",
            "创建新关卡"
        };
        const char* introduction[MAX_BUTTONS] = {
        NULL
        };
        command = menu(5, "剧情查看与创建器", slc_menu_arr, slc_menu_button, introduction);

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
            printf("退出程序。\n");
            return;
        default:
            printf("无效的命令！\n");
        }
    }
}

int StoryLineModeControl()
{
    //展示所有可用的剧情关卡
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
                story_list[story_line_real_count] = i;// 99代表全部通关
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
                    story_list[story_line_real_count] = -1;// 没玩到的玩不了
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

    // 选择关卡并设置
    int story_choice = menu(story_count, "关卡选择", story_list, const_level_buttons, const_introduction,1);

    if (story_choice != -10999)// menu的特殊ESC码
    {
        OPPONENT = STORY_LINES[story_choice].Opponent_Stats;
        if (fight())//打赢了
        {
            SKILL_PROPS Story_Line_Win_Consequence = STORY_LINES[story_choice].Win_Consequence;

            // 获取道具
            PLAYER.PROPS[99][0] = STORY_LINES[story_choice].Win_Award_Code;
            PLAYER.PROPS[99][1] = 1;
            cleanAndOrganizeProps();

            PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] = fmax(PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE], story_choice + 1);// 剧情坐标后移一位,如果打已经玩过的，就为0

            //role_stats Refreshed_Status;
            if (Story_Line_Win_Consequence.object == 1)
            {
                PLAYER.ATK = PLAYER.ATK * Story_Line_Win_Consequence.Operate_ATK;
                PLAYER.DEF = PLAYER.DEF * Story_Line_Win_Consequence.Operate_DEF;
                PLAYER.HP = PLAYER.HP + Story_Line_Win_Consequence.Operate_HP;
                PLAYER.Money = PLAYER.Money + Story_Line_Win_Consequence.Operate_Money;
                printf("%s\n按下任意键继续\n", Story_Line_Win_Consequence.prompt);
                clearInputBuffer();
                while (!_kbhit()) {}
            }
            PLAYER_SAVE.Player_Stats = PLAYER;
            int save_count = 1;
            if (!SaveSaveFile(&PLAYER_SAVE, &save_count))
            {
                printf("存档文件保存失败!\n");
            }
            else
            {
                printf("存档文件已保存\n");
            }
            return 0;

        }
        else// 输了
        {
            SKILL_PROPS Story_Line_Lose_Consequence = STORY_LINES[story_choice].Lose_Consequence;

            //role_stats Refreshed_Status;

            if (Story_Line_Lose_Consequence.object == 1)
            {
                PLAYER.ATK = PLAYER.ATK * Story_Line_Lose_Consequence.Operate_ATK;
                PLAYER.DEF = PLAYER.DEF * Story_Line_Lose_Consequence.Operate_DEF;
                PLAYER.HP = PLAYER.HP + Story_Line_Lose_Consequence.Operate_HP;
                PLAYER.Money = PLAYER.Money + Story_Line_Lose_Consequence.Operate_Money;
                printf("%s\n按下任意键继续\n", Story_Line_Lose_Consequence.prompt);
                clearInputBuffer();
                while (!_kbhit()) {}
            }
            PLAYER_SAVE.Player_Stats = PLAYER;
            int save_count = 1;
            if (!SaveSaveFile(&PLAYER_SAVE, &save_count))
            {
                printf("存档文件保存失败!\n");
            }
            else
            {
                printf("存档文件已保存\n");
            }
            return 0;
        }
        
    }
    else// 退出信号
    {
        return 0;
    }
        


    
}