#include "sdisk.h"

using namespace std;


Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{   
    this -> diskname = diskname;
    this -> numberofblocks = numberofblocks;
    this -> blocksize = blocksize;

    fstream disk;
    disk.open(this -> diskname.c_str(), ios::in);

    if(disk.fail()) 
    {
        disk.open(this -> diskname.c_str(), ios::out); 

        if(disk.fail())
        {
            return; 
        }
        else
        {  
            for(int i = 0; i < this -> numberofblocks * this -> blocksize; i++) 
            {
                disk.put('#'); 
            }   
        }
        
    }
    disk.close();
}

int Sdisk::putblock(int blocknumber, string buffer)
{
        fstream iofile(this -> diskname.c_str(), ios::in | ios::out); 
        
        if(iofile.fail())
        {
            return 0;  
        }

        if(blocknumber < 0 || blocknumber >= numberofblocks)
        {
            cout << "Block does not exist" << endl;
            return 0;
        }

        iofile.seekp(this -> blocksize * blocknumber);

        for(int i=0; i < buffer.length() && i < this -> blocksize; i++)
        {
            iofile.put(buffer[i]);
        }

        iofile.close();

        return 1;
}

int Sdisk::getblock(int blocknumber, string& buffer)
{
    fstream iofile;
    iofile.open(this -> diskname.c_str(), ios::in); 

    if(blocknumber < 0 || blocknumber >= numberofblocks)
    {
        cout << "Block does not exist" << endl; 
        return 0;
    }

    iofile.seekg(blocknumber * this -> blocksize);
    buffer.clear();
    char c;

    for(int i = 0; i < this -> blocksize; i++)
    {
        iofile.get(c);
        buffer.push_back(c); 
    }

    iofile.close();

    return 1;
}

int Sdisk::getnumberofblocks()
{
    return this -> numberofblocks; 
}

int Sdisk::getblocksize()
{
    return this -> blocksize; 
}