#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // ���� _kbhit() �� _getch()
#include<Windows.h>

bool develop_mode = 0;
int f_code = 0;//����cc��mainѭ�����ã�����ֻ��ǿ�и���������������

int Console_Command
(
	const char *f_message,
	int state,//0ָʾmain����
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
		"�˳�",
		"����ģʽ",
		"���ܲ�ѯ�봴��",
		"����鿴������",
		"�ҵ�",
		"�̵�",
		"ѵ����",
		"�޾�ģʽ",
		"װ�ؼ���",
		"����"
	};
	const char* introduction[MAX_BUTTONS] = {
	NULL,
	NULL,
	"ǿ�ҽ���ʹ�ã��������ģʽ���Ƚ�ȥ������������ԣ�Ȼ��ESC�������ü��ܣ���֢��ҩ"
	};
	if (PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] < 2)
	{
		cc_menu_arr[2] = -2;
		introduction[2] = "���ܴ�����������ɾ���ڶ���֮�󿪷ţ���Ҫ����Ϊ�����ز����Զ��弼�ܴ򲻹�ȥ������������";
	}

	if (PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE] < 5)
	{
		cc_menu_arr[5] = -5;
		cc_menu_arr[6] = -6;
		cc_menu_arr[7] = -7;
		introduction[5] = "�̵깦������ɾ�������֮�󿪷�";
		introduction[6] = "ѵ������������ɾ�������֮�󿪷�";
		introduction[7] = "�޾�ģʽ����ɾ�������֮�󿪷�";

	}
	char cc_cmd[401] = {'\0'};
	

	if ((f_code == -1) || (develop_mode))// -1ָʾ�û��ڲ˵���������#���ߵ�ǰ���ڿ�����ģʽ
	{
		printf("�����ǿ�����ģʽ�����롰#cc������ȡ�������\n");
		develop_mode = 1;

		scanf_s("%s", cc_cmd, 401);
		const char *cc_cmdinput = cc_cmd;
		if (strstr(cc_cmdinput, "#cc") || strstr(cc_cmdinput, "#CC"))//#cc�ĵ��÷�ʽ���ڲ��ԣ�֮����ܻ�ֱ�Ӵ��������Ϊ��֤
		{
			logger(INFO, ConsoleCommand, "��ȡ��#cc����̨�ؼ���");
			f_code = AnalyseCC(cc_cmdinput);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		
		f_code = menu(10, "���˵�", cc_menu_arr, cc_menu_buttons, introduction, 1);

	}
		
	
	//������Щ����ֻ����main�����е��ã�������ڱ�Ľ����е��ã�����Ҫͨ����Ȩ����ֹ�������
	//�����ڴ�֣���ֽ����ǵ�����һ����������ֵ�ʱ���ܴ浵
	//�������state״ָ̬ʾ����ô����Ҫ�������ֺ������浥��дһ���ж�
	//����state��f_code���ͨ��CC�ļ�飬����ִ�����������
	
	switch (f_code)
	{
	case 0:
	case -10999://0���˳�����
		if (last_f == 0)
		{
			PLAYER_SAVE.Player_Stats = PLAYER;
			SaveSaveFile(&PLAYER_SAVE, &save_count);
			logger(INFO, Saver, "��Ϸ�浵���Զ�����");//����浵����
			exit(0);//�˳�
			return 0;
		}
		else
		{
			printf("ȷ���˳����ظ��ղŵ��˳��ִʼ�ȷ��\n");
			Sleep(1000);
			last_f = 0;//����ȫ�ֱ���last_f��ֵΪ��ǰ��f_code

			return 0;//��һ���˳�����ʱ����Ҫ��һ��ȷ��
		}
		break;

	case 1:
		last_f = 1;
		StoryLineModeControl();
		return 1;
		break;

	case 2://����������
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
		develop_mode = 0;//�˳�������ģʽ
		return 1;
		break;
	case 10:
	case 'A':// ԭ�еĽ�����ʽ��10�������1�������л����So
		upgrade();
		return 1;
		break;
	default://δ֪������ؿ���̨��ʾ����ʵ����Analyse CC���ص�-1��
		logger(INFO, ConsoleCommand, "δ֪�Ŀ���ָ̨�����ָ���б�");
		printf("����������������δ֪�Ŀ���ָ̨�����ָ���б�ע�����е�ָ�Ҫ����#cc����������������\n");
		printf("0���˳�/tc/TC/tuichu/Exit/exit\n");
		printf("1��ս��/Fight/fight/zd/ZD/zhandou\n");
		printf("2�����ܴ���/���ߴ���/jncj/djcj/SPC/spc\n");
		printf("3�������ѯ/���鴴��/��������/jqcx/jqsc/SLC/slc\n");
		printf("4: ���Բ�ѯ/����/����״̬/��/Stats/stats/STATS\n");
		printf("5: �̵�/Shop/shop/SHOP\n");
		printf("9: �˳�������ģʽ\n");
		printf("===============================================\n");
		break;
	}

	return 0;
}


