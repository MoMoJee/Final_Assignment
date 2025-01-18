#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "functions.h"
#include <string.h>
#include <time.h>
#include <iostream>

void displayProps() {
    cleanAndOrganizeProps();
    printf("当前拥有的道具列表：\n");
    int found = 0; // 标记是否找到有效的属性行
    printf("道具序号\t简介\t\t\t\t道具数量\n");
    printf("=================================================================\n");
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][0] != 0 || PLAYER.PROPS[i][1] != 0) {
            printf("道具槽 %d:\t\t %s\t%d\n", i + 1, SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].prompt, PLAYER.PROPS[i][1]);
            found = 1;
        }
    }

    if (!found) {
        printf("您当前没有道具！\n");
    }
    printf("=================================================================\n");
    clearInputBuffer();
    printf("按任意键继续\n");
    while (!_kbhit()) {}

}

// 函数用于展示 PLAYER 的各个数据
void displayPlayerStats() {
    system("cls");
    printf("==============================我的=================================\n");
    printf("玩家名称: %s\n", PLAYER.Name);
    printf("攻击力: %d\n", PLAYER.ATK);
    printf("生命值: %d\n", PLAYER.HP);
    printf("防御力: %.2f\n", PLAYER.DEF);
    printf("金钱: %d\n", PLAYER.Money);
    printf("当前玩的剧情组：%d 号剧情线\n",STORY_LINE_CODE);
    printf("正在玩的关卡： 序号 %d %s\n", PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE], STORY_LINES[PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE]].Name);
    displayDetail(PLAYER.SKILL[0]);
}