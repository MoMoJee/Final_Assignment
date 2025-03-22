#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<Windows.h>
#include<math.h>

void shopping()
{
Start_Shopping:
	
	while (1)
	{
		int shop_num_buttons = 0;
		int shop_num_buttons_arr[MAX_BUTTONS];
		char* shop_num_buttons_buttons[MAX_BUTTONS] = {};
		char price[MAX_BUTTONS][20];
		// 使用 memset 将所有元素初始化为 '\0'
		memset(price, 0, sizeof(price));



		for (int i = 1500; i < fmin(skill_count, 2000); i++) {
			if (SKILL_PROPS_LIST[i].prompt[0] != '\0')
			{
				shop_num_buttons_arr[shop_num_buttons] = i;
				shop_num_buttons_buttons[shop_num_buttons] = SKILL_PROPS_LIST[i].prompt;
				// 使用 snprintf 将整数转换为字符串
				snprintf(price[shop_num_buttons], sizeof(price[shop_num_buttons]), "%d", SKILL_PROPS_LIST[i].Price);
				//printf("<<<%s>>>\n", price[shop_num_buttons]);
				shop_num_buttons += 1;
			}
		}
		const char* shop_num_buttons_buttons_const[MAX_BUTTONS];
		for (int i = 0; i < shop_num_buttons; i++)
		{
			shop_num_buttons_buttons_const[i] = shop_num_buttons_buttons[i];
		}
		const char* price_const[MAX_BUTTONS];
		for (int i = 0; i < shop_num_buttons; i++)
		{
			price_const[i] = price[i];
		}

		int choose = menu(shop_num_buttons, "商店在售道具", shop_num_buttons_arr, shop_num_buttons_buttons_const, price_const, 2);
		if (choose == -10999)
		{
			printf("欢迎下次光----临！\n");
			return;
		}

		int final_price = SKILL_PROPS_LIST[choose].Price;
		if ((final_price > PLAYER.Money) && (!develop_mode))
		{
			printf("没钱别来，你只有%d个金币，这个道具要%d个！\n", PLAYER.Money, final_price);
			goto Start_Shopping;
		}
		else
		{
			displayDetail(choose);



			// printf("你确定要花费%d个金币购买这个道具吗？\n你现在有%d个金币，买完还有%d个\n", final_price, PLAYER.Money, PLAYER.Money - final_price);

			if (!develop_mode) {
				int shop_menu_arr[MAX_BUTTONS];
				char shop_menu_buttons[MAX_BUTTONS][20];
				memset(shop_menu_buttons, 0, sizeof(shop_menu_buttons));
				const char* const_shop_menu_buttons[MAX_BUTTONS];
				const char* introduction[MAX_BUTTONS] = { NULL };
				int inum = 0;
				final_price = 0;
				for (inum; inum * SKILL_PROPS_LIST[choose].Price <= PLAYER.Money; inum++)
				{
					shop_menu_arr[inum] = inum;
					snprintf(shop_menu_buttons[inum], sizeof(shop_menu_buttons[inum]), "%d", inum * SKILL_PROPS_LIST[choose].Price);
					const_shop_menu_buttons[inum] = shop_menu_buttons[inum];
				}

				int buy_num = menu(inum, "您要购买几个这个技能？", shop_menu_arr, const_shop_menu_buttons, introduction, 2);
				if ((!buy_num) || buy_num == -10999)
				{
					printf("那您再看看\n");
					goto Start_Shopping;
				}
				else
				{
					final_price = SKILL_PROPS_LIST[choose].Price * buy_num;
					PLAYER.Money -= final_price;
					printf("你花费了%d个金币购买了%d个这个道具！\n", final_price, buy_num);
					PLAYER.PROPS[99][0] = choose;
					PLAYER.PROPS[99][1] = buy_num;
					cleanAndOrganizeProps();
					PLAYER_SAVE.Player_Stats = PLAYER;
					SaveSaveFile(&PLAYER_SAVE, &save_count);
					clearInputBuffer();
					printf("按任意键继续\n");
					while (!_kbhit()) {}
				}


			}
			else {
				final_price = SKILL_PROPS_LIST[choose].Price;
				PLAYER.Money -= 0;
				printf("你花费了%d（开发者模式，0元购）个金币购买了%d个这个道具！\n", final_price, 1);
				PLAYER.PROPS[99][0] = choose;
				PLAYER.PROPS[99][1] = 1;
				cleanAndOrganizeProps();
				PLAYER_SAVE.Player_Stats = PLAYER;
				SaveSaveFile(&PLAYER_SAVE, &save_count);
				clearInputBuffer();
				printf("按任意键继续\n");
				while (!_kbhit()) {}
			}


		}

	}

}