// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_LINE_LENGTH 1000
#define MAX_SKILLS 2000

#define MAX_STORY_LINES 100//һ�����������ô���

#define MAX_BUTTONS 2000//�˵������������˵�����


void displayLoadingBar(int duration);
enum LogLevel
{
    DEBUG,
    INFO,
    WARN,
    Error,//ɵ��VS�������Error����д��ERROR�͸��Ҳ�����
    CRITICAL
};
typedef enum LogLevel LogLevel;
//enum���ͣ���ֵ��ʱ��ֻ�ܸ����Ѿ������˵ļ����ؼ��֣������ã�����print����ʱ�򷵻�����ؼ����ڶ���ʱ���˳��ţ�������0-4��

typedef enum
{
    Logger,
    Main,
    ConsoleCommand,
    GameMain,
    Saver,
    Skills_Props,
    Creator
} WhoLog;
//typedef�����Լ�д���������

extern int last_f;//ȫ�֣�ָʾ��һ�ε��õĹ��ܣ�����ʵ����Ҫ����������õĺ�����


void logger(LogLevel level, WhoLog who, const char* message);

int Console_Command(
    const char* f_message,
    int state,//0ָʾmain����
    int special_int = 0,
    int special_int_arr_0[] = { 0 },
    int special_int_arr_1[] = { 0 },
    char special_char_0[] = { '\0' },
    char special_char_1[] = { '\0' }
);
int AnalyseCC(const char* f_message);
void clearInputBuffer();
int menu(int num_buttons, const char* title, int index[MAX_BUTTONS], const char* buttons[MAX_BUTTONS], const char* introduction[MAX_BUTTONS], int mode = 0);//mode = 1���ǲ���ʾ������mode = 2������ʾ�����������mode = 0����ʹ��Ĭ���������ز�����ʾ
extern bool develop_mode;


struct role_stats
{
    char Name[101];
    int ATK;
    int HP;
    float DEF;
    int Money;
    int SKILL[2];
    int PROPS[100][2];
    //����;
    //Ѫ��;
    //����;//����=0.9�����Է��Ĺ�������ԭ����
    //��Ǯ;
    //���⼼��;//���⼼����һ�������룬��Ӧ��txt
    //����;
};
typedef struct role_stats role_stats;
extern role_stats PLAYER;//���
extern role_stats OPPONENT;//��


struct SKILL_PROPS//���ܽṹ��
{
    char prompt[101];
    int state;
    int object;
    float Operate_ATK;
    int Operate_HP;
    float Operate_DEF;
    int Operate_Money;
    int Fight_Times;//ָʾս�����Ǽ����غ���Ч���ǶԾ���Ч��1��һ�غϣ�2�������غϣ�0�������Ծ�
    int Price;
    char Introduction[201];
    //���ܷ���ʱ����ʾ��;//���硱��ʹ�ü���XXX���Է�Ѫ������20��
    //��ʹ�õĳ���;//ָʾ��ս���С���ս���ڡ�ȫ������������״̬���ͱ����㲻���ڷ�ս�������ʹ��
    //���Լ����ǶԶԷ�;
    //�Թ����Ĳ���;//���ǰٷֱȣ�1.2�������ӵ�120%
    //��Ѫ���Ĳ���;//����Ѫ������
    //�Է����Ĳ���;
    //�Խ�Ǯ�Ĳ���;
};
typedef struct SKILL_PROPS SKILL_PROPS;

extern SKILL_PROPS SKILL_PROPS_LIST[];//�洢���еļ��ܣ����ļ�д�룩

extern int skill_count; // ��������



int ReadSkillsPropsFile(const wchar_t* filename, struct SKILL_PROPS* skills, int maxSkills);

bool LoadSkillsPropsFile(SKILL_PROPS* pDishes, int* iCount);

bool SaveSkillsPropsFile(SKILL_PROPS* plist, int* iCount);



void setTextColorRGB(int r, int g, int b);
float progress_bar();
void displayHealthBar(int maxHealth, int currentHealth, const char* characterName, int align);
bool isPositiveInt(const char* str, int* result);
int AnalyseSP(const char* SPmessage);

int fight(int * last_time_HP = nullptr);


