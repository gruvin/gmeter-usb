/* Name: main.c
 * Project: PowerSwitch based on AVR USB driver
 * Author: Christian Starkjohann
 * Creation Date: 2005-01-16
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 * This Revision: $Id$
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>

#include "usbdrv.h"
#include "oddebug.h"
#include <util/delay.h>


unsigned long healthCounter = 0; // 40000 is close to one minute
#define HEALTHCOUNTER_RESET_VALUE 246000 /* just over 6 minutes, timed */

unsigned char gAlarmOn = 0;

USB_PUBLIC uchar
usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;
static uchar    replyBuf[2];

    usbMsgPtr = replyBuf;
    if (rq->bRequest == 0) {  /* ECHO (for testing) */
        replyBuf[0] = rq->wValue.bytes[0];
        replyBuf[1] = rq->wValue.bytes[1];
        return 2;
    }
    if (rq->bRequest == 1) {  /* GET_STATUS -> result = 2 bytes */
        replyBuf[0] = 0; /* TODO */
        replyBuf[1] = 0; /* TODO */
        return 2;
    }
    if (rq->bRequest == 2) { /* Set LED display 'level', 0,1,2 or 3. (If level > 3 level=3) */
        uchar level = rq->wIndex.bytes[0] & 3;

        switch (level)
        {
          case 0:
            PORTB=8;
            gAlarmOn = 0;
            break;

          case 1:
            PORTB=12;
            gAlarmOn = 0;
            break;

          case 2:
            PORTB=14;
            gAlarmOn = 0;
            break;

          case 3:
            PORTB=15;
            gAlarmOn = 1;
            break;
        }
        healthCounter = HEALTHCOUNTER_RESET_VALUE;
    }
    if (rq->bRequest == 3) { /* Set audible alarm on PORTB[4] on (1) or off (0) */
      uchar alarmOn = rq->wIndex.bytes[0] & 1;
      gAlarmOn = alarmOn;
    }
    if (rq->bRequest == 4) { /* RESERVED ... might have a user alarm silence button, which could be detected here */
        replyBuf[0] = PINC;
        return 1;
    }
    return 0;
}

/* allow some inter-device compatibility */
#if !defined TCCR0 && defined TCCR0B
#define TCCR0   TCCR0B
#endif
#if !defined TIFR && defined TIFR0
#define TIFR    TIFR0
#endif

int
main(void)
{
    uchar   i;
    unsigned int j;

    wdt_enable(WDTO_1S);
    odDebugInit();
    
    DDRB = 0x3f; PORTB = 0x00; // all outputs, reset to low
    DDRC = 0x00; PORTC = 0x3f; // all inputs, pull-ups on

    /* Fake a physical disconnect for 500ms, in case we are resetting due to WDT event */
    PORTD &= ~USBMASK;
    DDRD |= USBMASK;        /* set both USB D+/D- to output (low/low) to force reset */
    for (i = 0; i < 250; i++) {
        wdt_reset();
        _delay_ms(2);
    }
    DDRD = 0x00;      // PORTD all inputs, including D+/D- 
    PORTD = ~USBMASK; // PORTD all with pull-ups, except USB D+/D-

    // Fancy reset LED sequence for eye candy/confidence
    for(i=8; i > 0; i >>= 1)
    {
      PORTB=i;
      _delay_ms(250);
    }
    PORTB=0;

    TCCR0 = 5;  /* set prescaler to 1/1024 */
    usbInit();
    sei();
    i = 0;
    for (;;) {    /* main event loop */
        wdt_reset();
        usbPoll();
        if (healthCounter && !(--i)) healthCounter--; // use i as a 256 count pre-scaler
        if (!healthCounter) PORTB=PORTB & ~1;
        if (gAlarmOn)
          PORTB=(PORTB & ~(1<<4)) | ((j-- & 0x8000) >> 11); // pulsating alarm on PORTB[4]
        else
          PORTB=PORTB & ~(1<<4); // alarm off
    }
    return 0;
}

