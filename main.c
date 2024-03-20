#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXARG 100
#define MAXLINE 200
#define FILENAME "../cal.txt"
#define TEMPFILE "../temp.txt"

void getLine();
void getArgs();
int matches(char s1[], char s2[]);
void pushToFile(char s[]);
void removeLine(int lineNum);
void readFromFile();
int stringToInt(char s[]);

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
            } else if (matches(arg1, "rm")) {
                int lineNum = stringToInt(arg2);
                if (lineNum > 0)
                    removeLine(lineNum);
                else
                    printf("Must input number 1 or greater after \'rm\' command!\n");
            }
        } else if (matches(arg1, "read")) {
            readFromFile();
        } else if (matches(arg1, "help")) {
            printf("read: view current calendar events\nadd 'event info': Add 'event info' to your calendar\nrm 'line number': remove 'line number' from calendar\nend: exit the program\n");
        } else if (matches(arg1, "end") || matches(arg1, "exit"))
            ;
        else {
            printf("Not enough arguments!\n");
        }
    } while (!matches(arg1, "end"));

    return 0;
}

void pushToFile(char s[]) {
    FILE *file = fopen(FILENAME, "a+");

    char c = getc(file);
    if (c != EOF) {
        ungetc(c, file);
        fseek(file, 0, SEEK_END);
        putc('\n', file);
    }

    for (int i = 0; i < strlen(s); i++)
        putc(s[i], file);
    putc('\n', file);
    fclose(file);
}

int stringToInt(char s[]) {
    int i;
    int pos = 1;
    int asInt = 0;
    for (i = 0; i < strlen(s); i++) {
        if (isblank(s[i]))
            ;
        else if (s[i] >= '0' && s[i] <= '9')
            asInt += pos++ * s[i] - '0';
        else return -1;
    }

    return asInt;
}

void removeLine(int targetLine) {
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen(TEMPFILE, "w");

    int currentLine = 1;
    char c;
    char removed[MAXARG];
    int remP = 0;

    while ((c = getc(file)) != EOF) {
        if (currentLine == targetLine) {
            removed[remP++] = c;
        } else {
            putc(c, tempFile);
        }
        if (c == '\n') {
            currentLine++;
        }
    }

    removed[remP] = '\0';
    printf("Removed line: %s\n", removed);

    fclose(file);
    fclose(tempFile);
    remove(FILENAME);
    rename(TEMPFILE, FILENAME);
}

void readFromFile() {
    FILE *file = fopen(FILENAME, "r");

    int itemNum = 1;
    char c = getc(file);
    if (c != EOF) {
        ungetc(c, file);
        printf("%d) ", itemNum++);
    } else {
        printf("No events here yet!");
    }

    char temp;
    while ((c = getc(file)) != EOF) {
        if ((temp = getc(file)) == EOF)
            break;
        ungetc(temp, file);
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
