#include <stdio.h>
#include <windows.h>
#include <locale.h>

void convertion( int n )
{
if ( n >= 2 )
{
convertion( n/2 );
}
printf("%d", n % 2);
}


int main (void) {
setlocale(LC_ALL, "Russian");
int n;
printf("Введите десятичное число: \n");
scanf("%d", &n);
printf("(Десятичная Cистема счисления): %d = ", n);
convertion( n );
printf(" (Двоичная система счисления)\n");
return 0;
}
