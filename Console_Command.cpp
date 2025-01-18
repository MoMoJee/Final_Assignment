#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // 用于 _kbhit() 和 _getch()
#include<Windows.h>

bool develop_mode = 0;
int f_code = 0;//由于cc是main循环调用，这里只能强行给他加生命周期了

int Console_Command
(
	const char *f_message,
	int state,//0指示main函数
	int special_int,
	int special_int_arr_0[],
	int special_int_arr_1[],
	char special_char_0[],
	char special_char_1[]
)
{
	int cc_menu_arr[MAX_BUTTONS] = { 0,1,2,3,4,5,6,7,8,10 };
	const char* cc_menu_buttons[MAX_BUTTONS] =
	{
		"退出",
		"剧情模式",
		"技能查询与创建",
		"剧情查看与生成",
		"我的",
		"商店",
		"训练场",
		"无尽模式",
		"装载技能",
		"升级"
	};
	const char* introduction[MAX_BUTTONS] = {
	NULL,
	NULL,
	"强烈建议使用，尤其剧情模式，先进去看看怪物的特性，然后ESC出来配置技能，对症下药"
	};
	if (PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] < 2)
	{
		cc_menu_arr[2] = -2;
		introduction[2] = "技能创建功能在完成剧情第二关之后开放，主要是因为第三关不用自定义技能打不过去，不信你试试";
	}

	if (PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] < 5)
	{
		cc_menu_arr[5] = -5;
		cc_menu_arr[6] = -6;
		cc_menu_arr[7] = -7;
		introduction[5] = "商店功能在完成剧情第五关之后开放";
		introduction[6] = "训练场功能在完成剧情第五关之后开放";
		introduction[7] = "无尽模式在完成剧情第五关之后开放";

	}
	char cc_cmd[401] = {'\0'};
	

	if ((f_code == -1) || (develop_mode))// -1指示用户在菜单中输入了#或者当前处于开发者模式
	{
		printf("这里是开发者模式，输入“#cc”来获取命令帮助\n");
		develop_mode = 1;

		scanf_s("%s", cc_cmd, 401);
		const char *cc_cmdinput = cc_cmd;
		if (strstr(cc_cmdinput, "#cc") || strstr(cc_cmdinput, "#CC"))//#cc的调用方式用于测试，之后可能会直接传入变量作为验证
		{
			logger(INFO, ConsoleCommand, "截取到#cc控制台关键词");
			f_code = AnalyseCC(cc_cmdinput);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		
		f_code = menu(10, "主菜单", cc_menu_arr, cc_menu_buttons, introduction, 1);

	}
		
	
	//比如有些功能只能在main进程中调用，那如果在别的进程中调用，就需要通过鉴权来阻止这个请求
	//比如在打怪，打怪进程是单独的一个函数，打怪的时候不能存档
	//如果不用state状态指示，那么就需要在这个打怪函数里面单独写一个判断
	//即，state和f_code组合通过CC的检查，才能执行这个操作。
	
	switch (f_code)
	{
	case 0:
	case -10999://0是退出命令
		if (last_f == 0)
		{
			PLAYER_SAVE.Player_Stats = PLAYER;
			SaveSaveFile(&PLAYER_SAVE, &save_count);
			logger(INFO, Saver, "游戏存档已自动保存");//保存存档函数
			exit(0);//退出
			return 0;
		}
		else
		{
			printf("确认退出？重复刚才的退出字词即确认\n");
			Sleep(1000);
			last_f = 0;//设置全局变量last_f的值为当前的f_code

			return 0;//第一次退出命令时，需要再一次确认
		}
		break;

	case 1:
		last_f = 1;
		StoryLineModeControl();
		return 1;
		break;

	case 2://技能生成器
		last_f = 2;
		Skills_Props_Creater_Main();
		return 1;
		break;

	case 3:
		last_f = 3;
		storyLineControl();
		return 1;
		break;

	case 4:
		last_f = 4;
		displayPlayerStats();
		displayProps();
		return 1;
		break;

	case 5:
		last_f = 5;
		shopping();
		return 1;
		break;
	case 6:
		last_f = 6;
		train();
		return 1;
		break;

	case 7:
		last_f = 7;
		endless_mode_control();
		return 1;
		break;

	case 8:
		last_f = 8;
		Choose_My_Skill();
		return 1;
		break;
	case 9:
		develop_mode = 0;//退出开发者模式
		return 1;
		break;
	case 10:
	case 'A':// 原有的解析方式，10会解析成1，命令行会出错，So
		upgrade();
		return 1;
		break;
	default://未知命令，返回控制台提示（其实就是Analyse CC返回的-1）
		logger(INFO, ConsoleCommand, "未知的控制台指令，返回指令列表");
		printf("————————未知的控制台指令，返回指令列表，注意所有的指令都要加上#cc————————\n");
		printf("0：退出/tc/TC/tuichu/Exit/exit\n");
		printf("1：战斗/Fight/fight/zd/ZD/zhandou\n");
		printf("2：技能创建/道具创建/jncj/djcj/SPC/spc\n");
		printf("3：剧情查询/剧情创建/剧情生成/jqcx/jqsc/SLC/slc\n");
		printf("4: 属性查询/属性/人物状态/我/Stats/stats/STATS\n");
		printf("5: 商店/Shop/shop/SHOP\n");
		printf("9: 退出开发者模式\n");
		printf("===============================================\n");
		break;
	}

	return 0;
}


