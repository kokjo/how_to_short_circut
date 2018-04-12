#include "util.h"

void delay(int ms){
    int start = ms_ticks;
    while(ms_ticks - start < ms);
}
