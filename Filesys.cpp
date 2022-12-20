#include "sdisk.h"
#include "filesys.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> block(string buffer, int b){
  vector<string> blocks;
  int numberofblocks=0;

  if (buffer.length() % b == 0){
    numberofblocks= buffer.length()/b;
  }
  else{
    numberofblocks= buffer.length()/b +1;
  }

  string tempblock;
  for (int i=0; i<numberofblocks; i++){
    tempblock=buffer.substr(b*i,b);
    blocks.push_back(tempblock);
  }

  int lastblock=blocks.size()-1;

  for (int i=blocks[lastblock].length(); i<b; i++){
    blocks[lastblock]+="#";
  }

  return blocks;
}

int Filesys::fsclose(){
	fssynch();
	return 0;
}

int Filesys::fssynch(){
	ostringstream rootstream;
    
    	for(int i = 0; i < rootsize; ++i){
        	rootstream << filename[i] << " " << firstblock[i] << " ";  
    	}	
    	string root = rootstream.str();
    	for(long j = root.size(); j < getblocksize(); j++){
        	root += "#";
    	}
    	putblock(1, root);
    
    	ostringstream fatstream;
    
    	for(int i = 0; i < getnumberofblocks(); i++){
        	fatstream << fat[i] << " ";
    	}
    	string fatstring = fatstream.str();
    	vector<string> blocks=block(fatstring,getblocksize());
    
    	for(int i = 0; i < blocks.size(); i++){
        	putblock(i+2, blocks[i]);
       	}
    	return 1; 
}

int Filesys::newfile(string file){
        for(int i=0; i<filename.size(); i++){
            if(filename[i] == file){
                cout << "File " << file << " already exists." << endl;
                return 1;
            }
        }

        for(int i=0; i<filename.size(); i++){
            if (filename[i] == "XXXXX"){
                cout << "Creating file " << file << endl;
                filename[i] = file;
		firstblock[i]=0;
                break;
            }
        }
     	fssynch();
     	return 1;
}

int Filesys::rmfile(string file){
        for(int i = 0; i < filename.size(); i++) {
		if(filename[i] == file && firstblock[i] == 0) {
			filename[i] = "XXXXXX";
			firstblock[i] = 0;
		}
	}
        fssynch();
        return 1;
}

int Filesys::getfirstblock(string file){
        int first_block = 0;
        for(int i=0; i<filename.size(); i++){
                if(filename[i]==file){
                        first_block = firstblock[i];
                        break;
                }
        }
        fssynch();
        return first_block;
}

int Filesys::addblock(string file, string buffer){
	int firstblock = getfirstblock(file), newblock = fat[0];
	if(newblock == 0) {
		cout << "Disk full" << endl;
		return -1;
	}
	if(firstblock == 0) {//file is empty
		for(int i = 0; i < filename.size(); i++) {
			if(filename[i] == file) {
				firstblock = newblock;
				fat[0] = fat[newblock];
				fat[newblock] = 0;
			}
		}
	}
	else {
		int nextblock = firstblock;
		while(fat[newblock] != 0) {
			nextblock = fat[nextblock];
			fat[nextblock] = nextblock;
			fat[0] = fat[newblock];
			fat[newblock] = 0;
		}
	}
	putblock(newblock, buffer);
	fssynch();
	return newblock;
}

int Filesys::delblock(string file, int blocknumber){
	if(blocknumber == getfirstblock(file)) {
		for(int i = 0; i < filename.size(); i++) {
			if(filename[i] == file) {
				firstblock[i] = fat[blocknumber];
			}
		}
	}
	else {
		int blockid = getfirstblock(file);
		while(fat[blockid] != blocknumber) {
			blockid = fat[blockid];
		}
		fat[blockid] = fat[blocknumber];
	}
	fat[blocknumber] = fat[0];
	fat[0] = blocknumber;
	fssynch();
}


Filesys::Filesys(string file, int numberofblocks, int blocksize):Sdisk(file,numberofblocks,blocksize){
    string buffer;
	rootsize = getblocksize()/12;
	fatsize = (getnumberofblocks()*5)/(getblocksize())+1;  
	getblock(1,buffer);
	if(buffer[1]=='#'){
                cout<<"No File System"<<endl;
		for(int i=0; i<=rootsize; i++){
                	filename.push_back("XXXXX");
                        firstblock.push_back(0);
                }
		fat.push_back(fatsize+2);
                for(int i=1; i<=fatsize + 1; i++){
                        fat.push_back(1);
                }
                for(int i=2+fatsize; i<getnumberofblocks(); i++){
                        fat.push_back(i+1);
                }
                fat[fat.size()-1] = 0;
		cout<<"Created File System"<<endl;
       }
       else{
                cout<<"File System Exists"<<endl;
		string buffer;
        	istringstream readroot;
        	readroot >> buffer;
		for(int i = 0; i < rootsize; i++){
			string s;
        		int n;
            		readroot >> s >> n;
            		filename.push_back(s);
            		firstblock.push_back(n);
        	}
		string fatbuffer;
        	for(int i = 0; i < fatsize; i++){
            		string s;
            		getblock(i + 2, s);
            		fatbuffer += s;
        	}
        	istringstream fatstream;
        	fatstream.str(fatbuffer);
		for(int i = 0; i < getnumberofblocks(); i++){
            		int temp;
            		fatstream >> temp;
            		fat.push_back(temp);
		}
	}
	fssynch();
}


