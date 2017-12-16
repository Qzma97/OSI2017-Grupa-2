//https://github.com/Qzma97/OSI2017-Grupa-2
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "osi.h"

int main()
{
	printf("ver. 1.0\n");
	printf("\n\n\n\n\t\t\t*****System of Consumer Analitics*****");
	Sleep(3000);//program se zaustavlja 3 sek
	system("cls");
	FILE *dat;
	int c = 10, n = 0;
	KORISNIK *niz = (KORISNIK*)malloc(c * sizeof(KORISNIK));
	if ((dat = fopen("korisnici.dat", "rb")) != NULL)
	{
		int p;
		KORISNIK  temp;
		do {
			if ((p = fread(&temp, sizeof(KORISNIK), 1, dat) == 1))
				if (n == c)
					niz = (KORISNIK*)realloc(niz, (c *= 2) * sizeof(KORISNIK));
			niz[n++] = temp;
		} while (p);
		n--;
		fclose(dat);
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("PRIJAVA-1\n");
		printf("REGISTRACIJA-2\n");
		printf("-------------------------------------------------------------------------------------------------\n");
		char i;
		int d = 0;
		do
		{
			scanf("%c", &i);
			if (i != '1' && i != '2')
				printf("Nepostojeca opcija!\n");
		} while (i != '1' && i != '2');
		if (i == '1')
			do {
				d = prijava(niz, n);
			} while (d == 0);

		else if (i == '2')
			registracija(niz, n, dat);
	}
	else
	{
		printf("REGISTRACIJA:\n");
		registracija(niz, n, dat);
	}
	getchar();
	getchar();
}