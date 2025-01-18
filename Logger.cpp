#include<stdio.h>
//ʹ�ö�д�ļ�����fopen��fclose��Ҫ������ͷ�ļ�
#include <stdlib.h>
#include<time.h>

#include"functions.h"



void logger(LogLevel level, WhoLog who, const char* message)
{
    time_t now = time(NULL);
    struct tm tm_info;
    char time_str[64];
    char log_filename[28];//����28���ַ����

    const char* level_strings[] = { "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL" };//���ж�����һ���ַ������� level_strings�����������ĸ��ַ������ֱ��Ӧ LogLevel ö���е��ĸ���־��������������ڽ�ö��ֵӳ�䵽��Ӧ���ַ�����ʾ��
    const char* who_strings[] = { "Logger", "Main", "ConsoleCommand","GameMain","Saver","Skills_Props", "Creator"};//ͬ�ϣ�������Ҫ������־�ߣ���Ҫͬʱ����ͷ�ļ���enum�������ӳ��
   
    

    // ʹ�� localtime_s ������ȡ����ʱ��
    errno_t err = localtime_s(&tm_info, &now);
    if (err) {
        perror("Failed to get local time");
        return;
    }

    strftime(time_str, sizeof(time_str), "%Y-%m-%d_%H-00-00", &tm_info);//ÿСʱ����һ���µ���־�ļ�
    //�������ʱ���log����
    snprintf(log_filename, sizeof(log_filename), "log-%s.log", time_str);// ��ʽ��ʱ���ַ���

    FILE* log_file;
    fopen_s(&log_file, log_filename, "a"); //���д��볢����׷��ģʽ��"a"����һ����Ϊlog_filename ���ļ����Ա㽫��־��Ϣ��ӵ��ļ�ĩβ������ļ������ڣ�������������fopen ��������һ�� FILE * ���͵�ָ�룬ָ���ļ�����
    
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);//��־��ʱ�������־�ļ�����ʱ�����Ӧ����һ��ʱ���ʽ,�������һ��time_str
    
    if (log_file == NULL) 
    {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, "[%s]-[%s]-[%s]-%s\n", level_strings[level], who_strings[who], time_str, message);
    fclose(log_file);
}


int main_logger_test() {//��־����ʱ����

    //ʱ����
    time_t now = time(NULL);
    struct tm tm_info;
    char time_str[64];

    if (localtime_s(&tm_info, &now) == 0) {
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);
        printf("Formatted time: %s\n", time_str);
    }
    else {
        printf("Failed to get local time\n");
    }
    //��־����
    logger(INFO, GameMain, "Hello World!");
    return 0;
}

