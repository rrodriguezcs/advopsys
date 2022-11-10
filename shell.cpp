#include <iostream>
#include "shell.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "sdisk.h"
#include "filesys.h"

using namespace std;

class Shell: public filesys
{
    public:
        Shell(string filename, int numberofblocks, int blocksize);
        int dir();
        int add(string file);
        int del(string file);
        int type(string file);
        int copy(string file1, string file2);
};

Shell::Shell(string diskname, int numberofblocks, int blocksize):
Filesys(diskname, numberofblocks, blocksize)
{

}

int Shell::dir()
{
    vector<string> flist = ls();
    for (int i=0; i < flist.size(); i++)
    {
        cout << flist[i] << endl;
    }
}