#include <stdio.h>
#include "remote.h"

int main(int argc, char *argv[]) {
  remote_hid_t remote_data;
  hid_device *handle;
  int res;
  int i;

  handle = hid_open(REMOTE_TYPE, REMOTE_MAN, NULL);
  while (1) {
    res = hid_read(handle, (unsigned char*)&remote_data, REMOTE_BUFSIZE);
    print_remote_data(&remote_data);
  }

  return 0;
}
