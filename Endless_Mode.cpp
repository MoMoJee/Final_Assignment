#include"functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <commdlg.h>
#include <time.h>

// 无尽模式中，每个回合间隙可以选择继续下一轮，或者领走基础奖励 + 额外奖励。而一旦战败，就只能获得基础奖励的一半
// 不回血
int endless_mode_control()
{
	int reward = 0;
	int bonus = 10;
	int lose = 0;

	int difficulty = 0;

	int last_HP = 0;
	int first_HP = PLAYER.HP;

	int train_cc_menu_arr[MAX_BUTTONS] = { -1 };
	const char* train_cc_menu_buttons[MAX_BUTTONS] =
	{
		"退出",
		"简单",
		"中等",
		"困难",
		"超难",
		"地狱"
	};
	const char* train_introduction[MAX_BUTTONS] =
	{
	NULL
	};

	difficulty = menu(6, "无尽模式，选择难度后无法更改", train_cc_menu_arr, train_cc_menu_buttons, train_introduction);
	if (difficulty == 0)
	{
		printf("下次再来哈\n");
		return 0;
	}
	while (!lose)
	{


		OPPONENT = generate_monster_stats(difficulty);

		char* monster_name;
		monster_name = generate_monster_name();
		const char* const_monster_name = monster_name;
		strcpy_s(OPPONENT.Name, const_monster_name);

		OPPONENT.Money = calculate_reward_gold(OPPONENT, difficulty);

		if (fight(&last_HP))// 赢了
		{
			bonus *= 2;
			reward += OPPONENT.Money;

			PLAYER.HP = last_HP;
			printf("恭喜你获得了这一轮比赛的胜利！\n");
			printf("你现在还剩余%d点血量，奖池中积累了%d个金币\n", last_HP, reward + bonus);
			printf("下一轮比赛胜利，你将再获得更多个金币，但是如果失败，你只能带走%d个金币，确定要继续吗？\n", reward / 2);

			printf("按任意键继续。。。\n");
			clearInputBuffer();
			while (!_kbhit()) {}
			int cc_menu_arr[MAX_BUTTONS] = { -1 };//使用默认返回索引
			const char* cc_menu_buttons[MAX_BUTTONS] =
			{
				"取消",
				"确定"
			};
			const char* introduction[MAX_BUTTONS] = { NULL };
			if (!(menu(2, "确定要继续吗？", cc_menu_arr, cc_menu_buttons, introduction) == 1))
			{
				PLAYER.HP = first_HP;
				break;
			}
		}
		else
		{
			lose = 1;
			PLAYER.HP = first_HP;
			printf("真遗憾，再接再厉吧！\n");
		}

	}


	if (!lose)// 没输，即自己离开的，而非被击败的
	{
		printf("你获得了%d个金币！\n", reward + bonus);
		printf("按任意键继续。。。\n");
		clearInputBuffer();
		while (!_kbhit()) {}
		PLAYER.Money += reward + bonus;
	}
	else
	{
		printf("你获得了%d个金币！\n", reward / 2);
		printf("按任意键继续。。。\n");
		clearInputBuffer();
		while (!_kbhit()) {}
		PLAYER.Money += reward / 2;
	}

	PLAYER_SAVE.Player_Stats = PLAYER;
	SaveSaveFile(&PLAYER_SAVE,&save_count);

	return 0;
}