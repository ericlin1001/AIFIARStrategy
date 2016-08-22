#include "stdafx.h"
#include "BasicScriptServer.h"
#define MAX_LINE_LEN 100
void BasicScriptServer::check(){//the entry point
	bool bSuccRead=false;
	if(isValidScript()){
		infile.open(infileName);
		char line[MAX_LINE_LEN];
		//cout<<"reading..."<<endl;
		while(infile.getline(line,MAX_LINE_LEN)){
			pharse(line);
			//cout<<"read:"<<line<<endl;
		}
		bSuccRead=true;
	}
	infile.close();
	if(bSuccRead){
		remove(infileName);
	}
}
bool BasicScriptServer::isValidScript(){
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