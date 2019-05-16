#include <stdio.h>
char *func() {
    char *r = "uahsudhaushda\n";
    return r;
}
int main() {
    char *a;
    a = func();
    puts(a);
    return 0;
}