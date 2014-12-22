#include "unixTime.h"

/* Global variables */
struct calendar_date initTime;

/* Functions */
void initUnixTimeStamp(
                        unsigned char second,
                        unsigned char minute,
                        unsigned char hour,
                        unsigned char date,
                        unsigned char month,
                        unsigned int year
                        )
{
    initTime.second = second;
    initTime.minute = minute;
    initTime.hour = hour;
    initTime.date = date;
    initTime.month = month;
    initTime.year = year;
}

static bool calendar_leapyear(unsigned int year)
{
       if(!((year) % 4) && (((year) % 100) || !((year) % 400))) {
              return true;
       } else {
              return false;
       }
}

static unsigned int calendar_yearsize(unsigned int year)
{
       if (calendar_leapyear(year)) {
              return 366;
       } else {
              return 365;
       }
}

bool calendar_is_date_valid(struct calendar_date *date)
{
       // Make sure time is valid
       if ((date->second >= 60) || (date->minute >= 60) || (date->hour >= 24)) {
              return false;
       }

       // Make sure month and date is valid
       if ((date->month >= 12) || (date->date >=31)) {
              return false;
       }

       // Make sure days in month are not more than it should be
       if (date->date >= month[calendar_leapyear(date->year)][date->month]) {
              return false;
       }

       // Make sure year is not earlier than 1970 and before 2106
       if ((date->year < EPOCH_YEAR) || (date->year >= 2106)) {
              return false;
       } else {
              return true;
       }
}

/**
* \brief Convert a date to a UNIX timestamp.
*
* \note
* If date is invalid, timestamp 0 will be returned.
*
* \param date  Date
*
* \return The corresponding UNIX timestamp
* \retval 0 if date is not valid
*/
unsigned long int calendar_date_to_timestamp(struct calendar_date *date)
{

       // Make sure date is valid
       if (!calendar_is_date_valid(date))
              return 0;

       unsigned long int    timestamp = 0;
       unsigned char        date_month;
       unsigned int         date_year;

       date_month = date->month;
       date_year = date->year;

       // Add number of seconds elapsed in current month
       timestamp += (date->date * SECS_PER_DAY) + (date->hour * SECS_PER_HOUR) +
                     (date->minute * SECS_PER_MINUTE) + date->second;

       while (date_month != 0) {
              date_month--;
              // Add number of seconds in months of current year
              timestamp += month[calendar_leapyear(date_year)][date_month]
                           * SECS_PER_DAY;
       }
       while (date_year > EPOCH_YEAR) {
              date_year--;
              // Add number of seconds in all years since epoch year
              timestamp += calendar_yearsize(date_year) * SECS_PER_DAY;
       }

       return timestamp;
}

struct calendar_date * getCalendarDate(void)
{
    return(&initTime);
}
