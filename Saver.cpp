#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <commdlg.h>


// 读取文本TXT文件并解析为结构体数组（由于SP结构体格式变了，这个函数需要修改
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
//    char* context = NULL; // 用于strtok_s
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
//        // 分配内存并复制字符串
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

// 读取二进制文件，这个可以直接解析，但是只能通过C程序内部进行修改
//读取技能道具文件的函数
bool LoadSkillsPropsFile(SKILL_PROPS* plist, int* iCount)//传入调用这个函数的位置边上的一个变量的地址，在这个函数内部通过解引用修改它。这相当于”两个返回值“
{
    //打开文件
    FILE* pf;
    fopen_s(&pf, "classic_skills_props.dat", "rb");
    
    //打开文件失败
    if (pf == NULL)
    {
        printf("[LoadSkillsPropsFile]-打开SkillsProps文件失败\n");
        return false;
    }
    if (!fread(iCount, sizeof(int), 1, pf))
    {
        printf("[LoadSkillsPropsFile]-打开SkillsProps文件成功，但是文件为空\n");
        *iCount = 0;
        fclose(pf);
        return true;
    }

    fread(plist, sizeof(SKILL_PROPS), *iCount, pf);
    printf("[LoadSkillsPropsFile]-读取到%d条SkillsProps文件信息\n", *iCount);

    //关闭文件
    fclose(pf);
    printf("[LoadSkillsPropsFile]-打开SkillsProps文件成功\n");
    return true;
}
//写入技能道具文件的函数
bool SaveSkillsPropsFile(SKILL_PROPS* plist, int* iCount)//用于写入保存技能道具文件
{
    //打开文件
    FILE* pf;
    fopen_s(&pf, "classic_skills_props.dat", "wb");


    //打开文件失败
    if (pf == NULL)
    {
        printf("[SaveSkillsPropsFile]-打开SkillsProps文件失败\n");
        return false;
    }

    fwrite(iCount, sizeof(int), 1, pf);
    fwrite(plist, sizeof(SKILL_PROPS), *iCount, pf);
    printf("[SaveSkillsPropsFile]-保存了%d条SkillsProps信息\n", * iCount);

    //关闭文件
    fclose(pf);

    return true;
}

//读取剧情文件的函数
bool LoadStoryLinesFile(Story_Line* plist, int* iCount)
{
    //打开文件
    FILE* pf;
    fopen_s(&pf, "classic_story_lines.dat", "rb");

    //打开文件失败
    if (pf == NULL)
    {
        printf("[LoadStoryLinesFile]-打开StoryLines文件失败\n");
        return false;
    }
    if (!fread(iCount, sizeof(int), 1, pf))
    {
        printf("[LoadStoryLinesFile]-打开StoryLines文件成功，但是文件为空\n");
        *iCount = 0;
        fclose(pf);
        return true;
    }

    fread(plist, sizeof(Story_Line), *iCount, pf);
    printf("[LoadStoryLinesFile]-读取到%d条StoryLines文件信息\n", *iCount);

    //关闭文件
    fclose(pf);
    printf("[LoadStoryLinesFile]-打开StoryLines文件成功\n");
    return true;
}
//写入剧情文件的函数
bool SaveStoryLinesFile(Story_Line* plist, int* iCount)
{
    //打开文件
    FILE* pf;
    fopen_s(&pf, "classic_story_lines.dat", "wb");


    //打开文件失败
    if (pf == NULL)
    {
        printf("[SaveStoryLinesFile]-打开SaveStoryLines文件失败\n");
        return false;
    }

    fwrite(iCount, sizeof(int), 1, pf);
    fwrite(plist, sizeof(Story_Line), *iCount, pf);
    printf("[SaveStoryLinesFile]-保存了%d条SaveStoryLines信息\n", *iCount);

    //关闭文件
    fclose(pf);

    return true;
}

//读取存档
bool LoadSaveFile(Save *plist, int* iCount, const wchar_t* filePath)
{
    //打开文件
    FILE* pf;
    _wfopen_s(&pf, filePath, L"rb");
    //fopen_s(&pf, "classic_save.dat", "rb");

    //打开文件失败
    if (pf == NULL)
    {
        printf("[LoadSaveFile]-打开save文件失败\n");
        return false;
    }
    if (!fread(iCount, sizeof(int), 1, pf))
    {
        printf("[LoadSaveFile]-打开save文件成功，但是文件为空\n");
        *iCount = 0;
        fclose(pf);
        return true;
    }

    fread(plist, sizeof(Save), *iCount, pf);
    printf("[LoadSaveFile]-读取到%d条save文件信息\n", *iCount);

    //关闭文件
    fclose(pf);
    printf("[LoadSaveFile]-打开save文件成功\n");
    return true;
}
//写入存档
bool SaveSaveFile(Save *plist, int* iCount)
{
    //打开文件
    FILE* pf;
    fopen_s(&pf, "classic_save.dat", "wb");


    //打开文件失败
    if (pf == NULL)
    {
        printf("[SaveSaveFile]-打开save文件失败\n");
        return false;
    }

    fwrite(iCount, sizeof(int), 1, pf);
    fwrite(plist, sizeof(Save), *iCount, pf);
    printf("[SaveSaveFile]-保存了%d条save信息\n", *iCount);

    //关闭文件
    fclose(pf);

    return true;
}
