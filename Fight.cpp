#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>


// 设置文本颜色为指定的 RGB 值
void setTextColorRGB(int r, int g, int b) {
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}
//战斗蓄力条，按下空格停止蓄力，按下回车选择技能
float progress_bar() {
    int progress = 0;
    int max_progress = 100;
    float current_value = 0.0;
    float increment = 0.04;
    clearInputBuffer();//清除缓冲区
    while (1) {
        // 清空当前行
        printf("\r");
        for (int i = 0; i < 80; i++) {
            printf(" ");
        }
        printf("\r");

        // 打印进度条
        printf("【");
        for (int i = 0; i < progress; i++) {
            // 根据进度设置颜色
            int r = (i * 255) / max_progress;
            int g = 255 - (i * 255) / max_progress;
            int b = 0; // 保持蓝色为0
            setTextColorRGB(r, g, b);
            printf("█");
        }
        for (int i = progress; i < max_progress; i++) {
            printf(" ");
        }
        printf("\x1b[0m】"); // 重置颜色

        // 更新进度和数值
        progress = (int)(current_value * max_progress);
        current_value += increment;
        if (current_value > 1.0) {
            current_value = 0.0;
        }

        // 检查键盘输入
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                printf("\n蓄力百分比: %.2f\n", current_value);
                return current_value + 0.5;//返回蓄力指数0.5-1.5
            }
            else if (ch == 13)
            {
                printf("\n选择了使用技能或道具：\n");
                return -1.0;//fight会判断返回值，如果是-1则开始技能相关操作
            }
        }

        // 稍作延迟
        Sleep(10); // 100毫秒
    }
}
// 显示角色血量的函数
void displayHealthBar(int maxHealth, int currentHealth, const char* characterName, int align) {
    const int barLength = 25; // 血条总长度为25个方块字符
    int filledBlocks = (currentHealth * barLength) / maxHealth; // 计算当前血量对应的方块数
    int emptyBlocks = barLength - filledBlocks; // 计算剩余的方块数

    // 打印血量信息和角色名称
    if (align == 1) { // 右对齐
        printf("%*s", 75, ""); // 在血量信息前打印空格以实现右对齐，假设控制台宽度为50
    }
    printf("%s: %d/%d\n", characterName, currentHealth, maxHealth);

    // 打印血条
    if (align == 1) { // 右对齐
        printf("%*s", 100 - barLength, ""); // 在血条前打印空格以实现右对齐
    }
    setTextColorRGB(255, 0, 0); // 设置血条颜色为红色
    for (int i = 0; i < filledBlocks; i++) {
        printf("█"); // 打印彩色方块表示当前血量
    }
    setTextColorRGB(255, 255, 255); // 设置剩余部分颜色为白色
    for (int i = 0; i < emptyBlocks; i++) {
        printf("█"); // 打印白色方块表示剩余血量
    }
    printf("\x1b[0m"); // 重置颜色
    printf("\n");
}




