struct afd
{
    unsigned int n;
    struct line **transitions;
};

struct line
{
    char symbol;
    unsigned int next_state;
    struct line *next;
};

struct afd *initializeAFD();

int match(char *string, int s, int f, struct afd *t);
