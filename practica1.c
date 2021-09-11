#include <stdio.h>
#include <dos.h>
#include <conio.h>

/* Cada interrupcion tiene un numero de interrupcion del reloj */
#define INTR 0X1C /* 18.2 Hz */
void interrupt ( *oldhandler)();
int count=0;
int frec;

void interrupt handler()
{
/* increase the global counter */
   count++;
/* call the old routine */
   oldhandler();
}

int main(void)
{
   printf("indique la frecuencia: ");
   scanf("%s", &frec);

   /* El vector de interrupción es el valor base del segmento y el desplazamiento de la rutina del servicio de interrupción. */
   oldhandler = getvect(frec); 

/* install the new interrupt handler */
   setvect(INTR, handler);

/* loop until the counter exceeds 20 */
   while (count < 100) {
   /*if (count%5 == 0)
      printf("count is %d\n",count);*/
   printf("count is %d\n",count);
   sleep(1);
   }

/* reset the old interrupt handler */
   setvect(INTR, oldhandler);

   return 0;
}