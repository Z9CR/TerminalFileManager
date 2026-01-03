// simple_config.h
#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <map>
using std::string;

// 初始化配置（程序启动时调用一次）
void config_init();

// 读取配置
string config_get(const string &key);
bool config_get_bool(const string &key);
int config_get_int(const string &key);

// 修改配置（自动保存）
void config_set(const string &key, const string &value);
// 查验文件是否存在
bool file_exists(const std::string& filename);
#endif