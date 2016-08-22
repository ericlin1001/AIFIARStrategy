// Strategy.cpp : Defines the entry point for the DLL application.   
   
#include "stdafx.h"   
#include "Strategy.h"   
   
#include <math.h>   
   
BOOL APIENTRY DllMain( HANDLE hModule,    
                       DWORD  ul_reason_for_call,    
                       LPVOID lpReserved   
                                         )   
{   
    switch (ul_reason_for_call)   
        {   
                case DLL_PROCESS_ATTACH:   
                case DLL_THREAD_ATTACH:   
                case DLL_THREAD_DETACH:   
                case DLL_PROCESS_DETACH:   
                        break;   
    }   
    return TRUE;   
}   
const int WHO = 0; //1 蓝方， 其他 黄方   
FILE *DEBUGFILE; // 调试文件   
Environment *ENV; //环境的全局变量   
int BLUES = 0,YELLOWS = 0; //blue yellow sccor   
bool INYELLOW = false, INBLUE = false; //球是否在门里   
const double PI = 3.1415926;   
double ROBOTWIDTH = 3.14; //机器人的宽度   
double BALLD = 1.7; //球的直径 1.916   
double HOMETRACE[5][2][2] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //纪录 5 个机器人的轨迹   
double BALLTRACE[1][2][2] = {-1,-1,-1,-1}; //球的轨迹   
double ENEMYTRACE[5][2][2] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //纪录 敌方5 个机器人的轨迹   
double HOMEDISPLACEMENT[5] = {0};    
double BALLDISPLACEMENT[1] = {0};    
double ENEMYDISPLACEMENT[5] = {0}; //纪录机器人和球在 1/30 秒内的位移   
int HOMEEV[5] = {0}; //estimated v 估计的机器人的速度   
int BALLEV[1] = {0}; //ball's speed   
int ENEMYEV[5] = {0}; //敌方机器人速度   
double COUNT1 = 0, COUNT2 = 0; //保存调用次数   
double HOMEVDIRECTION[5] = {0};   
double BALLVDIRECTION[1] = {0};   
double ENEMYVDIRECTION[5] = {0}; //球和机器人的速度方向   
double PBP[2] = {0, 0}; //预测的球的坐标 predict ball position   
double HOMEROTATION[5][2] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};   
double ENEMYROTATION[5][2] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //机器人的转角   
int ORDER[5] = {4,3,2,1,0}; //离机器人的距离   
int RORDER[5] = {0,1,2,3,4}; //各机器人对应的距离顺序   
void strategyForD(Environment *env); //default   
void strategyForFB(Environment *env);   
void strategyForPlK(Environment *env);   
void strategyForPeK(Environment *env);   
void strategyForFK(Environment *env);   
void strategyForGK(Environment *env);   
void ballInGate();   
void run(Robot *robot, int rID, int vl, int vr); //给左右轮子赋值，该函数保证数据在合法的范围   
void estimateV(); //估计所有机器人的速度,and the ball   
double lineAngel(double x1, double y1, double x2, double y2); //直线在 0-360 坐标系中的角度   
double robotAngel(Robot *robot, int rID); // 转换机器人角度   
void vDirection(); //计算球和机器人的方向   
double f(double k, double x0, double y0, double x); //计算直线在 x 的值   
double fn(double k,double x0,double y0,double y); //计算直线在 y 的值   
double l(double x1, double y1, double x2, double y2); //计算 2 点的距离   
void predictBall(double xs); //计算 xs 秒后球的位置,存入PBP[]   
void rotation(); //计算所有机器人的转角   
bool isStill(Robot *robot,int rID); //判断是否静止   
int direction(double ra,double la); //返回机器人旋转方向,正向时   
//advanced methods   
bool canKShoot(Robot *robot, int rID); //是否可以把球撞进   
bool canTShoot(Robot *robot,int rID); //是否可以旋转进球 可以就旋转   
void turn(Robot *robot,int rID,int dire); //顺(1)/逆(-1)时针旋转   
void goBackTo(Robot *robot, int rID, double x,double y); //   
void goTo(Robot *robot, int rID, double x, double y); //到某点,不会停止   
void sGo(Robot *robot, int rID, double x, double y); //super go 根据当前方向到某点   
void to(Robot *robot, int rID, double x, double y); //   
void backTo(Robot *robot, int rID, double x, double y); //到某点后静止   
void sTo(Robot *robot,int rID,double x,double y); //super to 根据当前方向到某点   
void rotateTo(Robot *robot, int rID, double x, double y); //指向某点，静止？？   
void rotateBackTo(Robot *robot,int rID, double x,double y);   
void sRotate(Robot *robot, int rID,double x, double y); //super   
void sRotate(Robot *robot, int rID, double angel);   
void order(); //返回机器人距离球距离的顺序，存入 ORDER[],由近到远   
bool hasEnemyNear(double x, double y); //是否有敌机在 x,y 附近   
bool hasEnemyBetween(double x1,double y1,double x2,double y2); //按步长执行 hasEnemyNear   
bool hasEnemyIn(double x1,double y1,double x2,double y2); // 是否有敌方在矩形区域   
void turnKick(Robot *robot,int rID,int where); //旋转以把球踢到 4 个象限中的一个   
//role controller   
void keeper(Robot *robot, int rID,double x,double y,double angel); //守卫者   
void pushHelper(Robot *robot,int rID); //助推员   
void goalie(Robot *robot,int rID); //守门员   
void toBRight(Robot *robot,int rID); //到球右边   
void toBLeft(Robot *robot,int rID); //到球左边   
void toBUp(Robot *robot,int rID); //到球上边   
void toBDown(Robot *robot,int rID); //到球下边   
void leftSoccer(Robot *robot,int rID); //   
void middleSoccer(Robot *robot,int rID); //   
void rightSoccer(Robot *robot,int rID); //   
void backSoccer(Robot *robot,int rID); //左中右后   
void Create ( Environment *env );   
void Destroy ( Environment *env );   
void Strategy ( Environment *env );   
extern "C" STRATEGY_API void Create ( Environment *env )   
{   
        // allocate user data and assign to env->userData   
        // eg. env->userData = ( void * ) new MyVariables ();   
}   
   
extern "C" STRATEGY_API void Destroy ( Environment *env )   
{   
        // free any user data created in Create ( Environment * )   
        // eg. if ( env->userData != NULL ) delete ( MyVariables * ) env->userData;   
}   
   
   
extern "C" STRATEGY_API void Strategy ( Environment *env )   
{   
        //here are my Strategies ,as the game state differes calls the responding method    
        COUNT2 ++;   
        ENV = env;   
        ballInGate();   
        estimateV();   
        rotation();   
        order();   
   
        switch(env->gameState){   
                case 0 : //s(env);break;   
                case FREE_BALL : strategyForD(env); break;   
                case PLACE_KICK : strategyForD(env); break;   
                case PENALTY_KICK : strategyForD(env); break;   
                case FREE_KICK : strategyForD(env); break;   
                case GOAL_KICK : strategyForD(env); break;   
        }   
}   
   
void strategyForD(Environment *env){   
        //   
        goalie(&env->home[0],0);   
        leftSoccer(&env->home[1],1);   
        rightSoccer(&env->home[4],4);   
        middleSoccer(&env->home[3],3);   
        backSoccer(&env->home[2],2);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d\n",);   
        //fclose(DEBUGFILE);   
}   
   
void strategyForFB(Environment *env){   
        //   
}   
   
void strategyForPlK(Environment *env){   
        //   
}   
   
void strategyForPeK(Environment *env){   
        //   
}   
   
void strategyForFK(Environment *env){   
        //   
}   
   
void strategyForGK(Environment *env){   
        //   
}   
void ballInGate(){ //进球是犯规的怎么办 ？？   
        //   
        double bx,by;   
   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        if(by < GTOPY && by > GBOTY && bx < FLEFTX){   
                if(!INYELLOW)   
                        BLUES ++;   
                INYELLOW = true;   
        }   
        else   
                INYELLOW = false;   
        if(by < GTOPY && by > GBOTY && bx > FRIGHTX){   
                if(!INBLUE)   
                        YELLOWS ++;   
                INBLUE = true;   
        }   
        else   
                INBLUE = false;   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "b:y %d:%d\n",BLUES,YELLOWS);   
        //fclose(DEBUGFILE);   
}   
   
void run(Robot *robot, int rID, int vl, int vr){   
        //   
        if(vl > 125)   
                vl = 125;   
        if(vr > 125)   
                vr = 125;   
        if(vl < -125)   
                vl = -125;   
        if(vr < -125)   
                vr = -125;   
        robot->velocityLeft = vl;   
        robot->velocityRight = vr;   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d\n",HOMEEV[rID]);   
        //fclose(DEBUGFILE);   
}   
   
