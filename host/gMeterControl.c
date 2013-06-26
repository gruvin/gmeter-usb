/* Name: powerSwitch.c
 * Project: PowerSwitch based on AVR USB driver
 * Author: Christian Starkjohann
 * Creation Date: 2005-01-16
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 * This Revision: $Id$
 */

/*
General Description:
This program controls the PowerSwitch USB device from the command line.
It must be linked with libusb, a library for accessing the USB bus from
Linux, FreeBSD, Mac OS X and other Unix operating systems. Libusb can be
obtained from http://libusb.sourceforge.net/.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usb.h>    /* this is libusb, see http://libusb.sourceforge.net/ */

#define USBDEV_SHARED_VENDOR    0x16C0  /* VOTI */
#define USBDEV_SHARED_PRODUCT   0x05DC  /* Obdev's free shared PID */
/* Use obdev's generic shared VID/PID pair and follow the rules outlined
 * in firmware/usbdrv/USBID-License.txt.
 */

/* These are the vendor specific SETUP commands implemented by our USB device */
#define PSCMD_ECHO  0
#define PSCMD_GET   1
#define PSCMD_SET   2
#define PSCMD_ALARM 3
#define PSCMD_RES   4

static void 
usage(char *name)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s test\n", name);
    fprintf(stderr, "  %s status -- not implememnted\n", name);
    fprintf(stderr, "  %s value [0-3] -- set display/alarm value\n", name);
    fprintf(stderr, "  %s alarm [on|off] -- set audible alarm\n", name);
}


static int
usbGetStringAscii(usb_dev_handle *dev, int index, int langid, char *buf, int buflen)
{
    char    buffer[256];
    int     rval, i;

    if ((rval = usb_control_msg(dev, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, 
                                  langid, buffer, sizeof(buffer), 1000)) < 0)
        return rval;
    if (buffer[1] != USB_DT_STRING)
        return 0;
    if ((unsigned char)buffer[0] < rval)
        rval = (unsigned char)buffer[0];
    rval /= 2;
    /* lossy conversion to ISO Latin1 */
    for (i=1;i<rval;i++){
        if (i > buflen)  /* destination buffer overflow */
            break;
        buf[i-1] = buffer[2 * i];
        if(buffer[2 * i + 1] != 0)  /* outside of ISO Latin1 range */
            buf[i-1] = '?';
    }
    buf[i-1] = 0;
    return i-1;
}


/* PowerSwitch uses the free shared default VID/PID. If you want to see an
 * example device lookup where an individually reserved PID is used, see our
 * RemoteSensor reference implementation.
 */

#define USB_ERROR_NOTFOUND  1
#define USB_ERROR_ACCESS    2
#define USB_ERROR_IO        3

static int 
usbOpenDevice(usb_dev_handle **device, int vendor, char *vendorName, int product, char *productName)
{
    struct usb_bus      *bus;
    struct usb_device   *dev;
    usb_dev_handle      *handle = NULL;
    int                 errorCode = USB_ERROR_NOTFOUND;
    static int          didUsbInit = 0;

    if (!didUsbInit){
        didUsbInit = 1;
        usb_init();
    }
    usb_find_busses();
    usb_find_devices();
    for (bus=usb_get_busses(); bus; bus=bus->next){
        for (dev=bus->devices; dev; dev=dev->next){
            if (dev->descriptor.idVendor == vendor && dev->descriptor.idProduct == product){
                char    string[256];
                int     len;
                handle = usb_open(dev); /* we need to open the device in order to query strings */
                if (!handle){
                    errorCode = USB_ERROR_ACCESS;
                    fprintf(stderr, "Warning: cannot open USB device: %s\n", usb_strerror());
                    continue;
                }
                if (vendorName == NULL && productName == NULL){  /* name does not matter */
                    break;
                }
                /* now check whether the names match: */
                len = usbGetStringAscii(handle, dev->descriptor.iManufacturer, 0x0409, string, sizeof(string));
                if (len < 0){
                    errorCode = USB_ERROR_IO;
                    fprintf(stderr, "Warning: cannot query manufacturer for device: %s\n", usb_strerror());
                } else {
                    errorCode = USB_ERROR_NOTFOUND;
                    /* fprintf(stderr, "seen device from vendor ->%s<-\n", string); */
                    if (strcmp(string, vendorName) == 0){
                        len = usbGetStringAscii(handle, dev->descriptor.iProduct, 0x0409, string, sizeof(string));
                        if (len < 0){
                            errorCode = USB_ERROR_IO;
                            fprintf(stderr, "Warning: cannot query product for device: %s\n", usb_strerror());
                        } else {
                            errorCode = USB_ERROR_NOTFOUND;
                            /* fprintf(stderr, "seen product ->%s<-\n", string); */
                            if (strcmp(string, productName) == 0)
                                break;
                        }
                    }
                }
                usb_close(handle);
                handle = NULL;
            }
        }
        if (handle)
            break;
    }
    if (handle != NULL){
        errorCode = 0;
        *device = handle;
    }
    return errorCode;
}


