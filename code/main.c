#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "stack.h"

///
/// Funções de converção de tipo
/// @param x é o elemento da Stack a ser reconvertido 
/// @returns O elemento em tipo double
double to_double(STACK_Elem x) 
{
    if (x.t == Double) return x.saved_value.d;
    else if (x.t == Float) return x.saved_value.f;
    else if (x.t == Char) return x.saved_value.c;
    else if (x.t == Int) return x.saved_value.i;
    else if (x.t == String) return atof(x.saved_value.str);
    else if (x.t == Array) 
    {
        if (x.saved_value.arr->sp == 0)
            return 0;
        return 1;
    }
    else return x.saved_value.l;
}

/// @param x é o elemento da Stack a ser reconvertido 
/// @returns O elemento em tipo long
long to_long(STACK_Elem x) 
{
    if (x.t == Double) return x.saved_value.d;
    else if (x.t == Float) return x.saved_value.f;
    else if (x.t == Char) return x.saved_value.c;
    else if (x.t == Int) return x.saved_value.i;
    else if (x.t == String) return atol(x.saved_value.str);
    else return x.saved_value.l;
}

/// @param x é o elemento da Stack a ser reconvertido 
/// @returns O elemento em tipo integer
int to_int(STACK_Elem x) 
{
    if (x.t == Double) return x.saved_value.d;
    else if (x.t == Float) return x.saved_value.f;
    else if (x.t == Char) return x.saved_value.c;
    else if (x.t == Int) return x.saved_value.i;
    else if (x.t == String) return atoi(x.saved_value.str);
    else return x.saved_value.l;
}

/// @param x é o elemento da Stack a ser reconvertido 
/// @returns O elemento em tipo array de caracters (string)
char* to_string(STACK_Elem x) 
{
    char *str = malloc (sizeof (char) *MAX_STRING);
    sprintf(str, "%d", x.saved_value.c);
    if (x.t == Double) 
    {
        sprintf(str, "%g", x.saved_value.d);
        return str;
    } else if (x.t == Float) 
    {
        sprintf(str, "%g", x.saved_value.f);
        return str;
    } else if (x.t == Char) 
    {
        char ch = x.saved_value.c;
        strcpy(str, (char[2]) 
        {(char) ch, '\0'});
        return str;
    } else if (x.t == Int || x.t == Long) 
    {
        sprintf(str, "%ld", to_long(x));
        return str;
    } else return x.saved_value.str;
}

///
/// Função auxiliares de confirmação de tipo
int check_types(TYPE type1, TYPE type2) 
{
    return (type1 == String && type2 == String) || (type1 == String && type2 == Char) || (type1 == Char && type2 == String);
}

///
/// Função auxiliares de confirmação de tipo
int check_types2(TYPE type1, TYPE type2) 
{
    return (type1 == Double || type2 == Double || type1 == Float || type2 == Float);
}

///
/// Função que concatena duas strings
/// @param str1 a string para ficar no inicio
/// @param str2 a string para ficar no fim
/// @returns A string concatenada
char* concat(char *str1, char *str2) 
{
    char *result = malloc(strlen(str1) + strlen(str2) + 1); 
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

///
/// Função que adiciona dois elementos
/// @param s Um pointer para a Stack
/// @returns A soma de dois elementos se forem numeros, uma frase concatenada se forem string ou os menbros de dos arrays
void add(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);

    if (check_types2(x.t, y.t)) 
    {
        double result2 = to_double(x) + to_double(y);
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = result2}
        };
        push(s, result);
    } else if (check_types(x.t, y.t)) 
    { 
        STACK_Elem result = (STACK_Elem) 
        {
            .t = String,
            .saved_value = 
            {.str = concat(to_string(y), to_string(x))}
        };
        push(s, result);
    } else if (x.t == Array && y.t == Array) 
    {
        
        for (int i = 1; i <= x.saved_value.arr->sp; i++) 
        {
            push(y.saved_value.arr, x.saved_value.arr->stack[i]);
        }
        push(s, y);
    } else if (y.t == Array) 
    {
        push(y.saved_value.arr, x);
        push(s, y);
    } else if (x.t == Array) 
    {

        STACK *s2 = new_stack();
        push(s2, y);
        for (int i = 1; i <= x.saved_value.arr->sp; i++) 
        {
            push(s2, x.saved_value.arr->stack[i]);
        }

        STACK_Elem result = 
        {
            .t = Array,
            .saved_value = 
            {.arr = s2}
        };
        push(s, result);
    } else 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(x) + to_long(y)}
        };
        push(s, result);
    } 
}

///
/// Função que subtrai o primeiro elemento ao segundo
void sub(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);
        
    if (x.t == Double || y.t == Double || x.t == Float || y.t == Float) 
    {
        double result2 = to_double(x) - to_double(y);
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = result2}
        };
        push(s, result);
    } else 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(x) - to_long(y)}
        };
        push(s, result);
    }
}

int check_types3(TYPE t1) {
    return (t1 == Double || t1 == Float);
}

