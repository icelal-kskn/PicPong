#include <main.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




void main()
{

   while(true) {
         output_b(0b00000001);
      delay_ms(DELAY);
      output_b(0b00000000);
      delay_ms(DELAY);
  
   }


}
