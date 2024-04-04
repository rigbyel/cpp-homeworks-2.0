#include <iostream>
#include <fstream>
#include "manager.h"
#include <stat.h>
#include <dirent.h>
#include <conio.h>

using namespace std;


manager::manager(int num_bucks) {
    n_buckets = num_bucks;
}

int manager::hash(string name) {
    int hashSum = 0;

    for (int i = 0; i < name.length(); i++) {
        hashSum += int(name[i]);
    }

    return hashSum % n_buckets;
}

void manager::hashAll(string dir, string prefix) {
    struct dirent *d;
	struct stat dst;
	
	DIR *dr;
	
	string path = ".\\";
	
	dr = opendir(path.c_str());
	
	if (dr != NULL)
	{
		for (d = readdir(dr); d != NULL; d = readdir(dr))
		{
			string type = d->d_name;
			type = path + type;
			if (stat(type.c_str(), &dst) == 0)
			{
				if (dst.st_mode & S_IFDIR)
				{
					type = "is a FOLDER.";
				}
				else if (dst.st_mode & S_IFREG)
				{
					type = "is a FILE.";
				}
			}
			cout<<d->d_name<<endl<<type<<endl;
		}
		closedir(dr);
	}
	else
	{
		cout<<"ERROR"<<endl;
	}
	getch();

}

void manager::writeToStorage(string hash, string path, string size) {
    string bucketPath = "../storage/bucket_" + hash + ".csv";

    std::ofstream bucket;
    bucket.open(bucketPath);

    bucket << path + "," + size + "\n";

    bucket.close();
}