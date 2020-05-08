#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char** argv)
{
    string dir = string(argv[1]);
    vector<string> files = vector<string>();

    getdir(dir,files);

    files.erase(files.begin());
    files.erase(files.begin());

  for (unsigned int i = 0;i < files.size();i++) {  //  debug loop to make sure all text file names were correctly put into files vector
        cout << i << files[i] << endl;
    }
    //return 0;
  

    ifstream myfile;
    for(int i = 0; i < files.size(); i++){
        string path = string(argv[1]) + string(files[i]);
        cout << path << endl; // debug line to make sure the correct path to the text files  is assigned to the path string
        myfile.open(path.c_str());
        if(!myfile.is_open()) {
            cout << "error opening file" << endl;
            return -1;
        }
        string word;
        vector<string> words = vector<string>(6);
        int count = 0;
        int wordCount = 0;
        while(myfile >> word) {
            wordCount++;
            if(count < atoi(argv[2])){
                words.push_back(word);
                count++;
            }
            else{
                string wordChunk = "";
                for(int i = 0; i < count; i++){
                    wordChunk = wordChunk + words[i];
                }
                
                cout << wordChunk << endl; // debug to see if chunks are correct
                words.erase(words.begin());
                words.push_back(word);
            }
        }
    }
}
