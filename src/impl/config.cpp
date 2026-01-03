#include "../head/config.h"
#include <fstream>
#include <sys/stat.h>
#include <iostream>
using std::ifstream;
using std::map;
using std::ofstream;
using std::cout;
using std::string;

static map<string, string> settings;
static string config_path;

void config_init()
{
    string home = getenv("HOME");
    if (home.empty())
        home = ".";
    config_path = home + "/.config/TerminalFileManager/prop.cfg";
    if(!file_exists(config_path)) {// 如果配置文件不存在
        ofstream properties;
        properties.open(config_path);
        // 写入默认配置
        properties << "aboveLines=3\n";
        properties << "belowLines=3\n";
        // 关闭+释放资源
        properties.close();
    }
    // 加载文件
    ifstream file(config_path);
    if (!file)
    {
        system(("mkdir -p " + config_path.substr(0, config_path.find_last_of('/'))).c_str());
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.find('=') != string::npos)
        {
            size_t pos = line.find('=');
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            settings[key] = value;
        }
    }
}

string config_get(const string &key)
{
    auto it = settings.find(key);
    return it != settings.end() ? it->second : "";
}

bool config_get_bool(const std::string &key)
{
    string val = config_get(key);
    return val == "true" || val == "1";
}

int config_get_int(const std::string &key)
{
    string val = config_get(key);
    return val.empty() ? 0 : std::stoi(val);
}

void config_set(const string &key, const string &value)
{
    settings[key] = value;

    // 保存到文件
    ofstream file(config_path);
    if (!file)
        return;
    for (const auto &[k, v] : settings)
    {
        file << k << "=" << v << "\n";
    }
}
// 用于判断文件是否存在
bool file_exists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}