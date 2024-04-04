#include <iostream>
#include <fstream>
#include "manager.h"
#include "filter.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>

#include <sstream>

using namespace std;


manager::manager(int num_bucks) {
    n_buckets = num_bucks;

    for (int i = 0; i < num_bucks; i++) {
        ofstream {"./storage/bucket_" + to_string(i) + ".csv"};
    }
}

int manager::hash(string name) {
    int hashSum = 0;

    for (int i = 0; i < name.length(); i++) {
        hashSum += int(name[i]);
    }

    return hashSum % n_buckets;
}

void manager::hashAll(string dir, string prefix) {
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    dp = opendir(dir.c_str());
    if (dp != nullptr) {
        while ((entry = readdir(dp)))
            if (entry->d_type == DT_DIR) {
                std::string name = entry->d_name;
                if (name !="." && name != "..") {
                    hashAll(entry->d_name, dir+"/");
                }
            } else {
                string fileHash = to_string(hash(entry->d_name));
                int size = entry->d_reclen;
                writeToStorage(fileHash, entry->d_name, prefix+dir+"/"+entry->d_name, to_string(size));
            }
    } 

    closedir(dp);
}

void manager::writeToStorage(string hash, string name, string path, string size) {
    string bucketPath = "storage/bucket_" + hash + ".csv";

    ofstream bucket;
    bucket.open(bucketPath, std::ios::out | std::ios::app);

    bucket << name + "," + path + "," + size + "\n";

    bucket.close();
}


vector<string> manager::search(string filename, filter filt){
    vector<string> result;
    int fileHash = hash(filename);

    string bucketPath = "storage/bucket_" + to_string(fileHash) + ".csv";

    vector<string> row;
    string line, word;

    fstream file (bucketPath, ios::in);
    
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
 
            stringstream str(line);
 
            while(getline(str, word, ','))
                row.push_back(word);
            
            if (row.size() > 1 && row[0] == filename) {
                if (filt.size != 0 && stoi(row[2]) == filt.size) {
                    result.push_back(row[1]);
                }
                if (filt.maxSize != 0 && stoi(row[2]) <= filt.maxSize && stoi(row[2]) >= filt.minSize) {
                    result.push_back(row[1]);
                }

                if (filt.minSize != 0 && stoi(row[2]) >= filt.minSize) {
                    result.push_back(row[1]);
                }

                if (filt.maxSize  == 0 && filt.size == 0 && filt.minSize == 0) {
                    result.push_back(row[1]);
                }
            }
        }
    }
    else{
        cout<<"Could not open the file\n";
    }

    return result;
}