///
/// Função que decrementa uma unidade
void decrement(STACK *s) 
{
    STACK_Elem x = pop(s);

    if (check_types3(x.t)) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = to_double(x) - 1}
        };
        push(s, result);
    } else if (x.t == Long || x.t == Int) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(x) - 1}
        };
        push(s, result);
    } else if (x.t == Char && x.saved_value.c >= '!' && x.saved_value.c < '~')
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Char,
            .saved_value = 
            {.l = x.saved_value.c - 1}
        };
        push(s, result);
    } else if (x.t == String) 
    {

        STACK_Elem y = (STACK_Elem) 
        {
            .t = Char,
            .saved_value = 
            {.c = x.saved_value.str[0]}
        };

        memmove(x.saved_value.str, x.saved_value.str+1, strlen(x.saved_value.str));
        STACK_Elem result = (STACK_Elem) 
        {
            .t = String,
            .saved_value = 
            {.str = x.saved_value.str}
        };
        push(s, result);
        push(s, y);
    } else if (x.t == Array) 
    {
       
        STACK *s2 = new_stack();

        STACK_Elem result = (STACK_Elem) 
        {
            .t = Array,
            .saved_value = 
            {.arr = s2}
        };

        for (int i = 2; i <= x.saved_value.arr->sp; i++) 
        {
            push(s2, x.saved_value.arr->stack[i]);
        }

        push(s, result);
        push(s, x.saved_value.arr->stack[1]);
    }
}

///
/// Função que incrementa uma unidade
void increment(STACK *s) 
{
    STACK_Elem x = pop(s);
    char c;

    if (x.t == Double || x.t == Float) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = to_double(x) + 1}
        };
        push(s, result);
    } else if (x.t == Long || x.t == Int) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(x) + 1}
        };
        push(s, result);
    } else if (x.t == Char && x.saved_value.c >= '!' && x.saved_value.c < '~')
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Char,
            .saved_value = 
            {.l = x.saved_value.c + 1}
        };
        push(s, result);
    } else if (x.t == String) 
    {

        c = x.saved_value.str[strlen(x.saved_value.str) - 1];
        x.saved_value.str[strlen(x.saved_value.str) - 1] = '\0';
        STACK_Elem result1 = (STACK_Elem) 
        {
            .t = String,
            .saved_value = 
            {.str = x.saved_value.str}
        };

        STACK_Elem result = (STACK_Elem) 
        {
            .t = Char,
            .saved_value = 
            {.c = c}
        };

        push(s, result1);
        push(s, result);
    } else if (x.t == Array) 
    {

        STACK_Elem y = x.saved_value.arr->stack[x.saved_value.arr->sp];
        x.saved_value.arr->sp--;
        push (s, x);
        push(s, y);
    }
}

char* to_string2(STACK_Elem x) {
    char *str = malloc (sizeof (char) *MAX_STRING);
    sprintf(str, "%d", x.saved_value.c);
    if (x.t == Double) 
    {
        sprintf(str, "%g", x.saved_value.d);
        return str;
    } else if (x.t == Float) 
    {
        sprintf(str, "%g", x.saved_value.f);
        return str;
    } else if (x.t == Char) 
    {
        char ch = x.saved_value.c;
        strcpy(str, (char[2]) {(char) ch, '\0'});
        return str;
    } else if (x.t == Int || x.t == Long) 
    {
        sprintf(str, "%ld", to_long(x));
        return str;
    } else if (x.t == String) {
        char *str = strdup(x.saved_value.str);
        return concat(concat(" \"", str), "\"");
    } else {
        return NULL;
    }
}

void read_line(STACK *s, char *line, STACK_Elem *vars);

void multiply_blockArray_aux(STACK *s, STACK_Elem x, STACK_Elem y, STACK_Elem *vars) {

    char *str = strdup(x.saved_value.str);
    memmove(str, str+1, strlen(str));
    str[strlen(str)-1] = '\0';

    STACK *s2 = new_stack();
    int sp = y.saved_value.arr->sp;

    for (int i = 1; i <= sp; i++) 
        read_line(s2, concat(to_string2(y.saved_value.arr->stack[i]), " "), vars);
        // printf("%s", concat(to_string2(y.saved_value.arr->stack[i]), " "));

    for (int i = 1; i < sp; i++)
        read_line(s2, str, vars);
        //printf("%s", str);
        

    STACK_Elem result = {
        .t = Array,
        .saved_value = {.arr = s2}
    };

    push(s, result);
    
}

void multiply_array_aux(STACK *s, STACK_Elem x, STACK_Elem y, int *stack_pointer) {
    *stack_pointer = y.saved_value.arr->sp;
    for (int i = 1 ; i < to_long(x); i++) {
        for (int i = 1; i <= *stack_pointer; i++) {
            push(y.saved_value.arr, y.saved_value.arr->stack[i]);
        }
    }
    push(s, y);
}

void multiply_string_aux(STACK *s, STACK_Elem x, STACK_Elem y) {
    char *str;
    str = strdup(x.saved_value.str);
    for (int i = 1; i < to_long(y); i++) {
        strcat(x.saved_value.str, str);
    }
    push(s, x);
}

///
/// Função que efetua a multiplicação entre dois elementos
void multiply(STACK *s, STACK_Elem *vars) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
    int stack_pointer;
        
    if (check_types2(x.t, y.t)) 
    {
        double result2 = to_double(x) * to_double(y);
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = result2}
        };
        push(s, result);
    } else if (x.t == Array) 
    {
        stack_pointer = x.saved_value.arr->sp;
        for (int i = 1 ; i < to_long(y); i++) 
        {
            for (int i = 1; i <= stack_pointer; i++) 
            {
                push(x.saved_value.arr, x.saved_value.arr->stack[i]);
            }
        }
        push(s, x);
    } else if (x.t == Bloco && y.t == Array) {

        multiply_blockArray_aux(s, x, y, vars);

    } else if (y.t == Array) {
        
        multiply_array_aux(s, x, y, &stack_pointer);

    } else if (x.t == String) {
        
        multiply_string_aux(s, x, y);

    } else if (y.t == String) {
        multiply_string_aux(s, y, x);

    } else {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(x) * to_long(y)}
        };
        push(s, result);
    }
}

