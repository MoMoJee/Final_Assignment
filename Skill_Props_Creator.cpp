#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>
#include<math.h>

int spcf_code = 0;

int Skills_Props_Creater_Main()//创建技能并写入
{

	int Money_Consumption = 0;
	bool Exit_SPC = 0;//SPCCC会在接收到退出指令时修改它
	while (1)
	{

		if (Exit_SPC)
		{
			logger(INFO, Creator, "[Skills_Props_Creater_Main]-接收到退出命令");
			printf("期待下次光临！\n");
			return Money_Consumption;
		}

		const char* SPCcmdinput = "nouse";
		Skills_Props_Creater_Console_Command(SPCcmdinput,&Exit_SPC);
	}
	return Money_Consumption;
}

int Skills_Props_Creater_Console_Command(const char* message,bool * Exit_SPC)//创建技能并写入的控制台
{
	{
		
		int cc_menu_arr[MAX_BUTTONS] = {-1};
		const char* cc_menu_buttons[MAX_BUTTONS] =
		{
			"退出",
			"技能查询台",
			"技能创建器"
		};
		const char* introduction[MAX_BUTTONS] = {
NULL
		};
		char spccc_cmd[401] = { '\0' };


		if ((spcf_code == -1) || (develop_mode))// -1指示用户在菜单中输入了#或者当前处于开发者模式
		{
			printf("这里是开发者模式，输入“#”来获取命令帮助\n");
			develop_mode = 1;

			scanf_s("%s", spccc_cmd, 401);
			const char* spccc_cmdinput = spccc_cmd;
			if (strstr(spccc_cmdinput, "#") || strstr(spccc_cmdinput, "#"))
			{
				logger(INFO, Creator, "[Skills_Props_Creater_Console_Command]-截取到#控制台关键词");
				spcf_code = AnalyseSPCCC(spccc_cmdinput);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			spcf_code = menu(3, "技能查询与创建", cc_menu_arr, cc_menu_buttons, introduction);
		}


		//比如有些功能只能在main进程中调用，那如果在别的进程中调用，就需要通过鉴权来阻止这个请求
		//比如在打怪，打怪进程是单独的一个函数，打怪的时候不能存档
		//如果不用state状态指示，那么就需要在这个打怪函数里面单独写一个判断
		//即，state和f_code组合通过CC的检查，才能执行这个操作。

		switch (spcf_code)
		{
		case 0://0是退出命令
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
		default://未知命令，返回控制台提示（其实就是AnalyseSPCCC返回的-1）
			logger(INFO, Creator, "[Skills_Props_Creater_Console_Command]-未知的指令，返回指令列表");
			printf("————————未知的指令，返回指令列表，注意所有的指令都要加上#————————\n");
			printf("0：退出/tc/TC/tuichu/Exit/exit\n");
			printf("1：查看技能列表/查看/列表/List/list/LIST/全部\n");
			printf("2：创建技能/创建/新建/Create/CREATE/create\n");
			printf("9: 退出开发者模式\n");
			printf("===============================================\n");
			break;
		}

		return 0;
	}

}


//对命令式的进行分析
int AnalyseSPCCC(const char* f_message)
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
		logger(INFO, ConsoleCommand, "[AnalyseSPCCC]-接收到退出SPCCC关键字");
		return 0;
	}

	else if (
		strstr(f_message, "查看")||
		strstr(f_message, "列表") ||
		strstr(f_message, "List") ||
		strstr(f_message, "LIST") ||
		strstr(f_message, "list") ||
		strstr(f_message, "全部") ||
		strstr(f_message, "1")
		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseSPCCC]-接收到查看技能列表关键字，启动进程");
		return 1;
	}

	else if (
		strstr(f_message, "创建") ||
		strstr(f_message, "技能") ||
		strstr(f_message, "新建") ||
		strstr(f_message, "Create") ||
		strstr(f_message, "create") ||
		strstr(f_message, "CREATE") ||
		strstr(f_message, "2")

		)
	{
		logger(INFO, ConsoleCommand, "[AnalyseSPCCC]-接收到创建信技能关键字，启动进程");
		return 2;
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




// 简略显示函数，同时用于承载详细显示、删除函数的初步显示。
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
	return(menu(skpr_num_buttons, "技能列表  0-999玩家自用，1000-1399剧情模式获取，1400-1499为可选技能，1500-1999为商店售卖", skpr_num_buttons_arr, skpr_num_buttons_buttons_const, introduction,2));
}

