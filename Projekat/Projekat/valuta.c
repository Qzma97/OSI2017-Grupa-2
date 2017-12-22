#include <stdio.h>
#include "valuta.h"

 void ucitajValutu()
{
	 FILE* fp;
	 int n = 3;
	 VALUTA *nizVal = (VALUTA*)malloc(n * sizeof(VALUTA));
	 int v, bv,i=0;
	 if ((fp = fopen("Valute.txt", "r")) != 0) {
		 fscanf(fp, "%d %d\n", &v,&bv);
		 while (i < bv) {
			 fscanf(fp, "%s %lf\n", nizVal[i].oznaka, &nizVal[i].koeficijent);
			 i++;
			 if (i == n)
				 nizVal = (VALUTA*)realloc(nizVal, (n *= 2) * sizeof(VALUTA));
		 }
	 }
	 else printf("Greska! Nije moguce otvoriti fajl.");
}