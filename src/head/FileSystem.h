#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <ctime>

// 文件类型枚举
enum class FileType {
    APP,   // 应用程序
    SH,    // shell脚本
    PROP,  // 配置文件  
    FILE   // 未知类型文件
};

// 权限枚举
enum class Permission {
    READ_ONLY,      // 只读
    READ_WRITE,     // 读写
    EXECUTABLE,     // 可执行
    FULL_CONTROL    // 完全控制
};

// 文件结构体
struct File {
    std::time_t modifiedTime;     // 修改时间
    Permission permission;        // 权限
    std::string parentPath;       // 父路径
    std::string name;             // 文件名
    FileType type;                // 文件类型
    
    // 构造函数
    File(const std::string& name = "",
         const std::string& parentPath = "",
         FileType type = FileType::FILE,
         Permission permission = Permission::READ_WRITE);
};

// 目录结构体
struct Dir {
    std::time_t modifiedTime;     // 修改时间
    Permission permission;        // 权限
    std::string parentPath;       // 父路径
    std::string name;             // 目录名
    bool bLink;                   // 是否为链接目录
    
    // 构造函数
    Dir(const std::string& name = "",
        const std::string& parentPath = "",
        bool isLink = false,
        Permission permission = Permission::READ_WRITE);
};

#endif // FILESYSTEM_H