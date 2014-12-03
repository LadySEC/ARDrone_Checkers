/**
 * \file 	log.c
 * \brief 	Enables logging for the embedded program
 * \author 	Lady team
 * \version 1.0
 * \date 	2 December 2014
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include "log.h"
 
#define	LOG_BUFF_SIZE	64
#define LOG_MAX_LINE	256
#define LOG_HEADER		"%18s | %8s | %7s\n"
#define LOG_FORMAT		"%18s | %08x | %7s | %s\n"
#define LOG_TIME_FORMAT	"%d-%b - %H:%M:%S"

static FILE * 	M_logFile = NULL;
static int		M_logLvl;

int LOG_WriteLine(char * I_str);
int LOG_WriteFormattedLine(char * I_str, int I_logLevel);
char* LOG_LogLevelToString(int I_logLevel);

int LOG_Init(char * I_filename, int I_logLevel) {
	int 	ret = LOG_ERR_OK;
	int		strLen;
	char 	buff[LOG_BUFF_SIZE];
	// The init() is only necessary if no previous initialization was done
	if (M_logFile == NULL) {
		M_logFile = fopen(I_filename, "a+");
		M_logLvl = I_logLevel;
		if (M_logFile == NULL) {
			ret = LOG_ERR_FILE;
			M_logLvl = 0;
		} else {
			// First line of the log file
			strLen = snprintf(buff, sizeof(buff), LOG_HEADER, "Date", "ThreadID", "LogLevel");
			if (strLen > 0) {
				LOG_WriteLine("--------------------------------------------------------------------------------------------\n");
				LOG_WriteLine("----------------------------------------/ LOG FILE \\----------------------------------------\n");
				LOG_WriteLine("--------------------------------/ Beginning of the program \\--------------------------------\n");
				LOG_WriteLine("--------------------------------------------------------------------------------------------\n");
				LOG_WriteLine(buff);
				LOG_WriteLine("--------------------------------------------------------------------------------------------\n");
			}
		}
	} else {
		ret = LOG_ERR_INIT;
	}
	return ret;
}

// Writes "as is" the line in the log file
int LOG_WriteLine(char * I_str) {
	int 	ret = LOG_ERR_OK;
	if (fwrite((void *)I_str, (size_t)1, strlen(I_str), M_logFile) != 0) { ret = LOG_ERR_WRITE; }
	return ret;
}

// Returns the string associated to a log level
char* LOG_LogLevelToString(int I_logLevel) {
	switch (I_logLevel) {
		case LOG_ERROR:		return "ERROR";
		case LOG_WARN:		return "WARNING";
		case LOG_INFO:		return "INFO";
		case LOG_DEBUG:		return "DEBUG";
		default:			return "DEFAULT";
	}
}

// Write the line in the log file with the log info at the beginning of the line
int LOG_WriteFormattedLine(char * I_str, int I_logLevel) {
	time_t	timeNow;
	char 	timeStr[LOG_BUFF_SIZE];
	char 	buff[LOG_MAX_LINE];
	
	memset(buff, 0, sizeof(buff));
	timeNow = time(NULL);
	strftime(timeStr, sizeof(timeStr), LOG_TIME_FORMAT, localtime(&timeNow));
	snprintf(buff, sizeof(buff), LOG_FORMAT, timeStr, getpid(), LOG_LogLevelToString(I_logLevel), I_str);
	return LOG_WriteLine(buff);
}

int LOG_Write(char * I_format, ...) {
	va_list	args;
	char	buff[LOG_MAX_LINE];
	
	memset(buff, 0, sizeof(buff));
	va_start(args, I_format);
	vsnprintf(buff, sizeof(buff), I_format, args);
	va_end(args);
	
	return LOG_WriteFormattedLine(buff, LOG_DEFAULT);
}

int LOG_WriteLevel(int I_logLevel, char * I_format, ...) {
	va_list	args;
	char 	buff[LOG_MAX_LINE];
	
	memset(buff, 0, sizeof(buff));
	va_start(args, I_format);
	vsnprintf(buff, sizeof(buff), I_format, args);
	va_end(args);
	
	// Calls the Log_Write() function if the LogLevel specified is equal or below the global LogLevel
	// (we do not want to log DEBUG strings if the global LogLevel is set to WARN)
	if (M_logFile != NULL && I_logLevel <= M_logLvl) {
		return LOG_WriteFormattedLine(buff, I_logLevel);
	}
	return LOG_IGNORED;
}

int LOG_End() {
	int ret = LOG_ERR_OK;
	// The end() is only necessary if the library was previously initialized
	if (M_logFile != NULL) {
		// We add a new line in the log file
		LOG_WriteLine("--------------------------------------------------------------------------------------------\n\n\n");
		close((int)M_logFile);
		M_logFile = NULL;
	} else {
		ret = LOG_ERR_CLOSE;
	}
	return ret;
}