void estimateV(){   
        //   
        double dx, dy;   
        double k; //位移对于速度的系数 v= k*s   
        int ym = 0;   
   
        k = 33.45; //k 由试验测得 10/1.47符合的很好对 50 100 也   
        if(HOMETRACE[0][0][0] == -1){   
                for(ym = 0; ym < 5; ym++){   
                        HOMETRACE[ym][0][0] = ENV->home[ym].pos.x;   
                        HOMETRACE[ym][0][1] = ENV->home[ym].pos.y;   
                        HOMETRACE[ym][1][0] = ENV->home[ym].pos.x;   
                        HOMETRACE[ym][1][1] = ENV->home[ym].pos.y;   
                }   
                for(ym = 0; ym < 5; ym++){   
                        ENEMYTRACE[ym][0][0] = ENV->opponent[ym].pos.x;   
                        ENEMYTRACE[ym][0][1] = ENV->opponent[ym].pos.y;   
                        ENEMYTRACE[ym][1][0] = ENV->opponent[ym].pos.x;   
                        ENEMYTRACE[ym][1][1] = ENV->opponent[ym].pos.y;   
                }   
                BALLTRACE[0][0][0] = ENV->currentBall.pos.x;   
                BALLTRACE[0][0][1] = ENV->currentBall.pos.y;   
                BALLTRACE[0][1][0] = ENV->currentBall.pos.x;   
                BALLTRACE[0][1][1] = ENV->currentBall.pos.y;   
        }   
        if(COUNT2 - COUNT1 >= 2){ //每调用 2 次纪录坐标   
                for(ym = 0; ym < 5; ym++){   
                        dx = HOMETRACE[ym][1][0] - HOMETRACE[ym][0][0];   
                        dy = HOMETRACE[ym][1][1] - HOMETRACE[ym][0][1];   
                        HOMEDISPLACEMENT[ym] = sqrt(dx*dx + dy*dy);   
                        HOMETRACE[ym][0][0] = HOMETRACE[ym][1][0];   
                        HOMETRACE[ym][0][1] = HOMETRACE[ym][1][1];   
                        HOMEEV[ym] = int(HOMEDISPLACEMENT[ym]*k); //用什么模型？   
                }   
                for(ym = 0; ym < 5; ym++){   
                        dx = ENEMYTRACE[ym][1][0] - ENEMYTRACE[ym][0][0];   
                        dy = ENEMYTRACE[ym][1][1] - ENEMYTRACE[ym][0][1];   
                        ENEMYDISPLACEMENT[ym] = sqrt(dx*dx + dy*dy);   
                        ENEMYTRACE[ym][0][0] = ENEMYTRACE[ym][1][0];   
                        ENEMYTRACE[ym][0][1] = ENEMYTRACE[ym][1][1];   
                        ENEMYEV[ym] = int(ENEMYDISPLACEMENT[ym]*k); //用什么模型？   
                }   
                dx = BALLTRACE[0][1][0] - BALLTRACE[0][0][0];   
                dy = BALLTRACE[0][1][1] - BALLTRACE[0][0][1];   
                BALLDISPLACEMENT[0] = sqrt(dx*dx + dy*dy);   
                BALLTRACE[0][0][0] = BALLTRACE[0][1][0];   
                BALLTRACE[0][0][1] = BALLTRACE[0][1][1];   
                BALLEV[0] = int(BALLDISPLACEMENT[0]*k); //用什么模型？   
                   
                COUNT1 = COUNT2;   
        }   
        else{   
                for(ym = 0; ym < 5; ym++){   
                        HOMETRACE[ym][1][0] = ENV->home[ym].pos.x;   
                        HOMETRACE[ym][1][1] = ENV->home[ym].pos.y;   
                }   
                for(ym = 0; ym < 5; ym++){   
                        ENEMYTRACE[ym][1][0] = ENV->opponent[ym].pos.x;   
                        ENEMYTRACE[ym][1][1] = ENV->opponent[ym].pos.y;   
                }   
                BALLTRACE[0][1][0] = ENV->currentBall.pos.x;   
                BALLTRACE[0][1][1] = ENV->currentBall.pos.y;   
   
                vDirection();   
        }   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f %f\n",HOMETRACE[3][0][0],HOMETRACE[3][1][0],COUNT2);   
        //fclose(DEBUGFILE);   
}   
double lineAngel(double x1, double y1, double x2, double y2){   
        //以 x1,y1 为起点   
        double length, dx, dy;   
        double sinValue, alpha;   
   
        dx = x2 - x1;   
        dy = y2 - y1;   
        if(fabs(dx) < 0.1 && dy > 0)   
                return 90.0;   
        else if(fabs(dx) < 0.1 && dy < 0)   
                return 270.0;   
        if(fabs(dy) < 0.1 && dx > 0)   
                return 0.0;   
        else if(fabs(dy) < 0.1 && dx < 0)   
                return 180.0;   
        if(dx < 1 || dy < 1){   
                dx = dx*1000;   
                dy = dy*1000;   
        }   
        if(dx < 0.1 || dy < 0.1){   
                dx = dx*10000;   
                dy = dy*10000;   
        }   
        else if(dx < 10 || dy < 10){   
                dx = dx*100;   
                dy = dy*100;   
        } //放大以减小误差   
        length = sqrt(dx*dx + dy*dy);   
        sinValue = dy/length;   
        if(sinValue >1)   
                sinValue = 1;   
        if(sinValue < -1)   
                sinValue = -1; //防止由于计算误差导致的溢出   
        alpha = asinf(sinValue)/PI * 180.0;   
        if(dx > 0){   
                if(alpha > 0)   
                        alpha = alpha;   
                else if(alpha < 0)   
                        alpha = 360.0 + alpha;   
        }   
        else if(dx < 0){   
                if(alpha > 0)   
                        alpha = 180.0 - alpha;   
                else if(alpha < 0)   
                        alpha = 180.0 + fabs(alpha);   
        }   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f %f\n", dy, length, alpha);   
        //fclose(DEBUGFILE);   
        return alpha;   
}   
   
double robotAngel(Robot *robot, int rID){   
        //   
        double alpha;   
   
        alpha = robot->rotation;   
        if(alpha > 0)   
                alpha = alpha;   
        else if(alpha < 0)   
                alpha = 360.0 + alpha;   
        return alpha;   
}   
   
double robotAngel(OpponentRobot *robot,int rID){   
        //   
        double alpha;   
   
        alpha = robot->rotation;   
        if(alpha > 0)   
                alpha = alpha;   
        else if(alpha < 0)   
                alpha = 360.0 + alpha;   
        return alpha;   
}   
   
void vDirection(){   
        //   
        int lt = 0;   
   
        for(lt = 0; lt < 5; lt++){   
                if(HOMEEV[lt] == 0)   
                        HOMEVDIRECTION[lt] = -1;   
                else   
                        HOMEVDIRECTION[lt] = lineAngel(   
                                HOMETRACE[lt][0][0],HOMETRACE[lt][0][1],   
                                HOMETRACE[lt][1][0],HOMETRACE[lt][1][1]   
                        );   
        }   
        for(lt = 0; lt < 5; lt++){   
                if(ENEMYEV[lt] == 0)   
                        ENEMYVDIRECTION[lt] = -1;   
                else   
                        ENEMYVDIRECTION[lt] = lineAngel(   
                                ENEMYTRACE[lt][0][0],ENEMYTRACE[lt][0][1],   
                                ENEMYTRACE[lt][1][0],ENEMYTRACE[lt][1][1]   
                        );   
        }   
        if(BALLEV[0] == 0)   
                        BALLVDIRECTION[0] = -1;   
        else   
                BALLVDIRECTION[0] = lineAngel(   
                        BALLTRACE[0][0][0],BALLTRACE[0][0][1],   
                        BALLTRACE[0][1][0],BALLTRACE[0][1][1]   
                );   
}   
   
double f(double k, double x0, double y0, double x){   
        //   
        return k*x - k*x0 + y0;   
}   
   
double fn(double k,double x0,double y0,double y){   
        //   
        return x0 + (y - y0)/k;   
}   
   
double l(double x1, double y1, double x2, double y2){   
        //   
        double dx,dy;   
           
        dx = x1 - x2;   
        dy = y1 - y2;   
        return sqrt(dx*dx + dy*dy);   
}   
   
void predictBall(double xs){   
        //xs 秒后球的位置   
        double dx, dy;   
   
        dx = BALLTRACE[5][1][0] - BALLTRACE[5][0][0];   
        dy = BALLTRACE[5][1][1] - BALLTRACE[5][0][1];   
        PBP[0] = ENV->currentBall.pos.x + dx*xs*30;   
        PBP[1] = ENV->currentBall.pos.y + dy*xs*30;   
}   
   
void rotation(){   
        //   
        int lt = 0;   
   
        if(HOMEROTATION[0][0] == -1){   
                for(lt= 0; lt <5; lt++){   
                        HOMEROTATION[lt][0] = robotAngel(&ENV->home[lt],lt);   
                        HOMEROTATION[lt][1] = robotAngel(&ENV->home[lt],lt);   
                }   
                for(lt= 0; lt <5; lt++){   
                        ENEMYROTATION[lt][0] = robotAngel(&ENV->home[lt],lt);   
                        ENEMYROTATION[lt][1] = robotAngel(&ENV->home[lt],lt);   
                }   
        }   
        else{   
                for(lt = 0; lt< 5; lt++){   
                HOMEROTATION[lt][0] = HOMEROTATION[lt][1];   
                HOMEROTATION[lt][1] = robotAngel(&ENV->home[lt],lt);   
                ENEMYROTATION[lt][0] = ENEMYROTATION[lt][1];   
                ENEMYROTATION[lt][1] = robotAngel(&ENV->home[lt],lt);   
                }   
        }   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f\n",HOMEROTATION[3][1] - HOMEROTATION[3][0]);   
        //fclose(DEBUGFILE);   
}   
   
bool isStill(Robot *robot,int rID){   
        //   
        if(HOMEEV[rID] < 1 && fabs(HOMEROTATION[rID][1] - HOMEROTATION[rID][0])<1)   
                return true;   
        else   
                return false;   
}   
   
int direction(double ra,double la){   
        //   
        int dire;   
        double beta;   
   
        beta = fabs(ra - la); //计算夹角   
        if(ra - la >0 && beta < 180)   
                dire = 1;   
        else if(ra - la >0 && beta > 180)   
                dire = -1;   
        else if(ra - la <0 && beta < 180)   
                dire = -1;    
        else if(ra - la <0 && beta > 180)   
                dire = 1;   
        return dire;   
}   
   
