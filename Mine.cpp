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
    printf("��ǰӵ�еĵ����б�\n");
    int found = 0; // ����Ƿ��ҵ���Ч��������
    printf("�������\t���\t\t\t\t��������\n");
    printf("=================================================================\n");
    for (int i = 0; i < 100; i++) {
        if (PLAYER.PROPS[i][0] != 0 || PLAYER.PROPS[i][1] != 0) {
            printf("���߲� %d:\t\t %s\t%d\n", i + 1, SKILL_PROPS_LIST[PLAYER.PROPS[i][0]].prompt, PLAYER.PROPS[i][1]);
            found = 1;
        }
    }

    if (!found) {
        printf("����ǰû�е��ߣ�\n");
    }
    printf("=================================================================\n");
    clearInputBuffer();
    printf("�����������\n");
    while (!_kbhit()) {}

}

// ��������չʾ PLAYER �ĸ�������
void displayPlayerStats() {
    system("cls");
    printf("==============================�ҵ�=================================\n");
    printf("�������: %s\n", PLAYER.Name);
    printf("������: %d\n", PLAYER.ATK);
    printf("����ֵ: %d\n", PLAYER.HP);
    printf("������: %.2f\n", PLAYER.DEF);
    printf("��Ǯ: %d\n", PLAYER.Money);
    printf("��ǰ��ľ����飺%d �ž�����\n",STORY_LINE_CODE);
    printf("������Ĺؿ��� ��� %d %s\n", PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE], STORY_LINES[PLAYER_SAVE.Story_Line_Coordinates[STORY_LINE_CODE]].Name);
    displayDetail(PLAYER.SKILL[0]);
}