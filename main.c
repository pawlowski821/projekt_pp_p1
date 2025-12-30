#include <stdio.h>

#include "types.h"
#include "list.h"
#include "display.h"
#include "fileio.h"

int main(int argc, char** argv){
    if(argc < 2){
        printf("use: %s <file>\n\n", argv[0]);
        return 0;
    }
    const char* file_path = argv[1];

    Creature* head = NULL;
    if(!creatureList_loadFromFile(&head, file_path)){
        return 1;
    }

    creatureList_simplePrint(head);

    creatureList_free(&head);
    return 0;
}