bool canKShoot(Robot *robot, int rID){   
        //是否可以用头撞球进 can kick shoot   
        double rx, ry, bx, by; //ball x,y and robot x,y   
        double k, y; //y 是直线与 x=6.8118,93.4259的交点   
        double length;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        length = sqrt((rx - bx)*(rx - bx) + (ry - by)*(ry - by));   
        if(fabs(bx - rx) < 0.1)   
                return false;   
        k = (by - ry)/(bx - rx);   
        if(WHO ==1){   
                if(length > 3 && rx - bx > 2.517){ //length 的作用 ？   
                        y = f(k, bx, by, 6.8118);   
                        if(y > 33.9 && y < 49.6)   
                                return true;   
                        else   
                                return false;   
                }   
                else   
                        return false;   
        }   
        else {   
                if(length > 3 && bx - rx > 2.517){ //length 的作用 ？   
                        y = f(k, bx, by, 93.4259);   
                        if(y > 33.9 && y < 49.6)   
                                return true;   
                        else   
                                return false;   
                }   
                else   
                        return false;   
        }   
}   
   
bool canTShoot(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double X; //界限   
        double cy; //与门线交点的 y 坐标   
        double  k; //斜率   
        int dire; //旋转方向   
   
        cy = 0;   
        k = 0;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        if(WHO == 1){   
                X = 27.81;   
                if(rx < X){   
                        if(dx>0 && dx<(BALLD/2+sqrt(2)*ROBOTWIDTH/2) && fabs(dy)<ROBOTWIDTH/2){ //球在左边   
                                if(ry > (GTOPY + GBOTY)/2){   
                                        k = sqrt(3)/3;   
                                        dire = -1;   
                                }   
                                else{   
                                        k = -1*sqrt(3)/3;   
                                        dire = 1;   
                                }   
                                cy = f(k,bx,by,GLEFT);   
                        }   
                        else if(dy<0 && dy>-1*(BALLD/2+sqrt(2)*ROBOTWIDTH/2) && fabs(dx)<ROBOTWIDTH/2){ //球在上边   
                                k = -1*sqrt(3)/3;   
                                dire = -1;   
                                cy = f(k,bx,by,GLEFT);   
                        }   
                        else if(dy>0 && dy<(BALLD/2+sqrt(2)*ROBOTWIDTH/2) && fabs(dx)<ROBOTWIDTH/2){ //球在下边   
                                k = sqrt(3)/3;   
                                dire = 1;   
                                cy = f(k,bx,by,GLEFT);   
                        }   
                        turn(robot,rID,dire);   
                        if(cy > GBOTY && cy < GTOPY)   
                                return true;   
                        else   
                                return false;   
                }   
                else   
                        return false;   
        }   
        else{   
                X = 70.12;   
                if(rx > X){   
                        if(dx<0 && dx>-1*(BALLD/2+sqrt(2)*ROBOTWIDTH/2) && fabs(dy)<ROBOTWIDTH/2){ //球在右边   
                                if(ry > (GTOPY + GBOTY)/2){   
                                        dire = 1;   
                                        k = -1*sqrt(3)/3;   
                                }   
                                else{   
                                        k = sqrt(3)/3;   
                                        dire = -1;   
                                }   
                                cy = f(k,bx,by,GRIGHT);   
                        }   
                        else if(dy<0 && dy>-1*(BALLD/2+sqrt(2)*ROBOTWIDTH/2) && fabs(dx)<ROBOTWIDTH/2){ //球在上边   
                                k = sqrt(3)/3;   
                                dire = 1;   
                                cy = f(k,bx,by,GRIGHT);   
                        }   
                        else if(dy>0 && dy<(BALLD/2+sqrt(2)*ROBOTWIDTH/2) && fabs(dx)<ROBOTWIDTH/2){ //球在下边   
                                k = -1*sqrt(3)/3;   
                                dire = -1;   
                                cy = f(k,bx,by,GRIGHT);   
                        }   
                        turn(robot,rID,dire);   
                        if(cy > GBOTY && cy < GTOPY)   
                                return true;   
                        else   
                                return false;   
                }   
                else   
                        return false;   
        }   
}   
   
void turn(Robot *robot,int rID,int dire){   
        //   
        if(dire ==1)   
                run(robot,rID,125,-125);   
        else if(dire == -1)   
                run(robot,rID,-125,125);   
        else   
                run(robot,rID,0,0); //error   
}   
   
void goBackTo(Robot *robot, int rID, double x,double y){   
        //   
        double rx,ry;   
        double alpha,ra,beta; //直线、机器人角度,夹角   
        int dire; //1 正 -1逆 时针   
        int vl,vr;   
        double length;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        alpha = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot, rID);   
        ra +=180.0;   
        if(ra >= 360.0)   
                ra -=360.0;   
        beta = fabs(ra - alpha); //计算夹角   
        dire = direction(ra, alpha);   
        if(beta > 180)   
                beta = 360 - beta;   
        else    
                beta = beta;   
        if(dire == 1){   
                vr = -1*125;   
                vl = int(-125 + beta*25/18); //假定在 3 个周期内完成转动   
                if(vl >= 0)   
                        vl = -1;   
                if(beta < 1)   
                        vl = -125;   
        }   
        if(dire == -1){   
                vl = -1*125;   
                vr = int(-125 + beta*25/18); //假定在 3 个周期内完成转动   
                if(vr >= 0)   
                        vr = -1;   
                if(beta < 1)   
                        vr = -125;   
        }   
        run(robot, rID,vl,vr);   
        length = l(x,y,rx,ry);   
        if(beta > 90.0)   
                beta = 180.0 - beta;   
        if(length < 3 && beta > 30.0)   
                sRotate(robot,rID,alpha);   
        beta = fabs(HOMEVDIRECTION[rID] - ra);   
        if(HOMEVDIRECTION[rID] != -1)   
                if((beta>180.0?360-beta:beta) > 90.0)   
                        run(robot,rID,0,0);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d %d %d %f %d\n",rID,vl,vr,beta,HOMEEV[rID]);   
        //fclose(DEBUGFILE);   
}   
   
void goTo(Robot *robot, int rID, double x, double y){   
        //   
        double rx,ry;   
        double alpha,ra,beta; //直线、机器人角度,夹角   
        int dire; //1 正 -1逆 时针   
        int vl,vr;   
        double length;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        alpha = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot, rID);   
        beta = fabs(ra - alpha); //计算夹角   
        dire = direction(ra,alpha);   
        if(beta > 180)   
                beta = 360 - beta;   
        else    
                beta = beta;   
        if(dire == 1){   
                vl = 125;   
                vr = int(125 - beta*25/18); //假定在 3 个周期内完成转动   
                if(vr <= 0)   
                        vr = 1;   
                if(beta < 1)   
                        vr = 125;   
        }   
        else if(dire == -1){   
                vr = 125;   
                vl = int(125 - beta*25/18); //假定在 3 个周期内完成转动   
                if(vl <= 0)   
                        vl = 1;   
                if(beta < 1)   
                        vl = 125;   
        }   
        run(robot, rID,vl,vr);   
        length = l(x,y,rx,ry);   
        if(beta > 90.0)   
                beta = 180.0 - beta;   
        if(length < 3 && beta > 30.0)   
                sRotate(robot,rID,alpha);   
        beta = fabs(HOMEVDIRECTION[rID] - ra);   
        if(HOMEVDIRECTION[rID] != -1)   
                if((beta>180.0?360-beta:beta) > 90.0)   
                        run(robot,rID,0,0);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d %d %d %f %d %f\n",rID,vl,vr,beta,HOMEEV[rID],HOMEVDIRECTION[rID]);   
        //fclose(DEBUGFILE);   
}   
   
void sGo(Robot *robot, int rID, double x, double y){   
        //   
        double rx,ry;   
        double ra,la; //robot angel,line angel   
        double beta;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        la = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot, rID);   
        beta = fabs(ra - la);   
        if(beta > 180.0)   
                beta = 360.0 - beta;   
        if(beta < 90.0)   
                goTo(robot,rID,x,y);   
        else   
                goBackTo(robot,rID,x,y);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f\n",ra,la);   
        //fclose(DEBUGFILE);   
}   
   
