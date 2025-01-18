#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <commdlg.h>


// ��ȡ�ı�TXT�ļ�������Ϊ�ṹ�����飨����SP�ṹ���ʽ���ˣ����������Ҫ�޸�
//int ReadSkillsPropsFile(const wchar_t* filename, struct SKILL_PROPS* skills, int maxSkills) {
//    FILE* file;
//    _wfopen_s(&file, filename, L"r");
//    if (file == NULL) {
//        perror("Failed to open file");
//        return 0;
//    }
//
//    char line[MAX_LINE_LENGTH];
//    int skillCount = 0;
//    char* context = NULL; // ����strtok_s
//
//    while (fgets(line, sizeof(line), file) && skillCount < maxSkills) {
//        char* token;
//        char* prompt = strtok_s(line, ",", &context);
//        int state = atoi(strtok_s(NULL, ",", &context));
//        int object = atoi(strtok_s(NULL, ",", &context));
//        float Operate_ATK = atof(strtok_s(NULL, ",", &context));
//        int Operate_HP = atoi(strtok_s(NULL, ",", &context));
//        float Operate_DEF = atof(strtok_s(NULL, ",", &context));
//        int Operate_Money = atoi(strtok_s(NULL, "\n", &context));
//
//        // �����ڴ沢�����ַ���
//        skills[skillCount].prompt = _strdup(prompt);
//        skills[skillCount].state = state;
//        skills[skillCount].object = object;
//        skills[skillCount].Operate_ATK = Operate_ATK;
//        skills[skillCount].Operate_HP = Operate_HP;
//        skills[skillCount].Operate_DEF = Operate_DEF;
//        skills[skillCount].Operate_Money = Operate_Money;
//
//        skillCount++;
//    }
//
//    fclose(file);
//    return skillCount;
//}

// ��ȡ�������ļ����������ֱ�ӽ���������ֻ��ͨ��C�����ڲ������޸�
//��ȡ���ܵ����ļ��ĺ���
bool LoadSkillsPropsFile(SKILL_PROPS* plist, int* iCount)//����������������λ�ñ��ϵ�һ�������ĵ�ַ������������ڲ�ͨ���������޸��������൱�ڡ���������ֵ��
{
    //���ļ�
    FILE* pf;
    fopen_s(&pf, "classic_skills_props.dat", "rb");
    
    //���ļ�ʧ��
    if (pf == NULL)
    {
        printf("[LoadSkillsPropsFile]-��SkillsProps�ļ�ʧ��\n");
        return false;
    }
    if (!fread(iCount, sizeof(int), 1, pf))
    {
        printf("[LoadSkillsPropsFile]-��SkillsProps�ļ��ɹ��������ļ�Ϊ��\n");
        *iCount = 0;
        fclose(pf);
        return true;
    }

    fread(plist, sizeof(SKILL_PROPS), *iCount, pf);
    printf("[LoadSkillsPropsFile]-��ȡ��%d��SkillsProps�ļ���Ϣ\n", *iCount);

    //�ر��ļ�
    fclose(pf);
    printf("[LoadSkillsPropsFile]-��SkillsProps�ļ��ɹ�\n");
    return true;
}
//д�뼼�ܵ����ļ��ĺ���
bool SaveSkillsPropsFile(SKILL_PROPS* plist, int* iCount)//����д�뱣�漼�ܵ����ļ�
{
    //���ļ�
    FILE* pf;
    fopen_s(&pf, "classic_skills_props.dat", "wb");


    //���ļ�ʧ��
    if (pf == NULL)
    {
        printf("[SaveSkillsPropsFile]-��SkillsProps�ļ�ʧ��\n");
        return false;
    }

    fwrite(iCount, sizeof(int), 1, pf);
    fwrite(plist, sizeof(SKILL_PROPS), *iCount, pf);
    printf("[SaveSkillsPropsFile]-������%d��SkillsProps��Ϣ\n", * iCount);

    //�ر��ļ�
    fclose(pf);

    return true;
}

//��ȡ�����ļ��ĺ���
bool LoadStoryLinesFile(Story_Line* plist, int* iCount)
{
    //���ļ�
    FILE* pf;
    fopen_s(&pf, "classic_story_lines.dat", "rb");

    //���ļ�ʧ��
    if (pf == NULL)
    {
        printf("[LoadStoryLinesFile]-��StoryLines�ļ�ʧ��\n");
        return false;
    }
    if (!fread(iCount, sizeof(int), 1, pf))
    {
        printf("[LoadStoryLinesFile]-��StoryLines�ļ��ɹ��������ļ�Ϊ��\n");
        *iCount = 0;
        fclose(pf);
        return true;
    }

    fread(plist, sizeof(Story_Line), *iCount, pf);
    printf("[LoadStoryLinesFile]-��ȡ��%d��StoryLines�ļ���Ϣ\n", *iCount);

    //�ر��ļ�
    fclose(pf);
    printf("[LoadStoryLinesFile]-��StoryLines�ļ��ɹ�\n");
    return true;
}
//д������ļ��ĺ���
bool SaveStoryLinesFile(Story_Line* plist, int* iCount)
{
    //���ļ�
    FILE* pf;
    fopen_s(&pf, "classic_story_lines.dat", "wb");


    //���ļ�ʧ��
    if (pf == NULL)
    {
        printf("[SaveStoryLinesFile]-��SaveStoryLines�ļ�ʧ��\n");
        return false;
    }

    fwrite(iCount, sizeof(int), 1, pf);
    fwrite(plist, sizeof(Story_Line), *iCount, pf);
    printf("[SaveStoryLinesFile]-������%d��SaveStoryLines��Ϣ\n", *iCount);

    //�ر��ļ�
    fclose(pf);

    return true;
}

//��ȡ�浵
bool LoadSaveFile(Save *plist, int* iCount, const wchar_t* filePath)
{
    //���ļ�
    FILE* pf;
    _wfopen_s(&pf, filePath, L"rb");
    //fopen_s(&pf, "classic_save.dat", "rb");

    //���ļ�ʧ��
    if (pf == NULL)
    {
        printf("[LoadSaveFile]-��save�ļ�ʧ��\n");
        return false;
    }
    if (!fread(iCount, sizeof(int), 1, pf))
    {
        printf("[LoadSaveFile]-��save�ļ��ɹ��������ļ�Ϊ��\n");
        *iCount = 0;
        fclose(pf);
        return true;
    }

    fread(plist, sizeof(Save), *iCount, pf);
    printf("[LoadSaveFile]-��ȡ��%d��save�ļ���Ϣ\n", *iCount);

    //�ر��ļ�
    fclose(pf);
    printf("[LoadSaveFile]-��save�ļ��ɹ�\n");
    return true;
}
//д��浵
bool SaveSaveFile(Save *plist, int* iCount)
{
    //���ļ�
    FILE* pf;
    fopen_s(&pf, "classic_save.dat", "wb");


    //���ļ�ʧ��
    if (pf == NULL)
    {
        printf("[SaveSaveFile]-��save�ļ�ʧ��\n");
        return false;
    }

    fwrite(iCount, sizeof(int), 1, pf);
    fwrite(plist, sizeof(Save), *iCount, pf);
    printf("[SaveSaveFile]-������%d��save��Ϣ\n", *iCount);

    //�ر��ļ�
    fclose(pf);

    return true;
}
