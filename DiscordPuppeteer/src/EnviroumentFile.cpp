#include "EnviroumentFile.h"
#include <fstream>
#include <string>

EnviroumentFile::EnviroumentFile() noexcept {
    openFile();
}

void EnviroumentFile::openFile() noexcept {
    constexpr auto filename = ".env";

    mArguments.clear();

    std::ifstream fin;
    fin.open(filename);

    if (!fin.is_open()) {
        printf("%s(): file \"%s\" doesn't exist\n", __FUNCTION__, filename);
        return;
    }

    std::string line;
    size_t equalIndex = 0;
    size_t lineIndex = 0;

    while (!fin.eof()) {
        std::getline(fin, line);
        lineIndex++;

        if (line.empty()) continue;

        equalIndex = line.find('=');

        if (equalIndex == -1) {
            printf("%s(): no equal sign in %zu\n", __FUNCTION__, lineIndex);
            continue;
        }

        mArguments.insert(std::make_pair(line.substr(0, equalIndex), line.substr(equalIndex + 1)));
    }

    fin.close();
}

const std::string& EnviroumentFile::operator[](const std::string& name) const {
    return mArguments.at(name);
}
