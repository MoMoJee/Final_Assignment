#include<stdio.h>
//使用读写文件函数fopen和fclose需要包含该头文件
#include <stdlib.h>
#include<time.h>

#include"functions.h"



void logger(LogLevel level, WhoLog who, const char* message)
{
    time_t now = time(NULL);
    struct tm tm_info;
    char time_str[64];
    char log_filename[28];//正好28个字符的嗷

    const char* level_strings[] = { "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL" };//这行定义了一个字符串数组 level_strings，它包含了四个字符串，分别对应 LogLevel 枚举中的四个日志级别。这个数组用于将枚举值映射到对应的字符串表示。
    const char* who_strings[] = { "Logger", "Main", "ConsoleCommand","GameMain","Saver","Skills_Props", "Creator"};//同上，因此如果要增加日志者，就要同时更改头文件的enum和这里的映射
   
    

    // 使用 localtime_s 函数获取本地时间
    errno_t err = localtime_s(&tm_info, &now);
    if (err) {
        perror("Failed to get local time");
        return;
    }

    strftime(time_str, sizeof(time_str), "%Y-%m-%d_%H-00-00", &tm_info);//每小时创建一个新的日志文件
    //构造带有时间的log名称
    snprintf(log_filename, sizeof(log_filename), "log-%s.log", time_str);// 格式化时间字符串

    FILE* log_file;
    fopen_s(&log_file, log_filename, "a"); //这行代码尝试以追加模式（"a"）打开一个名为log_filename 的文件，以便将日志消息添加到文件末尾。如果文件不存在，它将被创建。fopen 函数返回一个 FILE * 类型的指针，指向文件流。
    
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);//日志的时间戳和日志文件名的时间戳不应该是一个时间格式,这里更新一下time_str
    
    if (log_file == NULL) 
    {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, "[%s]-[%s]-[%s]-%s\n", level_strings[level], who_strings[who], time_str, message);
    fclose(log_file);
}


int main_logger_test() {//日志出错时运行

    //时间检查
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
    //日志创建
    logger(INFO, GameMain, "Hello World!");
    return 0;
}

