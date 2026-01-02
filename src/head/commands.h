#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <vector>
using std::string;
using std::vector;

// 获取ls命令的返回值 *弃用
// vector<string> getLS();
/* 
获取用户输入，返回按键的字符串表示
 返回值示例: 
 - 单字符: "a", "1", "\n", " "
 - 方向键: "UP", "DOWN", "LEFT", "RIGHT"
 - 功能键: "ESC", "BACKSPACE", "DELETE", "HOME", "END", "PAGEUP", "PAGEDOWN"
 - 其他: "UNKNOWN"
*/
string getKeyInput();
// 获取pwd命令的返回值
string getPWD();
// 清空终端
void clear();
// 打印信息提示符
void printInfoPrompt(const tinydir_dir& pwd);
// 打印文件列表
void printFileList(const vector<tinydir_file>& files, int chosen);
// 设置原始终端模式
void set_raw_mode(bool enable);
#endif // COMMANDS_H