///
/// Função que exponencializa um elemento noutro
void exponentiation(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
        
    if (x.t == Double || y.t == Double || x.t == Float || y.t == Float) 
    {
        double result2 = pow(to_double(y), to_double(x));
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = result2}
        };
        push(s, result);
    } else if (x.t == String && y.t == String) 
    {

        int location = -1;
        char *str = y.saved_value.str;
        char *p = strstr(y.saved_value.str, x.saved_value.str);
        if (p != NULL) 
        {
            location = (long int)p - (long int)str;
        }

        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long, 
            .saved_value = 
            {.l = location}
        };
        push(s, result);
    } else 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = pow(to_long(y), to_long(x))}
        };
        push(s, result);
    }
}

void module_blockArray_aux(STACK_Elem x, STACK_Elem y, STACK *s, STACK_Elem *vars) {

    char *str = strdup(x.saved_value.str);
    memmove(str, str+1, strlen(str));
    str[strlen(str)-1] = '\0';

    STACK *s2 = new_stack();

    for (int i = 1; i <= y.saved_value.arr->sp; i++) {
        read_line(s2, concat(to_string2(y.saved_value.arr->stack[i]), str), vars);
    }

    STACK_Elem result = {
        .t = Array,
        .saved_value = {.arr = s2}
    };

    push(s, result);

}

void module_blockStrings_aux(STACK *s, STACK_Elem x, STACK_Elem y, STACK_Elem *vars) {

    STACK *stack2 = new_stack();
    char *s1 = strdup(x.saved_value.str);
    s1[strlen(s1)-1] = '\0';
    memmove(s1, s1+1, strlen(s1));

    char *s2 = strdup(y.saved_value.str);

    int size = strlen(s2), flag = 0;
    char *str = malloc(sizeof(char) * 1000);
    char *str3 = malloc(sizeof(char) * 100);

    for (int i = 0; i < size; i++) {
        if (s2[i] != '\n') {
            sprintf(str3, "%d", (int)s2[i]);
            char str2[] = {' ', 'c' , '\0'};
            str = concat(str, concat(strdup(concat(str3, str2)), s1));
        }
    }
    read_line(stack2, str, vars);

    char *str4 = malloc(sizeof(char));
    for (int i = 1; i <= stack2->sp; i++) {
        if (flag == 0) { 
            str4 = to_string(stack2->stack[i]);
            flag = 1;
        } else 
            str4 = concat(str4, to_string(stack2->stack[i]));
    }

    STACK_Elem result = {
        .t = String,
        .saved_value = {.str = str4}
    };
    push(s, result);

}

///
/// Função que retorna o modulo de um numero
void module(STACK *s, STACK_Elem *vars) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
        
    if (check_types2(x.t, y.t)) {
        long result2 = to_long(x) % to_long(y);
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = result2}
        };
        push(s, result);

    } else if (x.t == Bloco && y.t == Array) {

        module_blockArray_aux(x, y, s, vars);
        
    } else if (x.t == Bloco && y.t == String) {

        module_blockStrings_aux(s, x, y, vars);

    } else {

        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(y) % to_long(x)}
        };
        push(s, result);
    }
}

// bitwises retornam sempre 32-bit signed integer informação importante ?????

///
///  Funções Bitwise
///
/// Função ( XOR ) que retorna um numero se os dois introduzidos forem diferentes e 0 se forem igauis
void hat(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);
        
    if (x.t == Double || y.t == Double || x.t == Float || y.t == Float) 
    {
        long result2 = to_long(x) ^ to_long(y);
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = result2}
        };
        push(s, result);
    } else 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(x) ^ to_long(y)}
        };
        push(s, result);
    }
}

///
/// Função ( & ) que retorna um numero apenas quandos os dois elementos são iguais e diferentes de 0
void and(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
        
    long result2 = to_long(x) & to_long(y);
    STACK_Elem result = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = result2}
    };
        push(s, result);
}

///
/// Função ( OR ) que retorna um numero se um dos elementos for diferente de 0 e se ambos forem 0 retorna 0
void barra(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
        
    long result2 = to_long(x) | to_long(y);
    STACK_Elem result = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = result2}
    };
        push(s, result);
}

///
/// Função ( NOT ) que retorna os bits invertidos de um numero
void til(STACK *s, STACK_Elem *vars) 
{
    STACK_Elem x = pop(s);

    if (x.t == Array) 
    { // colocar todos os elementos do array na stack
        for (int i = 1; i <= x.saved_value.arr->sp; i++) {
            push(s, x.saved_value.arr->stack[i]);
        } 
    } else if (x.t == Bloco) {
        char *str = strdup(x.saved_value.str);
        str[strlen(str)-1] = '\0';
        memmove(str, str+1, strlen(str));

        read_line(s, str, vars);

    } else {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = ~to_long(x)}
        };
        push(s, result);
    }
}

///
/// Função que divide um elemento por outro
void divide(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
        
    if (check_types2(x.t, y.t)) 
    {
        double result2 = to_double(y) / to_double(x);
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = result2}
        };\
        push(s, result);
    } else if (x.t == String && y.t == String) 
    {
        STACK *s2 = new_stack();

        char *p;
        char *str1 = y.saved_value.str;
        char *str2 = x.saved_value.str;
        int length_str2 = strlen(str2);
        char *str3;

        p = strstr(str1, str2);

        while (p != NULL) 
        {
            int limit = (long int)p - (long int)str1;
            str3 = strdup(p);
            if (limit >= 0) str1[limit] = '\0';

            if (str1[0] != '\0') 
            {
                STACK_Elem result = 
                {
                    .t = String,
                    .saved_value = 
                    {.str = strdup(str1)}
                };
                push(s2, result);
            }

            str1 = str3;
            memmove(str1, str1+length_str2, strlen(str1));
            
            p = strstr(str1, str2);

            if (p == NULL && str1[0] != '\0') 
            {
                STACK_Elem result = 
                {
                    .t = String,
                    .saved_value = 
                    {.str = strdup(str1)}
                };
                push(s2, result);
            }
        }

        STACK_Elem result2 = 
        {
            .t = Array, 
            .saved_value = 
            {.arr = s2}
        };
        push(s, result2);

    } else 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = to_long(y) / to_long(x)}
        };
        push(s, result);
    }
}

