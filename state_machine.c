#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state_machine.h"

// DDDDD-DDD

#define NUM_STATES 9
#define START_STATE 1
#define FINAL_STATE 10
#define DASH_STATE 6
#define FINAL_DIGITS_STATE 7

struct afd *initializeAFD()
{
    struct afd *machine = (struct afd *) malloc(sizeof(struct afd));
    machine->n = NUM_STATES;
    machine->transitions = (struct line **) malloc(NUM_STATES * sizeof(struct line *));

    // inicializar as transições para cada estado
    for (int i = 0; i < NUM_STATES; i++)
    {
        machine->transitions[i] = NULL;
    }

    // transições para DIGIT_STATES (1-5)
    for (int i = 0; i <= 5; i++)
    {
        machine->transitions[i] = (struct line *) malloc (sizeof(struct line));
        machine->transitions[i]->symbol = 'D';
        machine->transitions[i]->next_state = i + 1;
        machine->transitions[i]->next = NULL;
    }

    // transição para DASH_STATE
    machine->transitions[5]->next_state = DASH_STATE;

    machine->transitions[DASH_STATE] = (struct line *) malloc (sizeof(struct line));
    machine->transitions[DASH_STATE]->symbol = '-';
    machine->transitions[DASH_STATE]->next_state = FINAL_DIGITS_STATE;
    machine->transitions[DASH_STATE]->next = NULL;

    // transições para FINAL_DIGIT_STATES (7-9)
    for (int i = 7; i <= 9; i++)
    {
        machine->transitions[i] = (struct line *) malloc (sizeof(struct line));
        machine->transitions[i]->symbol = 'D';
        machine->transitions[i]->next_state = i + 1;
        machine->transitions[i]->next = NULL;
    };

    return machine;
}

int match(char *string, int s, int f, struct afd *t)
{
    int current_state = START_STATE; // inicializa o estado atual

    for (int i = s; i <= f; i++)
    {
        char symbol = string[i]; 
        struct line *transition = t->transitions[current_state]; // obtem a transição atual

        while (transition != NULL){

            // para digitos
            if (transition->symbol == 'D' && symbol >= '0' && symbol <= '9') 
            {
                current_state = transition->next_state;
                break;
            }

            // para traço
            if (transition->symbol == '-' && symbol == '-')
            {
                current_state = transition->next_state;
                break;
            }

            // invalidar strings com traço fora do lugar
            if (symbol == '-' && current_state != DASH_STATE)
            {
                return 0;
            }

            transition = transition->next; // transiciona
        }


        if (transition == NULL)
        {
            return 0; // transição inválida
        }

        if (i == f && current_state == FINAL_STATE)
        {
            return 1; // string reconhecida
        }
    }

    return 0; // string não reconhecida
}

