#include <stdio.h>
#include <string.h>

#define MAXARG 100
#define MAXLINE 200

void getLine();
void getArgs();
int matches(char s1[], char s2[]);

char line[MAXLINE];
char arg1[MAXARG];
char arg2[MAXARG];

int main() {
    do {
        getLine();
        getArgs();

        if (!(strlen(arg1) && strlen(arg2))) {
            printf("Not enough arguments!\n");
        } else if (matches(arg1, "add")) {
            printf("Adding '%s' to calendar!\n", arg2);
        }
    } while (!matches(arg1, "end"));

    return 0;
}

void getLine() {
    int c;
    int i = 0;
    while ((c = getchar()) != '\n')
        line[i++] = c;
    line[i] = '\0';
    printf("got line: %s\n", line);
}

void getArgs() {
    int i, j;
    int len = strlen(line);

    for (i = 0; i < len && line[i] == ' '; i++)
        ;

    for (j = 0; i < len && line[i] != ' '; j++, i++)
        arg1[j] = line[i];
    arg1[j] = '\0';
    i++;

    for (j = 0; i < len; j++, i++)
        arg2[j] = line[i];
    arg2[j] = '\0';
}

int matches(char s1[], char s2[]) {
    int s1Len = strlen(s1);
    if (s1Len != strlen(s2))
        return 0;

    for (int i = 0; i < s1Len; i++)
        if (s1[i] != s2[i])
            return 0;
    return 1;
}
