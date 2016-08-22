// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
#include<iostream>
#include<fstream>
#include<cstring>
#include<string.h>
#define Trace(m) cout<<#m"="<<(m)<<endl;
using namespace std;
class BasicScriptServer{
public:
	BasicScriptServer(){
		isInReady=false;
		isOutReady=false;
		bOutPut=false;
	}
	BasicScriptServer(char *infile,char *outfile){
		setInFile(infile);setOutFile(outfile);
	}
	void setInFile(char *file){
		strcpy(infileName,file);
		isInReady=true;
	}
	void setOutFile(char *file){
		strcpy(outfileName,file);
		isOutReady=true;
	}
	void output(char *str){
		if(bOutPut){
			outfile<<str;
		}else{
		}
	}
	void closeAll(){
		infile.close();
		outfile.close();
	}
	void pharse(char *script){
		outfile<<script<<endl;
	}
	#define MAX_LINE_LEN 64
	void check(){//the entry point
		bool bSuccRead=false;
		if(isValidScript()){
			infile.open(infileName);
			//open the outfile
			if(isOutReady){
				outfile.open(outfileName,std::ios_base::app);
				if(!outfile.fail()){
					bOutPut=true;
				}else{
					bOutPut=false;
					cout<<"open "<<outfileName<<" fail!"<<endl;
				}
			}
			//
			char line[MAX_LINE_LEN];
			//cout<<"reading..."<<endl;
			while(infile.getline(line,MAX_LINE_LEN)){
				pharse(line);
				//cout<<"read:"<<line<<endl;
			}
			bSuccRead=true;
			
		}
		closeAll();
		if(bSuccRead){
			remove(infileName);
		}
	}
	bool isValidScript(){
		bool bretrun=false;
		if(isInReady){
			infile.open(infileName);
			if(!infile.fail()){
				infile.seekg(-5,std::ios_base::end);
				char endTag[10];
				infile.getline(endTag,4);
				if(strncmp(endTag,"end",3)==0){
					bretrun=true;
				}
			}else{
				//cout<<"open "<<infileName<<" fail!"<<endl;
			}
		}else{
		//	cout<<"in not ready!"<<endl;
		}
		infile.close();
		return bretrun;
	}
	~BasicScriptServer(){
		closeAll();
	}
private:
#define MAX_PATH_LEN 50
	char infileName[MAX_PATH_LEN];
	char outfileName[MAX_PATH_LEN];
	ifstream infile;
	ofstream outfile;
	bool bOutPut;
	bool isInReady;
	bool isOutReady;
};

class BasicScriptClient{
public:
	BasicScriptClient(){
		isInReady=false;
		isOutReady=false;
		bOutPut=false;
	}
	BasicScriptClient(char *infile,char *outfile){
		setInFile(infile);setOutFile(outfile);
	}
	void setInFile(char *file){
		strcpy(infileName,file);
		isInReady=true;
	}
	void setOutFile(char *file){
		strcpy(outfileName,file);
		isOutReady=true;
	}
	void output(char *str){
		if(bOutPut){
			outfile<<str;
		}else{
		}
	}
	bool tryWrite(char *str){
		if(isOutReady){
			outfile.open(outfileName,std::ios_base::app);
			if(!outfile.fail()){
				outfile<<str<<endl;
				outfile.close();
				return true;
			}else{
			}
		}
		outfile.close();
		return false;
	}
	bool tryRead(){
		bool bSucc=false;
		if(isInReady){
			infile.open(infileName);
			if(!infile.fail()){
				char buffer[100];
				while(infile.getline(buffer,100)){
					if(strcmp(buffer,"cls")==0){
						system("cls");
					}else{
						cout<<buffer<<endl;
					}
				}
				infile.close();
				bSucc=true;
			}else{
				//cout<<"Open "<<infileName<<" fail!"<<endl;
			}
		}else{
			//cout<<"in not ready!"<<endl;
		}
		infile.close();
		if(bSucc)remove(infileName);
		return bSucc;
	}
	void closeAll(){
		infile.close();
		outfile.close();
	}
	~BasicScriptClient(){
		closeAll();
	}
private:
#define MAX_PATH_LEN 50
	char infileName[MAX_PATH_LEN];
	char outfileName[MAX_PATH_LEN];
	ifstream infile;
	ofstream outfile;
	bool bOutPut;
	bool isInReady;
	bool isOutReady;
};
#define CASE2

#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"
#include<Windows.h>
#include<stdio.h>

#ifdef CASE5
int main(int argc, char* argv[])
{
	while(1){
		char buffer[100];
		cin>>buffer;
		int x,y;
		cout<<sscanf(string(buffer).c_str(),"move(%d,%d)",&x,&y)<<endl;
		Trace(x);Trace(y);
	}
	
	return 0;
}
#endif



//server:
#ifdef CASE1
int _tmain(int argc, _TCHAR* argv[])
{
	BasicScriptServer c(IN_FILE,OUT_FILE);
	char buffer[100];
	while(1){
		c.check();
		Sleep(100);
		//cout<<"Continue?";cin.get();
	}
	system("pause");
	return 0;
}
#endif

//show
#ifdef CASE4
int main(int argc, char* argv[])
{
	if(argc==3){
		BasicScriptClient c(argv[1],argv[2]);
		while(1){
			c.tryRead();
			Sleep(100);
		}
	}else{
		cout<<"Usage:Show.exe infileName outfileName"<<endl;
	}
	
	return 0;
}
#endif

#ifdef CASE2
int main(int argc, char* argv[])
{
	if(argc==3){
		BasicScriptClient c(argv[1],argv[2]);
		char buffer[100];
		while(1){
			cout<<"Script:";cin.getline(buffer,100,'\n');
			strcat(buffer,"\nend");
			int repeat=0;
			const int maxRepeat=5;
			while(!c.tryWrite(buffer)&&repeat++<maxRepeat){
					cout<<"Fail:Try "<<repeat<<" times."<<endl;
			}
			if(repeat>maxRepeat)cout<<"Send "<<buffer<<" Fail!"<<endl;
		}
	}else{
		cout<<"Usage:Send.exe infileName outfileName"<<endl;
	}
	
	//system("pause");
	return 0;
}
#endif
#ifdef CASE3
int _tmain(int argc, _TCHAR* argv[])
{
	BasicScriptClient c(OUT_FILE,IN_FILE);
	char buffer[100];
	while(1){
		cout<<"input:";cin>>buffer;
		int repeat=0;
		const int maxRepeat=5;
		while(!c.tryWrite(buffer)&&repeat++<maxRepeat){
				cout<<"Write:Try "<<repeat<<" times."<<endl;
		}
		if(repeat>maxRepeat)cout<<"Fail!"<<endl;
		else cout<<"Success!"<<endl;
		 repeat=0;
		 while(!c.tryRead()&repeat++<maxRepeat){
				cout<<"Read:Try "<<repeat<<" times."<<endl;
		}
		 if(repeat>maxRepeat)cout<<"Fail!"<<endl;
		else cout<<"Success!"<<endl;
	}
	system("pause");
	return 0;
}
#endif