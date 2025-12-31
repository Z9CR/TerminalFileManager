#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <vector>
using std::string;
using std::vector;

// 获取ls命令的返回值
vector<string> getLS();
// 获取pwd命令的返回值
string getPWD();
// 清空终端
void clear();
// 设置原始终端模式
void set_raw_mode(bool enable);
#endif // COMMANDS_H