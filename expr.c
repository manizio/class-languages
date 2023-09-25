 #include "state_machine.h"
 #include <stdio.h>
 #include <stdlib.h>

struct line *create_line(char s, unsigned int i)
{
    struct line *l = malloc(sizeof(struct line));

    l->symbol = s;
    l->next_state = i;
    l->next = NULL;

    return l;
}

void insert_line(struct line **l, struct line *n)
{
    n->next = *l;
    *l = n;
}

void destroy_line(struct line *l)
{
    if (l != NULL){
        destroy_line(l->next);
        free(l);
    }
}

void destroy_afd(struct afd *a)
{
    for (int i = 0; i < a->n; i++)
    {
        destroy_line(a->transitions[i]);
    }

    free(a->transitions);
}

 void create_afd(struct afd *a)
 {
    a->n = 3;
    a->start = 0;
    a->final = 1;
    a->transitions = malloc(a->n * sizeof(struct line *));

    // Inicializar todas as transições com NULL
    for (int i = 0; i < a->n; i++)
    {
        a->transitions[i] = NULL;
    }

    for (char s = '0'; s <= '9'; s++)
    {
        insert_line(&a->transitions[0], create_line(s, 1));
    }

    for (char s = '0'; s <= '9'; s++)
    {
        insert_line(&a->transitions[1], create_line(s, 1));
    }

    for (char s = '0'; s <= '9'; s++)
    {
        insert_line(&a->transitions[2], create_line(s, 1));
    }

    insert_line(&a->transitions[1], create_line('+', 2));
    insert_line(&a->transitions[1], create_line('-', 2));
    insert_line(&a->transitions[1], create_line('*', 2));
    insert_line(&a->transitions[1], create_line('/', 2));
 }

 int match(char *string, struct afd *t)
 {
    unsigned int current_state = t->start;
    unsigned int i = 0;
    struct line *l;

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

        if (l == NULL){
            return 0;
        }
        i++;
    }

    if (current_state == t->final)
    {
        return 1;
    }

    return 0;
 }

 int main(int argc, char *argv[])
 {
    struct afd a;

    create_afd(&a);
    printf("%d\n", match(argv[1], &a));
    destroy_afd(&a);
    return 0;
 }