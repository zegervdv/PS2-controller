#include <hidapi/hidapi.h>
#ifndef REMOTE_H
#define REMOTE_H

#define REMOTE_TYPE     (0x0400)
#define REMOTE_MAN      (0x5750)
#define REMOTE_BUFSIZE  (int)(5)

#define REMOTE_BUTTON_R (0x01)
#define REMOTE_BUTTON_L (0x02)

/**
 * Structure with HID data bytes from remote
 * buttons[0] - Right button
 * buttons[1] - Left button
 */
typedef struct {
  unsigned char RY;
  unsigned char RX;
  unsigned char LY;
  unsigned char LX;
  unsigned char buttons;
} remote_hid_t;
#endif

/**
 * Print data from remote to console
 */
void print_remote_data(remote_hid_t* data);
