#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Format3.h"


//void insert(NODE** head, RACUN* racun)
//{
//	NODE* newNode = (NODE*)malloc(sizeof(NODE));
//	newNode->racun = *racun;
//	newNode->next = 0;
//	if (*head != 0)
//		newNode->next = *head;
//	*head = newNode;
//}

void format3()
{
	RACUN racun;
	FILE* fp;
	NODE* head = 0;
	char pom[100], pom2[100];
	if ((fp = fopen("racuni.txt", "r")) != NULL)
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
			fscanf(fp, "%s %d", racun.nizA[i].naziv, &racun.nizA[i].sifra);
			fscanf(fp, "======%lf", &racun.nizA[i].kolicina);
			fscanf(fp, "======%lf", &racun.nizA[i].cijena);
			fscanf(fp, "======%lf\n", &racun.nizA[i].ukupno);
			i++;
		} while (fgetc(fp) != '-');
		fgets(pom, 100, fp);
		fscanf(fp, "%s %lf PDV: %lf\n", pom2, &racun.ukupno, &racun.pdv);
		fscanf(fp, "Ukupno za placanje: %lf", &racun.ukupnoPl);
		racun.brojArtikala = i;
		insert(&head, &racun);
	}
	else printf("Greska pri otvaranju datoteke!");	
}