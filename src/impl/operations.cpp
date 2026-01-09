#include "../head/operations.h"
#include "../head/thirdpartyLibs/tinydir.h"
#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::vector;

static vector<string> btns = {
    "[Open]",
    "[Del ]"
    // 以下添加按钮
};

int getAmountOfBtns() {
    return btns.size();
}

void eval(int chosenBtn, const tinydir_file& current) {
    bool bFile = !current.is_dir;// true -> 文件
                              // false-> 文件夹

    switch (chosenBtn) {
    case 0:// open
    if (bFile) {// 文件
        system((string("nvim ") + string(current.name)).c_str());
    }
    else {// 文件夹
        
    }
    break;
    
    }  
}

void printCmdButton(int chosenBtn) {
    string output = "";
    
    for(int i = 0;i < btns.size();i++) {
        if(i == chosenBtn) {
            // 如果是被选中的, 添加样式
            output += "\033[37;45m" + btns.at(i) + "\033[0m  ";
        }
        else {
            output += btns.at(i) + "  ";
        }
    }
    cout << output;
}