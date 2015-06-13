#include "remote.h"

void print_remote_data(remote_hid_t* data) {
  printf("RY: %x - ", data->RY);
  printf("RX: %x", data->RX);
  printf("\n");
  printf("LY: %x - ", data->LY);
  printf("LX: %x", data->LX);
  printf("\n");
  printf("%d %d\n", data->buttons & REMOTE_BUTTON_R, data->buttons & REMOTE_BUTTON_L);
}
