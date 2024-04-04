#include <iostream>
#include <map>
#include <string>
#include <set>
#include "manager.h"
#include "filter.h"

/*
filter makeFilter(int argc, char* argv[]) {
    filter f;
    f.size = 0;
    f.minSize = 0;
    f.maxSize = 0;

    set<string> flags{"--size", "--minSize", "--maxSize"};

    for (int i = 0; i < argc; ) {
        if (flags.find(argv[i]) != flags.end()){
            string flag = str(argv[i]);
            switch (flag)
            {
            case "--size":
                f.size = stoi(argv[i+1]);
            case "--minSize":
                f.minSize = stoi(argv[i+1]);
            case "--maxSize":
                f.maxSize = stoi(argv[i+1]);
            }
            i++;
        }
        i++;
    }

    return f;
} */

int main(int argc, char* argv[]) {

    filter f;
    f.size = 0;
    f.minSize = 0;
    f.maxSize = 0;

    manager m1 = manager(5);

    m1.hashAll(".", "");

    std::cout << "Ищем все файлы с названием fileX.txt" << std::endl;
    vector<string> result = m1.search("fileX.txt", f);

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << "\n";
    }

}