///
/// Função que duplica um elemento da Stack
void doubles(STACK *s) 
{
    STACK_Elem x = pop(s);
    push(s, x);
    push(s, x);
}

///
/// Função que retira um elemento da Stack
void popVoid(STACK *s) 
{
    pop(s);
}

///
/// Função que troca a ordem de dois elementos na Stack
void swap(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);

    push(s, x);
    push(s, y);
} 

///
/// Função que roda 3 elementos da Stack
void rotate (STACK *s) 
{
    STACK_Elem z = pop(s);
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);

    push(s, y);
    push(s, z);
    push(s, x);
}

///
/// Função auxiliar de outra função
/// @see dollar(STACK *s)
STACK_Elem dollarAux(STACK *s, STACK_Elem n) 
{
    STACK_Elem r = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 0}
    };
    while(n.saved_value.l>=0) 
    {
        r = pop(s);
        n.saved_value.l--;
    }
    return r;
}

///
/// Função que copia n-ésimo elemento para o topo da stack e a função auxiliar
void dollar(STACK *s, STACK_Elem *vars) 
{
    STACK_Elem r;
    STACK_Elem n = pop(s);
    STACK *d = new_stack();       
    *d = *s;
    
    if (n.t == Long) {
        r = dollarAux(d, n);
        push(s, r);
    } else if (n.t == Bloco) {
        STACK_Elem m = pop(s);
        int sp = m.saved_value.arr->sp;

        if (m.t == Array) {

            char *str = strdup(n.saved_value.str);
            memmove(str, str+1, strlen(str));
            str[strlen(str)-1] = '\0';
    
            STACK *s2 = new_stack();
    
            for (int i = 1; i <= sp; i++) {
                read_line(s2, concat(to_string2(m.saved_value.arr->stack[i]), str), vars);
            }

            int i, j, t;

            for(i = 1; i < sp; i++) {
                t = i;
                for (j = i+1; j <= sp; j++)
                    if (to_long(s2->stack[j]) < to_long(s2->stack[t]))
                        t = j;

                if (t != i) {
                    STACK_Elem temp1 = s2->stack[i];
                    s2->stack[i] = s2->stack[t];
                    s2->stack[t] = temp1;

                    STACK_Elem temp2 = m.saved_value.arr->stack[i];
                    m.saved_value.arr->stack[i] = m.saved_value.arr->stack[t];
                    m.saved_value.arr->stack[t] = temp2;
                }
            }

            STACK_Elem result2 = {
                .t = Array,
                .saved_value = {.arr = m.saved_value.arr}
            };
            push(s, result2);
        }

    }
}

///
/// Função que converte um elemento para um integer
void convert_to_int(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = (STACK_Elem) 
    {
        .t = Int,
        .saved_value = 
        {.i = to_int(x)}
    };
    push(s, y);
}

///
/// Função que converte um elemento para um double
void convert_to_double(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = (STACK_Elem) 
    {
        .t = Double,
        .saved_value = 
        {.d = to_double(x)}
    };
    push(s, y);
}

///
/// Função que converte um elemento para uma character
void convert_to_char(STACK *s) 
{
    STACK_Elem x = pop(s);
    long l = to_long(x);

    if (x.t == Int || x.t == Long)  
    {
        STACK_Elem y = (STACK_Elem) 
        {
        .t = Char,
        .saved_value = 
        {.c = l}
    };
    push(s, y);
    }
}

///
/// Função que converte um elemento para um array de characters
void convert_to_string(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = (STACK_Elem) 
    {
        .t = String,
        .saved_value = 
        {.str = to_string(x)}
    };
    push(s, y);
}

///
/// Função que lê mais uma linha
void line_input(STACK *s) 
{

    char *line = malloc(sizeof(char) * MAX_STRING);
    if (fgets(line, MAX_STRING, stdin) != NULL) 
    {
        STACK_Elem x = (STACK_Elem) 
        {
        .t = String,
        .saved_value = 
        {.str = line}
    };
    push(s, x);
    }
}

///
/// Função que retorna o segundo elemento se o primeiro não for 0, senão retorna o 3 elemento
void if_else (STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
    STACK_Elem z = pop(s);

    if (z.t == Float || z.t == Double || z.t == Array) 
    {
        if (to_double(z) == 0) 
            push(s, x);
        else
            push(s, y);
    } else if (z.t == Int || z.t == Long) 
    {
        if (to_long(z) == 0) 
            push(s, x);
        else
            push(s, y);
    } else push(s, y);
}

void equal_array_aux(STACK_Elem y, STACK_Elem x, STACK *s2, STACK *s) {

    for (int i = y.saved_value.arr->sp; i > 0; i--) {
        push(s2, y.saved_value.arr->stack[i]);
    }

    for (int i = 0; i < to_long(x); i++) pop(s2);
    push(s, s2->stack[s2->sp]);

}

