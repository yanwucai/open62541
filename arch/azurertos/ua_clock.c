/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 */

#ifdef UA_ARCHITECTURE_AZURERTOS

#ifndef _BSD_SOURCE
# define _BSD_SOURCE
#endif

#include <open62541/types.h>

#include "tx_api.h"

ULONG unix_time_base = 0;

UA_DateTime UA_DateTime_now(void) {
    UA_DateTime ms = ((UA_DateTime)tx_time_get()) * (1000000 / TX_TIMER_TICKS_PER_SECOND);
    return ((ms / 1000000 + unix_time_base) * UA_DATETIME_SEC) + ((ms % 1000000) * UA_DATETIME_USEC) + UA_DATETIME_UNIX_EPOCH;
}

UA_Int64 UA_DateTime_localTimeUtcOffset(void) {
    return 0;
}

UA_DateTime UA_DateTime_nowMonotonic(void) {
    return (((UA_DateTime)tx_time_get()) * 1000 / TX_TIMER_TICKS_PER_SECOND) * UA_DATETIME_MSEC;
}

#endif /* UA_ARCHITECTURE_AZURERTOS */
