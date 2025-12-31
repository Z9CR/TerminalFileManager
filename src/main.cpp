#include <string>
#include <iostream>
#include "./head/commands.h"
#include "./head/FileSystem.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;
char cmd = ' ';
string pwd = "/";

int main() {
    set_raw_mode(true);
    while(true) {
        clear();
        // init
        pwd = getPWD();
        cout << "\033[30;44mPath: " + pwd + "\033[0m"<< '\n';
        
        cmd = getchar();
        switch(cmd){
            // an case for example, I'll complete it
            case '1':
                cout<<111;
            break;
        }
    }
    return 0;
}