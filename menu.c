#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "list.h"
#include "menu.h"
#include "display.h"
#include "validate.h"

void clearInputBuffer(){
    while(getchar() != '\n');
}

int askForInt(const char* ask_text, const char* error_text, int min, int max){
    while(true){
        printf("%s", ask_text);
        int v = 0;
        if(scanf("%i", &v) == 1 && v >= min && v <= max){
            clearInputBuffer();
            return v;
        }
        clearInputBuffer();
        printf("%s, oczekiwano liczby w zakresie od %i do %i\n", error_text, min, max);
    }
}

float askForFloat(const char* ask_text){
    while(true){
        printf("%s", ask_text);
        float v = 0;
        if(scanf("%f", &v) == 1){
            clearInputBuffer();
            return v;
        }
        clearInputBuffer();
        printf("niepoprawna wartosc\n");
    }
}

size_t askForText(const char* ask_text, const char* error_text, char* dest, size_t dest_size){
    while(true){
        printf("%s", ask_text);
        size_t i = 0;
        for(; i < dest_size; i++){
            char c = getchar();
            if(c == '\n'){
                if(i == 0) break;
                dest[i] = 0;
                return i;
            }

            dest[i] = c;
        }
        if(i == 0){
            printf("%s, tekst nie moze byc pusty\n", error_text);
        }
        else{
            printf("%s, podany tekst jest zbyt dlugi\n", error_text);
            clearInputBuffer();
        }
    }
}

