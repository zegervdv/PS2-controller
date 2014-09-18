#include "stm32f0xx_conf.h"
#include "stm32f072b_discovery.h"

int main(int argc, char const* argv[])
{
  STM_EVAL_LEDInit(LED3); 
  STM_EVAL_LEDInit(LED4); 
  STM_EVAL_LEDInit(LED5); 
  STM_EVAL_LEDInit(LED6); 
  while(1) {
  }

  return 0;
}
