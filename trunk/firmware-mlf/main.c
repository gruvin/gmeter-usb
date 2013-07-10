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
    if (rq->bRequest == 2) { /* Light 0 through 8 LEDs, according to supplied 'level' */
        uchar level = rq->wIndex.bytes[0]; // level
        setLEDs((1<<level)-1); // level=0 is all LEDs off -- level=3 is first 3 LEDs on, etc.
        healthCounter = HEALTHCOUNTER_RESET_VALUE;
    }
    if (rq->bRequest == 3) { /* Set audible alarm on (see main() loop)  */
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

void setLEDs(unsigned char leds)
{
  PORTD = (PORTD & ~0x20) | (leds & 0x01)<<5; // LED 1
  PORTD = (PORTD & ~0x10) | (leds & 0x02)<<3; // LED 2
  PORTC = (PORTC & ~0x20) | (leds & 0x04)<<3; // LED 3
  PORTC = (PORTC & ~0x10) | (leds & 0x08)<<1; // LED 4
  PORTC = (PORTC & ~0x08) | (leds & 0x10)>>1; // LED 5
  PORTC = (PORTC & ~0x04) | (leds & 0x20)>>3; // LED 6
  PORTC = (PORTC & ~0x02) | (leds & 0x40)>>5; // LED 7
  PORTC = (PORTC & ~0x01) | (leds & 0x80)>>7; // LED 8
}

int
main(void)
{
    uchar   i;
    unsigned int j;

    wdt_disable();

    DDRB = 0x00; PORTB = 0x3f; // PORTB[2]=S4, [1]=S3, [0]=S2
    DDRC = 0x3f; PORTC = 0x00; // PORTC[5:4:3:2:1:0]=LEDS[3:4:5:6:7:8]
    DDRD = 0xb2; PORTD = 0x00; // PORTD[7]=BEEPER, [6]=S1, [5:4]=LEDS[1:2], [3]=D-, [2]D+, [1]=TX, [0]=RX 

    /* Fake a physical disconnect for 500ms, in case we are resetting due to WDT event */
    PORTD &= ~USBMASK; /* set both USB D+/D- to output (low/low) to force reset */
    DDRD |= USBMASK;        

/*
    // DEBUG
    PORTD |= 1<<7;
    _delay_ms(1000);
    PORTD &= ~(1<<7);
*/
    // Fancy reset LED sequence for eye candy/confidence (plus delay for USB reset)

    for(i=1; i != 0 ; i<<=1)
    {
      setLEDs(i);
      _delay_ms(100);
    }
    setLEDs(0);

/* ... was USB reset delay
    for (i = 0; i < 250; i++) {
        wdt_reset();
        _delay_ms(2);
    }
*/
    _delay_ms(2000);

    DDRD &= ~USBMASK; // D+/- set as inputs
    
    wdt_enable(WDTO_1S);
    odDebugInit();
    
    TCCR0 = 5;  /* set prescaler to 1/1024 */
    usbInit();
    
    sei();
    i = 0;
    for (;;) {    /* main event loop */
        wdt_reset();
        usbPoll();
        if (healthCounter && !(--i)) healthCounter--; // use i as a 256 count pre-scaler
        if (!healthCounter) PORTD=PORTD & ~0x20; // indicate data time-out by turning off LED 1 (leave all others as they are)
        if (gAlarmOn)
          PORTD=(PORTD & ~(1<<7)) | ((j-- & 0x8000) >> 8); // pulsating bepper
        else
          PORTD=PORTD & ~(1<<7); // beeper off
    }
    return 0;
}