// ͨ���������������ָ����
int AnalyseCC(const char *f_message)
{
	if (
		strstr(f_message, "�˳�") ||
		strstr(f_message, "Exit") ||
		strstr(f_message, "exit") ||
		strstr(f_message, "tuichu") ||
		strstr(f_message, "TC") ||
		strstr(f_message, "tc") ||
		strstr(f_message, "0")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ��˳���Ϸ�ؼ��֣������˳���Ϸ����");
		return 0;
	}

	else if (
		strstr(f_message, "ս��") ||
		strstr(f_message, "zhandou") ||
		strstr(f_message, "zd") ||
		strstr(f_message, "ZD") ||
		strstr(f_message, "Fight") ||
		strstr(f_message, "fight") ||
		strstr(f_message, "1")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ���ʼս���ؼ��֣�����ս������");
		return 1;
	}

	else if (
		strstr(f_message, "���ܴ���") ||
		strstr(f_message, "���ߴ���") ||
		strstr(f_message, "jncj") ||
		strstr(f_message, "djcj") ||
		strstr(f_message, "SPC") ||
		strstr(f_message, "spc") ||
		strstr(f_message, "2")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ���ʼ���ܻ���ߴ����ؼ��֣���������");
		return 2;
	}
	else if (
		strstr(f_message, "�����ѯ") ||
		strstr(f_message, "���鴴��") ||
		strstr(f_message, "��������") ||
		strstr(f_message, "jqcx") ||
		strstr(f_message, "jqsc") ||
		strstr(f_message, "SLC") ||
		strstr(f_message, "slc") ||
		strstr(f_message, "3")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ���ʼ���鴴�����ѯ�ؼ��֣���������");
		return 3;
	}
	else if (
		strstr(f_message, "���Բ�ѯ") ||
		strstr(f_message, "����") ||
		strstr(f_message, "����״̬") ||
		strstr(f_message, "��") ||
		strstr(f_message, "Stats") ||
		strstr(f_message, "stats") ||
		strstr(f_message, "STATS") ||
		strstr(f_message, "4")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ���������ʾ�ؼ��֣���������");
		return 4;
	}
	
	else if (
		strstr(f_message, "�̵�") ||
		strstr(f_message, "sd") ||
		strstr(f_message, "SD") ||
		strstr(f_message, "SHOP") ||
		strstr(f_message, "shop") ||
		strstr(f_message, "Shop") ||
		strstr(f_message, "5")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ��̵�ؼ��֣���������");
		return 5;
	}

	else if (
		strstr(f_message, "9") ||
		strstr(f_message, "�˳�������ģʽ")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseCC]-���յ��˳�������ģʽ�ؼ��֣���������");
		return 9;
	}

	else
	{
		return -1;
	}
}


// ��������������뻺����
void clearInputBuffer() {
	while (_kbhit()) {
		_getch(); // ��ȡ���������а���
	}
}

