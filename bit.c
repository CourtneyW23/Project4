#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/*#define WORDSIZE 32
#define BITS_WS 5 //number of bits required to represent the value of word size
#define MASK 0x1f //represents a bit mask with all the bits in BITS_WS set to 1

int initbv(int **bv, int val){
	//returns 1 if memory for the bv was successfully allocated
	*bv = calloc(val/WORDSIZE + 1, sizeof(int));

    return *bv != NULL;
}

void set(int bv[], pid_t i){
	bv[i>>BITS_WS] |= (1 << (i & MASK));
}

int member(int bv[], pid_t i){
	return bv[i>>BITS_WS] & (1 << (i & MASK));
}

//find and print matching numbers in both s1 and s2
int main(){
   int *bv, i;
   pid_t s1; //{100, 32, 5, 4, 1, 23, 43, 76, 3, 7, 87, 0};
   pid_t s2; //{32, 5, 98, 23, 11, 100, 134, 76, 84, 7, 3, 0};

   s1 = fork();
   s2 = fork();

   initbv(&bv, 32);

   for ( i = 0; s1; i++)
	   set(bv, s1);

   for ( i = 0; s2; i++)
       if (member(bv, s2))
	       printf("%d\n", s2);
   
   free(bv);

   return 0;
}
*/

