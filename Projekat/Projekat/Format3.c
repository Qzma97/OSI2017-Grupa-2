#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Format3.h"

RACUN format3(FILE*fp,char*txt)
{
	int check = 0;
	RACUN racun;
	NODE* head = 0;
	racun.brojArtikala = countf3(fp);
	racun.nizA = (ARTIKAL*)calloc(racun.brojArtikala, sizeof(ARTIKAL));
	fp = fopen(txt, "r");
	char pom[100], pom2[100];
	if (fp != NULL)
	{
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.kupac);
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.datum);
		for (int i = 0; i < 4; i++)
			fgets(pom, 100, fp);
		int i = 0;
		do {
			if (check)
				fseek(fp, -1L, SEEK_CUR);
			fscanf(fp, "%s %d", racun.nizA[i].naziv, &racun.nizA[i].sifra);
			fscanf(fp, "======%lf", &racun.nizA[i].kolicina);
			fscanf(fp, "======%lf", &racun.nizA[i].cijena);
			fscanf(fp, "======%lf\n", &racun.nizA[i].ukupno);
			check = 1;
			i++;
		} while (fgetc(fp) != '-');
		fgets(pom, 100, fp);
		fscanf(fp, "%s %lf PDV: %lf\n", pom2, &racun.ukupno, &racun.pdv);
		fscanf(fp, "Ukupno za placanje: %lf", &racun.ukupnoPl);
	}
	else printf("Greska pri otvaranju datoteke!");
	return racun;
}

int countf3(FILE *f)
{
	char junk[1024];
	int count = 0, n = 9, check = 1;
	while (n--)
		fgets(junk, sizeof(junk), f);
	while (check)
	{
		fgets(junk, sizeof(junk), f);
		if (strcmp(junk, "----------------------------------\n") == 0)
			check = 0;
		if (check)
			count++;
	}
	fclose(f);
	return count;
}
