#define MAX_STACK 100000
#define MAX_STRING 10000
#define MAX_INT 100

typedef enum {
    Char, 
    Int,
    Long,
    Float, 
    String, 
    Double,
    Array,
    Empty,
    Bloco
} TYPE;

struct STACK_Elem;

typedef struct STACK{
    struct STACK_Elem *stack;
    int sp;
} STACK;

typedef struct STACK_Elem{
    TYPE t;
    union saved_value {
        char c;
        char *str;
        double d;
        long l;
        float f;
        int i; 
        STACK* arr;
    } saved_value;
} STACK_Elem;

STACK *new_stack();
void push(STACK *s, STACK_Elem elem);
STACK_Elem pop(STACK *s);