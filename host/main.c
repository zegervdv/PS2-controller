#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "remote.h"

#define BUFFER_SIZE (sizeof(control_t))

int main(int argc, char *argv[]) {
  remote_hid_t remote_data;
  hid_device *handle;
  int res;
  int i;
  int port;
  control_t controls;

  handle = hid_open(REMOTE_TYPE, REMOTE_MAN, NULL);
  port = open("/dev/tty.Quadcopter-1-RNI-SPP", O_RDWR | O_NOCTTY);
  if (port == -1) {
    fprintf(stderr, "Could not open port\n");
    exit(1);
  }

  while (1) {
    res = hid_read(handle, (unsigned char*)&remote_data, REMOTE_BUFSIZE);
    convert_data(&remote_data, &controls);
    res = write(port, (unsigned char*)&controls, BUFFER_SIZE);
    if (res < 0) {
      fprintf(stderr, "Could not write to port\n");
      exit(1);
    }
  }

  return 0;
}
