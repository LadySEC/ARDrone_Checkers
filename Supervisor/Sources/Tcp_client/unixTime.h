#ifndef UNIXTIME_H
#define UNIXTIME_H

#include <stdbool.h>

/* Constants */
//! Unix epoch year
#define EPOCH_YEAR      1970

//! Number of seconds in a day
#define SECS_PER_DAY    86400UL

//! Number of seconds in an hour
#define SECS_PER_HOUR   3600UL

//! Number of seconds in a minute
#define SECS_PER_MINUTE 60UL

//! Number of days in a specified month. Index 1 for leap year, else 0.
const unsigned char month[2][12] = {
       { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
       { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/* Types */
//! Calendar structure to hold a date
struct calendar_date {
       unsigned char    second;        //!< 0-59
       unsigned char    minute;        //!< 0-59
       unsigned char    hour;          //!< 0-23
       unsigned char    date;          //!< 0-30 \note First day of month is 0, not 1.
       unsigned char    month;         //!< 0 January - 11 December
       unsigned int     year;         //!< 1970-2105
       unsigned char    dayofweek;     //!< 0 Sunday  - 6 Saturday
};

/* Function Prototype */

#ifdef __cplusplus
extern "C" {
#endif

/* Your C-callable prototypes */
void initUnixTimeStamp(
                        unsigned char second,
                        unsigned char minute,
                        unsigned char hour,
                        unsigned char date,
                        unsigned char month,
                        unsigned int year
                        );

unsigned long       calendar_date_to_timestamp(struct calendar_date *date);
struct calendar_date * getCalendarDate(void);
#ifdef __cplusplus
}
#endif

#endif // UNIXTIME_H
