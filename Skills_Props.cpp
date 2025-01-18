#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>
#include <iostream>


//Using_Skill_Props函数 接收技能/道具代码、发起时状态、玩家的stats、对手的stats（可选）
//函数根据代码查询全局变量：技能列表（SKILL_PROPS_LIST这个SKILL_PROPS结构体组），返回一个SKILL_PROPS结构体组
//函数把这个技能结构体组里面的操作对应执行给传入的两个stats，返回修改后的两个
//由于只能返回一个量，所以这里返回结构体组的首地址（或者说结构体的指针）
role_stats* Using_Skill_Props(bool* new_n_Round_Effect_Happpen, SKILL_PROPS * n_Round_Effect_SK, int * n_Round_Effect, int Skill_Prop_code, int state, role_stats Skill_PropsTempPlayerStatus, role_stats Skill_PropsTempOpponentStatus)
{
    SKILL_PROPS Skill_Props_Temp_PLAYER_PROPS;//初始化道具，方便战斗中传入并交由Using_Skill_Props分析

    role_stats *Refreshed_Status = new role_stats[2];//初始化更改后的玩家和对手stats，下面要更改返回并赋值给对居中的临时stats/非战斗中的全局stats

    Refreshed_Status[1] = Skill_PropsTempOpponentStatus;
    Refreshed_Status[0] = Skill_PropsTempPlayerStatus;

    Skill_Props_Temp_PLAYER_PROPS = SKILL_PROPS_LIST[Skill_Prop_code];//根据code查找SKILL_PROPS_LIST[]

    if (!Using_Skill_Props_Checker(Skill_Prop_code, state))//这里只使用了Using_Skill_Props_Checker的通过检查，更多丰富功能在别的高级查找中使用
    {
        printf("当前状态下不允许使用此技能或道具\n");
        printf("允许：%d-当前：%d\n", Skill_Props_Temp_PLAYER_PROPS.state, state);
        
        return Refreshed_Status;//返回仅初始化为原来输入进来的俩的
    }

    if ((*n_Round_Effect != -1))
    {
        if (Skill_Props_Temp_PLAYER_PROPS.Fight_Times != 0)
        {
            printf("有别的非全对局技能正在生效中，本次技能无法释放。作为惩罚，扣除一个该道具或技能使用机会！\n");//其实就是我懒得改bug
            return Refreshed_Status;
        }
        else
        {
            printf("有别的非全对局技能正在生效中，本次全局技能虽然成功释放，但是技能对于此前非全对局技能的对象的攻击力、防御力的操作会在非全局技能停止生效后被还原，不建议这种操作。更好的做法是在开局就使用全局技能。\n");
        }
    }
    if (Skill_Props_Temp_PLAYER_PROPS.Fight_Times != 0)
    {//渣渣是这样的，因为没设计好所以只能在这里乱指针
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
        printf("使用技能%s\n", Skill_Props_Temp_PLAYER_PROPS.prompt);
        logger(INFO, Skills_Props, "[Using_Skill_Props]-允许对自己技能释放");
        Refreshed_Status[0] = StatsAlterChecker(Refreshed_Status[0]);
        return Refreshed_Status;
    }
    else if (Skill_Props_Temp_PLAYER_PROPS.object == 2)//对敌人操作
    {
        Refreshed_Status[1].ATK = Skill_PropsTempOpponentStatus.ATK * Skill_Props_Temp_PLAYER_PROPS.Operate_ATK;
        Refreshed_Status[1].DEF = Skill_PropsTempOpponentStatus.DEF * Skill_Props_Temp_PLAYER_PROPS.Operate_DEF;
        Refreshed_Status[1].HP = Skill_PropsTempOpponentStatus.HP + Skill_Props_Temp_PLAYER_PROPS.Operate_HP;
        Refreshed_Status[1].Money = Skill_PropsTempOpponentStatus.Money + Skill_Props_Temp_PLAYER_PROPS.Operate_Money;
        printf("使用技能%s\n", Skill_Props_Temp_PLAYER_PROPS.prompt);
        logger(INFO, Skills_Props, "[Using_Skill_Props]-允许对敌人技能释放");
        Refreshed_Status[1] = StatsAlterChecker(Refreshed_Status[1]);
        return Refreshed_Status;
    }

    
    //匹配传入的state和AnalyseSP返回的技能码对应的技能的可用场景，比如加金币道具只能在非战斗使用
    //在本函数中根据技能的对象码修改
    //根据查找结果，解析后，返回一个stats，将被用于对局临时使用（因为战斗中可用的道具都是仅在对局内生效的）或者覆盖原有的stats
    return Refreshed_Status;//返回的是一个stats结构体组（指针），对应自己和对手
}