///
/// Função que retorna 1 se os 2 elementos forem iguais e 0 caso contrario
void equal(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);

    STACK_Elem vdd = (STACK_Elem) {
        .t = Long,
        .saved_value = 
        {.l = 1}
    };

    STACK_Elem falso = (STACK_Elem) {
        .t = Long,
        .saved_value = 
        {.l = 0}
    };

    if (check_types(x.t, y.t)) {
        if (strcmp(to_string(x), to_string(y)) == 0) 
            push(s, vdd);
        else 
            push(s, falso);
    } else if (x.t == String) {
        STACK_Elem result = (STACK_Elem) {
            .t = Char,
            .saved_value = 
            {.c = x.saved_value.str[to_long(y)]}
        };
        push(s, result);
    } else if (y.t == String) {
        STACK_Elem result = (STACK_Elem) {
            .t = Char,
            .saved_value = 
            {.c = y.saved_value.str[to_long(x)]}
        };
        push(s, result);
    } else if (y.t == Array) {        
        
        STACK *s2 = new_stack();
        equal_array_aux(y, x, s2, s);

    } else if (x.t == Array) {

        STACK *s2 = new_stack();
        equal_array_aux(x, y, s2, s);

    } else {
        if (to_double(x) == to_double(y)) {
            push(s, vdd);
        } else 
            push(s, falso);
    } 
}

/* Quando digo primeiro elemento estou me a referir ao primeiro elemento que foi introduzido 
 que enfluencia a função mas pela ordem da Stack o primeiro é o ultimo a ser introduzido 
 Não sei se isto é obvio ao se devia deixar explicito ????? 
*/

///
/// Função que verifica se o primeiro elemento é maior que o segundo e retorna 1 caso seja ou 0 caso não
void greater(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);
    char *str = malloc(sizeof(char) * MAX_STRING);
    STACK_Elem vdd = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 1}
    };

    STACK_Elem falso = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 0}
    };

    if (check_types2(x.t, y.t)) 
    {
        if (to_double(x) > to_double(y)) 
        {
            push(s, vdd);
        } else 
            push(s, falso);
    } else if (check_types(x.t, y.t)) 
    { 
        if (strcmp(to_string(x), to_string(y)) > 0) 
            push(s, vdd);
        else 
            push(s, falso);
    } else if (x.t == String) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = String,
            .saved_value = 
            {.str = strdup(strncpy(str, x.saved_value.str + strlen(x.saved_value.str) - to_long(y), strlen(x.saved_value.str)))}
        };
        push(s, result);
    } else if (x.t == Array) 
    {
        STACK *s2 = new_stack();
        STACK_Elem *array = malloc(sizeof(STACK_Elem) * 1000);
        
        for (int i = to_long(y); i > 0; i--) 
            array[i] = pop(x.saved_value.arr);
        
        for (int i = 1; i <= to_long(y); i++) 
        {
            push(s2, array[i]);
        }

        STACK_Elem result = 
        {
            .t = Array,
            .saved_value = 
            {.arr = s2}
        };
 
        push(s, result);
    } else 
    {
        if (to_long(x) > to_long(y)) 
        {
            push(s, vdd);
        } else 
            push(s, falso);
    } 
}

///
/// Função que verifica se o primeiro elemento é menor que o segundo e retorna 1 caso seja ou 0 caso não
void minor(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);
    char *str = malloc(sizeof(char) * MAX_STRING);
    STACK_Elem vdd = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 1}
    };

    STACK_Elem falso = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 0}
    };

    if (check_types2(x.t, y.t)) 
    {
        if (to_double(x) < to_double(y)) 
        {
            push(s, vdd);
        } else 
            push(s, falso);
    } else if (check_types(x.t, y.t)) 
    { 
        if (strcmp(to_string(x), to_string(y)) < 0) 
            push(s, vdd);
        else 
            push(s, falso);
    } else if (x.t == String) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = String,
            .saved_value = 
            {.str = strdup(strncpy(str, x.saved_value.str, to_long(y)))}
        };
        push(s, result);
    } else if (y.t == String) 
    {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = String,
            .saved_value = 
            {.str = strdup(strncpy(str, y.saved_value.str, to_long(x)))}
        };
        push(s, result);
    } else if (x.t == Array) 
    {
        x.saved_value.arr->sp = to_long(y);
        push(s, x);
    } else 
    {
        if (to_long(x) < to_long(y)) 
        {
            push(s, vdd);
        } else 
            push(s, falso);
    } 
}

///
/// Função que verifica se o primeiro elemento é maior que o segundo e retorna o maior
void eGreater(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);

    if (x.t == Float || x.t == Double || y.t == Float || y.t == Double) 
    {
        if (to_double(x) > to_double(y)) push(s,x);
        else push(s,y);
    } else if (x.t == String && y.t == String) 
    {
        if (strcmp(x.saved_value.str, y.saved_value.str) > 0) 
            push(s, x);
        else 
            push(s, y);
    } else 
    {
        if (to_long(x) > to_long(y)) push(s,x);
        else push(s,y);
    }
}

///
/// Função que verifica se o primeiro elemento é menor que o segundo e retorna o menor
void eMinor(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);

     if (x.t == Float || x.t == Double || y.t == Float || y.t == Double) 
     {
        if (to_double(x) < to_double(y)) push(s,x);
        else push(s,y);
    } else if (x.t == String && y.t == String) 
    {
        if (strcmp(x.saved_value.str, y.saved_value.str) < 0) 
            push(s, x);
        else 
            push(s, y);
    } else 
    {
        if (to_long(x) < to_long(y)) push(s,x);
        else push(s,y);
    }

}

