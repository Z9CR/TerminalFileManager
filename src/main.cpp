#include <string>
#include <iostream>
#include <filesystem>
#include "./head/thirdpartyLibs/tinydir.h"
#include "./head/commands.h"
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::endl;
int chosen = 0;
int main()
{
    set_raw_mode(true);
    while (true)
    {
        // 清空
        clear();
        // init
        tinydir_dir pwd;
        string current_path = getPWD();
        if (tinydir_open(&pwd, current_path.c_str()) != 0)// if panic
        {
            clear();
            cout << "[PANIC] Unable to open current dir";
            exit(1);
        }
        // 显示文件信息提示符
        printInfoPrompt(pwd);
        // 加载文件结构体至vector
        vector<tinydir_file> files;
        while (pwd.has_next)// 读入
        {
            tinydir_file file;
            tinydir_readfile(&pwd, &file);
            files.push_back(file);
            tinydir_next(&pwd);
        }
        /*//调试输出, 展开+取消注释
        cout << "共找到 " << files.size() << " 个文件：" << std::endl;
        
        for (const auto& file : files) {
            cout << "路径: " << file.path
                 << " 文件名: " << file.name
                 << " 是目录: " << (file.is_dir ? "是" : "否")
                 << std::endl;
        }
        *///关闭目录
        // 关闭dir释放资源
        tinydir_close(&pwd);
        // 打印文件列表
        printFileList(files, chosen);
        // 打印命令提示
        //开发中.................................................
        // 读取命令
        string cmd = getKeyInput();
        // if line.....
        if(cmd == "UP" || cmd == "k") 
            chosen = chosen - 1 >= 0 ? chosen - 1 : 0;
        else if (cmd == "DOWN" || cmd == "j" )
            chosen = chosen + 1 < files.size() ? chosen + 1 : files.size() - 1;
    }
    return 0;
}