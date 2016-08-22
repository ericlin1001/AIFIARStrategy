#ifndef _XL_LOGGER_H_ 
#define _XL_LOGGER_H_ 
#include "xl_global.h" 
 
 
//!  
enum ChannelTag 
{ 
	CT_TEST = 0, 
    CT_ERROR, 
    CT_CMD ,     //���� 
    CT_SENSE,    //��֪ 
    CT_TIME,     //��ʱ 
    CT_INTERCEPT,//���� 
    CT_PASS ,    //���� 
    CT_DRIBBLE,  //���� 
    CT_SHOOT,    //���� 
	CT_GOALIE,   //����Ա 
	CT_DEFENCE,  //���� 
    CT_MAX // ������CT_MAX֮ǰ����µ�ChannelTag 
}; 
 
#ifdef ENABLE_LOG 
  #define Log LogLine	 
#else 
  #define Log(x) NULL		 
#endif //ENABLE_LOG 
 
//��log�ļ� 
void OpenLogger(const char * fileName); 
 
//дlog,LogLine(CT_TEST,"%d",5); 
void LogLine(ChannelTag channelTag, const char* szFmt, ...); 
 
//ע��Ƶ����ֻ��ע����Ƶ���ſ���ʹ�ã�����������д�����ļ��� 
void RegisterChannel(ChannelTag channelTag,const char* channleName); 
 
//����Log���� 
void SetLogCycle(int nCycle); 
 
//�ر�log�ļ� 
void CloseLogger(); 
 
#endif 