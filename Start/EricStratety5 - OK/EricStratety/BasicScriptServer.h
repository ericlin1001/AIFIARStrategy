#ifndef BASEICSCRIPTSERVER_H
#define BASEICSCRIPTSERVER_H
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<string>
#include<list>
using namespace std;
class BasicScriptServer{
public:
	BasicScriptServer(){
		isInReady=false;
		isOutReady=false;
		bOutPut=false;
		open();
	}
	void open(){bOpen=true;}
	void close(){bOpen=false;}
	//void setSource(StrategyBasis *p){src=p;}
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
	ofstream &getOut(){return outfile;}
	string getScript(){
		string script=scripts.front();
		scripts.pop_front();
		return script;
	}
	bool isEmpty(){return scripts.empty();}
	void startOutPut(){
		if(!bOpen)return ;
		if(isOutReady){
			outfile.open(outfileName,std::ios_base::app);
			if(!outfile.fail()){
				bOutPut=true;
			}else{
				bOutPut=false;
				cout<<"open "<<outfileName<<" fail!"<<endl;
			}
		}
	}
	void endOutPut(){
		if(!bOpen)return ;
		outfile.close();
	}
	void check();
	list<string>getScripts(){return scripts;}
	~BasicScriptServer(){
		closeAll();
	}
private:
	void closeAll(){
		infile.close();
		outfile.close();
	}
	void pharse(char *script){
		scripts.push_back(script);	
	}
	bool isValidScript();
private:
#define MAX_PATH_LEN 50
	bool bOpen;
	char infileName[MAX_PATH_LEN];
	char outfileName[MAX_PATH_LEN];
	ifstream infile;
	ofstream outfile;
	bool bOutPut;
	bool isInReady;
	bool isOutReady;
	//
	list<string>scripts;
	//
	//StrategyBasis *src;
};
#endif