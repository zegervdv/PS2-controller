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

void convert_data(remote_hid_t* input, control_t* output) {
  output->indicator = 0x00;
  output->end = '\n';
  output->pitch = (M_PI / 480.0) * (103 - input->RY);
  printf("pitch = %f\n", output->pitch);
  output->roll = (M_PI / 480.0) * (input->RX - 118);
  printf("roll = %f\n", output->roll);
  output->yaw = (M_PI / 80.0) * (input->LX - 123);
  printf("yaw = %f\n", output->yaw);
  output->throttle = (100.0 / 80.0) * (113 - input->LY);
  printf("throttle = %f\n", output->throttle);
}
