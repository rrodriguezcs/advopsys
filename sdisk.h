#ifndef SDISK_H
#define SDISK_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Sdisk
{
    public:
        Sdisk(string diskname, int numberofblocks, int blocksize); 
        int getblock(int blocknumber, string& buffer);  
        int putblock(int blocknumber, string buffer);   
        int getnumberofblocks(); 
        int getblocksize(); 

    protected:
        string diskname;
        int numberofblocks;
        int blocksize;

};
#endif