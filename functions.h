// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_LINE_LENGTH 1000
#define MAX_SKILLS 2000

#define MAX_STORY_LINES 100//一个剧情最多这么多关

#define MAX_BUTTONS 2000//菜单生成器的最大菜单数量


void displayLoadingBar(int duration);
enum LogLevel
{
    DEBUG,
    INFO,
    WARN,
    Error,//傻逼VS，就这个Error，我写成ERROR就给我不运行
    CRITICAL
};
typedef enum LogLevel LogLevel;
//enum类型，赋值的时候只能给予已经定义了的几个关键字，而调用（比如print）的时候返回这个关键字在定义时候的顺序号（这里是0-4）

typedef enum
{
    Logger,
    Main,
    ConsoleCommand,
    GameMain,
    Saver,
    Skills_Props,
    Creator
} WhoLog;
//typedef语句可以简写成上面这个

extern int last_f;//全局，指示上一次调用的功能，用于实现需要多次连续调用的函数。


void logger(LogLevel level, WhoLog who, const char* message);

int Console_Command(
    const char* f_message,
    int state,//0指示main函数
    int special_int = 0,
    int special_int_arr_0[] = { 0 },
    int special_int_arr_1[] = { 0 },
    char special_char_0[] = { '\0' },
    char special_char_1[] = { '\0' }
);
int AnalyseCC(const char* f_message);
void clearInputBuffer();
int menu(int num_buttons, const char* title, int index[MAX_BUTTONS], const char* buttons[MAX_BUTTONS], const char* introduction[MAX_BUTTONS], int mode = 0);//mode = 1，是不显示索引。mode = 2，是显示传入的索引。mode = 0，是使用默认索引返回并不显示
extern bool develop_mode;


struct role_stats
{
    char Name[101];
    int ATK;
    int HP;
    float DEF;
    int Money;
    int SKILL[2];
    int PROPS[100][2];
    //攻击;
    //血量;
    //防御;//比如=0.9，即对方的攻击会变成原来的
    //金钱;
    //特殊技能;//特殊技能是一个技能码，对应到txt
    //道具;
};
typedef struct role_stats role_stats;
extern role_stats PLAYER;//玩家
extern role_stats OPPONENT;//怪


struct SKILL_PROPS//技能结构体
{
    char prompt[101];
    int state;
    int object;
    float Operate_ATK;
    int Operate_HP;
    float Operate_DEF;
    int Operate_Money;
    int Fight_Times;//指示战斗中是几个回合有效还是对局有效。1是一回合，2是两个回合，0是整个对局
    int Price;
    char Introduction[201];
    //技能发动时的提示词;//比如”已使用技能XXX，对方血量减少20“
    //可使用的场景;//指示在战斗中、非战斗在、全部禁用这三种状态，就比如你不能在非战斗情况下使用
    //对自己或是对对方;
    //对攻击的操作;//都是百分比，1.2代表增加到120%
    //对血量的操作;//增减血量上限
    //对防御的操作;
    //对金钱的操作;
};
typedef struct SKILL_PROPS SKILL_PROPS;

extern SKILL_PROPS SKILL_PROPS_LIST[];//存储所有的技能（从文件写入）

extern int skill_count; // 技能数量



int ReadSkillsPropsFile(const wchar_t* filename, struct SKILL_PROPS* skills, int maxSkills);

bool LoadSkillsPropsFile(SKILL_PROPS* pDishes, int* iCount);

bool SaveSkillsPropsFile(SKILL_PROPS* plist, int* iCount);



void setTextColorRGB(int r, int g, int b);
float progress_bar();
void displayHealthBar(int maxHealth, int currentHealth, const char* characterName, int align);
bool isPositiveInt(const char* str, int* result);
int AnalyseSP(const char* SPmessage);

int fight(int * last_time_HP = nullptr);


