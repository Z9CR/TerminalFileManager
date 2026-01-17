#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <filesystem>
#include "./head/operations.h"
#include "./head/config.h"
#include "./head/thirdpartyLibs/tinydir.h"
#include "./head/commands.h"
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
namespace fs = std::filesystem;
int chosen = 0;
int chosenBtn = 0;
string origin_path;
string current_path;
tinydir_dir pwd;

void onExit(int sig)
{
    if (current_path == origin_path)
        exit(0);
    else
    {
        clear();
        cout << "请 cd " << current_path << endl;
        exit(0);
    }
}

int main()
{
    origin_path = getPWD();
    current_path = getPWD();
    config_init();
    set_raw_mode(true);
    signal(SIGINT, onExit);
    ///*
    while (true)
    {
        // 清空
        clear();
        // init
        if (tinydir_open(&pwd, current_path.c_str()) != 0) // if panic
        {
            clear();
            cout << "[PANIC] Unable to open current dir\n";
            exit(1);
        }
        // 显示文件信息提示符
        printInfoPrompt(pwd);
        // 加载文件结构体至vector
        vector<tinydir_file> files;
        while (pwd.has_next)
        {
            tinydir_file file;
            tinydir_readfile(&pwd, &file);
            //// 检查是否是 . 或 .. # 我不知道为什么会闪退, 所以现取消feature
            // if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
            //{
            //     tinydir_next(&pwd); // 跳过，继续下一个
            //     continue;           // 不加入数组
            // }
            files.push_back(file); // 加入数组
            tinydir_next(&pwd);
        }
        std::sort(files.begin(), files.end(),
                  [](const tinydir_file &a, const tinydir_file &b)
                  {
                      return strcasecmp(a.name, b.name) < 0; // 不区分大小写
                      // 或者用区分大小写：
                      // return strcmp(a.name, b.name) < 0;
                  });
        // 关闭dir释放资源
        tinydir_close(&pwd);
        // 打印文件列表
        printFileList(files, chosen);
        // 打印命令提示
        printCmdButton(chosenBtn);
        cout << std::endl;
        // 读取命令
        string cmd = getKeyInput();
        // if line.....
        if (cmd == "UP" || cmd == "k")
            chosen = chosen - 1 >= 0 ? chosen - 1 : 0;
        else if (cmd == "DOWN" || cmd == "j")
            chosen = chosen + 1 < files.size() ? chosen + 1 : files.size() - 1;
        else if (cmd == "LEFT" || cmd == "h")
            chosenBtn = chosenBtn - 1 >= 0 ? chosenBtn - 1 : 0;
        else if (cmd == "RIGHT" || cmd == "l")
            chosenBtn = chosenBtn + 1 < getAmountOfBtns() ? chosenBtn + 1 : getAmountOfBtns() - 1;
        else if (cmd == "SPACE" || cmd == "ENTER")
        { // 执行按钮
            tinydir_file current = files[chosen];
            bool bFile = !current.is_dir; // true -> 文件 false-> 文件夹
            switch (chosenBtn)            // 按钮逻辑
            {
            case 0: // open
            {
                if (bFile) // 文件
                {
                    openFileWithEditorCheck(current);
                }
                else // 文件夹
                {
                    current_path = current.path;
                    chosen = 0;
                }
                break;
            }
            case 1: // delete
            {
                cout << "删除 " << current.name << "?(y/N)> ";
                char i = 'n';
                i = getchar();
                // cout<<current_path << " " << current.name << " " << (string("rm -rf \'") + current_path + string(current.name) + string("\'")).c_str();
                // getchar();
                if (i == 'Y' || i == 'y')
                {
                    system((string("rm -rf \'") + current_path + '/' + string(current.name) + string("\'")).c_str());
                }
                break;
            }
            case 2: // prev
            {
                current_path = getPREV(current_path);
                chosen = 0;
                break;
            }
            case 3: // new
            {
                set_raw_mode(false);
                char i;
                cout << endl
                     << "文件 or 目录?(f/d)> ";
                cin >> i;
                getchar();
                if (i == 'f' || i == 'F')
                {
                    string filename;
                    cout << "\r\033[2K"; // 清除行
                    cout << "文件名称> ";
                    cin >> filename;
                    string filepath = current_path + '/' + filename;
                    // 文件存在, 阻止创建
                    if (fileExists(filepath))
                        cout << "目录/文件已经存在, 无法创建";
                    else
                    {
                        fstream newFile;
                        newFile.open(filepath.c_str(), std::ios::out);
                        newFile << "";
                    }
                }
                else if (i == 'd' || i == 'D')
                {
                    string dirname;
                    bool flag = false;
                    cout << "\r\033[2K"; // 清除行
                    cout << "目录名称> ";
                    std::getline(cin, dirname);
                    cout << endl;

                    // 存在性检测
                    fs::path newDir = current_path + "/" + dirname;
                    if (fs::create_directories(newDir))
                    {
                        std::cout << "目录创建成功: " << newDir << std::endl;
                    }
                    else
                    {
                        std::cout << "目录/文件已经存在, 无法创建" << std::endl;
                    }
                }
                else
                {
                    cout << "无效输入";
                    getchar();
                }
                set_raw_mode(true);
                break;
            }
            case 4: // rename
            {
                cout << "新名称:";
                set_raw_mode(false);
                string input;
                std::getline(cin, input);
                // cout<<input;
                try
                {
                    fs::rename(current.name, input);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    getKeyInput();
                }
                set_raw_mode(true);
                break;
            }
            case 5: // exit
            {
                if (current_path == origin_path)
                    return 0;
                else
                {
                    clear();
                    cout << "请 cd " << current_path << endl;
                    return 0;
                }
                break;
            }
            }
        }
        else if (cmd == ":") // 命令
        {
            string command = "";
            set_raw_mode(false);
            cout << ":";
            std::getline(cin, command);
            // debug: //cout << endl << endl << command;
            string out = tryCommand(command);
            set_raw_mode(true);
            cout << out;
            getKeyInput();
        }
    }
    //*/
    return 0;
}