///
/// Função que retorna 1 caso o elemento seja 0 e retorna 0 caso seja qualquer outro numero
void negation(STACK *s) 
{
    STACK_Elem x = pop(s);

    STACK_Elem vdd = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 1}
    };

    STACK_Elem falso = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 0}
    };

    if (x.t == Float || x.t == Double) 
    {
        if (to_double(x) == 0) 
            push(s, vdd);
        else 
            push(s, falso);
    } else 
    {
        if (to_long(x) == 0)
            push(s, vdd);
        else 
            push(s, falso);
    }
}

///
/// Função que retorna 0 caso um dos dois elementos sejam 0 e retornam o primeiro caso contrario
void eShortcut(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);

    STACK_Elem zero = (STACK_Elem) 
    {
        .t = Long,
        .saved_value = 
        {.l = 0}
    };

    if (x.t == Float || x.t == Double || y.t == Float || y.t == Double) 
    {
        if (to_double(x) == 0 || to_double(y) == 0)
            push(s, zero);
        else
            push(s,x);
    } else 
    {
        if (to_long(x) == 0 || to_long(y) == 0)
            push(s, zero);
        else
            push(s,x);
    }    
}

///
/// Função que retorna o segundo elemento caso o primeiro elemento seja 0 e retornam o primeiro caso contrario
void ouShortcut(STACK *s) 
{
    STACK_Elem y = pop(s);
    STACK_Elem x = pop(s);

    if (x.t == Float || x.t == Double || y.t == Float || y.t == Double) 
    {
        if (to_double(x) != 0 )
            push(s, x);
        else
            push(s,y);
    } else 
    {
        if (to_long(x) != 0)
            push(s, x);
        else
            push(s,y);
    }
}

void topA(STACK *s, STACK_Elem *vars) 
{

    if (vars[0].t != Empty) 
    {
        push(s, vars[0]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 10}
        };
        push(s, y);
    }
}

void topB(STACK *s, STACK_Elem *vars) 
{

    if (vars[1].t != Empty) 
    {
        push(s, vars[1]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 11}
        };
        push(s, y);
    }
}

void topC(STACK *s, STACK_Elem *vars) 
{

    if (vars[2].t != Empty) 
    {
        push(s, vars[2]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 12}
        };
        push(s, y);
    }
}

void topD(STACK *s, STACK_Elem *vars) 
{

    if (vars[3].t != Empty) 
    {
        push(s, vars[3]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 13}
        };
        push(s, y);
    }
}

void topE(STACK *s, STACK_Elem *vars) 
{

    if (vars[4].t != Empty) 
    {
        push(s, vars[4]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 14}
        };
        push(s, y);
    }
}

void topF(STACK *s, STACK_Elem *vars) 
{

    if (vars[5].t != Empty) 
    {
        push(s, vars[5]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 15}
        };
        push(s, y);
    }
}

void topN(STACK *s, STACK_Elem *vars) 
{

    if (vars[13].t != Empty) 
    {
        push(s, vars[13]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Char,
            .saved_value = 
            {.c = '\n'}
        };
        push(s, y);
    }
}

void topS(STACK *s, STACK_Elem *vars) 
{

    if (vars[18].t != Empty) 
    {
        push(s, vars[18]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Char,
            .saved_value = 
            {.c = ' '}
        };
        push(s, y);
    }
}

void topX(STACK *s, STACK_Elem *vars) 
{

    if (vars[23].t != Empty) 
    {
        push(s, vars[23]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 0}
        };
        push(s, y);
    }
}

void topY(STACK *s, STACK_Elem *vars) 
{

    if (vars[24].t != Empty) 
    {
        push(s, vars[24]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 1}
        };
        push(s, y);
    }
}

void topZ(STACK *s, STACK_Elem *vars) 
{

    if (vars[25].t != Empty) 
    {
        push(s, vars[25]);
    } else 
    {
        STACK_Elem y = (STACK_Elem) 
        {
            .t = Long,
            .saved_value = 
            {.l = 2}
        };
        push(s, y);
    }
}

void setAll(STACK *s, STACK_Elem *vars, unsigned int i) 
{
    STACK_Elem x = pop(s);
    vars[i] = x;
    push(s, x);
}  


void topAll(STACK *s, STACK_Elem *vars, unsigned int i) 
{  
    int pos = i - 26;
    if (vars[pos].t != Empty) 
    {
        push(s, vars[pos]);
    }
}

void comma(STACK *s, STACK_Elem *vars) {
    STACK_Elem x = pop(s);

    if (x.t == String || x.t == Char) {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = strlen(to_string(x))}
        };
        push(s, result);
    } else if (x.t == Array) {
        STACK_Elem result = (STACK_Elem) 
        {
            .t = Double,
            .saved_value = 
            {.d = x.saved_value.arr->sp}
        };
        push(s, result);
    } else if (x.t == Bloco) {
        STACK_Elem y = pop(s);

        if (y.t == Array) {

            char *str = strdup(x.saved_value.str);
            memmove(str, str+1, strlen(str));
            str[strlen(str)-1] = '\0';
            STACK *s2 = new_stack();

            for (int i = 1; i <= y.saved_value.arr->sp; i++) {
                read_line(s, concat(to_string2(y.saved_value.arr->stack[i]), str), vars);
                STACK_Elem check = pop(s);

                if (to_long(check) == 1) {
                    push(s2, y.saved_value.arr->stack[i]);
                }
            }
            STACK_Elem result = {
                .t = Array,
                .saved_value = {.arr = s2}
            };
            push(s, result);
            
        }

    } else {
        int i, count = to_long(x);
        STACK *s2 = new_stack();

        for (i = 0; i < count; i++) 
        {
            STACK_Elem result = (STACK_Elem) 
            {
                .t = Long,
                .saved_value = 
                {.l = i}
            };
            push(s2, result);
        }
        
        STACK_Elem result2 = (STACK_Elem) 
        {
            .t = Array,
            .saved_value = 
            {.arr = s2}
        };
        push(s, result2);
    }
}

