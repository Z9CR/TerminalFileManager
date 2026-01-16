#include "../head/operations.h"
#include "../head/config.h"
#include "../head/thirdpartyLibs/tinydir.h"
#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::vector;

static vector<string> btns = {
    "[Open]",// 0
    "[Del ]",// 1
    "[Prev]",// 2
    "[New ]",// 3
    "\n[Exit]"// 4
    // 以下添加按钮
};

int getAmountOfBtns() {
    return btns.size();
}

void printCmdButton(int chosenBtn) {
    string output = "";
    
    for(int i = 0;i < btns.size();i++) {
        if(i == chosenBtn) {
            // 如果是被选中的, 添加样式
            output +=  config_get("chosenButtonColor") + btns.at(i) + "\033[0m  ";
        }
        else {
            output += btns.at(i) + "  ";
        }
    }
    cout << output;
}