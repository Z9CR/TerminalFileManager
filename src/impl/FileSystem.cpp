// FileSystem.cpp
#include "../head/FileSystem.h"
#include <sstream>

// File 构造函数
File::File(const std::string& name,
           const std::string& parentPath,
           FileType type,
           Permission permission)
    : modifiedTime(std::time(nullptr)),
      permission(permission),
      parentPath(parentPath),
      name(name),
      type(type) {}

// Dir 构造函数  
Dir::Dir(const std::string& name,
         const std::string& parentPath,
         bool isLink,
         Permission permission)
    : modifiedTime(std::time(nullptr)),
      permission(permission),
      parentPath(parentPath),
      name(name),
      bLink(isLink) {}