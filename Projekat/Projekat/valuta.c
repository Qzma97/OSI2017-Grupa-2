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
		 fclose(fp);
	 }
	 else printf("Greska! Valute.txt nije pronadjen! \n");
	 return nizVal[v];
}


 void izborValute()
 {

	 FILE* fp;
	 VALUTA* valute = 0;
	 int v = 0, br, i = 0, val=-1;
	 if ((fp = fopen("Valute.txt", "r")) != 0)
	 {
		 fscanf(fp, "%d %d\n", &v, &br);
		 valute = (VALUTA*)calloc(br, sizeof(VALUTA));
		 while (i < br)
		 {
			 fscanf(fp, "%s %lf\n", valute[i].oznaka, &valute[i].koeficijent);
			 i++;
		 }
		 fclose(fp);
	 }
	 else printf("Greska prilikom otvaranja datoteke! \n");
	 VALUTA t = ucitajValutu();
	 printf("TRENUTNA VALUTA:\n\t%s \n", t.oznaka);
	 printf("POSTOJECE VALUTE:\n");
	 for (int i = 0; i < br; i++)
		 printf("\t%d.%s \n", i + 1, valute[i].oznaka);
	 do
	 {
		 printf("IZABERITE VALUTU:\n");
		 scanf("%d", &val);
		 if (val <= 0 || val > br)
		 {
			 val = -1;
			 printf("Nepostojeca opcija!\n");
		 }
	 }while (val == -1);
	 i = 0;
	 if ((fp = fopen("Valute.txt", "w")) != 0)
	 {
		 fprintf(fp, "%d %d\n", val-1, br);
		 while (i < br)
		 {
			 fprintf(fp, "%s %lf\n", valute[i].oznaka, valute[i].koeficijent);
			 i++;
		 }
		 fclose(fp);
	 }

 }