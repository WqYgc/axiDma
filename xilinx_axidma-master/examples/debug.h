#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdio.h>
#include <stdarg.h>

#define    BUF_SIZE_MAX    300
#define    DEBUG_INIFO "/mnt/devDebugInfo.log"
enum _log_level{
    LOG_LEVEL_OFF       = 0,
    LOG_LEVEL_FATAL     = 1,
    LOG_LEVEL_ERROR     = 2,
    LOG_LEVEL_WARN      = 3,
    LOG_LEVEL_INFO      = 4,
    LOG_LEVEL_DEBUG     = 5,
    LOG_LEVEL_TRACE     = 6,
};

unsigned int  DEBUG_LEVEL=4;
typedef enum _log_level log_level;

#if 1
#define	log_bug(level, fmt, arg...)	        \
do{                                         \
    if(DEBUG_LEVEL >= level){               \
        switch (level){                     \
			case LOG_LEVEL_OFF:             \
				break;                      \
                                            \
			case LOG_LEVEL_FATAL:           \
                printf("log fatal : %s:%s:%u %s:%s  ::", __FILE__, __func__,__LINE__, __DATE__, __TIME__); \
                break;                      \
                                            \
			case LOG_LEVEL_ERROR:           \
                printf("log error : %s:%s:%u  ::", __FILE__, __func__,__LINE__); \
                break;                      \
                                            \
			case LOG_LEVEL_WARN:            \
				 printf("log warn : %s:%s:%u  ::", __FILE__, __func__,__LINE__); \
                break;                      \
                                            \
			case LOG_LEVEL_INFO:            \
                printf("log info : %s:%s:%u  ::", __FILE__, __func__,__LINE__); \
                break;                      \
                                            \
			case LOG_LEVEL_DEBUG:           \
			case LOG_LEVEL_TRACE:           \
             printf("log trace : %s:%s:%u  ::", __FILE__, __func__,__LINE__); \
                break;                      \
			default:                        \
				break;                      \
                                            \
		}                                   \
        printf(fmt, ##arg);                 \
        printf("\n");                       \
    }	                                    \
}while(0)

 #else
#define	log_bug(level,fmt, arg...)	            \
do{                                             \
    if(DEBUG_LEVEL >= level)                    \
    {                                           \
        int write_len_ygc = 0, total_len_ygc = 0;\
        char f_buf[BUF_SIZE_MAX]={'\0'};           \
        FILE *fp  = fopen(DEBUG_INIFO, "a+"); \
        write_len_ygc = snprintf(f_buf, BUF_SIZE_MAX, fmt, ##arg);\
        switch (level){                     \
			case LOG_LEVEL_FATAL ...LOG_LEVEL_TRACE:\
                total_len_ygc = snprintf(f_buf + write_len_ygc, BUF_SIZE_MAX - write_len_ygc,  "%s:%s %d \n", __FILE__, __func__, __LINE__); \
                total_len_ygc += write_len_ygc;         \
                fwrite(f_buf, total_len_ygc, 1, fp); \
                break;                      \
			default:                        \
				break;                      \
		}                                   \
        fclose(fp);                         \
    }	                                     \
}while(0)                                    
#endif

#endif