role_stats StatsAlterChecker(role_stats unCheckedStats)//检查修改后的stats是不是在合理范围，比如防御值范围是[0,1](其实不应该有0，但是基于某些特性，貌似也能打出一点点伤害。或者把这个做成一个无敌NPC也行
{
    
    role_stats CheckedStats = unCheckedStats;
    if (CheckedStats.ATK < 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-检测到对ATK的不合理修改（值<0），已修正为0");
        CheckedStats.ATK = 0;
    }
    if (CheckedStats.DEF < 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-检测到对DEF的不合理修改（值<0），已修正为0");
        CheckedStats.DEF = 0;
    }
    if (CheckedStats.DEF > 1)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-检测到对DEF的不合理修改（值>1），已修正为1");
        CheckedStats.DEF = 1;
    }
    if (CheckedStats.HP <= 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-检测到对HP的不合理修改（值<0），已修正为0");
        CheckedStats.HP = 1;
    }
    if (CheckedStats.Money < 0)
    {
        logger(INFO, Skills_Props, "[StatsAlterChecker]-检测到对Money的不合理修改（值<0），已修正为0");
        CheckedStats.Money = 0;
    }
    return CheckedStats;
}

bool isPositiveInt(const char* str, int* result) {//解析，如果传入的字符串里有数字，直接提取。
    const char* start = str;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            // 找到数字序列的开始
            const char* end = str;
            while (isdigit((unsigned char)*end)) {
                end++;
            }
            // 尝试转换为整数
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
        logger(INFO, Skills_Props, "[AnalyseSP]-匹配到技能码：");
        char spcode[5];//支持四位数的技能码
        sprintf_s(spcode, "%d", SPcode);
        logger(INFO, Skills_Props, spcode);
        if (SPcode == 0)//0技能不被允许，这是用于初始化角色道具列表的
        {
            return -1;
        }
        else
        {
            return SPcode;
        }
    }
    else {
        logger(WARN, Skills_Props, "[AnalyseSP]-没有找到命令中的整数型技能码，尝试使用中文解析语句：");
        logger(INFO, Skills_Props, SPmessage);
    }

    

    //如果输入的字符串没有数字，再执行下面的查找。这不是无限增多的

    if (//先写几个技能是有很多个对应词的，后面再增加更多的话，可能就只能用号码了。因为我想通过文件读取技能，方便增加，但是这里代码不能无限多
        //话说能不能把提示词也写进txt里面呢
        strstr(SPmessage, "一技能") ||
        strstr(SPmessage, "技能一") ||
        strstr(SPmessage, "坚如磐石") ||
        strstr(SPmessage, "jrps")

        )
    {
        
        SPcode = 1;
    }
    //解析键入的要发动的技能或者要使用的道具，返回技能码
    //战斗中、战斗外都可以用这个
    else
    {
        SPcode = -1;
        logger(WARN, Skills_Props, "[AnalyseSP]-没有找到命令中的技能");
        printf("没有找到命令中的技能\n");
        return -1;
    }
    logger(INFO, Skills_Props, "[AnalyseSP]-中文解析成功，找到命令中的技能");
    logger(WARN, Skills_Props, "[AnalyseSP] - 中文解析功能不支持大多数技能或道具，尽量使用技能代码，当前可用的技能码列表可以在选择技能时输入#h来获取");
    printf("中文解析功能不支持大多数技能或道具，尽量使用技能代码，当前可用的技能码列表可以在选择技能时输入#h来获取\n");//我还没写，这个函数是多功能的，根据调用状态（战斗中查询的是可用在战斗中的、自己拥有的道具；非战斗时返回所有的）（不过直接全返回好像也行）
    return SPcode;
}