void to(Robot *robot, int rID, double x, double y){   
        //   
        double rx,ry;   
        double length;   
        double alpha,ra,beta; //直线、机器人角度,夹角   
        int dire; //1 正 -1逆 时针   
        int vl,vr;   
        int v0;   
        double le; //误差   
   
        le = 0.3;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        length = l(rx,ry,x,y);   
        alpha = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot,rID);   
        beta = fabs(ra - alpha); //计算夹角   
        dire = direction(ra,alpha);   
        if(beta > 180)   
                beta = 360 - beta;   
        else    
                beta = beta;   
        if(length > 8.0)   
                v0 = 125;   
        else if(length > le){   
                if(HOMEEV[rID] >= int(11*length))   
                        v0 = 1;   
                else if(HOMEEV[rID] <= int(length))   
                        v0 = int(125*length);   
                else if(HOMEEV[rID] <= int(2*length))   
                        v0 = int(100*length);   
                else if(HOMEEV[rID] <= int(5*length))   
                        v0 = int(80*length);   
                else if(HOMEEV[rID] <= int(8*length))   
                        v0 = int(50*length);   
                else   
                        v0 = int(10*length) +1;   
                if(v0 > 125)   
                v0 = 125;   
        }   
        else if(length < le)   
                v0 = 0;   
        if(length > le){   
                if(dire == 1){   
                        vl = v0;   
                        vr = int(v0 - beta*25/36); //假定在 6 个周期内完成转动   
                        if(vr <= 0)   
                                vr = 1;   
                        if(beta < 1.0)   
                                vr = v0;   
                }   
                else if(dire == -1){   
                        vr = v0;   
                        vl = int(v0 - beta*25/36); //假定在 6 个周期内完成转动   
                        if(vl <= 0)   
                                vl = 1;   
                        if(beta < 1.0)   
                                vl = v0;   
                }   
                run(robot, rID,vl,vr);   
        }   
        else{   
                run(robot,rID,0,0);   
        }   
        if(beta > 90.0)   
                beta = 180.0 - beta;   
        if(length < 3 && beta > 30.0)   
                sRotate(robot,rID,alpha);   
        beta = fabs(HOMEVDIRECTION[rID] - ra);   
        if(HOMEVDIRECTION[rID] != -1)   
                if((beta>180.0?360-beta:beta) > 90.0)   
                        run(robot,rID,0,0);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d %d %f %d %f %f\n",dire, HOMEEV[rID],length,v0,HOMEVDIRECTION[rID] ,ra);   
        //fclose(DEBUGFILE);   
}   
void backTo(Robot *robot, int rID, double x, double y){   
        //   
        double rx,ry;   
        double length;   
        double alpha,ra,beta; //直线、机器人角度,夹角   
        int dire; //1 正 -1逆 时针   
        int vl,vr;   
        int v0;   
        double le; //误差   
   
        le = 0.3;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        length = l(rx,ry,x,y);   
        alpha = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot,rID);   
        ra += 180.0;   
        if(ra >= 360.0)   
                ra = ra - 360.0;   
        beta = fabs(ra - alpha); //计算夹角   
        dire = direction(ra,alpha);   
        if(beta > 180)   
                beta = 360 - beta;   
        else    
                beta = beta;   
        if(length > 8.0)   
                v0 = -125;   
        else if(length > le){   
                if(HOMEEV[rID] >= int(11*length))   
                        v0 = -3;   
                else if(HOMEEV[rID] <= int(length))   
                        v0 = int(-125*length);   
                else if(HOMEEV[rID] <= int(2*length))   
                        v0 = int(-100*length);   
                else if(HOMEEV[rID] <= int(5*length))   
                        v0 = int(-80*length);   
                else if(HOMEEV[rID] <= int(8*length))   
                        v0 = int(-50*length);   
                else   
                        v0 = int(-10*length) - 1;   
                if(v0 < -125)   
                        v0 = -125;   
        }   
        else if(length < le)   
                v0 = 0;   
        if(length > le){   
                if(dire == 1){   
                        vr = v0;   
                        vl = int(v0 + beta*25/36); //假定在 6 个周期内完成转动   
                        if(vl >= 0)   
                                vl = -1;   
                        if(beta < 1.0)   
                                vl = v0;   
                }   
                else if(dire == -1){   
                        vl = v0;   
                        vr = int(v0 + beta*25/36); //假定在 6 个周期内完成转动   
                        if(vr >= 0)   
                                vr = -1;   
                        if(beta < 1.0)   
                                vr = v0;   
                }   
                run(robot, rID,vl,vr);   
        }   
        else{   
                run(robot,rID,0,0);   
        }   
        if(beta > 90.0)   
                beta = 180.0 - beta;   
        if(length < 3 && beta > 30.0)   
                sRotate(robot,rID,alpha);   
        beta = fabs(HOMEVDIRECTION[rID] - ra);   
        if(HOMEVDIRECTION[rID] != -1)   
                if((beta>180.0?360.0-beta:beta) > 90.0)   
                        run(robot,rID,0,0);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d %d %f %d %f %f %f %d %d\n",dire, HOMEEV[rID],length,v0,beta,ra,alpha,vl,vr);   
        //fclose(DEBUGFILE);   
}   
void sTo(Robot *robot, int rID, double x, double y){   
        //   
        double rx,ry;   
        double ra,la; //robot angel,line angel   
        double beta;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        la = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot, rID);   
        beta = fabs(ra - la);   
        if(beta > 180.0)   
                beta = 360.0 - beta;   
        if(beta < 90.0)   
                to(robot,rID,x,y);   
        else   
                backTo(robot,rID,x,y);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f\n",ra,la);   
        //fclose(DEBUGFILE);   
}   
   
void rotateTo(Robot *robot, int rID, double x, double y){   
        //   
        int dire; //旋转方向   
        double rx,ry,ra; //机器人坐标和角度   
        double la,beta; //线角度   
        int v0;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        ra = robotAngel(robot,rID);   
        la = lineAngel(rx,ry,x,y);   
        dire = direction(ra,la);   
        beta = ra - la;   
        if(beta < -180.0)   
                beta += 360.0;   
        if(beta > 180.0)   
                beta = 360.0 - beta;   
        v0 = int(fabs(beta)*5/12); //速度选择   
        if(v0 < 3)   
                v0 =3;   
        else if(v0 > 60)   
                v0 = 60;   
        if(dire == 1)   
                run(robot, rID,v0,-1*v0);   
        else if(dire == -1)   
                run(robot, rID, -1*v0,v0);   
        if(fabs(beta) < 1.5)   
                run(robot,rID,0,0);   
        if(HOMEDISPLACEMENT[rID] > 0.05)   
                run(robot,rID,0,0);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%d %f\n",dire,beta);   
        //fclose(DEBUGFILE);   
}   
   
void rotateBackTo(Robot *robot,int rID, double x,double y){   
        //   
        double rx,ry;   
        double dx,dy;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        dx = 2*rx - x;   
        dy = 2*ry - y;   
        rotateTo(robot,rID,dx,dy);   
}   
   
void sRotate(Robot *robot, int rID,double x, double y){   
        //   
        double rx,ry;   
        double ra,la; //robot angel,line angel   
        double beta;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        la = lineAngel(rx,ry,x,y);   
        ra = robotAngel(robot, rID);   
        beta = fabs(ra - la);   
        if(beta > 180.0)   
                beta = 360.0 - beta;   
        if(beta < 90.0)   
                rotateTo(robot,rID,x,y);   
        else   
                rotateBackTo(robot,rID,x,y);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f\n",ra,la);   
        //fclose(DEBUGFILE);   
}   
   
void sRotate(Robot *robot, int rID,double angel){   
        //   
        double dx;   
        double dy,k;   
   
        if(fabs(angel - PI/2) < 0.05){   
                dx = 0;   
                dy = 50;   
        }   
        else if(fabs(angel - PI*3/2) < 0.05){   
                dx = 0;   
                dy = -50;   
        }   
        else{   
                k = tanf(angel/180.0*PI);   
                dx = 100;   
                dy = dx*k;   
        }   
        sRotate(robot,rID,robot->pos.x + dx,robot->pos.y + dy);   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f %f %f %f\n",dx,dy,angel,tanf(angel/180.0*PI),robotAngel(robot,rID));   
        //fclose(DEBUGFILE);   
}   
   
void order(){   
        //   
        double rx[5],ry[5],len[5];   
        double bx,by;   
        int lt,ll;   
        int temp;   
   
        lt = 0;   
        ll = 0;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        for(lt = 0; lt < 5; lt++){   
                rx[lt] = ENV->home[lt].pos.x;   
                ry[lt] = ENV->home[lt].pos.y;   
                len[lt] = l(rx[lt], ry[lt], bx, by);   
        }   
        for(lt = 0; lt < 5; lt++){   
                for(ll = lt+1; ll < 5; ll++){   
                        if(len[ORDER[lt]] > len[ORDER[ll]]){   
                                temp = ORDER[ll];   
                                ORDER[ll] = ORDER[lt];   
                                ORDER[lt] = temp;   
                        }   
                }   
        }   
        for(lt = 0; lt< 5; lt++){   
                for(ll = 0;ll <5; ll++){   
                        if(ORDER[ll] == lt)   
                                RORDER[lt] = ll;   
                }   
        }   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %f %f %f %f\n",len[0],len[1],len[2],len[3],len[4]);   
        //fprintf(DEBUGFILE, "%d %d %d %d %d\n",ORDER[0],ORDER[1],ORDER[2],ORDER[3],ORDER[4]);   
        //fclose(DEBUGFILE);   
}   
   
bool hasEnemyNear(double x, double y){   
        //   
        int lt = 0;   
        double rx,ry,len;   
   
        for(lt = 0; lt < 5; lt++){   
                rx = ENV->opponent[lt].pos.x;   
                ry = ENV->opponent[lt].pos.y;   
                len = l(x,y,rx,ry);   
                if(len < sqrt(2)*ROBOTWIDTH/2)   
                        return true;   
        }   
        return false;   
}   
   
bool hasEnemyBetween(double x1,double y1,double x2,double y2){   
        //   
        double space; //步长   
        double k; //斜率   
        double cx,cy; //current x,y   
   
        cx = x1;   
        cy = y1;   
        space = ROBOTWIDTH/2; //??   
        k = (y2 - y1)/(x2 - x1); //?? x2 == x1   
        if(x2 < x1){   
                space *= -1;   
                while(cx > x2){   
                        if(hasEnemyNear(cx,cy))   
                                return true;   
                        cx += space;   
                        cy = cy + space*k;   
                }   
                return false;   
        }   
        else if(x2 > x1){   
                while(cx < x2){   
                        if(hasEnemyNear(cx,cy))   
                                return true;   
                        cx += space;   
                        cy = cy + space*k;   
                }   
                return false;   
        }   
        return false;   
}   
   
bool hasEnemyIn(double x1,double y1,double x2,double y2){   
        //   
        double rx,ry;   
        int lt = 0;   
   
        for(lt = 0; lt < 5; lt++){   
                rx = ENV->opponent[lt].pos.x;   
                ry = ENV->opponent[lt].pos.y;   
                if((rx > x1 && rx <x2) || (rx > x2 && rx <x1)){ //== ??   
                        if((ry > y1 && ry <y2) || (ry > y2 && ry <y1))   
                                return true;   
                }   
        }   
        return false;   
}   
   