void text_input(STACK *s) 
{
    char *line = malloc(sizeof(char) * MAX_STRING);
    char *text = malloc(sizeof(char));
    while (fgets(line, MAX_STRING, stdin) != NULL) 
    {
        text = concat(text, line);
    }
    
    STACK_Elem result = 
    {
        .t = String,
        .saved_value = {.str = text}
    };
    push(s, result);
}

void split_by_whitespace(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK *s2 = new_stack();

    char *yep;
    yep = strtok (x.saved_value.str, " \t\r\n\v\f");

    while(yep != NULL) 
    {
        STACK_Elem result = 
        {
            .t = String,
            .saved_value = 
            {.str = strdup(yep)}
        };
        push(s2, result);
        yep = strtok(NULL, " \t\r\n\v\f");
    }

    STACK_Elem result2 = 
    {
        .t = Array,
        .saved_value = 
        {.arr = s2}
    };
    push(s, result2);
}

void split_by_newlines(STACK *s) 
{
    STACK_Elem x = pop(s);
    STACK *s2 = new_stack();

    char *yep;
    yep = strtok (x.saved_value.str, "\n");

    while(yep != NULL) 
    {
        STACK_Elem result = 
        {
            .t = String,
            .saved_value = 
            {.str = strdup(yep)}
        };
        push(s2, result);
        yep = strtok(NULL, "\n");
    }

    STACK_Elem result2 = 
    {
        .t = Array,
        .saved_value = 
        {.arr = s2}
    };
    push(s, result2);
}

void loop_while(STACK *s, STACK_Elem *vars) {
    STACK_Elem x = pop(s);
    STACK_Elem y = pop(s);
    int check = to_int(y);

    while (check != 0) {

        char *str = strdup(x.saved_value.str);
        memmove(str, str+1, strlen(str));
        str[strlen(str)-1] = '\0';

        char *str2 = to_string(y);
        read_line(s, concat(str2, str), vars);

        check = to_int(pop(s));
        y = pop(s);

    }
    push(s, y);
}

int token_lookup(char *token, STACK *s, STACK_Elem *vars) 
{

    typedef struct fn_table_entry 
    {
        char *token;
        void (*fn)();
    } token_table_entry;

    token_table_entry token_table[] = 
    {
        {":A", setAll},
        {":B", setAll},
        {":C", setAll},
        {":D", setAll},
        {":E", setAll},
        {":F", setAll},
        {":G", setAll},
        {":H", setAll},
        {":I", setAll},
        {":J", setAll},
        {":K", setAll},
        {":L", setAll},
        {":M", setAll},
        {":N", setAll},
        {":O", setAll},
        {":P", setAll},
        {":Q", setAll},
        {":R", setAll},
        {":S", setAll},
        {":T", setAll},
        {":U", setAll},
        {":V", setAll},
        {":W", setAll},
        {":X", setAll},
        {":Y", setAll},
        {":Z", setAll},
        {"A", topA},
        {"B", topB},
        {"C", topC},
        {"D", topD},
        {"E", topE},
        {"F", topF},
        {"G", topAll},
        {"H", topAll},
        {"I", topAll},
        {"J", topAll},
        {"K", topAll},
        {"L", topAll},
        {"M", topAll},
        {"N", topN},
        {"O", topAll},
        {"P", topAll},
        {"Q", topAll},
        {"R", topAll},
        {"S", topS},
        {"T", topAll},
        {"U", topAll},
        {"V", topAll},
        {"W", topAll},
        {"X", topX},
        {"Y", topY},
        {"Z", topZ},
        {"+", add}, 
        {"-", sub},
        {"(", decrement},
        {")", increment},
        {"*", multiply},
        {"#", exponentiation},
        {"%", module},
        {"^", hat},
        {"&", and},
        {"|", barra},
        {"/", divide},
        {"~", til},
        {"_", doubles},
        {";", popVoid},
        {"\\", swap},
        {"@", rotate},
        {"$", dollar},
        {"i", convert_to_int},
        {"f", convert_to_double},
        {"c", convert_to_char},
        {"s", convert_to_string},
        {"l", line_input},
        {"?", if_else},
        {"=", equal},
        {">", greater},
        {"<", minor},
        {"!", negation},
        {"e&", eShortcut},
        {"e|", ouShortcut},
        {"e<", eMinor},
        {"e>", eGreater},
        {",", comma},
        {"t", text_input},
        {"S/", split_by_whitespace},
        {"N/", split_by_newlines},
        {"w", loop_while}
    };

    for (unsigned int i = 0; i < sizeof(token_table)/sizeof(token_table[0]); ++i) 
        if (!strcmp(token, token_table[i].token)) 
        {
            token_table[i].fn(s, vars, i);
            return 1;
        }
    
    return 0;
}

void check_token(char *token, STACK *s, STACK_Elem *vars) 
{
    if (token_lookup(token, s, vars) == 0) 
    {
        char *end;
        errno = 0;
        long  result1 = strtol(token, &end, 0);
        if (errno == 0 && *end == '\0') 
        {
            STACK_Elem x1 = (STACK_Elem) 
            { // LONG
                .t = Long,
                .saved_value = 
                {.l = result1}
            };
            push(s, x1);
        } else 
        {
            errno = 0;
            float result2 = strtof(token, &end); // FLOAT
            if (errno == 0 && *end == '\0') 
            {
                STACK_Elem x2 = (STACK_Elem) 
                {
                    .t = Float,
                    .saved_value = 
                    {.f = result2}
                };
                push(s, x2);
            } else 
            {
                errno = 0;
                double result3 = strtod(token, &end); // DOUBLE
                if (errno == 0 && *end == '\0') 
                {
                    STACK_Elem x3 = (STACK_Elem) 
                    {
                        .t = Double,
                        .saved_value = 
                        {.d = result3}
                    };
                    push(s, x3);
                } else if (strlen(token) == 1) 
                {
                    STACK_Elem x4 = (STACK_Elem) 
                    {
                        .t = Char,
                        .saved_value = 
                        {.c = token[0]}
                    };
                    push(s, x4);
                } 
            } 
        }
    }
}

