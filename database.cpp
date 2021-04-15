#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>  
// Actually I was going to make something better than that but there was no time already =(
using namespace std;
class Data
{
public:
    string get(string key){
        ifstream ifile ("main.txt");
        string temp;
        bool found=false;
        while(getline(ifile,temp)){
            found=false;
            if(temp == key){
                found = true;
                getline(ifile,temp);
                ifile.close();
                return temp;
            }
            getline(ifile,temp);
        }
        ifile.close();
        return "";
    }
    void put(string key, string val){
        ifstream ifile ("main.txt");
        string temp;
        string fullFile;
        bool done=false;
        while(getline(ifile,temp)){
            fullFile+=temp+"\n";
            if(temp==key){
                getline(ifile,temp);
                fullFile+=val+"\n";
                done=true;
            }else{
                getline(ifile,temp);
                fullFile+=temp+"\n";
            }
        }
        if(!done){
            //cout<<"NOTDONE"<<endl;
            fullFile+=key+"\n";
            fullFile+=val+"\n";
        }
        ifile.close();
        
        ofstream ofile ("main.txt", ios::out | ios::trunc);
        
        ofile<<fullFile;
        ofile.close();
        
        
    }
};