// 通过命令解析，返回指令码
int AnalyseCC(const char *f_message)
{
	if (
		strstr(f_message, "退出") ||
		strstr(f_message, "Exit") ||
		strstr(f_message, "exit") ||
		strstr(f_message, "tuichu") ||
		strstr(f_message, "TC") ||
		strstr(f_message, "tc") ||
		strstr(f_message, "0")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到退出游戏关键字，启动退出游戏进程");
		return 0;
	}

	else if (
		strstr(f_message, "战斗") ||
		strstr(f_message, "zhandou") ||
		strstr(f_message, "zd") ||
		strstr(f_message, "ZD") ||
		strstr(f_message, "Fight") ||
		strstr(f_message, "fight") ||
		strstr(f_message, "1")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到开始战斗关键字，启动战斗进程");
		return 1;
	}

	else if (
		strstr(f_message, "技能创建") ||
		strstr(f_message, "道具创建") ||
		strstr(f_message, "jncj") ||
		strstr(f_message, "djcj") ||
		strstr(f_message, "SPC") ||
		strstr(f_message, "spc") ||
		strstr(f_message, "2")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到开始技能或道具创建关键字，启动进程");
		return 2;
	}
	else if (
		strstr(f_message, "剧情查询") ||
		strstr(f_message, "剧情创建") ||
		strstr(f_message, "剧情生成") ||
		strstr(f_message, "jqcx") ||
		strstr(f_message, "jqsc") ||
		strstr(f_message, "SLC") ||
		strstr(f_message, "slc") ||
		strstr(f_message, "3")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到开始剧情创建或查询关键字，启动进程");
		return 3;
	}
	else if (
		strstr(f_message, "属性查询") ||
		strstr(f_message, "属性") ||
		strstr(f_message, "人物状态") ||
		strstr(f_message, "我") ||
		strstr(f_message, "Stats") ||
		strstr(f_message, "stats") ||
		strstr(f_message, "STATS") ||
		strstr(f_message, "4")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到打开属性显示关键字，启动进程");
		return 4;
	}
	
	else if (
		strstr(f_message, "商店") ||
		strstr(f_message, "sd") ||
		strstr(f_message, "SD") ||
		strstr(f_message, "SHOP") ||
		strstr(f_message, "shop") ||
		strstr(f_message, "Shop") ||
		strstr(f_message, "5")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到商店关键字，启动进程");
		return 5;
	}

	else if (
		strstr(f_message, "9") ||
		strstr(f_message, "退出开发者模式")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-接收到退出开发者模式关键字，启动进程");
		return 9;
	}

	else
	{
		return -1;
	}
}


// 函数用于清除输入缓冲区
void clearInputBuffer() {
	while (_kbhit()) {
		_getch(); // 读取并丢弃所有按键
	}
}

