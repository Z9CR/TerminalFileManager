// commands.cpp
#include "../head/commands.h"

// 获取ls命令的返回值
vector<string> getLS()
{
    vector<string> lines;
    FILE *pipe = popen("ls -la", "r");
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