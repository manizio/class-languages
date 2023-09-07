struct afd
{
    unsigned int n;
    unsigned int start;
    unsigned int final;
    struct line **transitions;
};

struct line
{
    char symbol;
    unsigned int next_state;
    struct line *next;
};

struct line *create_line(char s, unsigned int i);
void insert_line(struct line **l, struct line *n);
void destroy_line(struct line *l);

void initializeAFD(struct afd *a);
void destroy_afd(struct afd *a);


int match(char *string, struct afd *t);
