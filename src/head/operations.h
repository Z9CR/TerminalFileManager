#ifndef _OPERATIONS_H
#define _OPERATIONS_H
#include "../head/thirdpartyLibs/tinydir.h"
// the lib is used to deal with
// file-IO operations in the program
// 本库用于处理终端中的文件IO

void printCmdButton(int chosenBtn);

int getAmountOfBtns();

void eval(int chosenBtn, const tinydir_file& File);

#endif