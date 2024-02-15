#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct Config {
    int pivot;
    string filePath;
};

Config makeConfig(int argc, char* argv[]) {
    Config cfg;

    cfg.pivot = 2;
    cfg.filePath = "0";

    if (argc > 1) {
        if (atoi(argv[1]) != 0) {
            cfg.pivot = atoi(argv[1]);
        } else {
            cfg.filePath = argv[1];
            return cfg;
        }
    }

    if (argc > 2) {
        cfg.filePath = argv[2];
    }

    return cfg;
}

string getUserText(string filePath) {
    std::string line;
 
    std::ifstream in(filePath);
    string text;
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            text += line;
            text += "\n";
        }
    } else {
        while (true)
        {   
            string line;
            getline(cin, line);
            
            if (line == ":q") {
                break;
            }

            text += line;
            text += "\n";
        }
    }
    in.close(); 

    return text;
}

string encryptCaesar(string& text, int pivot) {
    const int lastCode = 'z';
    const int firstCode = '0';
    const int alphabetLen = lastCode - firstCode;

    string encrText;

    pivot = pivot % alphabetLen;

    for (int i = 0; i < text.size(); i++)
    {
        int code = text[i];
        if (code > 'z' || code < '0') {
            encrText += text[i];
            continue;
        }

        int newCode = code + pivot;
        
        if (newCode > lastCode) {
            newCode = newCode % lastCode + firstCode - 1;
        }

        if (newCode < firstCode) {
            newCode = lastCode - (firstCode - newCode) + 1;
        }

        encrText += char(newCode);
    }
    
    return encrText;
}

int main(int argc, char* argv[]) {
    Config cfg = makeConfig(argc, argv);
    
    string text = getUserText(cfg.filePath);
    string encrText = encryptCaesar(text, cfg.pivot);

    cout << encrText;
}