int
main(int argc, char **argv)
{
    usb_dev_handle      *handle = NULL;
    unsigned char       buffer[8];
    int                 nBytes;

    if (argc < 2){
        usage(argv[0]);
        exit(1);
    }
    usb_init();
    if (usbOpenDevice(&handle, USBDEV_SHARED_VENDOR, "www.gruvin9x.com", USBDEV_SHARED_PRODUCT, "gMeter-std") != 0){
        fprintf(stderr, "Could not find USB device \"TrafficMeter\" with vid=0x%x pid=0x%x\n", USBDEV_SHARED_VENDOR, USBDEV_SHARED_PRODUCT);
        exit(1);
    }
/* We have searched all devices on all busses for our USB device above, and found it.
 * The USB device is already "opened", as referenced by file handle, 'handle'.
 * Let's now perform our vendor specific control operations for the
 * function requested by the user.
 */
    if (strcmp(argv[1], "test") == 0){
        int i, v, r;
/* The test consists of writing 1000 random numbers to the device and checking
 * the echo. This should discover systematic bit errors (e.g. in bit stuffing).
 */
        for (i=0; i<1000; i++){
            v = rand() & 0xffff;
            nBytes = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, PSCMD_ECHO, 
                                      v, 0, (char *)buffer, sizeof(buffer), 5000);
            if (nBytes < 2){
                if (nBytes < 0)
                    fprintf(stderr, "USB error: %s\n", usb_strerror());
                fprintf(stderr, "only %d bytes received in iteration %d\n", nBytes, i);
                fprintf(stderr, "value sent = 0x%x\n", v);
                exit(1);
            }
            r = buffer[0] | (buffer[1] << 8);
            if (r != v){
                fprintf(stderr, "data error: received 0x%x instead of 0x%x in iteration %d\n", r, v, i);
                exit(1);
            }
        }
        printf("test succeeded\n");

    } else if (strcmp(argv[1], "status") == 0) {

        nBytes = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, PSCMD_GET, 
                                  0, 0, (char *)buffer, sizeof(buffer), 5000);
        if (nBytes < 2) {
            if(nBytes < 0)
                fprintf(stderr, "USB error: %s\n", usb_strerror());
            fprintf(stderr, "only %d bytes status received\n", nBytes);
            exit(1);
        }
        printf("Status=0x%4x\n", (buffer[0] + (buffer[1]<<8)));

    } else if (strcmp(argv[1], "alarm") == 0) {

      unsigned char alarmOn;
      if (argc > 2)
      {
        if (strcmp(argv[2], "off") == 0) alarmOn = 0;
        else if (strcmp(argv[2], "on") == 0) alarmOn = 1;
        else
        {
          nBytes = 0;
          usage(argv[0]);
          exit(1);
        }

        nBytes = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, PSCMD_ALARM, 
                              0/*wValue*/, alarmOn/*wIndex*/, (char *)buffer, sizeof(buffer), 5000);
      }

    } else { // assume an integer meter level has been provided

        int level;
        if (sscanf(argv[1], "%d", &level))
        {
          nBytes = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, PSCMD_SET, 
                                      0/*wValue*/, level/*wIndex*/, (char *)buffer, sizeof(buffer), 5000);
        } else {
            nBytes = 0;
            usage(argv[0]);
            exit(1);
        }
        if (nBytes < 0)
            fprintf(stderr, "USB error: %s\n", usb_strerror());
    }
    usb_close(handle);
    return 0;
}
