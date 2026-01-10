#include <string>
#include <iostream>
#include <filesystem>
#include "./head/operations.h"
#include "./head/config.h"
#include "./head/thirdpartyLibs/tinydir.h"
#include "./head/commands.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
int chosen = 0;
int chosenBtn = 0;
string current_path;
tinydir_dir pwd;
int main()
{
    current_path = getPWD();
    config_init();
    set_raw_mode(true);
    ///*
    while (true)
    {
        // 清空
        clear();
        // init
        if (tinydir_open(&pwd, current_path.c_str()) != 0) // if panic
        {
            clear();
            cout << "[PANIC] Unable to open current dir";
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

            // 检查是否是 . 或 ..
            if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
            {
                tinydir_next(&pwd); // 跳过，继续下一个
                continue;           // 不加入数组
            }

            files.push_back(file); // 加入数组
            tinydir_next(&pwd);
        }
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
            switch (chosenBtn)
            {
            case 0: // open
                if (bFile)
                { // 文件
                    system((string("nvim ") + string(current.name)).c_str());
                }
                else
                { // 文件夹
                    current_path = current.path;
                    chosen = 0;
                }
                break;
            }
        }
    }
    //*/
    return 0;
}