void turnKick(Robot *robot,int rID,int where){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        if(dy < 0 && dy > -1*(BALLD/2 + sqrt(2)*ROBOTWIDTH/2) && fabs(dx) < ROBOTWIDTH/2){   
                if(where == 1)   
                        turn(robot,rID,1);   
                else if(where == 2)   
                        turn(robot,rID,-1);   
        } //右   
        else if(dy > 0 && dy < (BALLD/2 + sqrt(2)*ROBOTWIDTH/2) && fabs(dx) < ROBOTWIDTH/2){   
                if(where == 3)   
                        turn(robot,rID,1);   
                else if(where == 4)   
                        turn(robot,rID,-1);   
        } //下   
        if(dx > 0 && dx < (BALLD/2 + sqrt(2)*ROBOTWIDTH/2) && fabs(dy) < ROBOTWIDTH/2){   
                if(where == 2)   
                        turn(robot,rID,1);   
                else if(where == 3)   
                        turn(robot,rID,1);   
        } //左   
        else if(dx < 0 && dx > -1*(BALLD/2 + sqrt(2)*ROBOTWIDTH/2) && fabs(dy) < ROBOTWIDTH/2){   
                if(where == 1)   
                        turn(robot,rID,-1);   
                else if(where == 4)   
                        turn(robot,rID,1);   
        } //右   
}   
   
void keeper(Robot *robot, int rID,double x,double y,double angel){   
        //   
        double rx,ry,length; //robot x,y   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        length = l(x,y,rx,ry);   
        if(length > 0.3)   
                sTo(robot,rID,x,y);   
        else{   
                if(HOMEEV[rID] < 1)   
                        sRotate(robot,rID,angel);   
                if(HOMEEV[rID] >= 1)   
                        run(robot,rID,0,0);   
        }   
        //DEBUGFILE = fopen("debug.txt", "a");   
        //fprintf(DEBUGFILE, "%f %d\n", length,HOMEEV[rID]);   
        //fclose(DEBUGFILE);   
           
}   
   
void pushHelper(Robot *robot,int rID){   
        //   
        double bx,by,rx,ry; //ball robot x,y   
        double x1,x2; //边界,x2 > x1   
        double dx,dy;   
   
        x1 = FLEFTX + ROBOTWIDTH;   
        x2 = FRIGHTX - ROBOTWIDTH;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        if(WHO ==1){ //blue   
                if(bx < x1){   
                        if(by < GBOTY){   
                                if(dy <= -3/2*ROBOTWIDTH && fabs(dx) < ROBOTWIDTH*2/3)   
                                        sGo(robot,rID,bx,by);   
                                else if(dy < -2*ROBOTWIDTH)   
                                        sGo(robot,rID,bx,by);   
                                else   
                                        sGo(robot,rID,bx + BALLD/2,by - 2*ROBOTWIDTH);   
                        }   
                        else if(by > GTOPY){   
                                if(dy >= 3/2*ROBOTWIDTH && fabs(dx) < ROBOTWIDTH*2/3)   
                                        sGo(robot,rID,bx,by);   
                                else if(dy < 2*ROBOTWIDTH)   
                                        sGo(robot,rID,bx,by);   
                                else   
                                        sGo(robot,rID,bx,by + 2*ROBOTWIDTH);   
                        }   
                }   
        }   
        else{   
                if(bx > x2){   
                        if(by < GBOTY){   
                                if(dy <= -3/2*ROBOTWIDTH && fabs(dx) < ROBOTWIDTH*2/3)   
                                        sGo(robot,rID,bx,by);   
                                else if(dy < -2*ROBOTWIDTH)   
                                        sGo(robot,rID,bx,by);   
                                else   
                                        sGo(robot,rID,bx + BALLD/2,by - 2*ROBOTWIDTH);   
                        }   
                        else if(by > GTOPY){   
                                if(dy >= 3/2*ROBOTWIDTH && fabs(dx) < ROBOTWIDTH*2/3)   
                                        sGo(robot,rID,bx,by);   
                                else if(dy < 2*ROBOTWIDTH)   
                                        sGo(robot,rID,bx,by);   
                                else   
                                        sGo(robot,rID,bx,by + 2*ROBOTWIDTH);   
                        }   
                }   
        }   
}   
   
void goalie(Robot *robot,int rID){   
        //   
        double X;   
        double bx,by,rx,ry;   
        double desX,desY; //守门员应该在的地方   
        double mx,my; //球场中点 x,y   
        double k; //斜率   
   
        mx = (FLEFTX + FRIGHTX)/2;   
        my = (FBOT + FTOP)/2;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        if(WHO ==1){ //for blue   
                X = 93.0 - ROBOTWIDTH/2;   
                if(bx < 70.12){   
                        k = (my - by)/(GRIGHT - bx);   
                        desY = f(k,bx,by,X);   
                        desX = X;   
                        keeper(robot,rID,desX,desY,270.0);   
                }   
                else if(bx >= 70.12 && bx < 93.0 - ROBOTWIDTH){   
                        if(BALLVDIRECTION[0] > 91.0 && BALLVDIRECTION[0] < 269.0){   
                                k = (my - by)/(GRIGHT - bx);   
                                desY = f(k,bx,by,X);   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                desX = X;   
                                keeper(robot,rID,desX,desY,270.0);   
                        }   
                        else if(fabs(BALLVDIRECTION[0] - 90.0)<1 || fabs(BALLVDIRECTION[0] - 270.0)<1){   
                                desY = by;   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                desX = X;   
                                keeper(robot,rID,desX,desY,270.0);   
                        }   
                        else {   
                                k = tanf(BALLVDIRECTION[0]/180.0*PI);   
                                desX = X;   
                                desY = f(k,bx,by,X);   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                keeper(robot,rID,desX,desY,270.0);   
                        }   
                        if(BALLEV[0] == 0){   
                                desY = by;   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                keeper(robot,rID,X,desY,270.0);   
                        }   
                }   
                else if(bx >= 93.0 - ROBOTWIDTH){   
                        desX = X;   
                        if(by > 58.56 + BALLD/2)   
                                keeper(robot,rID,desX,GTOPY + 2,270.0);   
                        else if(by < 27.89 - BALLD/2)   
                                keeper(robot,rID,desX,GBOTY- 2,270.0);   
                        else if(by >= 52.92 && by <= 58.56 + BALLD/2){   
                                if(hasEnemyNear(X,51.30) && by - ry > ROBOTWIDTH)   
                                        keeper(robot,rID,desX,GTOPY + 2,270.0);   
                                else   
                                        sGo(robot,rID,X,FTOP);   
                        }   
                        else if(by <= 33.71 && by >= 27.89 - BALLD/2){   
                                if(hasEnemyNear(X,30.80)&& ry - by > ROBOTWIDTH)   
                                        keeper(robot,rID,desX,GBOTY- 2,270.0);   
                                else   
                                        sGo(robot,rID,X,FBOT);   
                        }   
                        else if(by >33.71 && by < 52.92){   
                                if(by > ry)   
                                        sGo(robot,rID,X,FTOP);   
                                else if(by < ry)   
                                        sGo(robot,rID,X,FBOT);   
                        }   
                } //卡住归位   
                if(rx > 93.0 - ROBOTWIDTH/2 + 0.8 && (49.68 - ry < 5.0 || ry - 33.93 < 5.0)){   
                        if(ry < my)   
                                sTo(robot,rID,93.0 - ROBOTWIDTH,GBOTY + ROBOTWIDTH*3/2);   
                        else if(ry > my)   
                                sTo(robot,rID,93.0 - ROBOTWIDTH,GTOPY - ROBOTWIDTH*3/2);   
                }   
                if(!hasEnemyIn(80.43,27.89,FRIGHTX,58.56)){   
                        if(bx > 80.43 && by > 27.98 && by < 58.56){   
                                if(rx > bx)   
                                        sGo(robot,rID,bx+ 0.5,by);   
                        }   
                }   
        } //for yellow   
        else{   
                X = 7.23 + ROBOTWIDTH/2;   
                if(bx > 27.81){   
                        k = (my - by)/(GLEFT - bx);   
                        desY = f(k,bx,by,X);   
                        desX = X;   
                        keeper(robot,rID,desX,desY,270.0);   
                }   
                else if(bx >= 7.23 + ROBOTWIDTH && bx <= 27.81){   
                        if(BALLVDIRECTION[0] < 89.0 || BALLVDIRECTION[0] > 271.0){   
                                k = (my - by)/(GLEFT - bx);   
                                desY = f(k,bx,by,X);   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                desX = X;   
                                keeper(robot,rID,desX,desY,270.0);   
                        }   
                        else if(fabs(BALLVDIRECTION[0] - 90.0)<1 || fabs(BALLVDIRECTION[0] - 270.0)<1){   
                                desY = by;   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                desX = X;   
                                keeper(robot,rID,desX,desY,270.0);   
                        }   
                        else{   
                                k = tanf(BALLVDIRECTION[0]/180.0*PI);   
                                desX = X;   
                                desY = f(k,bx,by,X);   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                keeper(robot,rID,desX,desY,270.0);   
                        }   
                        if(BALLEV[0] == 0){   
                                desY = by;   
                                if(desY > GTOPY+2)   
                                        desY = GTOPY + 2;   
                                else if(desY < GBOTY- 2)   
                                        desY = GBOTY- 2;   
                                keeper(robot,rID,X,desY,270.0);   
                        }   
                }   
                else if(bx <= 7.23 + ROBOTWIDTH){   
                        desX = X;   
                        if(by > 58.56 + BALLD/2)   
                                keeper(robot,rID,desX,GTOPY + 2,270.0);   
                        else if(by < 27.89 - BALLD/2)   
                                keeper(robot,rID,desX,GBOTY- 2,270.0);   
                        else if(by >= 52.92 && by <= 58.56 + BALLD/2){   
                                if(hasEnemyNear(X,51.80) && by - ry > ROBOTWIDTH)   
                                        keeper(robot,rID,desX,GTOPY + 2,270.0);   
                                else   
                                        sGo(robot,rID,X,FTOP);   
                        }   
                        else if(by <= 33.71 && by >= 27.89 - BALLD/2){   
                                if(hasEnemyNear(X,30.30) && ry - by > ROBOTWIDTH)   
                                        keeper(robot,rID,desX,GBOTY- 2,270.0);   
                                else   
                                        sGo(robot,rID,X,FBOT);   
                        }   
                        else if(by >33.71 && by < 52.92){   
                                if(by > ry)   
                                        sGo(robot,rID,X,FTOP);   
                                else if(by < ry)   
                                        sGo(robot,rID,X,FBOT);   
                        }   
                } //卡住归位   
                if(rx < 7.23 + ROBOTWIDTH/2 - 0.8 && (49.68 - ry < 5.0 || ry - 33.93 < 5.0) ){   
                        if(ry < my)   
                                sTo(robot,rID,7.23 + ROBOTWIDTH,GBOTY + ROBOTWIDTH*3/2);   
                        else if(ry > my)   
                                sTo(robot,rID,7.23 +  ROBOTWIDTH,GTOPY - ROBOTWIDTH*3/2);   
                }   
                if(!hasEnemyIn(FLEFTX,27.89,19.80,58.56)){   
                        if(bx < 19.80 && by > 27.98 && by < 58.56){   
                                if(rx < bx)   
                                        sGo(robot,rID,bx+ 0.5,by);   
                        }   
                }   
        }   
}   
   
