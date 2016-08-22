// CallTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "interface.h"
#include "GeometryR.h"
#include "base.h"
#include <iostream>
using namespace std;
/*extern "C" STRATEGY_API void StrategyInit(Environment* Env);
extern "C" STRATEGY_API void StrategyStep(Environment* Env);
extern "C" STRATEGY_API void StrategyDrop(Environment* Env);
extern "C" STRATEGY_API void Author(char* team);*/

typedef void (*PStrategyInit)(Environment* Env);
typedef void (*PStrategyStep)(Environment* Env);
typedef void (*PStrategyDrop)(Environment* Env);
typedef void (*PAuthor)(char* team);

class Object{
public:
	Object(){
	}
	double getX(){return pos.GetX();}
	double getRotation(){return theta;}
	VecPosition pos;
	double getY(){return pos.GetY();}
	double theta;
	void addVeclocity(double vl,double vr){
		this->vl=vl;
		this->vr=vr;
		if(vl>100)vl=100;
		if(vl<-100)vl=-100;
		if(vr>100)vr=100;
		if(vr<-100)vr=-100;
	};
	double vl, vr;
	void limit(){
		while(theta>180)theta-=180*2;
		while(theta<=-180)theta+=180*2;
	}
	double getLength(){return ROBOT_INFO::LENGTH;}
	VecPosition getDir(int len){
		VecPosition dir(len,0);
		dir.Rotate(theta/180*PI);
		return dir;
	}
	void print(){
		cout<<"Object(";
		cout<<"Pos("<<this->getX()<<","<<this->getY()<<"),";
		cout<<"Theta("<<this->getRotation()<<"deg "<<this->getRotation()*PI/180<<"rad"<<"))";
	}
	void printVec(){
		cout<<"Object(vl("<<vl<<"),vr("<<vr<<"))";
	}
};
Object objects[11];
void initObjects(){
	Object *ball,*yellow,*blue;
	yellow=&objects[0];
	blue=&objects[5];
	ball=&objects[10];
	//init the all objects's position:
}
#define Trace(m) cout<<#m"="<<(m)<<endl;
void startStimulate(){
	Object *ball,*yellow,*blue;
	yellow=&objects[0];
	blue=&objects[5];
	ball=&objects[10];
	//
	int i;
	for(i=0;i<5;i++){//the first 5one
		if(i==1){
		Object *p=objects+i;
		double newX,newY;
		double x=p->getX(),y=p->getY();
		//
		double w,v,vx,vy;
		cout<<"Robot("<<i<<")";p->printVec();cout<<endl;
	
		w=(p->vr-p->vl)/(double)(2.0*ROBOT_INFO::HALF_LENGTH);
		double addedTheta=w/PI*180;
		addedTheta/=5;
		
		v=(p->vl+p->vr)/2;
		v/=5;
		vx=v*Maths::cosDeg(p->getRotation());
		vy=v*Maths::sinDeg(p->getRotation());
		Trace(vx);
		Trace(vy);
		//
		p->pos.SetX(x+vx);
		p->pos.SetY(y+vy);
		Trace(addedTheta);
		p->theta+=addedTheta;
		p->limit();
		}
	}
}
void startDraw(){
	Object *ball,*yellow,*blue;
	yellow=&objects[0];
	blue=&objects[5];
	ball=&objects[10];
	//
	int i;
	cout<<"************Start drawing*************"<<endl;
	for(i=0;i<5;i++){//the first 5one
		if(i==1){
			Object *p=objects+i;
			cout<<"home["<<i<<"]:";p->print();cout<<endl;
		}
	}
	cout<<"************End drawing*************"<<endl;
}
int main()
{
	PStrategyInit StrategyInit;
	PStrategyStep StrategyStep;
	PStrategyDrop StrategyDrop;
	PAuthor  Author;
	//
	//HINSTANCE hModule=LoadLibrary("..\\Debug\\MyStrategy.dll");
	HINSTANCE hModule=LoadLibrary("..\\Release\\MyStrategy.dll");
	//
	StrategyInit=(PStrategyInit)GetProcAddress(hModule,"StrategyInit");
	StrategyStep=(PStrategyStep)GetProcAddress(hModule,"StrategyStep");
	StrategyDrop=(PStrategyDrop)GetProcAddress(hModule,"StrategyDrop");
	Author=(PAuthor)GetProcAddress(hModule,"Author");
#define NotNull(m) if(m==NULL){ cout<<#m<<" not exist"<<endl;}else {cout<<"load "#m" successfully!"<<endl;}
#define Trace(m) cout<<#m"="<<(m)<<endl;
	NotNull(StrategyInit);
	NotNull(StrategyStep);
	NotNull(StrategyDrop);
	NotNull(Author);
	//
	char teamName[100];
	Environment env;
	Environment *p=&env;
	//
	
	Object *ball,*yellow,*blue;
	yellow=&objects[0];
	blue=&objects[5];
	ball=&objects[10];
	//
	Object *home,*opponent;
	home=yellow;
	opponent=blue;
	//
	cout<<"Before Author "<<endl;
	Author(teamName);//load as yellow
	Trace(teamName);

	StrategyInit(p);
	env.halfArea=LeftArea;
	env.kickOffStyle=Normal;
	env.whoseBall=ANYONES_BALL;
	initObjects();
	while(1){
		env.currentBall_pos_x=ball[0].getX();
		env.currentBall_pos_y=ball[0].getY();
		//
		env.home0_pos_x=home[0].getX();
		env.home0_pos_y=home[0].getY();
		env.home1_pos_x=home[1].getX();
		env.home1_pos_y=home[1].getY();
		env.home2_pos_x=home[2].getX();
		env.home2_pos_y=home[2].getY();
		env.home3_pos_x=home[3].getX();
		env.home3_pos_y=home[3].getY();
		env.home4_pos_x=home[4].getX();
		env.home4_pos_y=home[5].getY();
		env.home0_rotation=home[0].getRotation();
		env.home1_rotation=home[1].getRotation();
		env.home2_rotation=home[2].getRotation();
		env.home3_rotation=home[3].getRotation();
		env.home4_rotation=home[4].getRotation();
		//
		env.opponent0_pos_x=opponent[0].getX();
		env.opponent0_pos_y=opponent[0].getY();
		env.opponent1_pos_x=opponent[1].getX();
		env.opponent1_pos_y=opponent[1].getY();
		env.opponent2_pos_x=opponent[2].getX();
		env.opponent2_pos_y=opponent[2].getY();
		env.opponent3_pos_x=opponent[3].getX();
		env.opponent3_pos_y=opponent[3].getY();
		env.opponent4_pos_x=opponent[4].getX();
		env.opponent4_pos_y=opponent[5].getY();
		env.opponent0_rotation=opponent[0].getRotation();
		env.opponent1_rotation=opponent[1].getRotation();
		env.opponent2_rotation=opponent[2].getRotation();
		env.opponent3_rotation=opponent[3].getRotation();
		env.opponent4_rotation=opponent[4].getRotation();
		//
		StrategyStep(p);
		//
		home[0].addVeclocity(env.home0_velocityLeft,env.home0_velocityRight);
		home[1].addVeclocity(env.home1_velocityLeft,env.home1_velocityRight);
		home[2].addVeclocity(env.home2_velocityLeft,env.home2_velocityRight);
		home[3].addVeclocity(env.home3_velocityLeft,env.home3_velocityRight);
		home[4].addVeclocity(env.home4_velocityLeft,env.home4_velocityRight);
		//
		startStimulate();
		startDraw();
		//
		cin.get();
		//Sleep(30);
	}
	
	StrategyDrop(p);
	//
	FreeLibrary(hModule);
	system("pause");
	return 0;
}

