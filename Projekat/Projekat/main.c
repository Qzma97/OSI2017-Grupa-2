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
		int i, d = 0;
		do
		{
			scanf("%d", &i);
		} while (i != 1 && i != 2);
		if (i == 1)
			do {
				d = prijava(niz, n);
			} while (d == 0);

		else if (i == 2)
			registracija(niz, n, dat);
	}
	else
	{
		printf("REGISTRACIJA:\n");
		registracija(niz, n, dat);
	}
	///UCITAVANJE IZ DIREKTORIJUMA I BRISANJE DATOKE NAKON CITANJA
	/*WIN32_FIND_DATA findFileData;
	HANDLE hFind;
	FILE* f;
	char *c = "./folder/";
	hFind = FindFirstFile("./input/*.txt", &findFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			char*d = (char*)calloc(strlen(findFileData.cFileName), sizeof(char));
			strcpy(d, findFileData.cFileName);
			char*e = (char*)calloc(strlen(d) + strlen(c), sizeof(char));
			strcat(e, c);
			strcat(e, d);
			f = fopen(e, "r");
			if (f != NULL)
			{
				printf("%c\n", fgetc(f));
				fclose(f);
				if (remove(e) == 0)
					printf("Deleted successfully\n");
				else
					printf("Unable to delete the file\n");
			}
			else printf("Greska!\n");
		} while (FindNextFile(hFind, &findFileData) != 0);

		FindClose(hFind);
	}
	
	*/
	getchar();
	getchar();
}