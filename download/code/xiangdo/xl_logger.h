#ifndef _XL_LOGGER_H_ 
#define _XL_LOGGER_H_ 
#include "xl_global.h" 
 
 
//!  
enum ChannelTag 
{ 
	CT_TEST = 0, 
    CT_ERROR, 
    CT_CMD ,     //命令 
    CT_SENSE,    //感知 
    CT_TIME,     //计时 
    CT_INTERCEPT,//截球 
    CT_PASS ,    //传球 
    CT_DRIBBLE,  //带球 
    CT_SHOOT,    //射门 
	CT_GOALIE,   //守门员 
	CT_DEFENCE,  //防守 
    CT_MAX // 可以在CT_MAX之前添加新的ChannelTag 
}; 
 
#ifdef ENABLE_LOG 
  #define Log LogLine	 
#else 
  #define Log(x) NULL		 
#endif //ENABLE_LOG 
 
//打开log文件 
void OpenLogger(const char * fileName); 
 
//写log,LogLine(CT_TEST,"%d",5); 
void LogLine(ChannelTag channelTag, const char* szFmt, ...); 
 
//注册频道，只有注册后的频道才可以使用，否则其内容写不到文件里 
void RegisterChannel(ChannelTag channelTag,const char* channleName); 
 
//设置Log周期 
void SetLogCycle(int nCycle); 
 
//关闭log文件 
void CloseLogger(); 
 
#endif 