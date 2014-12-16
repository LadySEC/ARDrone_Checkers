/**
 * \file 	log.h
 * \brief 	Enables logging for the embedded program
 * \author 	Lady team
 * \version 1.0
 * \date 	2 December 2014
 *
 */

#ifndef _LOG_H_
#define _LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define	LOG_PRINTF		0	// Change this value to enable (1) or disable (0) the display of the log messages on the standard output

#define LOG_DEBUG		4	// Verbose mode, used to log repetitive actions such as AT commands
#define LOG_INFO		3	// Information mode, used to log interesting actions and events
#define	LOG_WARN		2	// Warning mode, used to log unexpected events or small problems
#define LOG_ERROR		1	// Error mode, used to log errors and fatal errors
#define LOG_DEFAULT		0	// Default value, used only when no value is passed

#define LOG_ERR_OK		0x0 // No error
#define LOG_ERR_INIT	0x1	// Error, log library already initialized
#define LOG_ERR_FILE	0x2 // Error, unable to open log file
#define LOG_ERR_CLOSE	0x3 // Error, log library was closed before it was initialized
#define LOG_ERR_WRITE	0x4 // Error while writing to file
#define LOG_IGNORED		0xf // The log string was not written to the file because of the log level



/**
 * \fn 		int LOG_Init(char * I_filename)
 * \brief 	Initializes logging to the specified file (should only be called once)
 *
 * \param 	I_filename	name of the file to log into 
 * \param	I_LogLevel	logging level of the program
 * \return 	TODO
 */
int LOG_Init(char * I_filename, int I_LogLevel);


/**
 * \fn 		int LOG_Write(char * I_ftm, ...)
 * \brief 	Writes the specified string to the log file, regardless of the logging level specified
 *
 * \param 	I_ftm 		format of the string to write (like for printf())
 * \param	...			optional parameters depending on the format string
 * \return 	TODO
 */
int LOG_Write(char * I_format, ...);


/**
 * \fn 		int LOG_WriteLevel(int I_logLevel, char * I_fmt, ...)
 * \brief 	Writes the specified string to the log file, if the logging level of the program is greater or equal to I_LogLevel
 *
 * \param	I_LogLevel	logging level of the string to write
 * \param 	I_ftm 		format of the string to write (like for printf())
 * \param	...			optional parameters depending on the format string
 * \return 	TODO
 */
int LOG_WriteLevel(int I_logLevel, char * I_format, ...);


/**
 * \fn 		int LOG_End()
 * \brief 	Closes the logging library
 *
 * \return 	TODO
 */
int LOG_End();

#ifdef __cplusplus
}
#endif

#endif