int fight(int *last_time_HP)//一整个打架流程，默认返回的是输赢的布尔值，last_time_HP用来传回对局结束时玩家的剩余血量，
{
    role_stats FightTempPlayerStats = PLAYER;
    role_stats FightTempOpponentStats = OPPONENT;//因为技能会在对局内更改stats，对局结束后恢复，所以这里临时存储，Using_Skill_Props函数的操作都针对这两个临时变量

    int ROUND = 1;
    int state = 2;

    int n_Round_Effect = -1;//指示那些n回合有效的技能。启动n回合有效技能会刷新计数器，在计数器归零后，对双方的stats执行反向操作
    bool new_n_Round_Effect_Happpen = 0;//指示是否发生了新的n回合式技能道具操作
    SKILL_PROPS n_Round_Effect_SK;//用于存储这个技能，方便回溯
    role_stats n_Round_Effect_FightTempPlayerStats = PLAYER;//用来存储n回合有效技能的断点信息。回断点时，生命值采用回溯SPR操作的方式，否则会把回合中打下的血加回去。，防御值和攻击力用这个断点，不然比如无坚不摧通过*99999，再依靠更改检查，来把防御值变为1.再回溯的话就是除以99999，这个起不到意义
    role_stats n_Round_Effect_FightTempOpponentStats = OPPONENT;
    
    displayHealthBar(PLAYER.HP, FightTempPlayerStats.HP, FightTempPlayerStats.Name, 0);//打印开始时双方血量
    displayHealthBar(OPPONENT.HP, FightTempOpponentStats.HP, FightTempOpponentStats.Name, 1);//1代表右对齐

    while (1)
    {
        printf("===================================第%d回合===================================\n",ROUND);
        Sleep(2000);
        float ATTACK;
        float charged_value = progress_bar();
        if (charged_value < 0)
        {
            int code;
            char SPmessage[101] = { '\0' };
            printf("请输入要发动的技能名称或代码，输入“h”可以显示当前可用的技能：");
            fflush(stdin);
            scanf_s("%s", SPmessage, 101);
            const char* pSPmessage = SPmessage;

            //显示可用技能
            if (strstr(pSPmessage, "h"))
            {
                printf("======================当前可用的道具====================\n");
                for (int i = 0; i < 100; i++) {
                    if (PLAYER.PROPS[i][0] != 0 || PLAYER.PROPS[i][1] != 0) {
                        if (SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].state == state)
                        {
                            printf("编号 %d:\t\t %s\t剩余%d个\n", PLAYER.PROPS[i][0], SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].prompt, PLAYER.PROPS[i][1]);
                        }
                    }
                }
                printf("======================当前可用的技能====================\n");
                if (PLAYER.SKILL[1])
                {
                    printf("编号 %d\t%s\n", PLAYER.SKILL[0], SKILL_PROPS_LIST[PLAYER.SKILL[0]].prompt);
                }
                printf("============================================================\n");
                continue;
            }

            //处理技能释放
            {
                role_stats* FightTempPlayer_OpponentStatsList = Using_Skill_Props(&new_n_Round_Effect_Happpen, &n_Round_Effect_SK, &n_Round_Effect,AnalyseSP(pSPmessage), state, FightTempPlayerStats, FightTempOpponentStats);//2代表战斗中
                if (!new_n_Round_Effect_Happpen)//当新的n回合型技能生效，这里保存一组状态断点。由于更改是在这行的上一行完成的，所以这里的逻辑是每轮都断点，发生上述就开始不断点
                {
                    n_Round_Effect_FightTempPlayerStats = FightTempPlayerStats;
                    n_Round_Effect_FightTempOpponentStats = FightTempOpponentStats;
                }
                FightTempPlayerStats = FightTempPlayer_OpponentStatsList[0];//USP函数返回的是结构体组的指针，组的第一个是玩家，第二个是对手
                FightTempOpponentStats = FightTempPlayer_OpponentStatsList[1];//先创建一个新的结构体组用于存储USP的返回，避免要调用两次。局部这个新的，节省内存
            }
            continue;
        }
        ATTACK = FightTempOpponentStats.DEF * FightTempPlayerStats.ATK * charged_value;

        FightTempOpponentStats.HP = FightTempOpponentStats.HP + 0.5 - ATTACK;
        printf("你对敌人产生了%f点伤害，敌人当前血量：%d\n\n", ATTACK, FightTempOpponentStats.HP);
        
        displayHealthBar(OPPONENT.HP, FightTempOpponentStats.HP, FightTempOpponentStats.Name, 1);//1代表右对齐
        if (FightTempOpponentStats.HP <= 0)//对面死了
        {
            printf("敌人战败，你胜利了！\n");
            printf("=============================================================================\n");
            PLAYER.SKILL[1] = 1;
            cleanAndOrganizeProps();

            if (last_time_HP != nullptr)
            {
                *last_time_HP = FightTempPlayerStats.HP;
            }
            printf("按任意键继续\n");
            while (!_kbhit()) {}
            return 1;
        }
        // 初始化随机数生成器
        //srand((unsigned int)time(NULL));
        // 生成一个介于 0.0 到 1.0 之间的随机浮点数
        Sleep(2000);
        float randomFloat = (float)rand() / RAND_MAX;
        ATTACK = FightTempOpponentStats.ATK * FightTempPlayerStats.DEF * (randomFloat + 0.5);//怪的蓄力值随机
        FightTempPlayerStats.HP = FightTempPlayerStats.HP + 0.5 - ATTACK;//四舍五入
        printf("敌人对你产生了%f点伤害，你当前血量：%d\n\n", ATTACK, FightTempPlayerStats.HP);
        displayHealthBar(PLAYER.HP, FightTempPlayerStats.HP, FightTempPlayerStats.Name, 0);
        if (FightTempPlayerStats.HP <= 0)//玩家死了
        {
            printf("你被击败了！\n");
            printf("=============================================================================\n");
            PLAYER.SKILL[1] = 1;
            cleanAndOrganizeProps();
            printf("按任意键继续\n");
            while (!_kbhit()) {}
            return 0;
        }
        printf("=============================================================================\n");
        ROUND += 1;

        if (n_Round_Effect > 0)//每轮后减少一个计数次数
        {
            n_Round_Effect -= 1;
        }
        if (n_Round_Effect == 0)
        {//回溯逻辑
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
            printf("对n回合型道具或技能的禁用已解除！\n其效果已消失！\n");
            n_Round_Effect = -1;
            new_n_Round_Effect_Happpen = 0;//0指示没有新的回合技能，此时上面的断点获取会继续
        }//一个神奇的小逻辑，可以控制这个计数器的启停和存储数字
    }



    return 1;
}