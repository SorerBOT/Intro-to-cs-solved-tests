#include <stdio.h>
typedef int *i;
int j;
int f(i a){
*a = ++j;
int j = 2;
return *a+j;
}
int main() {
int a = 7;
for(int j=0;a;j++){
printf("%d\n", f(&a));
a>>=j;
}
printf("%d\n", a);
return 0;
}
