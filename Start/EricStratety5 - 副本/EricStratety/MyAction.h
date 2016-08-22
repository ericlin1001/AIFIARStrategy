#ifndef MYACTION_H
#define MYACTION_H 
#include "base.h" 
#include "strategy.h"
#define Environment MyEnvironment
/** 
基本动作——Basic Actions, BA
		ToPostion 	到定点（停）
		TurnAngle	转动一定角度
		MoveAlong	向某点(或方向)作定向运动
		//
		MoveToPt
技术动作——Skilled Actions, SA
		KickBall		    踢球动作
		ShootGoal	    射门
		TurnShoot	    转身射门
		DefenseBall	    防球（回防）
		BlockMan	    盯人防守
		AvoidBound	    防止碰撞边界
		//
		KeepGoal 			守门员防守
		ProcessBoundBall 	边界球处理
		ProcessCornerBall 	角球处理
		PassBallToPt 			传球到定点
		AvoidObstToPt 		避障碍到定点

组合动作(单人)
              ——Combinatorial Action, CA
    
战术动作(多人)
             ——Tactical Actions, TA   
			NormalKickoff 			中场开球
			PassToShoot 			一传一射
			BL_PassToCenterShoot 	底线传中射门

*/ 
void ShootGoal (Robot &robot, const Environment &env);
void EndProcess(Robot &robot, const Environment &env,const VecPosition &goal);
#endif