#include "stdafx.h"
#include "action.h"
inline double getAngleBetween(const VecPosition &a,const VecPosition& b){
	return fabs(VecPosition::NormalizeAngle(b.GetDirection()-a.GetDirection()));
}
inline double getAngleFromTo(const VecPosition &a,const VecPosition& b){
	return VecPosition::NormalizeAngle(b.GetDirection()-a.GetDirection());
}
void EndProcess(Robot &robot, const Environment &env,const VecPosition &goal){
	//Show("EndProcess");
	double kp,ka;
	double vl,vr;
	double a;
	kp=90;
	ka=40;
	//
	a=getAngleFromTo(robot.getDirection(),goal-robot.get_position());
	if(fabs(a)>PI/2){
		double b=a;
		if(b<0)b+=2*PI;
		b-=PI;

		vl=kp*cos(a)-ka*b;
		vr=kp*cos(a)+ka*b;
	}else{
		vl=kp*cos(a)-ka*a;
		vr=kp*cos(a)+ka*a;
	}
	
	robot.set_left_velocity(vl);
	robot.set_right_velocity(vr);
	robot.LimitSpeed();
	return ;
}
void DynamicCicleShoot (Robot &robot, const Environment &env);
inline bool isInField(const VecPosition &p){
	return FLEFTX<p.GetX() && p.GetX()<FRIGHTX && FBOT<p.GetY() && p.GetY()<FTOP;
}
void ShootGoal (Robot &robot, const Environment &env){
	DynamicCicleShoot(robot,env);
}
void ShootGoal (Robot &robot, const Environment &env){
void DynamicCicleShoot (Robot &robot, const Environment &env){
	//dynamic circle shoot:
	double r0=3*ROBOT_INFO::HALF_LENGTH;
	VecPosition ball=VecPosition(env.currentBall.pos.x,env.currentBall.pos.y);
	VecPosition goal=VecPosition(FIELD_INFO::GOAL::getOppCenterX(),FIELD_INFO::GOAL::getOppCenterY())-ball;
	VecPosition my=robot.get_position()-ball;
	VecPosition mydir=VecPosition::GetVecPositionFromPolar(1,robot.get_theta());
	//
	VecPosition temp,temp2,center;
	double angle_GBR=getAngleBetween(my,goal);
	double r=r0*(1+tan(angle_GBR/2));
	temp=goal;
	temp=temp.Rotate(PI/2);
	temp=temp.SetMagnitude(r);
	temp2=temp*-1;
	if(temp.GetDistanceTo(my)>temp2.GetDistanceTo(my))center=temp2;
	else center=temp;
	//
	double speed=ROBOT_INFO::WHEEL::MAX_SPEED*0.7;
	//
	double dist;
	temp=my-center;
	dist=temp.GetMagnitude();
	//Show("robot:"<<robot.index<<" radius:"<<r<<" dist:"<<dist<<" center:"<<(ball+center));
	
	if(dist<=r){
		//cout<<"in"<<endl;
		if((PI-angle_GBR)<PI/2/8){
			EndProcess(robot,env,ball);
			return ;
		}
		//robot.ToPositionPD(ball);
		double vl,vr;
		double v=speed*ROBOT_INFO::WHEEL::RADIUS;
		double w=v/r;
		VecPosition rightDir=mydir;
		if(getAngleBetween((my+mydir),goal)<getAngleBetween((my-mydir),goal)){
			v*=-1;
			rightDir*=-1;//the correct dir.
		}
		//
		temp2=temp=rightDir;
		temp=temp.Rotate(w);
		temp2=temp2.Rotate(-w);
		if(center.GetDistanceTo(temp+my)>center.GetDistanceTo(temp2+my)){
			w*=-1;
		}
		//
		v/=ROBOT_INFO::WHEEL::RADIUS;
		vr=v+w;
		vl=v-w;
		//
		robot.set_left_velocity(vl);
		robot.set_right_velocity(vr);
		return ;
		robot.set_left_velocity(0);
		robot.set_right_velocity(0);
		Show(" stay");
		return ;
	}else{
		//Show("out circle");
		VecPosition cut1=temp;
		cut1=cut1.SetMagnitude(r);
		VecPosition cut2=cut1;
		double cutAngle=acos(r/dist);
		cut1=cut1.Rotate(cutAngle);
		cut2=cut2.Rotate(-cutAngle);
		cut1+=center;
		cut2+=center;
		VecPosition cut;
		if(getAngleBetween(goal,cut1)>getAngleBetween(goal,cut2)){
			cut=cut1;
		}else{
			cut=cut2;
		}
		//Show("cutPoint:"<<(cut+ball));
		cut+=ball;
		if(isInField(cut)){
			robot.ToPositionPD(cut);
		}else{
			robot.ToPositionPD(ball);
		}
		
		return ;
	}
	return ;
}