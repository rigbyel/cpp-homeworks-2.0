#ifndef MANAGER
#define MANAGER

#include <string>
#include <vector>
#include "filter.h"

using namespace std;

class manager
{
public:
    int n_buckets;

    manager(int num_bucks);
    void hashAll(string dir, string prefix);
    int hash(string mame);
    void writeToStorage(string hash, string name, string path, string size);
    vector<string> search(string filename, filter filt);
};

#endif