void toBRight(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double ax,ay;   
   
        ax = 10;   
        ay = 2*ROBOTWIDTH;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        predictBall(1/10);   
        if(dx > - 3/2*ROBOTWIDTH && dx < 2){   
                if(dy < 0){   
                        if(PBP[1] > FBOT + 2*ROBOTWIDTH)   
                                sGo(robot,rID,PBP[0],PBP[1] - ay);   
                        else   
                                sGo(robot,rID,PBP[0],PBP[1] + ay);   
                }   
                else{   
                        sGo(robot,rID,PBP[0],PBP[1] + ay);   
                }   
                if(dy > 3/2*ROBOTWIDTH || dy < -3/2*ROBOTWIDTH){   
                        sGo(robot,rID,PBP[0] + ax + 2,PBP[1] );   
                }   
        }   
        else if(dx <= -3/2*ROBOTWIDTH){   
                if(dy > 3/2*ROBOTWIDTH || dy < -3/2*ROBOTWIDTH)   
                        sGo(robot,rID,PBP[0] + ax + 2,PBP[1] + ay/2);   
                else if(dy > -3/2*ROBOTWIDTH && dy < 0){   
                        if(PBP[1] > FBOT + 3/2*ROBOTWIDTH)   
                                sGo(robot,rID,PBP[0] + ax + 2, PBP[1] - ay);   
                        else   
                                sGo(robot,rID,PBP[0],PBP[1] + ay);   
                }   
                else if(dy > 0 && dy < 3/2*ROBOTWIDTH)   
                        sGo(robot,rID,PBP[0]  + ax + 2,PBP[1] + ay);   
        }   
        else if(dx >= 10)   
                run(robot,rID,0,0);   
}   
   
void toBLeft(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double ax,ay;   
   
        ax = 10;   
        ay = 2*ROBOTWIDTH;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        predictBall(1/10);   
        if(dx < 3/2*ROBOTWIDTH && dx > -2){   
                if(dy < 0){   
                        if(PBP[1] > FBOT + 2*ROBOTWIDTH)   
                                sGo(robot,rID,PBP[0],PBP[1] - ay);   
                        else   
                                sGo(robot,rID,PBP[0],PBP[1] + ay);   
                }   
                else{   
                        sGo(robot,rID,PBP[0],PBP[1] + ay);   
                }   
                if(dy >= 3/2*ROBOTWIDTH || dy <= -3/2*ROBOTWIDTH){   
                        sGo(robot,rID,PBP[0] - ax - 2,PBP[1] );   
                }   
        }   
        else if(dx >= 3/2*ROBOTWIDTH){   
                if(dy > 3/2*ROBOTWIDTH || dy < -3/2*ROBOTWIDTH)   
                        sGo(robot,rID,PBP[0] - ax - 2,PBP[1] + ay/2);   
                else if(dy > -3/2*ROBOTWIDTH && dy < 0){   
                        if(PBP[1] > FBOT + 3/2*ROBOTWIDTH)   
                                sGo(robot,rID,PBP[0] - ax - 2, PBP[1] - ay);   
                        else   
                                sGo(robot,rID,PBP[0],PBP[1] + ay);   
                }   
                else if(dy > 0 && dy < 3/2*ROBOTWIDTH)   
                        sGo(robot,rID,PBP[0]  - ax - 2,PBP[1] + ay);   
        }   
        else if(dx <= -10)   
                run(robot,rID,0,0);   
}   
   
void toBUp(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        if(fabs(dx) > 5){   
                if(dy > 0)   
                        sGo(robot,rID,bx,by + 3/2*ROBOTWIDTH);   
                else if(dy < 0)   
                        sGo(robot,rID,bx,by + 3/2*ROBOTWIDTH);   
        }   
        else if(dx > 0 && dx < 5){   
                if(dy >= 1)   
                        sGo(robot,rID,bx,by + 3/2*ROBOTWIDTH);   
                else if(dy < 1)   
                        sGo(robot,rID,bx + 6,by -0.5);   
        }   
        else if(dx < 0 && dx > -5){   
                if(dy >= 1)   
                        sGo(robot,rID,bx,by + 3/2*ROBOTWIDTH);   
                else if(dy < 1)   
                        sGo(robot,rID,bx - 6,by -0.5);   
        }   
}   
   
void toBDown(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        if(fabs(dx) > 5){   
                if(dy > 0)   
                        sGo(robot,rID,bx,by - 3/2*ROBOTWIDTH);   
                else if(dy < 0)   
                        sGo(robot,rID,bx,by - 3/2*ROBOTWIDTH);   
        }   
        else if(dx > 0 && dx < 5){   
                if(dy <= -1)   
                        sGo(robot,rID,bx,by - 3/2*ROBOTWIDTH);   
                else if(dy > -1)   
                        sGo(robot,rID,bx + 6,by +0.5);   
        }   
        else if(dx < 0 && dx > -5){   
                if(dy <= -1)   
                        sGo(robot,rID,bx,by - 3/2*ROBOTWIDTH);   
                else if(dy > -1)   
                        sGo(robot,rID,bx - 6,by +0.5);   
        }   
}   
   
void leftSoccer(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double bvd,bv;   
        double desX,desY;   
        double L; //活动边界   
        double revise;   
   
        revise = 5.0;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        bvd = BALLVDIRECTION[0];   
        bv = BALLEV[0];   
        if(bv > 100 || l(rx,ry,bx,by) > 15)   
                predictBall(1/8);   
        else if(bv > 80 || l(rx,ry,bx,by) > 10)   
                predictBall(1/15);   
        else if(bv > 50 || l(rx,ry,bx,by) > 7)   
                predictBall(1/25);   
        else   
                predictBall(1/40);   
        if(l(rx,ry,bx,by) < 3)   
                predictBall(0.0);   
        if(WHO ==1){   
                L = 33.71 + revise;   
                if(by < L){ //球在范围   
                        if(rx > bx+ 2.5){ //挨在球右边   
                                if(fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2 && fabs(dy) < BALLD/2 + ROBOTWIDTH/2){   
                                        if(by < FBOT + ROBOTWIDTH){   
                                                if(hasEnemyNear(bx,by))   
                                                        turn(robot,rID,1);   
                                                else   
                                                        sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                        }   
                                        else{   
                                                if(bx < 27.81)   
                                                        turnKick(robot,rID,2);   
                                                else   
                                                        sGo(robot,rID,GLEFT,(FTOP + FBOT)/2);   
                                        }   
                                }   
                                else{   
                                        if(by < FBOT + ROBOTWIDTH)   
                                                sGo(robot,rID,bx,by + 1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1]);   
                                }                   
                        }   
                        else{ //在球左边   
                                toBRight(robot,rID);   
                        }   
                        if(bx < FLEFTX + ROBOTWIDTH){ //球到敌方底线   
                                if(dy < -0.5 && dy > -3.0 && fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                }   
                                else if(dx > 1){   
                                        toBDown(robot,rID);   
                                }   
                                else   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                        }   
                        if(bx > 70.12){ //回防   
                                if(rx - bx > 2.5){   
                                        sGo(robot,rID,PBP[0] - 1,PBP[1]);   
                                }   
                                else{   
                                        if(by < 27.89 - ROBOTWIDTH){   
                                                toBRight(robot,rID);   
                                        }   
                                        else   
                                                keeper(robot,rID,FRIGHTX - ROBOTWIDTH,27.89 - ROBOTWIDTH/2,180.0);   
                                }   
                        }   
                        if(bx > FRIGHTX - ROBOTWIDTH){ //球到我方底线   
                                if(dy > 0.5 && dy < 2.5 && fabs(dx) < 1.2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,1);   
                                        else   
                                                sGo(robot,rID,bx,by);   
                                }   
                                else if(dy > 0.5 && fabs(dx) < 1.8)   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                                else //if(dx < -1)   
                                        toBUp(robot,rID);   
                        }   
                }   
                else if(by > L){ //球不在范围   
                        if(bvd > 180.0 && bvd < 360.0){   
                                double k;   
                                desY = 19.94;   
                                k = tanf(bvd/180.0*PI);   
                                desX = fn(k,bx,by,desY);   
                                desX += 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                        else{   
                                desY = 19.94;   
                                desX = bx + 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                }   
        }   
        else{ //for yellow   
                L = 52.92 - revise;   
                if(by > L){ //球在范围   
                        if(rx < bx -2.5){ //挨在球左边   
                                if(fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2 && fabs(dy) < BALLD/2 + ROBOTWIDTH/2){   
                                        if(by > FTOP - ROBOTWIDTH){   
                                                if(hasEnemyNear(bx,by))   
                                                        turn(robot,rID,1);   
                                                else   
                                                        sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                        }   
                                        else{   
                                                if(bx > 70.12)   
                                                        turnKick(robot,rID,4);   
                                                else   
                                                        sGo(robot,rID,GRIGHT,(FTOP + FBOT)/2);   
                                        }   
                                }   
                                else{   
                                        if(by > FTOP - ROBOTWIDTH)   
                                                sGo(robot,rID,bx,by + 1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1]);   
                                }                   
                        }   
                        else{ //在球右边   
                                toBLeft(robot,rID);   
                        }   
                        if(bx > FRIGHTX - ROBOTWIDTH){ //球到敌方底线   
                                if(dy > 0.5 && dy < 3.0 && fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                }   
                                else if(dx < -1){   
                                        toBUp(robot,rID);   
                                }   
                                else   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                        }   
                        if(bx < 27.81){ //回防   
                                if(rx - bx < -2.5){   
                                        sGo(robot,rID,PBP[0] + 1,PBP[1]);   
                                }   
                                else{   
                                        if(by > 58.56 + ROBOTWIDTH){   
                                                toBLeft(robot,rID);   
                                        }   
                                        else   
                                                keeper(robot,rID,FLEFTX + ROBOTWIDTH,58.56 + ROBOTWIDTH/2,180.0);   
                                }   
                        }   
                        if(bx < FLEFTX + ROBOTWIDTH){ //球到我方底线   
                                if(dy < -0.5 && dy > -2.5 && fabs(dx) < 1.2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,1);   
                                        else   
                                                sGo(robot,rID,bx,by);   
                                }   
                                else if(dy < -0.5 && fabs(dx) < 1.8)   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                                else //if(dx < -1)   
                                        toBDown(robot,rID);   
                        }   
                }   
                else if(by < L){ //球不在范围   
                        if(bvd < 180.0 && bvd > 0.0){   
                                double k;   
                                desY = 66.39;   
                                k = tanf(bvd/180.0*PI);   
                                desX = fn(k,bx,by,desY);   
                                desX -= 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                        else{   
                                desY = 66.39;   
                                desX = bx - 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                }   
        }   
}   
   