// 详细显示函数
void displayDetail(int index) {
	if (index < 0 || index >= skill_count) {
		printf("序号超出范围！\n");
		return;
	}
	if (SKILL_PROPS_LIST[index].prompt[0] == '\0')
	{
		printf("此处技能为空！\n");
		return;
	}
	SKILL_PROPS skill = SKILL_PROPS_LIST[index];
	Sleep(1000);
	printf("=======================================\n");
	printf("技能序号：%d\n", index);
	printf("战斗中提示信息：%s\n", skill.prompt);
	printf("可用时的状态（0是无法使用，仅供观赏，1是非战斗（还没写非战斗技能的使用），2是战斗时）：%d\n", skill.state);
	printf("对象（1是对自己，2是对敌人）：%d\n", skill.object);
	printf("对攻击力的操作：*%.2f\n", skill.Operate_ATK);
	printf("对生命值的操作：+%d\n", skill.Operate_HP);
	printf("对防御力的操作：*%.6f\n", skill.Operate_DEF);
	printf("对金钱的操作：+%d\n", skill.Operate_Money);
	printf("对局中有效回合数（0为整个对局）：%d\n", skill.Fight_Times);
	printf("价格：%d\n", skill.Price);
	printf("详细介绍：%s\n", skill.Introduction);
	printf("=======================================\n按任意键继续\n");
	while (!_kbhit()) {}

}

// 删除覆盖函数
void deleteSkill(int index) {
	if (index < 0 || index >= skill_count) {
		printf("序号超出范围！\n");
		return;
	}
	if (index < MAX_SKILLS - 1 && index > 999)
	{
		printf("序号1000-1999是系统保留的技能道具分区！\n");
		if (!develop_mode)
		{
			return;
		}
		
	}
	displayDetail(index);
	printf("确定要删除这个技能吗？\n");
	int cc_menu_arr[MAX_BUTTONS] = {-1};//使用默认返回索引
	const char* cc_menu_buttons[MAX_BUTTONS] =
	{
		"取消",
		"确定"
	};
	const char* introduction[MAX_BUTTONS] = {
NULL
	};
	if (!(menu(2, "确定要删除这个技能吗？", cc_menu_arr, cc_menu_buttons, introduction) == 1))
	{
		return;
	}
	SKILL_PROPS_LIST[index].prompt[0] = '\0'; // 清空字符串
	SKILL_PROPS_LIST[index].state = 0;
	SKILL_PROPS_LIST[index].object = 1;
	SKILL_PROPS_LIST[index].Operate_ATK = 1.0f;
	SKILL_PROPS_LIST[index].Operate_HP = 0;
	SKILL_PROPS_LIST[index].Operate_DEF = 1.0f;
	SKILL_PROPS_LIST[index].Operate_Money = 0;
	SKILL_PROPS_LIST[index].Fight_Times = 0;
	SKILL_PROPS_LIST[index].Price = 0;
	SKILL_PROPS_LIST[index].Introduction[0] = '\0'; // 清空字符串
	printf("技能已删除并覆盖！\n");
	Sleep(2000);
}

// 查看器控制函数
void ShowSKPRmainControl() {
	int command;
	printf("进入技能与道具查询主控台\n");
	while (1) {
		int sskprc_menu_arr[MAX_BUTTONS] = {-1};
		const char* sskprc_menu_buttons[MAX_BUTTONS] =
		{
			"退出",
			"所有技能",
			"查询单个技能",
			"删除技能"
		};
		const char* introduction[MAX_BUTTONS] = {
NULL
		};
		command = menu(4, "技能与道具查询主控台", sskprc_menu_arr, sskprc_menu_buttons, introduction);
		
		switch (command) {
		case 1:
			Sleep(1000);
			displayBrief();
			break;
		case 2:
			Sleep(1000);
			displayDetail(displayBrief()); // 用户输入的序号从1开始，数组索引从0开始
			break;
		case 3:
			Sleep(1000);
			deleteSkill(displayBrief()); // 用户输入的序号从1开始，数组索引从0开始
			break;
		case 0:
			printf("退出技能查看程序，回到技能控制总程序。\n");
			return;
		default:
			printf("无效的命令！\n");
		}
	}
}