///
/// Função que Imprime todos os elementos da Stack depois de feitas todas as operações independentemente de tipo.
void printStack(STACK *s) 
{
    for (int i = 1; i <= s->sp; i++) 
    {
        if (s->stack[i].t == Long)
            printf("%ld", s->stack[i].saved_value.l);
        else if (s->stack[i].t == Int)
            printf("%d", s->stack[i].saved_value.i);
        else if (s->stack[i].t == Float)
            printf("%g", s->stack[i].saved_value.f);
        else if (s->stack[i].t == Double)
            printf("%g", s->stack[i].saved_value.d);
        else if (s->stack[i].t == Char)
            printf("%c", s->stack[i].saved_value.c);
        else if (s->stack[i].t == String || s->stack[i].t == Bloco) 
            printf("%s", s->stack[i].saved_value.str);
        else if (s->stack[i].t == Array) 
        {
            STACK *array = s->stack[i].saved_value.arr;
            printStack(array);
        }
    }
}

void aux_quotes (STACK *s, char *line, char *str, int *pos, int *pos2, int *length) {

    *pos += 1;

    while (line[*pos] != '"' && *pos < *length) {
        str[*pos2] = line[*pos];
        *pos = *pos + 1;
        *pos2 = *pos2 + 1;
    }
    str[*pos2] = '\0';

    STACK_Elem x = (STACK_Elem) {
        .t = String,
        .saved_value = {.str = strdup(str)}
    };

    push(s, x);

}

void aux_brackets(STACK *s, char *line, char *str, int *pos, int *pos2, int *length) {

    while (line[*pos] != '}' && *pos < *length) {
        str[*pos2] = line[*pos];
        *pos = *pos + 1;
        *pos2 = *pos2 + 1;
    }
    str[*pos2] = line[*pos];
    str[*pos2+1] = '\0';

    STACK_Elem x = (STACK_Elem) {
        .t = Bloco,
        .saved_value = {.str = strdup(str)}
    };
    push(s, x);

}

void aux_arrays(STACK *s, char *line, char *str, int *pos, int *pos2, int *length, int *count, STACK_Elem *vars) {

    *count += 1;
    *pos += 2;

    while (*pos < *length && *count != 0) {

        if (line[*pos] == '[') {
            *count += 1;
        } else if (line[*pos] == ']')
            *count -= 1;

        str[*pos2] = line[*pos];
        *pos += 1;
        *pos2 += 1;
    }

    str[*pos2] = '\0';

    STACK *s2 = new_stack();
    STACK_Elem x = (STACK_Elem) {
        .t = Array,
        .saved_value = {.arr = s2}
    };
    push(s, x);

    read_line(s2, strdup(str), vars);

}

void else_aux(STACK *s, char *line, char *str, int *pos, int *pos2, int *length, int *flag, STACK_Elem *vars) {

    while(line[*pos] != ' ' && *pos < *length-1) {
        str[*pos2] = line[*pos];
        *pos += 1;
        *pos2 += 1;
        *flag = 1;
    }
            
    if (*flag) {
        *flag = 0;
        str[*pos2] = '\0';
        check_token(strdup(str), s, vars);
    }

}

///
/// Função que lê a linha, ignora os espaços vazios e insere os elementos na Stack
void read_line(STACK *s, char *line, STACK_Elem *vars) 
{
    int pos, pos2 = 0, length = strlen(line), flag = 0, count = 0;
    char *str = malloc(sizeof(char) * MAX_STRING);
    for (pos = 0; pos < length; pos++) 
    {
        pos2 = 0;
        if (line[pos] == ' ') ;
        else if (line[pos] == '"') 
            aux_quotes(s, line, str, &pos, &pos2, &length);
        else if (line[pos] == '[')
            aux_arrays(s, line, str, &pos, &pos2, &length, &count, vars);
        else if (line[pos] == '{')
            aux_brackets(s, line, str, &pos, &pos2, &length);
        else  {
            else_aux(s, line, str, &pos, &pos2, &length, &flag, vars);
        }
    }
    free(str);
}

///
/// Pretende-se que implemente um interpretador de uma linguagem de
/// programação orientada à stack, chamado $0M. O seu programa
/// deverá permitir ler comandos do stdin ou de um ficheiro,
/// interpretá-los, e imprimir o conteúdo da stack no stdout.
/*! 
* \author Grupo 4 da PL 7.
* \since 06/05/22
* \version 0.5 alfa
*/
///
/// Funcão Main que recebe todos os elementos do standard input
/// ou de um ficheiro e interpeta-los usando a Stack

int main() 
{

    STACK_Elem vars[100]; 
    
    for (int i = 0; i < 100; i++) 
    {
        STACK_Elem result = 
        {
            .t = Empty
        };

        vars[i] = result;
    }

    STACK *s = new_stack();
    char *line = malloc(sizeof(char) * MAX_STRING);

    if (fgets(line, MAX_STRING, stdin) != NULL) 
    {
        read_line(s, line, vars);
    }
    printStack(s);
    printf("\n");
    return 0;
}