role_stats* Using_Skill_Props(bool* new_n_Round_Effect_Happpen, SKILL_PROPS* n_Round_Effect_SK, int * n_Round_Effect, int Skill_Prop_code, int state, role_stats Skill_PropsTempPlayerStatus, role_stats Skill_PropsTempOpponentStatus = { {} });
role_stats StatsAlterChecker(role_stats unCheckedStats);
int Using_Skill_Props_Checker(int Skill_Prop_code, int state);
int findPropIndex(int target);
void cleanAndOrganizeProps();
void displayProps();

//����ṹ�壬һ���ؿ�һ��
typedef struct
{
    char Name[101];
    char Introduction[401];
    role_stats Opponent_Stats;
    SKILL_PROPS Win_Consequence;
    SKILL_PROPS Lose_Consequence;//���ֱ�Ӷ����ڴ浵�ļ������֮�����USP����ֱ�Ӷ���Ҳ�������������100���
    int Win_Award_Code;//�����д��SKILL_PROPS_LIST����ģ�ֻ��ͨ��ս����õļ���/����
    int Repeatable;//ָʾ����ؿ��ܲ����ظ��棬����ĳЩ�������ֻ�ܻ��һ�Σ������ó�ֻ����һ�Ρ�0ָʾ�����ظ���1ָʾֻ����һ��
    //������жϷ�ʽ�ǣ������Ҵ浵��ؿ���ǰλ���룬�����������ṹ���ڶ����Serial_Num���Ͳ�����
    //������ͨ�غ��޸Ĵ浵�еĹؿ�λ����Ϊ0�����ɶ��档

}Story_Line;


typedef struct
{
    role_stats Player_Stats;
    int Story_Line_Coordinates[100];//ָʾ�����ÿ�������еĹؿ����꣬���֧��100������

}Save;

extern Save PLAYER_SAVE;
extern int save_count;

#include <wchar.h>
#include <locale.h>



bool LoadSaveFile(Save* plist, int* iCount, const wchar_t* filePath);
bool SaveSaveFile(Save *plist, int* iCount);

extern Story_Line STORY_LINES[];//������
extern int story_count; // ��ǰ��������




int Skills_Props_Creater_Main();//�������ܵĺ���
int Skills_Props_Creater_Console_Command(const char* message, bool* Exit_SPC);
int AnalyseSPCCC(const char* f_message);
int displayBrief();// ������ʾ���ܺ���
// ��ϸ��ʾ����
void displayDetail(int index);
// ɾ�����Ǻ���
void deleteSkill(int index);
// ���ܲ鿴���������ƺ���
void ShowSKPRmainControl();
void createSkill();




void deleteStoryLine();
void displayDetailedStoryLine();
void displayBriefStoryLines();
void createStoryLine();
void storyLineControl();
bool LoadStoryLinesFile(Story_Line* plist, int* iCount);
bool SaveStoryLinesFile(Story_Line* plist, int* iCount);
int StoryLineModeControl();
extern int STORY_LINE_CODE;//ָʾ���ǵڼ��׾��飬Ĭ��0



void displayPlayerStats();

void shopping();//�̵�

int train();
role_stats generate_monster_stats(int difficulty);
int calculate_reward_gold(struct role_stats monster, int difficulty);
char* generate_monster_name();
SKILL_PROPS calculate_reward_stats(role_stats monster);// ������������


int endless_mode_control();

int Choose_My_Skill();

int upgrade();

#endif // FUNCTIONS_H

/*
#ifndef FUNCTIONS_H������һ��Ԥ����ָ����ڼ���Ƿ��Ѿ�������FUNCTIONS_H�ꡣ���û�ж��壬��ô������������ִ������Ĵ��롣�����ͨ��������ֹͷ�ļ����ظ�����������һ�ֳ����ı��ʵ������Ϊ��������ʿ����ͷ�ļ���ʿ����
#define FUNCTIONS_H�����ָ�����FUNCTIONS_H�ꡣ���������ͷ�ļ����ٴΰ�����Ԥ���������鵽FUNCTIONS_H�Ѿ������壬���������ļ������ಿ�֣���ֹ�ظ�������
#endif // FUNCTIONS_H�����ָ������#ifndef��Ľ��������FUNCTIONS_H���Ѿ������壬Ԥ������������#ifndef��#endif֮������д��롣
*/