#include"functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <commdlg.h>


// �����Լ��������еĺ�û�еķ�ս�����ߣ�û�еĵ��ߣ�ֻ��ʾ�̵���۵ģ�
// �������Ҳ���Լ��ɣ�����һ��������n���Ľ��档ShopҲ�������
// ʹ�ý��棬����һ����ʹ��n����
int upgrade()
{
	while (1)
	{
		int upgrade_menu_arr[MAX_BUTTONS];
		int upgrade_menu_num = 0;
		const char* upgrade_menu_buttons[MAX_BUTTONS];
		char number[MAX_BUTTONS][20];
		const char* const_number[MAX_BUTTONS];


		for (int i = 0; i < 100; i++) {
			if (PLAYER.PROPS[i][0] != 0 || PLAYER.PROPS[i][1] != 0) {
				if (SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].state == 1)
				{
					upgrade_menu_arr[upgrade_menu_num] = PLAYER.PROPS[i][0];
					upgrade_menu_buttons[upgrade_menu_num] = SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].prompt;
					snprintf(number[upgrade_menu_num], sizeof(number[upgrade_menu_num]), "%d", PLAYER.PROPS[i][1]);
					const_number[upgrade_menu_num] = number[upgrade_menu_num];
					upgrade_menu_num += 1;
				}
			}
		}

		int choice = menu(upgrade_menu_num, "ѡ����������Ҫ�õĵ���", upgrade_menu_arr, upgrade_menu_buttons, const_number, 1);
		if ((choice == -10999))
		{
			return 0;
		}
		displayDetail(choice);

		int index = findPropIndex(choice);

		int use_number = PLAYER.PROPS[index][1] + 1;
		int use_number_arr[MAX_BUTTONS];
		const char* upgrade_menu_buttons_use[MAX_BUTTONS];
		const char* useless[MAX_BUTTONS] = { NULL };
		for (int i = 0; i < use_number; i++)
		{
			use_number_arr[i] = i;
			upgrade_menu_buttons_use[i] = "��";
		}
		
		use_number = menu(use_number, "����Ҫ�ü���������ߣ�", use_number_arr, upgrade_menu_buttons_use, useless, 2);
		if ((use_number == 0) || (use_number == -10999))
		{
			return 0;
		}
		for (int i = 0; i < use_number; i++)
		{
			PLAYER.ATK *= SKILL_PROPS_LIST[choice].Operate_ATK;
			PLAYER.DEF *= SKILL_PROPS_LIST[choice].Operate_DEF;
			PLAYER.HP += SKILL_PROPS_LIST[choice].Operate_HP;
			PLAYER.Money += SKILL_PROPS_LIST[choice].Operate_Money;
			
			
		}

		PLAYER.PROPS[index][1] -= use_number;
		cleanAndOrganizeProps();
		printf("�����������������\n");
		while (!_kbhit()) {}
		
	}
	return 0;
}