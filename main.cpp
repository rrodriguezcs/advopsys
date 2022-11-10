#include <iostream>
#include <fstream>
#include <string>
#include "filesys.h"
#include "sdisk.h"

using namespace std;


class Sdisk
{
public :
Sdisk(string diskname);
Sdisk(string diskname, int numberofblocks, int blocksize);
int getblock(int blocknumber, string& buffer);
int putblock(int blocknumber, string buffer);
private :
string diskname;        // file name of software-disk
int numberofblocks;     // number of blocks on disk
int blocksize;          // block size in bytes
};

Sdisk::Sdisk(string diskname)
{
}

//Sdisk
Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
	
}

//getblock
int Sdisk::getblock(int blocknumber, string& buffer)
{

}

//putblock
int Sdisk::putblock(int blocknumber, string buffer)
{
    iofile.open(diskname.c.str(), ios::in|io::out);
    iofile.seekp(blocksize + blocknumber);
        buffersize()
    for (i=0; i<blocksize; i++)
        iofile.put(buffer[i]);
    if (blocknumber < 0 or blocknumber >= numberofblocks)
        {
            cout << "Block doesn't exist";
            return 0;
        }
    iofile.seeks(blocknumber + blocksize);
    buffer.clear();
    char c;

    for (i=0; i<blocksize; i++)
        iofile.get(c);
        buffer.push_back(c);

}



int main()
{
  Sdisk disk1("test1",16,32);
  string block1, block2, block3, block4;
  for (int i=1; i<=32; i++) block1=block1+"1";
  for (int i=1; i<=32; i++) block2=block2+"2";
  disk1.putblock(4,block1);
  disk1.getblock(4,block3);
  cout << "Should be 32 1s : ";
  cout << block3 << endl;
  disk1.putblock(8,block2);
  disk1.getblock(8,block4);
  cout << "Should be 32 2s : ";
  cout << block4 << endl;;
}