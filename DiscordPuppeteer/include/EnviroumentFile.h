#pragma once
#include <unordered_map>
#include <string>

class EnviroumentFile {
public:
    EnviroumentFile() noexcept;
    void openFile() noexcept;

    const std::string& operator[] (const std::string& name) const;

private:
    std::unordered_map<std::string, std::string> mArguments;
};