void middleSoccer(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double bvd,bv;   
        double desX,desY;   
        double L; //活动边界   
        double R; //活动边界   
        double revise;   
   
        revise = 5.0;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        bvd = BALLVDIRECTION[0];   
        bv = BALLEV[0];   
        if(bv > 100 || l(rx,ry,bx,by) > 15)   
                predictBall(1/8);   
        else if(bv > 80 || l(rx,ry,bx,by) > 10)   
                predictBall(1/15);   
        else if(bv > 50 || l(rx,ry,bx,by) > 7)   
                predictBall(1/25);   
        else   
                predictBall(1/40);   
        if(l(rx,ry,bx,by) < 3)   
                predictBall(0.0);   
        if(WHO ==1){   
                L = 27.89 - revise;   
                R = 58.56 + revise;   
                if(by < L || by > R){ //范围外   
                        if(by < L){   
                                if(bvd > 0 && bvd < 180.0){   
                                        double k;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = 43.00;   
                                        desX = fn(k,bx,by,desY);   
                                        desX += 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                                else{   
                                        desY = 43.00;   
                                        desX = bx + 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                        }   
                        else{ //by >R   
                                if(bvd > 180.0 && bvd < 360.0){   
                                        double k;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = 43.00;   
                                        desX = fn(k,bx,by,desY);   
                                        desX += 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                                else{   
                                        desY = 43.00;   
                                        desX = bx + 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                        }   
                }   
                else{ //在范围   
                        if(rx < bx + 2.5)   
                                toBRight(robot,rID);   
                        else{   
                                if(fabs(dy) < 1.5)   
                                        sGo(robot,rID,GLEFT,(FTOP + FBOT)/2);   
                                else   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                        }   
                        if(bx > 88.28)   
                                run(robot,rID,0,0);   
                        else if(bx < 88.28 && bx > 80.43){   
                                if(rx > bx && fabs(dy) > 3)   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                                else   
                                        run(robot,rID,0,0);   
                        }   
                        else if(bx < 11.95){   
                                if(by > 33.93 && by < 49.68)   
                                        sTo(robot,rID,PBP[0],PBP[1]);   
                                else   
                                        sTo(robot,rID,20.69,43.00);   
                        }   
                }   
        }   
        else{ //for yellow   
                R = 27.89 - revise;   
                L = 58.56 + revise;   
                if(by > L || by < R){ //范围外   
                        if(by > L){   
                                if(bvd < 360.0 && bvd > 180.0){   
                                        double k;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = 43.00;   
                                        desX = fn(k,bx,by,desY);   
                                        desX -= 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                                else{   
                                        desY = 43.00;   
                                        desX = bx - 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                        }   
                        else{ //by >R   
                                if(bvd < 180.0 && bvd > 0.0){   
                                        double k;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = 43.00;   
                                        desX = fn(k,bx,by,desY);   
                                        desX -= 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                                else{   
                                        desY = 43.00;   
                                        desX = bx - 3*ROBOTWIDTH;   
                                        if(desX > 80.43)   
                                                desX = 80.43;   
                                        if(desX < 19.80)   
                                                desX = 19.80;   
                                        sTo(robot,rID,desX,desY);   
                                }   
                        }   
                }   
                else{ //在范围   
                        if(rx > bx - 2.5)   
                                toBLeft(robot,rID);   
                        else{   
                                if(fabs(dy) < 1.5)   
                                        sGo(robot,rID,GRIGHT,(FTOP + FBOT)/2);   
                                else   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                        }   
                        if(bx < 11.95)   
                                run(robot,rID,0,0);   
                        else if(bx > 11.95 && bx < 17.69){   
                                if(rx < bx && fabs(dy) > 3)   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                                else   
                                        run(robot,rID,0,0);   
                        }   
                        else if(bx > 88.28){   
                                if(by > 33.93 && by < 49.68)   
                                        sTo(robot,rID,PBP[0],PBP[1]);   
                                else   
                                        sTo(robot,rID,79.55,43.00);   
                        }   
                }   
        }   
}   
void rightSoccer(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double bvd,bv;   
        double desX,desY;   
        double R; //活动边界   
        double revise;   
   
        revise = 5.0;   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        bvd = BALLVDIRECTION[0];   
        bv = BALLEV[0];   
        if(bv > 100 || l(rx,ry,bx,by) > 15)   
                predictBall(1/8);   
        else if(bv > 80 || l(rx,ry,bx,by) > 10)   
                predictBall(1/15);   
        else if(bv > 50 || l(rx,ry,bx,by) > 7)   
                predictBall(1/25);   
        else   
                predictBall(1/40);   
        if(l(rx,ry,bx,by) < 3)   
                predictBall(0.0);   
        if(WHO ==1){   
                R = 52.92 -revise;   
                if(by > R){ //球在范围   
                        if(rx > bx+2.5){ //挨在球右边   
                                if(fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2 && fabs(dy) < BALLD/2 + ROBOTWIDTH/2){   
                                        if(by > FTOP - ROBOTWIDTH){   
                                                if(hasEnemyNear(bx,by))   
                                                        turn(robot,rID,-1);   
                                                else   
                                                        sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                        }   
                                        else{   
                                                if(bx < 27.81)   
                                                        turnKick(robot,rID,3);   
                                                else   
                                                        sGo(robot,rID,GLEFT,(FTOP + FBOT)/2);   
                                        }   
                                }   
                                else{   
                                        if(by > FTOP - ROBOTWIDTH)   
                                                sGo(robot,rID,PBP[0],PBP[1] - 1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1]);   
                                }                   
                        }   
                        else{ //在球左边   
                                toBRight(robot,rID);   
                        }   
                        if(bx < FLEFTX + ROBOTWIDTH){ //球到敌方底线   
                                if(dy > 0.5 && dy < 3.0 && fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,-1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                }   
                                else if(dx > 1){   
                                        toBUp(robot,rID);   
                                }   
                                else   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                        }   
                        if(bx > 70.12){ //回防   
                                if(rx - bx > 2.5){   
                                        sGo(robot,rID,PBP[0] - 1,PBP[1]);   
                                }   
                                else{   
                                        if(by > 52.92 + ROBOTWIDTH){   
                                                toBDown(robot,rID);   
                                        }   
                                        else   
                                                keeper(robot,rID,FRIGHTX - ROBOTWIDTH,52.92 + ROBOTWIDTH/2,180.0);   
                                }   
                        }   
                        if(bx > FRIGHTX - ROBOTWIDTH){ //球到我方底线   
                                if(dy < -0.5 && dy >- 2.5 && fabs(dx) < 1.2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,-1);   
                                        else   
                                                sGo(robot,rID,PBP[0] -1.0,PBP[1]);   
                                }   
                                else if(dy < -0.5 && fabs(dx) < 1.8)   
                                        sGo(robot,rID,PBP[0] -1.0,PBP[1]);   
                                else //if(dx < -1)   
                                        toBDown(robot,rID);   
                        }   
                }   
                else if(by < R){ //球不在范围   
                        if(bvd > 0.0 && bvd < 180.0){   
                                double k;   
                                desY = 66.39;   
                                k = tanf(bvd/180.0*PI);   
                                desX = fn(k,bx,by,desY);   
                                desX += 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                        else{   
                                desY = 66.39;   
                                desX = bx + 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                }   
        }   
        else{   
                R = 33.71 + revise;   
                if(by < R){ //球在范围   
                        if(rx < bx - 2.5){ //挨在球左边   
                                if(fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2 && fabs(dy) < BALLD/2 + ROBOTWIDTH/2){   
                                        if(by < FBOT + ROBOTWIDTH){   
                                                if(hasEnemyNear(bx,by))   
                                                        turn(robot,rID,-1);   
                                                else   
                                                        sGo(robot,rID,PBP[0],PBP[1] - 1);   
                                        }   
                                        else{   
                                                if(bx > 70.12)   
                                                        turnKick(robot,rID,2);   
                                                else   
                                                        sGo(robot,rID,GRIGHT,(FTOP + FBOT)/2);   
                                        }   
                                }   
                                else{   
                                        if(by < FBOT + ROBOTWIDTH)   
                                                sGo(robot,rID,PBP[0],PBP[1] + 1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1]);   
                                }                   
                        }   
                        else{ //在球右边   
                                toBLeft(robot,rID);   
                        }   
                        if(bx > FRIGHTX - ROBOTWIDTH){ //球到敌方底线   
                                if(dy < -0.5 && dy > -3.0 && fabs(dx) < BALLD/2 + sqrt(2)*ROBOTWIDTH/2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,1);   
                                        else   
                                                sGo(robot,rID,PBP[0],PBP[1] - 1);   
                                }   
                                else if(dx < -1){   
                                        toBDown(robot,rID);   
                                }   
                                else   
                                        sGo(robot,rID,PBP[0],PBP[1]);   
                        }   
                        if(bx < 27.81){ //回防   
                                if(rx - bx < -2.5){   
                                        sGo(robot,rID,PBP[0] + 1,PBP[1]);   
                                }   
                                else{   
                                        if(by < 27.89 - ROBOTWIDTH){   
                                                toBUp(robot,rID);   
                                        }   
                                        else   
                                                keeper(robot,rID,FLEFTX + ROBOTWIDTH,27.89 - ROBOTWIDTH/2,180.0);   
                                }   
                        }   
                        if(bx < FLEFTX + ROBOTWIDTH){ //球到我方底线   
                                if(dy > 0.5 && dy < 3 && fabs(dx) < 1.2){   
                                        if(hasEnemyNear(bx,by))   
                                                turn(robot,rID,-1);   
                                        else   
                                                sGo(robot,rID,PBP[0] + 1.0,PBP[1]);   
                                }   
                                else if(dy < 0.5 && fabs(dx) < 1.8)   
                                        sGo(robot,rID,PBP[0] + 1.0,PBP[1]);   
                                else //if(dx < -1)   
                                        toBUp(robot,rID);   
                        }   
                }   
                else if(by > R){ //球不在范围   
                        if(bvd > 180.0 && bvd < 360.0){   
                                double k;   
                                desY = 19.94;   
                                k = tanf(bvd/180.0*PI);   
                                desX = fn(k,bx,by,desY);   
                                desX -= 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                        else{   
                                desY = 19.94;   
                                desX = bx - 3*ROBOTWIDTH;   
                                if(desX > 70.12)   
                                        desX = 70.12;   
                                if(desX < 27.81)   
                                        desX = 27.81;   
                                sTo(robot,rID,desX,desY);   
                        }   
                }   
        }   
}   
   
void backSoccer(Robot *robot,int rID){   
        //   
        double rx,ry,bx,by;   
        double dx,dy;   
        double bvd,bv;   
        double desX,desY;   
        double B; //活动边界   
   
        rx = robot->pos.x;   
        ry = robot->pos.y;   
        bx = ENV->currentBall.pos.x;   
        by = ENV->currentBall.pos.y;   
        dx = rx - bx;   
        dy = ry - by;   
        bvd = BALLVDIRECTION[0];   
        bv = BALLEV[0];   
        if(WHO ==1){   
                B = 60.27;   
                if(bx < B){ //attack   
                        if(bx > 19.80){ //19.80--60.27   
                                if(bvd < 90.0 || bvd > 270.0){   
                                        double k;   
                                        desX = B;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = f(k,bx,by,desX);   
                                        if(desY > FTOP - ROBOTWIDTH)   
                                                desY = FTOP - ROBOTWIDTH;   
                                        else if(desY < FBOT + ROBOTWIDTH)   
                                                desY = FBOT + ROBOTWIDTH;   
                                        keeper(robot,rID,desX,desY,90.0);   
                                }   
                                else   
                                        keeper(robot,rID,B,by,90.0);   
                                if(dx > 0 && dx < ROBOTWIDTH + 1){   
                                        if(by > (FTOP + FBOT)/2)   
                                                turnKick(robot,rID,3);   
                                        else   
                                                turnKick(robot,rID,2);   
                                }   
                        }   
                        else{ // --19.80   
                                if(bvd < 90.0 || bvd > 270.0){   
                                        double k;   
                                        desX = 37.20;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = f(k,bx,by,desX);   
                                        if(desY > FTOP - ROBOTWIDTH)   
                                                desY = FTOP - ROBOTWIDTH;   
                                        else if(desY < FBOT + ROBOTWIDTH)   
                                                desY = FBOT + ROBOTWIDTH;   
                                        keeper(robot,rID,desX,desY,90.0);   
                                }   
                                else   
                                        keeper(robot,rID,37.20,by,90.0);   
                                if(dx > 0 && dx < ROBOTWIDTH + 1){   
                                        if(by > (FTOP + FBOT)/2)   
                                                turnKick(robot,rID,3);   
                                        else   
                                                turnKick(robot,rID,2);   
                                }   
                        }   
                }   
                else{ //defend   
                        if(bx < 88.28 - ROBOTWIDTH){ //60.27--88.28 - ROBOTWIDTH   
                                if(bvd < 90.0 || bvd > 270.0){   
                                        double k;   
                                        desX = 88.28 - ROBOTWIDTH;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = f(k,bx,by,desX);   
                                        if(desY > FTOP - ROBOTWIDTH)   
                                                desY = FTOP - ROBOTWIDTH;   
                                        else if(desY < FBOT + ROBOTWIDTH)   
                                                desY = FBOT + ROBOTWIDTH;   
                                        keeper(robot,rID,desX,desY,90.0);   
                                }   
                                else{   
                                        if(by > (FTOP + FBOT)/2)   
                                                keeper(robot,rID,88.28 - ROBOTWIDTH,by - 2*ROBOTWIDTH,90.0);   
                                        else   
                                                keeper(robot,rID,88.28 - ROBOTWIDTH,by + 2*ROBOTWIDTH,90.0);   
                                }   
                                if(dx > 0 && dx < ROBOTWIDTH + 1){   
                                        if(by > (FTOP + FBOT)/2)   
                                                turnKick(robot,rID,3);   
                                        else   
                                                turnKick(robot,rID,2);   
                                }   
                        }   
                        else{ //88.28 - ROBOTWIDTH--   
                                if(by > (FTOP + FBOT)/2)   
                                        sTo(robot,rID,FRIGHTX - ROBOTWIDTH,66.39);   
                                else   
                                        sTo(robot,rID,FRIGHTX - ROBOTWIDTH,19.94);   
                        }   
                }   
        }   
        else{   
                B = 37.20;   
                if(bx > B){ //attack   
                        if(bx < 80.43){ //37.20--80.43   
                                if(bvd > 90.0 && bvd < 270.0){   
                                        double k;   
                                        desX = B;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = f(k,bx,by,desX);   
                                        if(desY > FTOP - ROBOTWIDTH)   
                                                desY = FTOP - ROBOTWIDTH;   
                                        else if(desY < FBOT + ROBOTWIDTH)   
                                                desY = FBOT + ROBOTWIDTH;   
                                        keeper(robot,rID,desX,desY,90.0);   
                                }   
                                else   
                                        keeper(robot,rID,B,by,90.0);   
                                if(dx < 0 && dx > -1*(ROBOTWIDTH + 1)){   
                                        if(by > (FTOP + FBOT)/2)   
                                                turnKick(robot,rID,4);   
                                        else   
                                                turnKick(robot,rID,1);   
                                }   
                        }   
                        else{ // 80.43---   
                                if(bvd > 90.0 && bvd < 270.0){   
                                        double k;   
                                        desX = 60.27;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = f(k,bx,by,desX);   
                                        if(desY > FTOP - ROBOTWIDTH)   
                                                desY = FTOP - ROBOTWIDTH;   
                                        else if(desY < FBOT + ROBOTWIDTH)   
                                                desY = FBOT + ROBOTWIDTH;   
                                        keeper(robot,rID,desX,desY,90.0);   
                                }   
                                else   
                                        keeper(robot,rID,60.27,by,90.0);   
                                if(dx < 0 && dx < -1*(ROBOTWIDTH + 1)){   
                                        if(by > (FTOP + FBOT)/2)   
                                                turnKick(robot,rID,4);   
                                        else   
                                                turnKick(robot,rID,1);   
                                }   
                        }   
                }   
                else{ //defend   
                        if(bx > 11.95 + ROBOTWIDTH){ //11.95+ Rd --37.20   
                                if(bvd > 90.0 && bvd < 270.0){   
                                        double k;   
                                        desX = 11.95 + ROBOTWIDTH;   
                                        k = tanf(bvd/180.0*PI);   
                                        desY = f(k,bx,by,desX);   
                                        if(desY > FTOP - ROBOTWIDTH)   
                                                desY = FTOP - ROBOTWIDTH;   
                                        else if(desY < FBOT + ROBOTWIDTH)   
                                                desY = FBOT + ROBOTWIDTH;   
                                        keeper(robot,rID,desX,desY,90.0);   
                                }   
                                else{   
                                        if(by > (FTOP + FBOT)/2)   
                                                keeper(robot,rID,11.95 + ROBOTWIDTH,by - 2*ROBOTWIDTH,90.0);   
                                        else   
                                                keeper(robot,rID,11.95 + ROBOTWIDTH,by + 2*ROBOTWIDTH,90.0);   
                                }   
                                if(dx < 0 && dx > -1*(ROBOTWIDTH + 1)){   
                                        if(by > (FTOP + FBOT)/2)   
                                                turnKick(robot,rID,4);   
                                        else   
                                                turnKick(robot,rID,1);   
                                }   
                        }   
                        else{ //88.28 - ROBOTWIDTH--   
                                if(by > (FTOP + FBOT)/2)   
                                        sTo(robot,rID,FLEFTX + ROBOTWIDTH,66.39);   
                                else   
                                        sTo(robot,rID,FLEFTX + ROBOTWIDTH,19.94);   
                        }   
                }   
        }   
}   
   
   
/*  
        DEBUGFILE = fopen("debug.txt", "a");  
        fprintf(DEBUGFILE, "%f %f\n", , );  
        fclose(DEBUGFILE);  
*/   