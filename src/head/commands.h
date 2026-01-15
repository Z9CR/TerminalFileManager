#ifndef COMMANDS_H
#define COMMANDS_H
// the head file is used for screen works
// 本库用于处理终端显示
#include <string>
#include <vector>
using std::string;
using std::vector;

// 在终端中尝试某个命令, 并且返回命令输出
string tryCommand(string command);
// 补足前导0并转字符串
string intToStringWithZero(int number, int width);
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
// 获取上级目录
string getPREV(string current_path);
// 清空终端
void clear();
// 打印信息提示符
void printInfoPrompt(const tinydir_dir& pwd);
// 打印文件列表
void printFileList(const vector<tinydir_file>& files, int chosen);
// 设置原始终端模式
void set_raw_mode(bool enable);
// spec to YYYY:MM:DD - hh:mm
string timespecToYMDhm(const struct timespec& ts);
// 检测命令是否可执行
bool command_exists(const string& cmd);
// 打开文件
void openFileWithEditorCheck(const tinydir_file& file);
// 判断文件是否存在
bool fileExists(const std::string& filename);
// 判断文件夹是否存在
bool dirExists(const std::string& path);
#endif // COMMANDS_H