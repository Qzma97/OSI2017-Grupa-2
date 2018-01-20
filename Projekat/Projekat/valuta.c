#include <stdio.h>
#include <stdlib.h>
#include "valuta.h"

 VALUTA ucitajValutu()
{
	 FILE* fp;
	 VALUTA* nizVal=0;
	 int indexDefaultValute=0, brValuta,i=0;
	 if ((fp = fopen("Valute.txt", "r")) != 0) 
	 {
		 fscanf(fp, "%d %d\n", &indexDefaultValute,&brValuta);
		 nizVal = (VALUTA*)calloc(brValuta, sizeof(VALUTA));
		 while (i < brValuta) 
		 {
			 fscanf(fp, "%s %lf\n", nizVal[i].oznaka, &nizVal[i].koeficijent);
			 i++;
		 }
		 fclose(fp);
	 }
	 else printf("Greska! Valute.txt nije pronadjen! \n");
	 return nizVal[indexDefaultValute];
}

 void izborValute()
 {

	 FILE* fp;
	 VALUTA* valute = 0;
	 int indexDefaultValute = 0, brValuta, i = 0, val=-1;
	 if ((fp = fopen("Valute.txt", "r")) != 0)
	 {
		 fscanf(fp, "%d %d\n", &indexDefaultValute, &brValuta);
		 valute = (VALUTA*)calloc(brValuta, sizeof(VALUTA));
		 while (i < brValuta)
		 {
			 fscanf(fp, "%s %lf\n", valute[i].oznaka, &valute[i].koeficijent);
			 i++;
		 }
		 fclose(fp);
	 }
	 else printf("Greska prilikom otvaranja datoteke! \n");
	 VALUTA temp = ucitajValutu();
	 printf("TRENUTNA VALUTA:\n\t%s \n", temp.oznaka);
	 printf("POSTOJECE VALUTE:\n");
	 for (int i = 0; i < brValuta; i++)
		 printf("\t%d.%s \n", i + 1, valute[i].oznaka);
	 do
	 {
		 char pom[21] = { 0 };
		 printf("IZABERITE VALUTU:\n");
		 scanf("%s", pom);
		 val = pom[0] - 48;
		 if (val <= 0 || val > brValuta)
		 {
			 val = -1;
			 printf("Nepostojeca opcija!\n");
		 }
	 }while (val == -1);
	 i = 0;
	 if ((fp = fopen("Valute.txt", "w")) != 0)
	 {
		 fprintf(fp, "%d %d\n", val-1, brValuta);
		 while (i < brValuta)
		 {
			 fprintf(fp, "%s %lf\n", valute[i].oznaka, valute[i].koeficijent);
			 i++;
		 }
		 fclose(fp);
	 }

 }