// commands.cpp
#include "../head/thirdpartyLibs/tinydir.h"
#include "../head/commands.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>
using std::cin;
using std::cout;
/*// 获取ls命令的返回值(无用)
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
            line.pop_back(); // 去除endl
        lines.push_back(line);
    }

    pclose(pipe); // release FILE*
    return lines;
} */
// 打印文件列表并为chosen项(index 0)添加被选中样式
void printFileList(const vector<tinydir_file>& files, int chosen) {
    int left = chosen - 4 >= 0 ? chosen - 4 : 0;// 不可越左边界
    int right = chosen + 5 <= files.size() - 1 ? chosen + 5 : files.size() - 1;// 不可越右边界
    //上限显示10个
    for(int i = left;i <= right;i++) {
        tinydir_file file = files.at(i);
        string output = "";
        // type项
        if(file.is_dir == 1) output += "[DIR ]";
        else output += "[FILE]";
        // 最后为被选中项添加样式并换行
        if (i == chosen) output = "\033[1;30;45m" + output + "\033[0m\n";
        else output = output + "\n";
        cout << output;
    }
} 
/* 
获取用户输入，返回按键的字符串表示
 返回值示例: 
 - 单字符: "a", "1", "\n", " "
 - 方向键: "UP", "DOWN", "LEFT", "RIGHT"
 - 功能键: "ESC", "BACKSPACE", "DELETE", "HOME", "END", "PAGEUP", "PAGEDOWN"
 - 其他: "UNKNOWN"
*/
string getKeyInput() {
    char first;
    
    // 确保读取到字符
    while (read(STDIN_FILENO, &first, 1) != 1) {
        usleep(1000);  // 短暂等待
    }
    
    // 普通字符
    if (first != 27) {
        if (first == '\n') return "ENTER";
        if (first == ' ') return "SPACE";
        if (first == 127) return "BACKSPACE";
        if (first >= 32 && first <= 126) return std::string(1, first);
        return "UNKNOWN";
    }
    
    // 检查是否是方向键
    char seq[2];
    int n = read(STDIN_FILENO, seq, 2);
    
    if (n == 2 && seq[0] == '[') {
        switch (seq[1]) {
            case 'A': return "UP";
            case 'B': return "DOWN";
            case 'C': return "RIGHT";
            case 'D': return "LEFT";
            case 'H': return "HOME";
            case 'F': return "END";
        }
    }
    
    // 单独的 ESC 或其他 ESC 序列
    return "ESC";
}
// 获取pwd命令的返回值
string getPWD()
{
    char buf[4096];
    FILE *pipe = popen("pwd", "r");
    if (!pipe)
    {
        printf("[PANIC] unable to open");
        exit(1);
    }
    else
    {
        fgets(buf, sizeof(buf), pipe);
    }
    pclose(pipe);
    // 去除末尾的换行符
    std::string result(buf);

    // 检查并删除末尾的 \n 和 \r
    while (
        !result.empty() &&
        (result.back() == '\n' || result.back() == '\r' || result.back() == ' '))
    {
        result.pop_back();
    }

    return result;
}
// 打印信息提示符
void printInfoPrompt(const tinydir_dir& pwd)
{
    // 打印蓝底黑字路径
    cout << "\033[30;44mPath: " + string(pwd.path) + "\033[0m\n";
    // 类型提示符
    cout << "[\033[4;1;35mT\033[0m\033[1;35mype\033[0m]" << "  ";
    // 类型 [Type] or [Dir ], 6chars
    cout << "[\033[4;1;35mS\033[0m\033[1;35mize\033[0m]" << "   ";
    // 大小 xxxxxxM, 7chars
    cout << "[\033[4;1;35mD\033[0m\033[1;35mate\033[0m]" << "    ";
    // 日期 yyyy:mm:dd, 10chars
    cout << "[\033[4;1;35mN\033[0m\033[1;35mame\033[0m]" << '\n';
    // 名称 asgsaghbasytgfuyhsygysda, unk chars
}
// 设置原始终端模式
void set_raw_mode(bool bEnable)
{
    static struct termios oldt, newt;

    if (bEnable)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}
// 清屏
void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}