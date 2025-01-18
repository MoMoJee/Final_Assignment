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
            "退出",
            "C级",
            "B级",
            "A级",
            "S级",
            "AUVR级",
        };
        const char* train_introduction[MAX_BUTTONS] = {
        NULL,
        "普通小怪物",
        "中级小怪物",
        "高级怪物",
        "超级怪物！",
        "AUVR，您吃了没？"
        };

        difficulty = menu(6, "训练场", train_cc_menu_arr, train_cc_menu_buttons, train_introduction);
        if (difficulty == 0)
        {
            printf("下次再来哈\n");
            break;
        }

        role_stats monster = generate_monster_stats(difficulty);

        int reward_gold = calculate_reward_gold(monster, difficulty);
        monster.Money = reward_gold;
        
        monster_name = generate_monster_name();
        const char* const_monster_name = monster_name;
        strcpy_s(monster.Name, const_monster_name);

        printf("生成的怪物名字： %s\n", monster.Name);
        printf("攻击力： %d\n", monster.ATK);
        printf("生命值： %d\n", monster.HP);
        printf("防御力： %.8f\n", monster.DEF);
        printf("击败该怪物可获得的金币奖励： %d\n", monster.Money);

        SKILL_PROPS reward_stats = calculate_reward_stats(monster);
        printf("击败该怪物可获得的属性提升：\n");
        printf("=======================================\n");
        printf("对攻击力的操作：*%.8f\n", reward_stats.Operate_ATK);
        printf("对生命值的操作：+%d\n", reward_stats.Operate_HP);
        printf("对防御力的操作：*%.8f\n", reward_stats.Operate_DEF);
        printf("=======================================\n");



        printf("确定要开始战斗吗？\n");
        printf("按任意键继续。。。\n");
        while (!_kbhit()) {}
        int cc_menu_arr[MAX_BUTTONS] = { -1 };//使用默认返回索引
        const char* cc_menu_buttons[MAX_BUTTONS] =
        {
            "取消",
            "确定"
        };
        const char* introduction[MAX_BUTTONS] = { NULL };
        if (!(menu(2, "确定要开始战斗吗？", cc_menu_arr, cc_menu_buttons, introduction) == 1))
        {
            goto Start_Train;
        }

        OPPONENT = monster;
        if (fight())
        {
            PLAYER.Money += OPPONENT.Money;
            printf("你胜利了！你获得了%d个金币和属性提升！", OPPONENT.Money);
            //bool useless = 0;
            //PLAYER = Using_Skill_Props(&useless)
            //不用这个了，麻烦
            PLAYER.ATK *= reward_stats.Operate_ATK;
            PLAYER.DEF *= reward_stats.Operate_DEF;
            PLAYER.HP += reward_stats.Operate_HP;
            printf("按任意键继续。。。\n");
            while (!_kbhit()) {}
        }
        else
        {
            printf("没实力就别来\n");
            printf("按任意键继续。。。\n");
            while (!_kbhit()) {}
        }
    }
    return 0;
}



// 根据难度生成怪物属性
role_stats generate_monster_stats(int difficulty)
{
    difficulty *= 5;
    role_stats monster;
    srand(time(NULL)); // 初始化随机数种子

    // 根据难度设置攻击力范围
    int min_atk = difficulty * 10;
    int max_atk = difficulty * 20;
    monster.ATK = rand() % (max_atk - min_atk + 1) + min_atk;

    // 根据难度设置生命值范围
    int min_hp = difficulty * 50;
    int max_hp = difficulty * 100;
    monster.HP = rand() % (max_hp - min_hp + 1) + min_hp;

    // 根据难度设置防御力范围，难度越高，防御力越低
    float min_def = 1.0 - (0.04 * difficulty);
    float max_def = 1.0 - (0.01 * difficulty);
    if (min_def <= 0) min_def = 0.000001; // 防止防御力小于0
    if (max_def <= 0) max_def = 0.000001;
    monster.DEF = (float)(rand() % 100) / 100.0 * (max_def - min_def) + min_def;

    return monster;
}

// 根据怪物属性和难度计算奖励金币数量
int calculate_reward_gold(struct role_stats monster, int difficulty)
{
    difficulty *= 5;
    // 基础金币奖励与难度成正比
    int base_gold = difficulty * 100;

    // 根据攻击力增加金币奖励
    int atk_bonus_gold = monster.ATK * 2;

    // 根据生命值增加金币奖励
    int hp_bonus_gold = monster.HP / 2;

    // 防御力越低（防御能力越强），金币奖励越多
    int def_bonus_gold = (int)(100/ monster.DEF);

    // 总金币奖励为各部分之和
    int total_gold = base_gold + atk_bonus_gold + hp_bonus_gold + def_bonus_gold;

    return total_gold;
}

// 中文词库
const char* word_library[][10] = {
    {"赤炎", "青霜", "黄沙", "白雪", "黑雾", "金光", "木影", "水波", "火海", "土石"},
    {"龙吟", "虎啸", "豹跃", "熊舞", "狼奔", "狐媚", "蛇行", "鹰击", "狮吼", "象踏"},
    {"影刃", "爪牙", "翼展", "角触", "鳞甲", "须拂", "尾扫", "足踏", "身隐", "心狠"},
    {"巨灵", "小鬼", "长臂", "短腿", "高耸", "矮小", "胖墩", "瘦骨", "快速", "慢吞"},
    {"魔影", "妖姬", "鬼魅", "怪兽", "灵狐", "仙子", "神使", "佛祖", "圣灵", "邪魔"},
    {"幽冥", "暗夜", "明月", "亮光", "冷风", "热浪", "寒冰", "暖阳", "湿气", "燥热"},
    {"山岳", "海洋", "河川", "湖泊", "江水", "溪流", "峡谷", "峰顶", "岭脚", "崖壁"},
    {"风暴", "雨露", "雷鸣", "电闪", "云海", "雾霭", "霜降", "雪舞", "冰封", "雹打"},
    {"天际", "地平", "日出", "月落", "星辰", "辰光", "宇宙", "宙斯", "阴暗", "阳明"},
    {"上古", "下界", "左道", "右行", "前程", "后退", "东方", "西方", "南方", "北方"}
};

// 随机生成怪物名字
char* generate_monster_name()
{
    char name[101] = { 0 }; // 静态数组，用于存储生成的名字
    int word_count = sizeof(word_library) / sizeof(word_library[0]); // 词库中词组的数量
    int max_words_per_name = 50 / word_count; // 每个词组最多可以使用的次数，以保证名字长度不超过50个汉字

    srand(time(NULL)); // 初始化随机数种子

    // 随机选择词组并拼接名字
    for (int i = 0; i < word_count; ++i)
    {
        int word_index = rand() % 5; // 随机选择每个词组中的一个词
        strncat_s(name, word_library[word_count - i - 1][word_index], 2); // 将选中的词追加到名字中，注意每个汉字占2个字节
        if (strlen(name) >= 50 * 2) // 如果名字长度接近限制，停止拼接
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
    strcpy_s(reward_stats.prompt, "[Train]的获胜奖励");

    return reward_stats;
}