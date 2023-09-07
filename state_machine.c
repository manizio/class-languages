#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state_machine.h"

// DDDDD-DDD

// Criar uma linha na tabela
struct line *create_line(char s, unsigned int i)
{
    // Aloca memória para uma linha
    struct line *l =  malloc(sizeof(struct line));

    // Insere o símbolo, número do próximo estado e o próximo estado (NULL)
    l->symbol = s;
    l->next_state = i;
    l->next = NULL;

    return l;
}

void insert_line(struct line **l, struct line *n)
{   
    // Insere a linha na tabela
    n->next = *l;
    *l = n;
}

void destroy_line (struct line *l)
{
    if (l != NULL)
    {
        destroy_line(l->next);
        free(l);
    }
}

void destroy_afd(struct afd *a)
{
    unsigned int i;
    for (i = 0; i < a->n; i++)
    {
        destroy_line(a->transitions[i]);
    }

    free(a->transitions);
}

void initializeAFD(struct afd *a)
{
    /*
    * DDDDD-DDD
    * 10 estados
    * começo = 0
    * final = 9
    */
    a->n = 10; 
    a->start = 0;
    a->final = 9;
    a->transitions = malloc(a->n * sizeof(struct line *));
    
    unsigned int i;
    char s;

    // Inicializa todas as transições em NULL
    for (i = 0; i < a->n; i++)
    {
        a->transitions[i] = NULL;
    }


    // Transições do estado 0 até o 4 podem receber qualquer digito de 0-9 
    for (i = 0; i <= 4; i++)
    {
        for (s = '0'; s <= '9'; s++)
        {
            insert_line(&a->transitions[i], create_line(s, i+1));
        }
    }


    // Transições do estado 5 caso receba um -
    insert_line(&a->transitions[5], create_line('-', 6));

    // Caso receba apenas números, pula para o estado 7
    for (s = '0'; s <= '9'; s++)
    {
        insert_line(&a->transitions[5], create_line(s, 7));
    }

    // Transições finais do estado 6 ao 8
    for (i = 6; i <= 8; i++)
    {
        for (s = '0'; s <= '9'; s++)
        {
            insert_line(&a->transitions[i], create_line(s, i + 1));
        }
    }

}

int match(char *string, struct afd *t)
{
    unsigned int current_state = t->start; // inicializa o estado atual
    unsigned int i = 0; // inicializa contador
    struct line *l; // inicializa uma linha da tabela
    
    while (string[i] != '\0')
    {
        l = t->transitions[current_state];

        while (l != NULL)
        {
            if (l->symbol == string[i])
            {
                current_state = l->next_state;
                break;
            }

            l = l->next;
        }

        if (l == NULL)  
        {   
            return 0;
        }

        i++;
    }

    if (current_state == t->final)
    {
        return 1;
    }
    return 0; // string não reconhecida
}

