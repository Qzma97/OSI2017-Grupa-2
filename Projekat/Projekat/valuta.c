#include <stdio.h>
#include <stdlib.h>
#include "valuta.h"

 VALUTA ucitajValutu()
{
	 FILE* fp;
	 VALUTA* nizVal=0;
	 int v=0, bv,i=0;
	 if ((fp = fopen("Valute.txt", "r")) != 0) 
	 {
		 fscanf(fp, "%d %d\n", &v,&bv);
		 nizVal = (VALUTA*)calloc(bv, sizeof(VALUTA));
		 while (i < bv) 
		 {
			 fscanf(fp, "%s %lf\n", nizVal[i].oznaka, &nizVal[i].koeficijent);
			 i++;
		 }
	 }
	 else printf("Greska! Valute.txt nije pronadjen! \n");
	 return nizVal[v];
}