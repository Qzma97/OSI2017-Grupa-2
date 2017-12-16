#include "Format4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insert(NODE** head, RACUN* racun)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->racun = *racun;
	newNode->next = 0;
	if (*head != 0)
		newNode->next = *head;
	*head = newNode;
}
RACUN format4(FILE* dat, char*txt)
{
	RACUN racun;
	char pom[50], pom2[50];
	int n;
	n= countf4(dat);
	racun.brojArtikala = n;
	dat = fopen(txt, "r");
	if (dat != NULL)
	{
		
		racun.nizA = (ARTIKAL*)calloc(n, sizeof(ARTIKAL));
		fseek(dat, 6, 1);
		fscanf(dat, "%s\n", racun.kupac);
		fseek(dat, 6, 1);
		fscanf(dat, "%s\n", racun.datum);
		for (int i = 0; i < 4; i++)
			fgets(pom, 50, dat);
		int check = 0, j = 0;
		do
		{
			if(check)
				fseek(dat, -1L, SEEK_CUR);
			fscanf(dat, "%s %d", racun.nizA[j].naziv, &racun.nizA[j].sifra);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf", &racun.nizA[j].kolicina);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf", &racun.nizA[j].cijena);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf\n", &racun.nizA[j].ukupno);
			check = 1;
			j++;
		} while (fgetc(dat) != '-');
		fgets(pom, 50, dat);
		fscanf(dat, "%s %lf\n", pom2, &racun.ukupno);
		fscanf(dat, "%s %lf\n", pom2, &racun.pdv);
		fgets(pom, 50, dat);
		fgets(pom, 20, dat);
		fscanf(dat, "%lf\n",&racun.ukupnoPl);
		return racun;
	}
	return racun;
}

int countf4(FILE *f)
{
	char junk[1024];
	int count = 0, n = 7, check=1;
	while (n--)
		fgets(junk, sizeof(junk), f);
	while (check)
	{
		fgets(junk, sizeof(junk), f);
		if (strcmp(junk, "---------------------------------------\n") == 0)
			check = 0;
		if(check)
			count++;
	}
	fclose(f);
	return count;
}
