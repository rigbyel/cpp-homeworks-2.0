#include <string>

using namespace std;

class manager
{
public:
    int n_buckets;

    manager(int num_bucks);
    void hashAll(string dir, string prefix);
    int hash(string mame);
    void writeToStorage(string hash, string path, string size);
    string search(string filename, int minSize, int maxSize);
};

