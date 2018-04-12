#include "util.h"

volatile int ms_ticks;

void delay(int ms){
    int start = ms_ticks;
    while(ms_ticks - start < ms);
}
