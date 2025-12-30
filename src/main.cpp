#include <string>
#include <iostream>
#include "./head/commands.h"
#include "./head/FileSystem.h"
using std::cout;
using std::cin;

int main() {
    char cmd = ' ';
    auto lines = getLS();
    for(auto line : lines) {
        cout<<line<<'\n';
    }
    // test code, getLS() works

    /*
    while(true) {
        switch(cmd)
            case '':
            
            break;
            
    }
    */
    return 0;
}