role_stats* Using_Skill_Props(bool* new_n_Round_Effect_Happpen, SKILL_PROPS* n_Round_Effect_SK, int * n_Round_Effect, int Skill_Prop_code, int state, role_stats Skill_PropsTempPlayerStatus, role_stats Skill_PropsTempOpponentStatus = { {} });
role_stats StatsAlterChecker(role_stats unCheckedStats);
int Using_Skill_Props_Checker(int Skill_Prop_code, int state);
int findPropIndex(int target);
void cleanAndOrganizeProps();
void displayProps();

//剧情结构体，一个关卡一个
typedef struct
{
    char Name[101];
    char Introduction[401];
    role_stats Opponent_Stats;
    SKILL_PROPS Win_Consequence;
    SKILL_PROPS Lose_Consequence;//这个直接定义在存档文件里，打完之后借用USP函数直接对玩家操作，比如增加100金币
    int Win_Award_Code;//这个是写在SKILL_PROPS_LIST里面的，只能通过战斗获得的技能/道具
    int Repeatable;//指示这个关卡能不能重复玩，比如某些特殊道具只能获得一次，就设置成只能玩一次。0指示可以重复，1指示只能玩一次
    //这个的判断方式是，检查玩家存档里关卡当前位置码，如果大于这个结构体内定义的Serial_Num，就不允许。
    //在整个通关后，修改存档中的关卡位置码为0，即可都玩。

}Story_Line;


typedef struct
{
    role_stats Player_Stats;
    int Story_Line_Coordinates[100];//指示玩家在每个剧情中的关卡坐标，最大支持100个剧情

}Save;

extern Save PLAYER_SAVE;
extern int save_count;

#include <wchar.h>
#include <locale.h>



bool LoadSaveFile(Save* plist, int* iCount, const wchar_t* filePath);
bool SaveSaveFile(Save *plist, int* iCount);

extern Story_Line STORY_LINES[];//剧情组
extern int story_count; // 当前剧情数量




int Skills_Props_Creater_Main();//创建技能的函数
int Skills_Props_Creater_Console_Command(const char* message, bool* Exit_SPC);
int AnalyseSPCCC(const char* f_message);
int displayBrief();// 简略显示技能函数
// 详细显示函数
void displayDetail(int index);
// 删除覆盖函数
void deleteSkill(int index);
// 技能查看器的主控制函数
void ShowSKPRmainControl();
void createSkill();




void deleteStoryLine();
void displayDetailedStoryLine();
void displayBriefStoryLines();
void createStoryLine();
void storyLineControl();
bool LoadStoryLinesFile(Story_Line* plist, int* iCount);
bool SaveStoryLinesFile(Story_Line* plist, int* iCount);
int StoryLineModeControl();
extern int STORY_LINE_CODE;//指示这是第几套剧情，默认0



void displayPlayerStats();

void shopping();//商店

int train();
role_stats generate_monster_stats(int difficulty);
int calculate_reward_gold(struct role_stats monster, int difficulty);
char* generate_monster_name();
SKILL_PROPS calculate_reward_stats(role_stats monster);// 属性升级奖励


int endless_mode_control();

int Choose_My_Skill();

int upgrade();

#endif // FUNCTIONS_H

/*
#ifndef FUNCTIONS_H：这是一个预处理指令，用于检查是否已经定义了FUNCTIONS_H宏。如果没有定义，那么编译器将继续执行下面的代码。这个宏通常用来防止头文件被重复包含，这是一种常见的编程实践，称为“包含卫士”或“头文件卫士”。
#define FUNCTIONS_H：这个指令定义了FUNCTIONS_H宏。这样，如果头文件被再次包含，预处理器会检查到FUNCTIONS_H已经被定义，并且跳过文件的其余部分，防止重复包含。
#endif // FUNCTIONS_H：这个指令标记了#ifndef块的结束。如果FUNCTIONS_H宏已经被定义，预处理器会跳过#ifndef和#endif之间的所有代码。
*/