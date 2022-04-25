#include<stdio.h>
int main(void)
{
   int x = 91, y = 100;
   int temp = 0;
   while (y > 0) {
       if (x > 100) { x -= 10; y--; }
       else x++;
       temp++;
   }
   printf("%d", temp);
    return 0;
}