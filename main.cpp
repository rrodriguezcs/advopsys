#include<iostream>
#include<fstream>
using namespace std;


Class Sdisk{
public :
Sdisk(string diskname, int numbblocks, int blocksize)
{
diskname=block; numbblocks=4;
blocksize=4;
}

int getblock(int blocknumber, string& buffer);
int putblock(int blocknumber, string buffer);
int getnumbblocks(); // accessor function
int getblocksize(); // accessor function
void stubs();
private :
string diskname;        // file name of software-disk
int numbblocks;     // number of blocks on disk
int blocksize;          // block size in bytes
};

int Sdisk::putblock(int blocknumber,string& buffer)

{ 
ifstream f1;
f1.open("file.DAT");
if(!f1)

{
cout << "ERROR file.DAT|n";
exit(102);
}

f1.get(buffer);

f1.close();

}
int Sdisk::getblock(int blocknumber, string buffer)
{
ofstream f2;
f2.open("file2.DAT);
cout << "DATA IN FILE";
while(!f2.eof())
{
f2.get(buffer);
cout<<buffer;
}
f2.close();
}
void Sdisk::stubs()
{}

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


Class putblock{

}