int Using_Skill_Props_Checker(int Skill_Prop_code, int state)//只检查，不输出（但是下面那个”对局中已经使用过该技能！“是个例外，因为在非对局中不会有这个情况
{
    if (Skill_Prop_code == -1)//-1是ASP的错误码：未找到对应技能
    {
        printf("未匹配到输入的技能码信息\n");
        return -1;//-1代表未查找到错误
    }
    if (SKILL_PROPS_LIST[Skill_Prop_code].state == state)
        if (Skill_Prop_code == PLAYER.SKILL[0])//先检查技能
            if (PLAYER.SKILL[1])//大于0即可通过，不过按道理只有0或1，这也可以算个后门了，可以定义次数 > 1，这样可以用很多次，或者直接=-1
            {
                logger(INFO, Skills_Props, "[Using_Skill_Props_Checker]-技能使用检查通过");
                PLAYER.SKILL[1] = 0;//这里就不用战斗中创建的临时属性了。
                return 1;//代表是可用技能
            }
            else
            {
                printf("对局中已经使用过该技能！\n");
                logger(INFO, Skills_Props, "[Using_Skill_Props_Checker]-技能使用检查不通过，因为技能可用次数为0");
                return 0;
            }
        else//检查道具在不在玩家属性道具列表里、可不可用
        {
            for (int i = 0; i < 100; i++)
            {
                if ((PLAYER.PROPS[i][0] == Skill_Prop_code) && (PLAYER.PROPS[i][1] > 0))//查找到玩家属性道具列表中的指定技能
                {
                    PLAYER.PROPS[i][1] -= 1;
                    return 2;//代表是可用道具
                }
            }
            printf("选择的道具剩余可用次数为0！\n");
            return 0;
        }
    else
    {
        logger(INFO, Skills_Props, "[Using_Skill_Props]-拒绝了上述的技能发起请求，因为状态检查不通过");
        return 0;
    }
}

//查找技能码在props列表中的位置
int findPropIndex(int target) {
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][0] == target) {
            return i; // 找到匹配的索引，返回
        }
    }
    return -1; // 没有找到匹配的索引，返回-1
}

//整理PLAYER.PROPS数组的函数，每次执行完对PLAYER.PROPS的操作都运行
void cleanAndOrganizeProps() {
    int temp[100][2]; // 用于临时存储整理后的数组
    int count = 0;          // 用于记录整理后数组的有效行数
    int found;              // 用于标记是否找到重复编码

    // 遍历数组，检查并设置第一个数字为0
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][1] == 0) {
            PLAYER.PROPS[i][0] = 0;
        }
    }

    // 整理数组，将第一个数字不为0的行挪到前面，并合并重复编码
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][0] != 0) {
            found = 0;
            // 检查是否已存在该编码
            for (int j = 0; j < count; j++) {
                if (temp[j][0] == PLAYER.PROPS[i][0]) {
                    temp[j][1] += PLAYER.PROPS[i][1]; // 合并数量
                    found = 1;
                    break;
                }
            }
            // 如果未找到，添加到临时数组
            if (!found) {
                temp[count][0] = PLAYER.PROPS[i][0];
                temp[count][1] = PLAYER.PROPS[i][1];
                count++;
            }
        }
    }

    // 将整理后的数组复制回原数组
    for (int i = 0; i < count; i++) {
        PLAYER.PROPS[i][0] = temp[i][0];
        PLAYER.PROPS[i][1] = temp[i][1];
    }

    // 将剩余的行设置为0
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
            if ((PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] < 5) && (i >= 1410))// 玩5关之前只能选前10个技能
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
    int choice = menu(skpr_num_buttons, "技能列表", skpr_num_buttons_arr, skpr_num_buttons_buttons_const, introduction, 2);
    if (choice == -10999)
    {
        return 0;
    }
    PLAYER.SKILL[0] = choice;
    PLAYER.SKILL[1] = 1;
    PLAYER_SAVE.Player_Stats = PLAYER;
    SaveSaveFile(&PLAYER_SAVE, &save_count);
    printf("你选择了技能 %s 装载到你的技能槽中！下面是这个技能的详细参数（价格忽略，免费释放）\n", SKILL_PROPS_LIST[choice].prompt);
    displayDetail(choice);
    return 0;
}