#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 302

typedef struct StackStruct
{
    char* darr;
    int size;
    int inUse; 
} Stack;

void init (Stack* s)
{
    s->size = 2;
    s->darr = (char*) malloc ( sizeof (char) * s->size );
    s->inUse = 0;
}

void push (Stack* s, char val, int debug)
{
    char* temp = s->darr;
    int i, j=s->size;
    if(s->inUse == s->size)
    {
        if (debug)
        {
            printf("\nstack growth: old darr size %d\n",s->size);
        }
        s->size = s->size+2;
        s->darr = (char*) malloc ( sizeof (char) * s->size );
        for(i=0; i< j; i++)
        {
            s->darr[i] = temp[i];
        }
        free(temp);
        if (debug)
        {
            printf("\n new darr size %d\n",s->size);
            printf("\nvalues copied to (new) darr %d\n",s->inUse);
        }
            
    }
    if (debug)
        printf("\npushed %c onto stack\n", val);
    s->darr[s->inUse] = val;
    s->inUse = s->inUse + 1;
}

int isEmpty (Stack* s)
{
    if ( s->inUse == 0)
    return TRUE;
    else
    return FALSE;
}

char top (Stack* s)
{
    return ( s->darr[s->inUse-1] );
}

void pop (Stack* s, int debug)
{
    if (debug)
        printf("\npopped %c off stack\n", top (s));
    s->inUse = s->inUse - 1;
}

void reset (Stack* s)
{
    s->inUse = 0;
}

int isOpeningSymbol( char ch )
{
    if ( ch == '{' || ch == '(' || ch == '[' || ch == '<' )
        return TRUE;
    else
        return FALSE;
}

int isClosingSymbol ( char ch )
{
    if ( ch == '}' || ch == ')' || ch == ']' || ch == '>' )
        return TRUE;
    else
        return FALSE;
}

char getMatchingSymbol ( char ch )
{
    if ( ch == '(' ) return ')';
    if ( ch == '[' ) return ']';
    if ( ch == '{' ) return '}';
    if ( ch == '<' ) return '>';
    if ( ch == ')' ) return '(';
    if ( ch == ']' ) return '(';
    if ( ch == '}' ) return '{';
    if ( ch == '>' ) return '<';
}

int doSymbolsMatch ( char ch1, char ch2 )
{
    char symbols[8] = { '(', '{', '[', '<', ')', '}', ']', '>' };
    int a;
    for ( a = 0 ; a < 8 ; a++ )
    {
        int b = (a + 4) % 8;
        if ( ch1 == symbols[a] && ch2 == symbols[b] )
            return TRUE;
    }
    return FALSE;
}

int main (int argc, char** argv)
{
    int debug = FALSE, balanced = TRUE, a = 0, i, err_pos, input_sz;
    char input[MAX], match;
    Stack st1;
    
        if( argc == 2 && argv[1][0] == '-' && argv[1][1] == 'd' )
        {
            printf("\nDebuging information\n");
            debug = TRUE;
        }
        init (&st1);
    while( TRUE )
    {
        balanced = TRUE;
        a = 0;
        printf("Enter your expression or type 'q' to leave: ");
        fgets(input, MAX, stdin);
        if(input[0]=='q' || input[0]=='Q' )
        {
            exit(0);
        }
        
        while ( input[a] != '\0' )
        {
            if ( '\n' == input[a] )
            {
                input[a] = '\0';
                input_sz = a;
            }
                
            a++;
        }
        for(i = 0; i<input_sz; i++)
        {
            switch (isOpeningSymbol( input[i] ))
            {
                case TRUE:
                
            }
            
            
            
            
            if(isOpeningSymbol( input[i] ))
            {
                push (&st1, input[i], debug);
            }
            else if(isClosingSymbol ( input[i] ))
            {
                if(doSymbolsMatch ( input[i], top(&st1) ))
                    pop(&st1, debug);  
                else if (isEmpty (&st1))
                {
                    match = getMatchingSymbol ( input[i] );
                    balanced = FALSE;
                    err_pos = 0;
                    i=a;
                }
                else
                {
                    match = getMatchingSymbol ( top(&st1) );
                    balanced = FALSE;
                    err_pos = i;
                    i=a;
                }
                    
            }
        }
        if (balanced == TRUE && !isEmpty (&st1))
        {
            balanced = FALSE;
            err_pos = input_sz;
            match = getMatchingSymbol ( top(&st1) );
        }
        printf("\n ");
        
        for(i = 0; i<input_sz; i++)
            printf("%c", input[i]);
        
        if(!balanced)
        {
            if(err_pos > 0)
            {
                printf("\n ");
                for(i = 0; i<err_pos; i++)
                    printf(" ");
                printf("^ expecting %c\n", match);
            }
            else
                printf("\n^ expecting %c\n", match);
            
        }
        else
        {
            printf("\nExpression is balanced\n");
        }
        reset (&st1);
    }
    free(st1.darr);
}