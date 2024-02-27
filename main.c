#include <stdio.h>
#include <string.h>

#define MAXARG 100
#define MAXLINE 200
#define FILENAME "../cal.txt"

void getLine();
void getArgs();
int matches(char s1[], char s2[]);
void pushToFile(char s[]);
void readFromFile();

char line[MAXLINE];
char arg1[MAXARG];
char arg2[MAXARG];

int main() {
    do {
        getArgs();

        if (strlen(arg2)) {
            if (matches(arg1, "add")) {
                pushToFile(arg2);
                printf("Added event: %s\n", arg2);
            }
        } else if (matches(arg1, "read")) {
            readFromFile();
        } else if (matches(arg1, "end"))
            ;
        else {
            printf("Not enough arguments!\n");
        }
    } while (!matches(arg1, "end"));

    return 0;
}

void pushToFile(char s[]) {
    FILE *file = fopen(FILENAME, "a+");

    fseek(file, 0, SEEK_SET);

    char c = getc(file);
    if (c != EOF) {
        ungetc(c, file);
        fseek(file, 0, SEEK_END);
        putc('\n', file);
    }

    for (int i = 0; i < strlen(s); i++)
        putc(s[i], file);
    fclose(file);
}

void readFromFile() {
    FILE *file = fopen(FILENAME, "r");
    char c;
    int itemNum = 1;
    printf("%d) ", itemNum++);
    while ((c = getc(file)) != EOF) {
        putchar(c);
        if (c == '\n')
            printf("%d) ", itemNum++);
    }
    putchar('\n');
    fclose(file);
}

void getLine() {
    int c;
    int i = 0;
    while ((c = getchar()) != '\n')
        line[i++] = c;
    line[i] = '\0';
}

void getArgs() {
    getLine();
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
