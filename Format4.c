
#include "Format4.h"

void insert(NODE** head, RACUN* racun)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->racun = *racun;
	if (*head != 0)
		newNode->next = *head;
	*head = newNode;
}
void format4()
{
	RACUN racun;
	NODE* head = 0;
	FILE* dat;
	char pom[50], pom2[50];
	if ((dat = fopen("racuni.txt", "r")) != NULL)
	{
		fseek(dat, 6, 1);
		fscanf_s(dat, "%s\n", racun.kupac);
		fseek(dat, 6, 1);
		fscanf(dat, "%s\n", racun.datum);
		for (int i = 0; i < 5; i++)
			fgets(pom, 50, dat);
		int j = 0;
		do
		{
			fscanf(dat, "%s %d", racun.nizA[j].naziv, &racun.nizA[j].sifra);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf", &racun.nizA[j].kolicina);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf", &racun.nizA[j].cijena);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf\n", &racun.nizA[j].ukupno);
			j++;
		} while (fgetc(dat) != '-');
		fgets(pom, 50, dat);
		fscanf(dat, "%s %lf\n", pom2, &racun.ukupno);
		fscanf(dat, "%s %lf\n", pom2, &racun.pdv);
		fgets(pom, 50, dat);
		fscanf(dat, "%s %lf\n", pom2, &racun.ukupnoPl);
		racun.brojArtikala = j;
		printf("Kupac je:%s", racun.kupac);
		insert(&head, &racun);
	}

}
