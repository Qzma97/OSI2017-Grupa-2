//https://github.com/Qzma97/OSI2017-Grupa-2
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "osi.h"

int main()
{
	printf("ver. 1.0\n");
	printf("\n\n\n\n\t\t\t*****System of Consumer Analytics*****");
	Sleep(3000);		//Program se zaustavlja 3 sekunde
	system("cls");		//Brisanje prethodnog ispisanog sadrzaja na ekranu
	FILE *dat;
	int defaultVelicina = 10, indexNaloga = 0;
	KORISNIK *nizNaloga = (KORISNIK*)malloc(defaultVelicina * sizeof(KORISNIK));  //Ucitavanje korisnickih naloga
	if ((dat = fopen("korisnici.dat", "rb")) != NULL)
	{
		int pom;
		KORISNIK  temp;
		do {
			if ((pom = fread(&temp, sizeof(KORISNIK), 1, dat) == 1))
				if (indexNaloga == defaultVelicina)
					nizNaloga = (KORISNIK*)realloc(nizNaloga, (defaultVelicina *= 2) * sizeof(KORISNIK));
			nizNaloga[indexNaloga++] = temp;
		} while (pom);
		indexNaloga--;
		fclose(dat);
		//Ispis pocetnog menija
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("PRIJAVA-1\n");
		printf("REGISTRACIJA-2\n");
		printf("-------------------------------------------------------------------------------------------------\n");
		char izborOpcije[100];
		int povratnaVrijednost = 0;
		//Izbor opcije sve dok korisnik ne izabere jednu od opcija
		do
		{
			scanf("%s", izborOpcije);
			if(strcmp("1",izborOpcije) && strcmp("2",izborOpcije))
			printf("Nepostojeca opcija!\nPonovite unos:");
		} while (strcmp(izborOpcije,"1") && strcmp(izborOpcije, "2"));
		if (!strcmp(izborOpcije, "1"))
			do {
				povratnaVrijednost = prijava(nizNaloga, indexNaloga); //Prijava za postojece korisnike
			} while (povratnaVrijednost == 0);

		else if (!strcmp(izborOpcije,"2"))
			registracija(nizNaloga, indexNaloga, dat); //Registracija novih korisnika
	}
	else //Ako nema fajla "korisnici.dat" pocinje se automatski sa registracijom
	{
		printf("REGISTRACIJA:\n");
		registracija(nizNaloga, indexNaloga, dat);
	}
	getchar();
	getchar();
}