// 选择式菜单，包含对命令解析式选择的大部分映射，但部分开发者功能需要通过#来进入命令模式才能运行。而在玩家版，#会被禁用
int menu(int num_buttons, const char* title, int index[MAX_BUTTONS], const char* buttons[MAX_BUTTONS], const char* introduction[MAX_BUTTONS], int mode) {//mode = 1，是不显示索引。mode = 2，是显示传入的索引。mode = 0，是使用默认索引返回并不显示
	printf("Loading......\n");
	Sleep(1500);
	int selected = 0; // 当前选中的按钮索引
	if (mode == 0)
	{
		//index = { 0 };//忽略传入的索引
		memset(index, 0, sizeof(int) * num_buttons);
	}

	while (1) {

		// 清屏
		system("cls");
		// 显示菜单
		printf("————<<<<<<<<<<%s>>>>>>>>>>————\n", title);
		if (mode == 2)
		{
			for (int i = 0; i < num_buttons; i++) {
				if (index[i] < 0) {
					if (i == selected)
					{
						printf("\033[31m%d\t%s\033[0m", index[i], buttons[i]); // 红色显示被选中的不可用的菜单项
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("：\033[31m%s\033[0m\n", introduction[i]); // 红色显示被选中的不可用的菜单项的详情
							}
						}

						else
						{
							printf("\n");
						}
					}
					else
					{
						printf("\033[90m%d\t%s\033[0m\n", index[i], buttons[i]); // 灰色显示不可用的菜单项
					}
				}
				else {
					if (i == selected) {
						printf("\033[33m%d\t%s\033[0m", index[i], buttons[i]); // 黄色高亮显示选中的菜单项
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("：\033[33m%s\033[0m\n", introduction[i]); //黄色显示被选中的菜单项详情
							}
							else
							{
								printf("\n");
							}
						}

						else
						{
							printf("\n");
						}

					}
					else {
						printf("%d\t%s\n", index[i], buttons[i]); // 正常显示可用的菜单项
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < num_buttons; i++) {
				if (index[i] < 0) {
					if (i == selected)
					{
						printf("\033[31m%s\033[0m", buttons[i]); // 红色显示被选中的不可用的菜单项
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("：\033[31m%s\033[0m\n", introduction[i]); // 红色显示被选中的不可用的菜单项的详情
							}
						}
						else
						{
							printf("\n");
						}
					}
					else
					{
						printf("\033[90m%s\033[0m\n", buttons[i]); // 灰色显示不可用的菜单项
					}
				}
				else {
					if (i == selected) {
						printf("\033[33m%s\033[0m", buttons[i]); // 黄色高亮显示选中的菜单项
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("：\033[33m%s\033[0m\n", introduction[i]); // 黄色显示被选中可用的菜单项的详情
							}
						}
						else
						{
							printf("\n");
						}
					}
					else {
						printf("%s\n", buttons[i]); // 正常显示可用的菜单项
					}
				}
			}
		}


		clearInputBuffer();
		while (!_kbhit()) { // 等待按键输入
			// 可以在这里添加一些其他逻辑，例如延时等
		}
		int input = _getch(); // 获取按键


		// 处理用户输入
		if (input == 0 || input == 224) { // 检测到特殊键的前导字节
			input = _getch(); // 获取实际的方向键代码
			switch (input) {
			case 72: // 上方向键
			case 75:// 左键
				selected = (selected > 0) ? selected - 1 : (num_buttons - 1);
				break;
			case 80: // 下方向键
			case 77: //右方向键
				selected = (selected < num_buttons - 1) ? selected + 1 : 0;
				break;
			}
		}
		else {
			switch (input) {
			case 'w':
			case 'W':
			case 'a':
			case 'A':
				selected = (selected > 0) ? selected - 1 : (num_buttons - 1);
				break;
			case 's':
			case 'S':
			case 'd':
			case 'D':
				selected = (selected < num_buttons - 1) ? selected + 1 : 0;
				break;
			case '\r':
			case ' ': // Enter 键、空格键为选中
				if (index[selected] < 0)
				{
					break;
				}
				else
				{
					if (mode == 0)
					{
						return selected;
					}
					else
					{
						return index[selected];//注意这里的返回值是第selected个数组值，而不是selected
					}

				}
			case 27:
				if (mode == 0)
				{
					return 0;//默认索引下，0代表退出指令
					break;
				}
				else
				{
					return -10999;//非默认索引的特殊返回值
					break;
				}
			case '#'://进入开发者命令
				return -1;
				break;
			}
		}
	}

}