//创建器
//玩家自己创建的技能，被限制为只能通过创建器获取一个（花金币），即0-999号技能只能在背包中存放一个
//这是为了避免玩家先创建一个存档，里面已经有100个便宜技能（技能码比如是5）。
//然后在创建一个高级技能覆盖它，再载入这个存档，企图让存档配合SKP表格解析为100个高级技能
//而强制只能在创建器获取，最多就是你用一个很富的存档弄到了一个高级技能，然后再用一个低级存档读取
//另外在覆盖（或者删除）新技能之前，要把玩家背包里这个技能删除
void createSkill() {
	int index;
	printf("请输入要写入的序号（0-%d）：", MAX_SKILLS - 1);
	scanf_s("%d", &index);

	if (index < 0 || index > MAX_SKILLS - 1) {
		printf("序号超出范围！\n");
		return;
	}
	if (index < MAX_SKILLS - 1 && index > 999)
	{
		printf("序号1000-1999是系统保留的技能道具分区！\n");
		if (!develop_mode)
		{
			return;
		}
		
	}
	int index_in_propslist = findPropIndex(index);
	if (index_in_propslist > 0)
	{
		printf("该技能码已存在于您的技能道具背包中的第%d格，详情：\n",index_in_propslist);
		displayDetail(index);
		Sleep(1000);
		printf("键入“d”删除您已有的道具并重写，键入任意键退出并选择其他位置。\n");
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
			printf("退出技能创建程序，回到技能控制总程序。\n");
			return;
		}
	}
	if (SKILL_PROPS_LIST[index].prompt[0] != '\0') {
		printf("该位置已被别的技能道具占用，详情：\n");
		displayDetail(index);
		Sleep(1000);
		printf("键入“d”删除并重写，键入任意键退出并选择其他位置。\n");
		char temp[20] = { '\0' };
		rewind(stdin);
		scanf_s("%s", &temp, 19);
		if (strstr(temp, "d"))
		{
			deleteSkill(index);
		}
		else
		{
			printf("退出技能创建程序，回到技能控制总程序。\n");
			return;
		}
	}


Start_Create://goto用的

	rewind(stdin);
	printf("请输入战斗中提示信息：");
	scanf_s("%s", SKILL_PROPS_LIST[index].prompt, 201);
	rewind(stdin);
	printf("请输入可用状态（0是永久不可用，1是非战斗，2是战斗时）：");
	scanf_s("%d", &SKILL_PROPS_LIST[index].state);

	printf("请输入对象（1是对自己，2是对敌人）：");
	scanf_s("%d", &SKILL_PROPS_LIST[index].object);

	if ((SKILL_PROPS_LIST[index].state == 1) && (SKILL_PROPS_LIST[index].object == 2))
	{
		printf("非战斗技能不能对敌人释放！请重写\n");
		goto Start_Create;
	}

	printf("请输入对攻击力的操作：");
	scanf_s("%f", &SKILL_PROPS_LIST[index].Operate_ATK);

	printf("请输入对生命值的操作（非对局中更改生命上限，对局中更改当前生命值。注意对自己的技能建议设置为正数，对敌人建议设置为负数：");
	scanf_s("%d", &SKILL_PROPS_LIST[index].Operate_HP);

	printf("请输入对防御力的操作：");
	scanf_s("%f", &SKILL_PROPS_LIST[index].Operate_DEF);