void runEditMenu(Creature* cr){
    while(true){
        int opcja = 0;
        while(true){
            printf(
                "\n"
                "== menu edycji ==\n"
                "    nazwa:                    %s\n"
                " 2. gatunek:                  %s\n"
                " 3. ostatnio karmiony:        %s\n"
                " 4. moc magiczna:             %f\n"
                " 5. poziom niebezpieczenstwa: %i\n"
                " 6. stan:                     %s\n"
                " 0. powrot\n"
                ": ",
                cr->name, cr->gatunek, cr->last_feeding_date,
                cr->magic_power, cr->danger_level,
                gc_creature_state_names[cr->state]
            );
            if(scanf("%i", &opcja) == 1 && opcja >= 0 && opcja <= 6 && opcja != 1){
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            printf("Niepoprawna opcja, oczekiwano liczby w zakresie od 2 do 6 albo liczby 0\n");
        }

        if(opcja == 0) break;

        switch(opcja){
        case 2:
            askForText("Podaj nowy gatunek stworzenia: ", "Niepoprawny gatunek", cr->gatunek, GATUNEK_TEXT_SIZE);
            break;
        case 3:
            while(true){
                char new_date[DATE_TEXT_SIZE];
                askForText("Podaj nowa date karmienia: ", "Niepoprawna data", new_date, DATE_TEXT_SIZE);
                if(isValidDate(new_date)){
                    memcpy(cr->last_feeding_date, new_date, DATE_TEXT_SIZE);
                    break;
                }
                printf("Niepoprawna data, data musi byc w formacie yyyy-mm-dd\n");
            }
            break;
        case 4:
            while(true){
                float new_power = askForFloat("Podaj nowa moc magiczna: ");
                if(isValidMagicPower(new_power)){
                    cr->magic_power = new_power;
                    break;
                }
                printf("Niepoprawna wartosc mocy magicznej\n");
            }
            break;
        case 5:
            cr->danger_level = askForInt(
                "Podaj nowy poziom niebezpieczenstwa: ",
                "Niepoprawny poziom niebezpieczenstwa",
                DANGER_LEVEL_MIN, DANGER_LEVEL_MAX
            );
            break;
        case 6:
            if(cr->state == creature_state_dangerous){
                puts("Stworzenie niest w stanie niebezpiecznym, zmiana tego pola wymaga specialnych procedur.");
                break;
            }
            cr->state = (CreatureState)askForInt(
                "Podaj nowy stan stworzenia: \n"
                " 1) stabilny\n"
                " 2) niespokojny\n"
                " 3) agresywny\n"
                " 4) niebezpieczny\n"
                " 5) w kwarantanie\n",
                "Niepoprawny stan stworzenia",
                creature_state_first + 1,
                creature_state_count 
            ) - 1;
            break;
        }
    }
}

void runManagementMenu(Creature** head){
    while(true){
        int opcja = askForInt(
            "\n"
            "== menu zarzadzania ==\n"
            " 1. dodaj stworzenie\n"
            " 2. edytuj informacje o stworzeniu\n"
            " 3. usun stworzenie\n"
            " 4. wyswietl liste\n"
            " 0. powrot\n"
            ": ",
            "Niepoprawna opcja",
            0, 4
        );

        if(opcja == 0) break;

        switch(opcja){
        case 1:
            // addCreature(head);
            break;
        case 2:
            {
                char name[NAME_TEXT_SIZE];
                askForText("Podaj nazwe stworzenia: ", "Niepoprawna nazwa stworzenia", name, NAME_TEXT_SIZE);
                Creature* creature = creatureList_findByName(*head, name);
                if(creature == NULL) puts("Nie znaleziono stworzenia o takiej nazwie");
                else runEditMenu(creature);
            }
            break;
        case 3:
            // runDeleteMenu(head);
            break;
        case 4:
            creatureList_print(*head);
            break;
        }
    }
}

void runSearchMenu(Creature** head){
    while(true){
        int opcja = askForInt(
            "\n"
            "== menu wyszukiwania ==\n"
            " 1. wyszukiwanie po gatunku (pelne)\n"
            " 2. wyszukiwanie po gatunku (prefiksowe)\n"
            " 3. wyszukiwanie po poziomie niebezpieczenstwa\n"
            " 0. powrot\n"
            ": ",
            "Niepoprawna opcja",
            0, 3
        );

        if(opcja == 0) break;

        switch(opcja){
        case 1:
            // Creature* filtered = creatureList_filterBySpecies(head, species);
            // creatureList_print(filtered);
            // creatureList_free(filtered);
            break;
        case 2:
            // Creature* filtered = creatureList_filterBySpeciesPrefix(head, species);
            // creatureList_print(filtered);
            // creatureList_free(filtered);
            break;
        case 3:
            // Creature* filtered = creatureList_filterByDangerLevel(head, danger_level);
            // creatureList_print(filtered);
            // creatureList_free(filtered);
            break;
        }
    }
}

void runSortingMenu(Creature** head){
    while(true){
        int opcja = askForInt(
            "\n"
            "== menu sortowania ==\n"
            " 1. sortowanie po nazwie\n"
            " 2. sortowanie po mocy magicznej\n"
            " 3. wyswietl liste\n"
            " 0. powrot\n"
            ": ",
            "Niepoprawna opcja",
            0, 3
        );

        if(opcja == 0) break;

        switch(opcja){
        case 1:
            // creatureList_sortByName(head);
            break;
        case 2:
            // creatureList_sortByMagicPower(head);
            break;
        case 3:
            creatureList_print(*head);
            break;
        }
    }
}

void runMenu(Creature** head){
    while(true){
        int opcja = askForInt(
            "\n"
            "== menu glowne ==\n"
            " 1. zarzadzanie\n"
            " 2. wyszukiwanie\n"
            " 3. sortowanie\n"
            " 4. wyswietl liste\n"
            " 0. zapisz zmiany i zakoncz\n"
            ": ",
            "Niepoprawna opcja",
            0, 4
        );

        if(opcja == 0) break;

        switch(opcja){
        case 1:
            runManagementMenu(head);
            break;
        case 2:
            runSearchMenu(head);
            break;
        case 3:
            runSortingMenu(head);
            break;
        case 4:
            creatureList_print(*head);
            break;
        }
    }
}
