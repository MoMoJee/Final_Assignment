#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>
#include<math.h>

int spcf_code = 0;

int Skills_Props_Creater_Main()//�������ܲ�д��
{

	int Money_Consumption = 0;
	bool Exit_SPC = 0;//SPCCC���ڽ��յ��˳�ָ��ʱ�޸���
	while (1)
	{

		if (Exit_SPC)
		{
			logger(INFO, Creator, "[Skills_Props_Creater_Main]-���յ��˳�����");
			printf("�ڴ��´ι��٣�\n");
			return Money_Consumption;
		}

		const char* SPCcmdinput = "nouse";
		Skills_Props_Creater_Console_Command(SPCcmdinput,&Exit_SPC);
	}
	return Money_Consumption;
}

int Skills_Props_Creater_Console_Command(const char* message,bool * Exit_SPC)//�������ܲ�д��Ŀ���̨
{
	{
		
		int cc_menu_arr[MAX_BUTTONS] = {-1};
		const char* cc_menu_buttons[MAX_BUTTONS] =
		{
			"�˳�",
			"���ܲ�ѯ̨",
			"���ܴ�����"
		};
		const char* introduction[MAX_BUTTONS] = {
NULL
		};
		char spccc_cmd[401] = { '\0' };


		if ((spcf_code == -1) || (develop_mode))// -1ָʾ�û��ڲ˵���������#���ߵ�ǰ���ڿ�����ģʽ
		{
			printf("�����ǿ�����ģʽ�����롰#������ȡ�������\n");
			develop_mode = 1;

			scanf_s("%s", spccc_cmd, 401);
			const char* spccc_cmdinput = spccc_cmd;
			if (strstr(spccc_cmdinput, "#") || strstr(spccc_cmdinput, "#"))
			{
				logger(INFO, Creator, "[Skills_Props_Creater_Console_Command]-��ȡ��#����̨�ؼ���");
				spcf_code = AnalyseSPCCC(spccc_cmdinput);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			spcf_code = menu(3, "���ܲ�ѯ�봴��", cc_menu_arr, cc_menu_buttons, introduction);
		}


		//������Щ����ֻ����main�����е��ã�������ڱ�Ľ����е��ã�����Ҫͨ����Ȩ����ֹ�������
		//�����ڴ�֣���ֽ����ǵ�����һ����������ֵ�ʱ���ܴ浵
		//�������state״ָ̬ʾ����ô����Ҫ�������ֺ������浥��дһ���ж�
		//����state��f_code���ͨ��CC�ļ�飬����ִ�����������

		switch (spcf_code)
		{
		case 0://0���˳�����
			*Exit_SPC = 1;
			return 1;
			break;

		case 1:
			ShowSKPRmainControl();
			return 1;
			break;

		case 2:
			createSkill();
			return 1;
			break;

		case 3:
			return 1;
			break;

		case 9:
			develop_mode = 0;
			return 1;
			break;
		default://δ֪������ؿ���̨��ʾ����ʵ����AnalyseSPCCC���ص�-1��
			logger(INFO, Creator, "[Skills_Props_Creater_Console_Command]-δ֪��ָ�����ָ���б�");
			printf("����������������δ֪��ָ�����ָ���б�ע�����е�ָ�Ҫ����#����������������\n");
			printf("0���˳�/tc/TC/tuichu/Exit/exit\n");
			printf("1���鿴�����б�/�鿴/�б�/List/list/LIST/ȫ��\n");
			printf("2����������/����/�½�/Create/CREATE/create\n");
			printf("9: �˳�������ģʽ\n");
			printf("===============================================\n");
			break;
		}

		return 0;
	}

}


//������ʽ�Ľ��з���
int AnalyseSPCCC(const char* f_message)
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
		logger(INFO, ConsoleCommand, "[AnalyseSPCCC]-���յ��˳�SPCCC�ؼ���");
		return 0;
	}

	else if (
		strstr(f_message, "�鿴")||
		strstr(f_message, "�б�") ||
		strstr(f_message, "List") ||
		strstr(f_message, "LIST") ||
		strstr(f_message, "list") ||
		strstr(f_message, "ȫ��") ||
		strstr(f_message, "1")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseSPCCC]-���յ��鿴�����б�ؼ��֣���������");
		return 1;
	}

	else if (
		strstr(f_message, "����") ||
		strstr(f_message, "����") ||
		strstr(f_message, "�½�") ||
		strstr(f_message, "Create") ||
		strstr(f_message, "create") ||
		strstr(f_message, "CREATE") ||
		strstr(f_message, "2")

		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseSPCCC]-���յ������ż��ܹؼ��֣���������");
		return 2;
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




