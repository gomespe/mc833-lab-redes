#include <stdio.h>
#include <string.h>

char *func( char *buff) {
    puts(buff);
    char *token;
    char *s = ";";

    token = strtok(buff, s);
    puts(buff);
    return buff;
}
int main() {
    char *a = "blablablalab;aushdauhsudas";
    a = func(a);
    puts(a);
    return 0;
}