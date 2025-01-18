#include"functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <commdlg.h>
#include <time.h>

// �޾�ģʽ�У�ÿ���غϼ�϶����ѡ�������һ�֣��������߻������� + ���⽱������һ��ս�ܣ���ֻ�ܻ�û���������һ��
// ����Ѫ
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
		"�˳�",
		"��",
		"�е�",
		"����",
		"����",
		"����"
	};
	const char* train_introduction[MAX_BUTTONS] =
	{
	NULL
	};

	difficulty = menu(6, "�޾�ģʽ��ѡ���ѶȺ��޷�����", train_cc_menu_arr, train_cc_menu_buttons, train_introduction);
	if (difficulty == 0)
	{
		printf("�´�������\n");
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

		if (fight(&last_HP))// Ӯ��
		{
			bonus *= 2;
			reward += OPPONENT.Money;

			PLAYER.HP = last_HP;
			printf("��ϲ��������һ�ֱ�����ʤ����\n");
			printf("�����ڻ�ʣ��%d��Ѫ���������л�����%d�����\n", last_HP, reward + bonus);
			printf("��һ�ֱ���ʤ�����㽫�ٻ�ø������ң��������ʧ�ܣ���ֻ�ܴ���%d����ң�ȷ��Ҫ������\n", reward / 2);

			printf("�����������������\n");
			clearInputBuffer();
			while (!_kbhit()) {}
			int cc_menu_arr[MAX_BUTTONS] = { -1 };//ʹ��Ĭ�Ϸ�������
			const char* cc_menu_buttons[MAX_BUTTONS] =
			{
				"ȡ��",
				"ȷ��"
			};
			const char* introduction[MAX_BUTTONS] = { NULL };
			if (!(menu(2, "ȷ��Ҫ������", cc_menu_arr, cc_menu_buttons, introduction) == 1))
			{
				PLAYER.HP = first_HP;
				break;
			}
		}
		else
		{
			lose = 1;
			PLAYER.HP = first_HP;
			printf("���ź����ٽ������ɣ�\n");
		}

	}


	if (!lose)// û�䣬���Լ��뿪�ģ����Ǳ����ܵ�
	{
		printf("������%d����ң�\n", reward + bonus);
		printf("�����������������\n");
		clearInputBuffer();
		while (!_kbhit()) {}
		PLAYER.Money += reward + bonus;
	}
	else
	{
		printf("������%d����ң�\n", reward / 2);
		printf("�����������������\n");
		clearInputBuffer();
		while (!_kbhit()) {}
		PLAYER.Money += reward / 2;
	}

	PLAYER_SAVE.Player_Stats = PLAYER;
	SaveSaveFile(&PLAYER_SAVE,&save_count);

	return 0;
}