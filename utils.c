/*
 * utils.c
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#include "utils.h"

void utils_killdog()
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
}
