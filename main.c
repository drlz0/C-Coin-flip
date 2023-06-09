#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* INPUT can be done either by this method with array OR with getchar*/
/* Using getchar()

getchar() (and scanf() for that matter) provide an equally easy way to do the same thing,
the difference being you will be handling things a character at a time from your input 
buffer rather than buffering the first buffer size number of characters -- and you must
remove any additional character -- including the '\n' generated by pressing Enter, yourself.
The code is actually a few lines shorter, e.g.
https://stackoverflow.com/questions/51528147/how-to-limit-user-input-to-a-single-char-only */

#define MAXC 1024 /* to manage input from user, do NOT skimp on buffer size */

int input_check(char *buf, char one, char two);

int main () {

    srand(time(NULL));
    int bilans = 10;

    char buf[MAXC] = "";  /* to manage input from user */
    
    printf("====================================\n");
    printf("=========== Coin flip gane =========\n");
    printf("====================================\n");
    printf("\n");
    printf("--------- Heads - you win 1$ -------\n");
    printf("--------- Tails - you lose 1$ ------\n");
    printf("\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("..............Wanna play?...........\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("\n");
    printf("Press R for roll\n");
    printf("Press X for exit\n");

    while (true) {
        printf("Your bilans: %d\n", bilans);

        fputs ("Input: ", stdout);
        /* ADVICE: MAKING SEPARATE FUNCTION FOR CODE THAT WILL REPEAT LATER
            don't try to separate everything at once, try fragment by fragment*/
        if (!input_check(buf, 'r', 'x'))
            continue;

        if (*buf == 'r') {
            bool randbool = rand() % 2;
            if (randbool == 1) {
                printf("\n");
                printf("Heads - you win 1$\n");
                bilans++;
            }
            else {
                printf("\n");
                printf("Tails - you lose 1$\n");
                bilans--;
            }
        }
        if (*buf == 'x') 
            return 0;
        

        while (bilans < 1) {
            printf("You lost all your money!\n");
            printf("Press P for playing again or X for exit\n");
            fputs ("Input: ", stdout);

            if (!input_check(buf, 'p', 'x'))
                continue;
            
            if (*buf == 'p') {
                bilans = 10;
                printf("\n");
                printf("Press R for roll\n");
                printf("Press X for exit\n");
                break;
            }
            else if (*buf == 'x') {
                return 0;
            }
            
        }

    }
    return 0;
}

/* when using printf, printf, c = getchar()
It prints two times in loop because when you input r + enter it gets 'r' and '\n' which is enter
thats why using scanf(" %c", &c) is better */

int input_check(char *buf, char one, char two) {
    size_t len = 0;

    if (!fgets (buf, sizeof buf, stdin)) {  /* validate read */
     /* manual EOF */
    fputs ("(user canceled input)\n", stderr);
    }

    if (*buf == '\n')       /* check for [Enter] alone */
        printf("Input character");

    if (*buf != one && *buf != two) /* if not 'r' || 'p', error */
        fprintf (stderr, " error: invalid input '%c'\n", *buf);

    len = strlen (buf);    /* get length of input (+ '\n') */

    /* validate entire line read */
    while (len && buf[len-1] != '\n') {
        fgets (buf, sizeof buf, stdin);
        len = strlen (buf);
    }

}
