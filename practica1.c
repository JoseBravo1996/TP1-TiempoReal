#include <stdio.h>
#include <dos.h>
#include <conio.h>

/* Cada interrupcion tiene un numero de interrupcion del reloj */
#define INTR 0X1C /* 18.2 Hz */
void interrupt ( *oldhandler)();
int count=0;
int interrupcion;

void interrupt handler()
{
   /* increase the global counter */
   count++;
}

int main(void)
{
   printf("\nIndique el num. de interrupciones x seg: ");
   scanf("%d", &interrupcion);

   disable();
   outportb(0x043, 0x00 | 0x00 | 0x36);
   outportb(0x040, 1193800/interrupcion % 256);
   outportb(0x040, 1193800/interrupcion / 256);

   /* El vector de interrupción es el valor base del segmento y el desplazamiento de la rutina del servicio de interrupción. */
   oldhandler = getvect(INTR); 

   /* install the new interrupt handler */
   setvect(INTR, handler);
   enable();

   /* loop until the counter exceeds 20 */
   while (1) {
      if (count != 0 && count%interrupcion==0){
            printf("interrupciones en este segundo: %d\n",count); /* interrupciones por segundo*/
      }
      if(count>20*interrupcion){   /* luego de 20 segundos */
         break;
      }
   }
      
   disable();
   /* reset the old interrupt handler */
   setvect(INTR, oldhandler);
   outportb(0x43, 0x36);
   outportb(0x40, 0xFF);

   printf("/n PROGRAMA FINALIZADO...");
   getch();

   return 0;
}