// ѡ��ʽ�˵����������������ʽѡ��Ĵ󲿷�ӳ�䣬�����ֿ����߹�����Ҫͨ��#����������ģʽ�������С�������Ұ棬#�ᱻ����
int menu(int num_buttons, const char* title, int index[MAX_BUTTONS], const char* buttons[MAX_BUTTONS], const char* introduction[MAX_BUTTONS], int mode) {//mode = 1���ǲ���ʾ������mode = 2������ʾ�����������mode = 0����ʹ��Ĭ���������ز�����ʾ
	printf("Loading......\n");
	Sleep(1500);
	int selected = 0; // ��ǰѡ�еİ�ť����
	if (mode == 0)
	{
		//index = { 0 };//���Դ��������
		memset(index, 0, sizeof(int) * num_buttons);
	}

	while (1) {

		// ����
		system("cls");
		// ��ʾ�˵�
		printf("��������<<<<<<<<<<%s>>>>>>>>>>��������\n", title);
		if (mode == 2)
		{
			for (int i = 0; i < num_buttons; i++) {
				if (index[i] < 0) {
					if (i == selected)
					{
						printf("\033[31m%d\t%s\033[0m", index[i], buttons[i]); // ��ɫ��ʾ��ѡ�еĲ����õĲ˵���
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("��\033[31m%s\033[0m\n", introduction[i]); // ��ɫ��ʾ��ѡ�еĲ����õĲ˵��������
							}
						}

						else
						{
							printf("\n");
						}
					}
					else
					{
						printf("\033[90m%d\t%s\033[0m\n", index[i], buttons[i]); // ��ɫ��ʾ�����õĲ˵���
					}
				}
				else {
					if (i == selected) {
						printf("\033[33m%d\t%s\033[0m", index[i], buttons[i]); // ��ɫ������ʾѡ�еĲ˵���
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("��\033[33m%s\033[0m\n", introduction[i]); //��ɫ��ʾ��ѡ�еĲ˵�������
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
						printf("%d\t%s\n", index[i], buttons[i]); // ������ʾ���õĲ˵���
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
						printf("\033[31m%s\033[0m", buttons[i]); // ��ɫ��ʾ��ѡ�еĲ����õĲ˵���
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("��\033[31m%s\033[0m\n", introduction[i]); // ��ɫ��ʾ��ѡ�еĲ����õĲ˵��������
							}
						}
						else
						{
							printf("\n");
						}
					}
					else
					{
						printf("\033[90m%s\033[0m\n", buttons[i]); // ��ɫ��ʾ�����õĲ˵���
					}
				}
				else {
					if (i == selected) {
						printf("\033[33m%s\033[0m", buttons[i]); // ��ɫ������ʾѡ�еĲ˵���
						if (introduction[i] != NULL)
						{
							if (introduction[i][0] != '\0')
							{
								printf("��\033[33m%s\033[0m\n", introduction[i]); // ��ɫ��ʾ��ѡ�п��õĲ˵��������
							}
						}
						else
						{
							printf("\n");
						}
					}
					else {
						printf("%s\n", buttons[i]); // ������ʾ���õĲ˵���
					}
				}
			}
		}


		clearInputBuffer();
		while (!_kbhit()) { // �ȴ���������
			// �������������һЩ�����߼���������ʱ��
		}
		int input = _getch(); // ��ȡ����


		// �����û�����
		if (input == 0 || input == 224) { // ��⵽�������ǰ���ֽ�
			input = _getch(); // ��ȡʵ�ʵķ��������
			switch (input) {
			case 72: // �Ϸ����
			case 75:// ���
				selected = (selected > 0) ? selected - 1 : (num_buttons - 1);
				break;
			case 80: // �·����
			case 77: //�ҷ����
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
			case ' ': // Enter �����ո��Ϊѡ��
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
						return index[selected];//ע������ķ���ֵ�ǵ�selected������ֵ��������selected
					}

				}
			case 27:
				if (mode == 0)
				{
					return 0;//Ĭ�������£�0�����˳�ָ��
					break;
				}
				else
				{
					return -10999;//��Ĭ�����������ⷵ��ֵ
					break;
				}
			case '#'://���뿪��������
				return -1;
				break;
			}
		}
	}

}
