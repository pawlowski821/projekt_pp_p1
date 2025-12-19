#include <stdio.h>

#include "types.h"

int main(int argc, char** argv){
    printf("Dziala, %s\n", gc_creature_state_names[creature_state_anxious]);
    return 0;
}
