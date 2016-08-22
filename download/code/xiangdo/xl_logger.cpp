#include <stdarg.h>   
#include <windows.h>   
#include <stdio.h>   
#include "xl_logger.h"   
   
const int  MAX_LINE_SIZE      = 2048; // 2K   
   
typedef struct     
{   
    bool Enabled;   
    char *Name;   
} ChannelInfo;   
   
FILE *  LOGGER = NULL; //文件指针   
char pBuffer[MAX_LINE_SIZE];   
ChannelInfo channelInfo[CT_MAX];   
bool initOK = false;   
int  cycle = 0;   
   
void SetLogCycle(int nCycle)   
{   
    cycle = nCycle;   
}   
   
void RegisterChannel(ChannelTag channelTag,const char* channleName)    
{      
    if(!initOK ) return;   
    channelInfo[channelTag].Enabled = true;   
    size_t length = strlen(channleName);   
    channelInfo[channelTag].Name = (char*)malloc(length*sizeof(char));    
    strncpy(channelInfo[channelTag].Name,channleName,length);   
    channelInfo[channelTag].Name[length] = '\0';   
}   
   
   
void LogLine(ChannelTag channelTag, const char* szFmt, ...)   
{   
    if (initOK && channelInfo[channelTag].Enabled)   
    {   
        va_list ap;   
        va_start(ap, szFmt);   
        ::_vsnprintf(pBuffer, MAX_LINE_SIZE, szFmt, ap);           
        va_end(ap);        
        fprintf(LOGGER, "(%d)[%s]%s\n",cycle,channelInfo[channelTag].Name,pBuffer);     
    }   
}   
   
void OpenLogger(const char * fileName)   
{   
    initOK = false;   
       
    //打开Log文件   
    LOGGER = fopen(fileName,"w");   
    if (LOGGER) initOK = true;   
   
    //初始化频道   
    for(int idx = 0; idx  CT_MAX; idx++)   
    {   
        channelInfo[idx].Enabled = false;   
        channelInfo[idx].Name = NULL;   
    }   
    SetLogCycle(0);   
}   
   
   
void CloseLogger()   
{   
    initOK = false;   
    if (LOGGER)   
    {   
        fclose(LOGGER);   
    }   
    for(int idx = 0; idx  CT_MAX; idx++)   
    {   
        channelInfo[idx].Enabled = false;   
        if ( channelInfo[idx].Name ) free(channelInfo[idx].Name);   
    }   
}   
   