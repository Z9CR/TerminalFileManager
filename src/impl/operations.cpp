#include "../head/operations.h"
#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::vector;

vector<string> btns = {
    "[Open]",
    "[Del ]"
    // 以下添加按钮
};

int getAmountOfBtns() {
    return btns.size();
}

void eval(int chosenBtn) {
    
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