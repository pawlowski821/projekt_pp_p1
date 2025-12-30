#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include "types.h"
#include "list.h"
#include "fileio.h"

/*
format pliku (dla kazdego stworzenia):
<nazwa>
<gatunek>
<last_feeding_date>
<magic_power> <danger_level> <state>
*/

bool readLineSized(FILE* fin, char* dest, int size){
    for(int i = 0; i < size; i++){
        char c = fgetc(fin);
        if(feof(fin)){
            fputs("Nieoczekiwany koniec plkiu\n", stderr);
            return false;
        }
        if(c == '\r' || c == '\n'){
            if(c == '\r') c = fgetc(fin);
            if(i == 0){
                fputs("Pusty tekst jest niepoprawny\n", stderr);
                return false;
            }
            dest[i] = 0;
            return true;
        }
        dest[i] = c;
    }
    fprintf(stderr, "Tekst dluzszy niz %i znakow jest niepoprawny\n", size - 1);
    return false;
}

bool isValidDate(const char* text){
    // yyyy-mm-dd
    // 0123456789
    if(strlen(text) < 10) return false;
    if(text[4] != '-' || text[7] != '-') return false;
    if(!isdigit(text[0]) || !isdigit(text[1]) || !isdigit(text[2]) || !isdigit(text[3])) return false;
    if((text[5] != '0' && text[5] != '1') || !isdigit(text[6])) return false;
    if(text[5] == '1' && text[6] > '2') return false;
    if(text[5] == '0' && text[6] == '0') return false;
    if(!isdigit(text[8]) || !isdigit(text[9])) return false;
    return true;
}

bool isValidState(CreatureState state){
    return state >= creature_State_first && state < creature_state_count;
}

bool isValidDangerLevel(int danger_level){
    return danger_level >= DANGER_LEVEL_MIN && danger_level <= DANGER_LEVEL_MAX;
}

bool isValidMagicPower(float magic_power){
    return magic_power >= 0.0f;
}

bool skipUntilNewLine(FILE* fin){
    while(true){
        char c = fgetc(fin);
        if(c == '\r') continue;
        if(feof(fin) || c == '\n') return true;
        if(!isspace(c)) return false;
    }
}

bool creatureList_loadFromFile(Creature** head, const char* path){
    FILE* fin = fopen(path, "r");
    if(fin == NULL){
        fprintf(stderr, "Nie udalo sie otworzyc pliku \"%s\" do odczytu: %s\n", path, strerror(errno));
        return false;
    }

    bool success = true;

    while(!feof(fin)){
        Creature cr = {0};

        {
            char c = fgetc(fin);
            if(feof(fin)) break;
            ungetc(c, fin);
        }

        if(!readLineSized(fin, cr.name, sizeof(cr.name))){
            fprintf(stderr, "Nieporawna nazwa stworzenia\n");
            success = false;
            break;
        }

        if(!readLineSized(fin, cr.gatunek, sizeof(cr.gatunek))){
            fprintf(stderr, "\"%s\": Nieporawny gatunek stworzenia\n", cr.name);
            success = false;
            break;
        }

        if(!readLineSized(fin, cr.last_feeding_date, sizeof(cr.last_feeding_date)) || !isValidDate(cr.last_feeding_date)){
            fprintf(stderr, "\"%s\": Nieporawna data ostatniego karmienia\n", cr.name);
            success = false;
            break;
        }

        int n_read = fscanf(fin, "%f %i %i", &cr.magic_power, &cr.danger_level, (int*)&cr.state);
        if(n_read != 3){
            fprintf(stderr, "\"%s\": niepelnie informacje o stworzeniu\n", cr.name);
            success = false;
            break;
        }
        if(!isValidState(cr.state)){
            fprintf(stderr, "\"%s\": Niepoprawny stan stworzenia (%i)\n", cr.name, cr.state);
            success = false;
            break;
        }
        if(!isValidDangerLevel(cr.danger_level)){
            fprintf(stderr, "\"%s\": Niepoprawny poziom niebezpieczenstwa stworzenia (%i)\n", cr.name, cr.danger_level);
            success = false;
            break;
        }
        if(!isValidMagicPower(cr.magic_power)){
            fprintf(stderr, "\"%s\": Niepoprawna moc magiczna stworzenia (%f)\n", cr.name, cr.magic_power);
            success = false;
            break;
        }

        if(!skipUntilNewLine(fin)){
            fprintf(stderr, "\"%s\": Nieoczekiwane dane po informacjach o stworzeniu\n", cr.name);
            success = false;
            break;
        }

        if(!creatureList_append(head, &cr)){
            success = false;
            break;
        }
    }

    fclose(fin);

    if(!success){
        creatureList_free(head);
        fprintf(stderr, "Wczytanie pliku \"%s\" sie nie powiodlo\n", path);
        return false;
    }
    return true;
}

bool creatureList_writeToFile(Creature* head, const char* path){
    fprintf(stderr, "TODO: creatureList_writeToFile\n");
    return false;
}