Second_Create:
	printf("请输入对金钱的操作：");
	scanf_s("%d", &SKILL_PROPS_LIST[index].Operate_Money);

	if ((SKILL_PROPS_LIST[index].state == 1) && (SKILL_PROPS_LIST[index].Operate_Money != 0))
	{
		printf("对局中不能对金币进行修改！\n");
		rewind(stdin);
		goto Second_Create;

	}

	printf("请输入对局中有效次数，其中0为全局生效：");
	scanf_s("%d", &SKILL_PROPS_LIST[index].Fight_Times);
	if (SKILL_PROPS_LIST[index].Fight_Times < 0)
	{
		printf("有效次数应当大于等于0！\n");
	}
	int total_prize = 0;

	if (SKILL_PROPS_LIST[index].state == 2)//战斗技能分支
	{
		if (SKILL_PROPS_LIST[index].object == 1)//对自己的战斗技能
		{
			total_prize = (
				(pow((SKILL_PROPS_LIST[index].Operate_ATK - 1) * PLAYER.ATK, 1.1) * 100) +
				pow(SKILL_PROPS_LIST[index].Operate_HP, 3) + 
				(100 / SKILL_PROPS_LIST[index].Operate_DEF) - 100 +
				SKILL_PROPS_LIST[index].Operate_Money
				);
		}
		else if (SKILL_PROPS_LIST[index].object == 2)//对敌人的技能
		{
			total_prize = (//对敌人，ATK越小技能越强
				100.f / SKILL_PROPS_LIST[index].Operate_ATK - //对敌人，Operate_HP按照常理会设置为负数，因此这里用减号。如果输入的是正数，则会便宜一些
				pow(SKILL_PROPS_LIST[index].Operate_HP, 3) + 
				(SKILL_PROPS_LIST[index].Operate_DEF - 1) * 100 +
				SKILL_PROPS_LIST[index].Operate_Money
				);
		}
		else
		{
			printf("输入的对象码（对敌人：2，或者对自己：1，错误了，请重新设定\n");
			goto Start_Create;
			//大概就是输错了，这里做一个返回逻辑，浅用一下goto
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
	else if (SKILL_PROPS_LIST[index].state == 1)//非战斗道具分支
	{
		if (SKILL_PROPS_LIST[index].object == 1)//对自己的
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
			//非战斗技能只能对自己使用，goto做修改
			printf("输入的对象码（对敌人：2，或者对自己：1，错误了，非战斗技能只能对自己使用，请重新设定\n");
			goto Start_Create;
		}
	}

	 


	printf("你创建的技能或道具的价格为%d\n", total_prize);
	if ((total_prize > PLAYER.Money) && !develop_mode)
	{
		printf("你创建的技能或道具的价格为%d，但您只有%d个金币了\n", total_prize, PLAYER.Money);
		printf("键入“e”放弃并退出，键入任意键重新创建\n");
		SKILL_PROPS_LIST[index].prompt[0] = '\0'; // 清空字符串
		SKILL_PROPS_LIST[index].state = 0;
		SKILL_PROPS_LIST[index].object = 1;
		SKILL_PROPS_LIST[index].Operate_ATK = 1.0f;
		SKILL_PROPS_LIST[index].Operate_HP = 0;
		SKILL_PROPS_LIST[index].Operate_DEF = 1.0f;
		SKILL_PROPS_LIST[index].Operate_Money = 0;
		SKILL_PROPS_LIST[index].Fight_Times = 0;
		SKILL_PROPS_LIST[index].Price = 0;
		SKILL_PROPS_LIST[index].Introduction[0] = '\0'; // 清空字符串
		
		char temp[20] = { '\0' };
		//rewind(stdin);
		scanf_s("%s", &temp, 19);
		if (strstr(temp, "e"))
		{
			printf("退出技能创建程序，回到技能控制总程序。\n");
			return;
		}
		else
		{
			goto Start_Create;
		}

	}
	Sleep(1000);
	printf("是否确认创建并购买？这将扣除你对应的金币，键入“e”放弃，键入任意键继续。\n");//扣除现在就做，下面全结束后加进stats
	char temp[20] = { '\0' };
	//rewind(stdin);
	scanf_s("%s", &temp, 19);
	if (strstr(temp, "e"))
	{
		SKILL_PROPS_LIST[index].prompt[0] = '\0'; // 清空字符串
		SKILL_PROPS_LIST[index].state = 0;
		SKILL_PROPS_LIST[index].object = 1;
		SKILL_PROPS_LIST[index].Operate_ATK = 1.0f;
		SKILL_PROPS_LIST[index].Operate_HP = 0;
		SKILL_PROPS_LIST[index].Operate_DEF = 1.0f;
		SKILL_PROPS_LIST[index].Operate_Money = 0;
		SKILL_PROPS_LIST[index].Fight_Times = 0;
		SKILL_PROPS_LIST[index].Price = 0;
		SKILL_PROPS_LIST[index].Introduction[0] = '\0'; // 清空字符串
		printf("退出技能创建程序，回到技能控制总程序。\n");
		return;
	}

	SKILL_PROPS_LIST[index].Price = total_prize;
	PLAYER.Money -= total_prize;
	PLAYER.PROPS[99][0] = index;
	PLAYER.PROPS[99][1] = 1;
	cleanAndOrganizeProps();

	printf("请输入详细介绍（最多200个字符）：");
	getchar(); // 清除缓冲区中的换行符
	fgets(SKILL_PROPS_LIST[index].Introduction, 201, stdin);
	SKILL_PROPS_LIST[index].Introduction[strcspn(SKILL_PROPS_LIST[index].Introduction, "\n")] = '\0'; // 去除末尾的换行符

	printf("技能已创建并写入到序号 %d。\n", index);
	skill_count = (skill_count > index + 1) ? skill_count : (index + 1); // 更新技能数量
	
	if (!SaveSkillsPropsFile(SKILL_PROPS_LIST, &skill_count))
	{
		printf("技能与道具列表文件保存失败!\n");
	}
	else
	{
		printf("技能与道具列表文件已更新\n");
	}
}