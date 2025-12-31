// commands.cpp
#include "../head/commands.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

// 获取ls命令的返回值
vector<string> getLS() {
    vector<string> lines;
    FILE* pipe = popen("ls -la", "r");
    if (!pipe)
    {
        printf("[PANIC] unable to open");
        exit(1);
    }
    char buf[4096];
    while (fgets(buf, sizeof(buf), pipe) != nullptr)
    {
        string line = buf;
        if (!line.empty() && line.back() == '\n')
            line.pop_back();    //去除endl
        lines.push_back(line);
    }

    pclose(pipe); //release FILE*
    return lines;
}

// 获取pwd命令的返回值
string getPWD() {
    char buf[4096];
    FILE* pipe = popen("pwd", "r");
    if(!pipe) {
        printf("[PANIC] unable to open");
        exit(1);
    }
    else {
        fgets(buf, sizeof(buf), pipe);
    }
    pclose(pipe);
    return string(buf);
}

// 设置原始终端模式
void set_raw_mode(bool bEnable) {
    static struct termios oldt, newt;
    
    if (bEnable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}