// ������ʾ������ͬʱ���ڳ�����ϸ��ʾ��ɾ�������ĳ�����ʾ��
int displayBrief() {
	int skpr_num_buttons = 0;
	int skpr_num_buttons_arr[MAX_BUTTONS];
	char * skpr_num_buttons_buttons[MAX_BUTTONS] = {};
	for (int i = 0; i < skill_count; i++) {
		if (SKILL_PROPS_LIST[i].prompt[0] != '\0')
		{
			//printf("%d. %s\n", i, SKILL_PROPS_LIST[i].prompt);

			skpr_num_buttons_arr[skpr_num_buttons] = i;
			skpr_num_buttons_buttons[skpr_num_buttons] = SKILL_PROPS_LIST[i].prompt;
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
	return(menu(skpr_num_buttons, "�����б�  0-999������ã�1000-1399����ģʽ��ȡ��1400-1499Ϊ��ѡ���ܣ�1500-1999Ϊ�̵�����", skpr_num_buttons_arr, skpr_num_buttons_buttons_const, introduction,2));
}

// ��ϸ��ʾ����
void displayDetail(int index) {
	if (index < 0 || index >= skill_count) {
		printf("��ų�����Χ��\n");
		return;
	}
	if (SKILL_PROPS_LIST[index].prompt[0] == '\0')
	{
		printf("�˴�����Ϊ�գ�\n");
		return;
	}
	SKILL_PROPS skill = SKILL_PROPS_LIST[index];
	Sleep(1000);
	printf("=======================================\n");
	printf("������ţ�%d\n", index);
	printf("ս������ʾ��Ϣ��%s\n", skill.prompt);
	printf("����ʱ��״̬��0���޷�ʹ�ã��������ͣ�1�Ƿ�ս������ûд��ս�����ܵ�ʹ�ã���2��ս��ʱ����%d\n", skill.state);
	printf("����1�Ƕ��Լ���2�ǶԵ��ˣ���%d\n", skill.object);
	printf("�Թ������Ĳ�����*%.2f\n", skill.Operate_ATK);
	printf("������ֵ�Ĳ�����+%d\n", skill.Operate_HP);
	printf("�Է������Ĳ�����*%.6f\n", skill.Operate_DEF);
	printf("�Խ�Ǯ�Ĳ�����+%d\n", skill.Operate_Money);
	printf("�Ծ�����Ч�غ�����0Ϊ�����Ծ֣���%d\n", skill.Fight_Times);
	printf("�۸�%d\n", skill.Price);
	printf("��ϸ���ܣ�%s\n", skill.Introduction);
	printf("=======================================\n�����������\n");
	while (!_kbhit()) {}

}

// ɾ�����Ǻ���
void deleteSkill(int index) {
	if (index < 0 || index >= skill_count) {
		printf("��ų�����Χ��\n");
		return;
	}
	if (index < MAX_SKILLS - 1 && index > 999)
	{
		printf("���1000-1999��ϵͳ�����ļ��ܵ��߷�����\n");
		if (!develop_mode)
		{
			return;
		}
		
	}
	displayDetail(index);
	printf("ȷ��Ҫɾ�����������\n");
	int cc_menu_arr[MAX_BUTTONS] = {-1};//ʹ��Ĭ�Ϸ�������
	const char* cc_menu_buttons[MAX_BUTTONS] =
	{
		"ȡ��",
		"ȷ��"
	};
	const char* introduction[MAX_BUTTONS] = {
NULL
	};
	if (!(menu(2, "ȷ��Ҫɾ�����������", cc_menu_arr, cc_menu_buttons, introduction) == 1))
	{
		return;
	}
	SKILL_PROPS_LIST[index].prompt[0] = '\0'; // ����ַ���
	SKILL_PROPS_LIST[index].state = 0;
	SKILL_PROPS_LIST[index].object = 1;
	SKILL_PROPS_LIST[index].Operate_ATK = 1.0f;
	SKILL_PROPS_LIST[index].Operate_HP = 0;
	SKILL_PROPS_LIST[index].Operate_DEF = 1.0f;
	SKILL_PROPS_LIST[index].Operate_Money = 0;
	SKILL_PROPS_LIST[index].Fight_Times = 0;
	SKILL_PROPS_LIST[index].Price = 0;
	SKILL_PROPS_LIST[index].Introduction[0] = '\0'; // ����ַ���
	printf("������ɾ�������ǣ�\n");
	Sleep(2000);
}

// �鿴�����ƺ���
void ShowSKPRmainControl() {
	int command;
	printf("���뼼������߲�ѯ����̨\n");
	while (1) {
		int sskprc_menu_arr[MAX_BUTTONS] = {-1};
		const char* sskprc_menu_buttons[MAX_BUTTONS] =
		{
			"�˳�",
			"���м���",
			"��ѯ��������",
			"ɾ������"
		};
		const char* introduction[MAX_BUTTONS] = {
NULL
		};
		command = menu(4, "��������߲�ѯ����̨", sskprc_menu_arr, sskprc_menu_buttons, introduction);
		
		switch (command) {
		case 1:
			Sleep(1000);
			displayBrief();
			break;
		case 2:
			Sleep(1000);
			displayDetail(displayBrief()); // �û��������Ŵ�1��ʼ������������0��ʼ
			break;
		case 3:
			Sleep(1000);
			deleteSkill(displayBrief()); // �û��������Ŵ�1��ʼ������������0��ʼ
			break;
		case 0:
			printf("�˳����ܲ鿴���򣬻ص����ܿ����ܳ���\n");
			return;
		default:
			printf("��Ч�����\n");
		}
	}
}

//������
//����Լ������ļ��ܣ�������Ϊֻ��ͨ����������ȡһ��������ң�����0-999�ż���ֻ���ڱ����д��һ��
//����Ϊ�˱�������ȴ���һ���浵�������Ѿ���100�����˼��ܣ������������5����
//Ȼ���ڴ���һ���߼����ܸ�����������������浵����ͼ�ô浵���SKP������Ϊ100���߼�����
//��ǿ��ֻ���ڴ�������ȡ������������һ���ܸ��Ĵ浵Ū����һ���߼����ܣ�Ȼ������һ���ͼ��浵��ȡ
//�����ڸ��ǣ�����ɾ�����¼���֮ǰ��Ҫ����ұ������������ɾ��
void createSkill() {
	int index;
	printf("������Ҫд�����ţ�0-%d����", MAX_SKILLS - 1);
	scanf_s("%d", &index);

	if (index < 0 || index > MAX_SKILLS - 1) {
		printf("��ų�����Χ��\n");
		return;
	}
	if (index < MAX_SKILLS - 1 && index > 999)
	{
		printf("���1000-1999��ϵͳ�����ļ��ܵ��߷�����\n");
		if (!develop_mode)
		{
			return;
		}
		
	}
	int index_in_propslist = findPropIndex(index);
	if (index_in_propslist > 0)
	{
		printf("�ü������Ѵ��������ļ��ܵ��߱����еĵ�%d�����飺\n",index_in_propslist);
		displayDetail(index);
		Sleep(1000);
		printf("���롰d��ɾ�������еĵ��߲���д������������˳���ѡ������λ�á�\n");
		char temp[20] = { '\0' };
		rewind(stdin);
		scanf_s("%s", &temp, 19);
		if (strstr(temp, "d"))
		{
			PLAYER.PROPS[index_in_propslist][0] = 0;
			PLAYER.PROPS[index_in_propslist][1] = 0;
			cleanAndOrganizeProps();
			deleteSkill(index);
		}
		else
		{
			printf("�˳����ܴ������򣬻ص����ܿ����ܳ���\n");
			return;
		}
	}
	if (SKILL_PROPS_LIST[index].prompt[0] != '\0') {
		printf("��λ���ѱ���ļ��ܵ���ռ�ã����飺\n");
		displayDetail(index);
		Sleep(1000);
		printf("���롰d��ɾ������д������������˳���ѡ������λ�á�\n");
		char temp[20] = { '\0' };
		rewind(stdin);
		scanf_s("%s", &temp, 19);
		if (strstr(temp, "d"))
		{
			deleteSkill(index);
		}
		else
		{
			printf("�˳����ܴ������򣬻ص����ܿ����ܳ���\n");
			return;
		}
	}


Start_Create://goto�õ�

	rewind(stdin);
	printf("������ս������ʾ��Ϣ��");
	scanf_s("%s", SKILL_PROPS_LIST[index].prompt, 201);
	rewind(stdin);
	printf("���������״̬��0�����ò����ã�1�Ƿ�ս����2��ս��ʱ����");
	scanf_s("%d", &SKILL_PROPS_LIST[index].state);

	printf("���������1�Ƕ��Լ���2�ǶԵ��ˣ���");
	scanf_s("%d", &SKILL_PROPS_LIST[index].object);

	if ((SKILL_PROPS_LIST[index].state == 1) && (SKILL_PROPS_LIST[index].object == 2))
	{
		printf("��ս�����ܲ��ܶԵ����ͷţ�����д\n");
		goto Start_Create;
	}

	printf("������Թ������Ĳ�����");
	scanf_s("%f", &SKILL_PROPS_LIST[index].Operate_ATK);

	printf("�����������ֵ�Ĳ������ǶԾ��и����������ޣ��Ծ��и��ĵ�ǰ����ֵ��ע����Լ��ļ��ܽ�������Ϊ�������Ե��˽�������Ϊ������");
	scanf_s("%d", &SKILL_PROPS_LIST[index].Operate_HP);

	printf("������Է������Ĳ�����");
	scanf_s("%f", &SKILL_PROPS_LIST[index].Operate_DEF);

Second_Create:
	printf("������Խ�Ǯ�Ĳ�����");
	scanf_s("%d", &SKILL_PROPS_LIST[index].Operate_Money);

	if ((SKILL_PROPS_LIST[index].state == 1) && (SKILL_PROPS_LIST[index].Operate_Money != 0))
	{
		printf("�Ծ��в��ܶԽ�ҽ����޸ģ�\n");
		rewind(stdin);
		goto Second_Create;

	}

	printf("������Ծ�����Ч����������0Ϊȫ����Ч��");
	scanf_s("%d", &SKILL_PROPS_LIST[index].Fight_Times);
	if (SKILL_PROPS_LIST[index].Fight_Times < 0)
	{
		printf("��Ч����Ӧ�����ڵ���0��\n");
	}
	int total_prize = 0;

	if (SKILL_PROPS_LIST[index].state == 2)//ս�����ܷ�֧
	{
		if (SKILL_PROPS_LIST[index].object == 1)//���Լ���ս������
		{
			total_prize = (
				(pow((SKILL_PROPS_LIST[index].Operate_ATK - 1) * PLAYER.ATK, 1.1) * 100) +
				pow(SKILL_PROPS_LIST[index].Operate_HP, 3) + 
				(100 / SKILL_PROPS_LIST[index].Operate_DEF) - 100 +
				SKILL_PROPS_LIST[index].Operate_Money
				);
		}
		else if (SKILL_PROPS_LIST[index].object == 2)//�Ե��˵ļ���
		{
			total_prize = (//�Ե��ˣ�ATKԽС����Խǿ
				100.f / SKILL_PROPS_LIST[index].Operate_ATK - //�Ե��ˣ�Operate_HP���ճ��������Ϊ��������������ü��š�����������������������һЩ
				pow(SKILL_PROPS_LIST[index].Operate_HP, 3) + 
				(SKILL_PROPS_LIST[index].Operate_DEF - 1) * 100 +
				SKILL_PROPS_LIST[index].Operate_Money
				);
		}
		else
		{
			printf("����Ķ����루�Ե��ˣ�2�����߶��Լ���1�������ˣ��������趨\n");
			goto Start_Create;
			//��ž�������ˣ�������һ�������߼���ǳ��һ��goto
		}
		if (SKILL_PROPS_LIST[index].Fight_Times == 0)
		{
			total_prize *= 10;
		}
		else
		{
			total_prize *= SKILL_PROPS_LIST[index].Fight_Times;
		}


	}
	else if (SKILL_PROPS_LIST[index].state == 1)//��ս�����߷�֧
	{
		if (SKILL_PROPS_LIST[index].object == 1)//���Լ���
		{
			total_prize = (
				(pow((SKILL_PROPS_LIST[index].Operate_ATK - 1) * PLAYER.ATK, 1.1) * 1000) +
				SKILL_PROPS_LIST[index].Operate_HP * 100 +
				1000 / SKILL_PROPS_LIST[index].Operate_DEF +
				SKILL_PROPS_LIST[index].Operate_Money
				);
		}
		else
		{
			//��ս������ֻ�ܶ��Լ�ʹ�ã�goto���޸�
			printf("����Ķ����루�Ե��ˣ�2�����߶��Լ���1�������ˣ���ս������ֻ�ܶ��Լ�ʹ�ã��������趨\n");
			goto Start_Create;
		}
	}

	 


	printf("�㴴���ļ��ܻ���ߵļ۸�Ϊ%d\n", total_prize);
	if ((total_prize > PLAYER.Money) && !develop_mode)
	{
		printf("�㴴���ļ��ܻ���ߵļ۸�Ϊ%d������ֻ��%d�������\n", total_prize, PLAYER.Money);
		printf("���롰e���������˳���������������´���\n");
		SKILL_PROPS_LIST[index].prompt[0] = '\0'; // ����ַ���
		SKILL_PROPS_LIST[index].state = 0;
		SKILL_PROPS_LIST[index].object = 1;
		SKILL_PROPS_LIST[index].Operate_ATK = 1.0f;
		SKILL_PROPS_LIST[index].Operate_HP = 0;
		SKILL_PROPS_LIST[index].Operate_DEF = 1.0f;
		SKILL_PROPS_LIST[index].Operate_Money = 0;
		SKILL_PROPS_LIST[index].Fight_Times = 0;
		SKILL_PROPS_LIST[index].Price = 0;
		SKILL_PROPS_LIST[index].Introduction[0] = '\0'; // ����ַ���
		
		char temp[20] = { '\0' };
		//rewind(stdin);
		scanf_s("%s", &temp, 19);
		if (strstr(temp, "e"))
		{
			printf("�˳����ܴ������򣬻ص����ܿ����ܳ���\n");
			return;
		}
		else
		{
			goto Start_Create;
		}

	}
	Sleep(1000);
	printf("�Ƿ�ȷ�ϴ����������⽫�۳����Ӧ�Ľ�ң����롰e�����������������������\n");//�۳����ھ���������ȫ������ӽ�stats
	char temp[20] = { '\0' };
	//rewind(stdin);
	scanf_s("%s", &temp, 19);
	if (strstr(temp, "e"))
	{
		SKILL_PROPS_LIST[index].prompt[0] = '\0'; // ����ַ���
		SKILL_PROPS_LIST[index].state = 0;
		SKILL_PROPS_LIST[index].object = 1;
		SKILL_PROPS_LIST[index].Operate_ATK = 1.0f;
		SKILL_PROPS_LIST[index].Operate_HP = 0;
		SKILL_PROPS_LIST[index].Operate_DEF = 1.0f;
		SKILL_PROPS_LIST[index].Operate_Money = 0;
		SKILL_PROPS_LIST[index].Fight_Times = 0;
		SKILL_PROPS_LIST[index].Price = 0;
		SKILL_PROPS_LIST[index].Introduction[0] = '\0'; // ����ַ���
		printf("�˳����ܴ������򣬻ص����ܿ����ܳ���\n");
		return;
	}

	SKILL_PROPS_LIST[index].Price = total_prize;
	PLAYER.Money -= total_prize;
	PLAYER.PROPS[99][0] = index;
	PLAYER.PROPS[99][1] = 1;
	cleanAndOrganizeProps();

	printf("��������ϸ���ܣ����200���ַ�����");
	getchar(); // ����������еĻ��з�
	fgets(SKILL_PROPS_LIST[index].Introduction, 201, stdin);
	SKILL_PROPS_LIST[index].Introduction[strcspn(SKILL_PROPS_LIST[index].Introduction, "\n")] = '\0'; // ȥ��ĩβ�Ļ��з�

	printf("�����Ѵ�����д�뵽��� %d��\n", index);
	skill_count = (skill_count > index + 1) ? skill_count : (index + 1); // ���¼�������
	
	if (!SaveSkillsPropsFile(SKILL_PROPS_LIST, &skill_count))
	{
		printf("����������б��ļ�����ʧ��!\n");
	}
	else
	{
		printf("����������б��ļ��Ѹ���\n");
	}
}