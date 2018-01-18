#include "Pretraga.h"
#include <string.h>
#include <stdlib.h>

int trazi_po_artiklu(NODE* head, char* naziv)
{
	int count = 0;
	NODE* temp = head;
	if (temp == NULL)
		return 0;
	while (temp != NULL)
	{
		int i = 0, n = temp->racun.brojArtikala;
		while (n--)
		{
			if (strcmp(naziv, temp->racun.nizA[i].naziv) == 0)
				count++;
			i++;
		}
		temp = temp->next;
	}
	return count;
}

void artikal(NODE* head, int num, char*pom)
{
	double ukupno=0 ,kolicina = 0;
	int index = 0;
	NODE* temp=head;
	RACUN* racuni = (RACUN*)calloc(num, sizeof(RACUN));
	while (num-index)
	{
		int i=0,n = temp->racun.brojArtikala;
		while (n--)
		{
			if (strcmp(pom, temp->racun.nizA[i].naziv) == 0)
			{
				racuni[index].nizA = &temp->racun.nizA[i];
				strcpy(racuni[index].datum, temp->racun.datum);
				ukupno += temp->racun.nizA[i].ukupno;
				kolicina += temp->racun.nizA[i].kolicina;
				racuni[index].valuta = temp->racun.valuta;
				index++;
			}
			i++;
		}
		temp = temp->next;
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("NAZIV: %s SIFRA: %d\n", pom,racuni->nizA->sifra);
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("DATUM\t\tKOLICINA\t\tCIJENA\t\t\tUKUPNO\n");
	for(int i=0;i<index;i++)
	{
		printf("%s\t%.2lf\t\t\t%.2lf %s\t\t%.2lf %s\n", racuni[i].datum, racuni[i].nizA->kolicina, racuni[i].nizA->cijena*racuni[i].valuta.koeficijent,racuni[i].valuta.oznaka, racuni[i].nizA->ukupno*racuni[i].valuta.koeficijent,racuni[i].valuta.oznaka);
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("UKUPNA KOLICINA: %.2lf			UKUPNA CIJENA: %.2lf %s\n", kolicina, ukupno*racuni[0].valuta.koeficijent, racuni[0].valuta.oznaka);
	printf("PDV: %.2lf %s			UKUPNO ZA PLACANJE: %.2lf %s\n", ukupno*racuni[0].valuta.koeficijent*0.17, racuni[0].valuta.oznaka, ukupno*racuni[0].valuta.koeficijent*0.17+ ukupno*racuni[0].valuta.koeficijent, racuni[0].valuta.oznaka);
	free(racuni);
}

void brisi_listu(NODE**head)
{
    NODE*temp=*head;
    while(temp)
    {
        *head=(*head)->next;
        free(temp->racun.nizA);
        free(temp);
        temp=*head;
    }
}

int trazi_po_kupcu(NODE*head,char*kupac)
{
    NODE*p=head;
	if (p == NULL)
		return 0;
    int br=0;
    for(;p!=NULL;p=p->next)
    {
        if(strcmp(p->racun.kupac,kupac)==0)
            br++;
    }
    return br;
}

int trazi_po_datumu(NODE*head, char*m)
{
	int broj = 0;
	NODE *p = head;
	if (p == NULL)
		return 0;
	for (; p; p = p->next)
	{
		if (p->racun.datum[3] == m[0] && p->racun.datum[4] == m[1])
			broj++;
	}
	return broj;
}

void mjesec(NODE *head, char* m, int broj)
{
	RACUN *niz = (RACUN*)calloc(broj, sizeof(RACUN));
	double ukupno = 0, pdv = 0;
	int i = 0;
	NODE *p = head;
	if (p == NULL)
		return;
	for (; p; p = p->next)
	{
		if (p->racun.datum[3] == m[0] && p->racun.datum[4] == m[1])
			niz[i++] = p->racun;
	}
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("DATUM\t\t\tKUPAC\t\tARTIKAL\t\tSIFRA\t\tCIJENA\t\tKOLICINA\tUKUPNO\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < broj; i++)
	{
		for (int j = 0; j < niz[i].brojArtikala; j++)
			printf("%s\t\t%s\t\t%s\t\t%d\t\t%.2lf %s\t%.2lf\t\t%.2lf %s\n", niz[i].datum, niz[i].kupac, niz[i].nizA[j].naziv, niz[i].nizA[j].sifra, niz[i].nizA[j].cijena*niz[i].valuta.koeficijent,niz[i].valuta.oznaka, niz[i].nizA[j].kolicina, niz[i].nizA[j].ukupno*niz[i].valuta.koeficijent, niz[i].valuta.oznaka);
		ukupno += niz[i].ukupno;
		pdv += niz[i].pdv;

	}
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("UKUPNO: %.2lf %s\n", ukupno*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
	printf("PDV: %.2lf %s\n", pdv*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
	printf("UKUPNO ZA PLACANJE: %.2lf %s\n", pdv*niz[0].valuta.koeficijent+ ukupno*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	free(niz);

}

void insert(NODE** head, RACUN* racun)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->racun = *racun;
	newNode->next = 0;
	if (*head != 0)
		newNode->next = *head;
	*head = newNode;
}

void kupac(NODE* lista, char* kupac, int broj)
{
	NODE* temp;
	int i = 0, j, k;
	RACUN* niz = (RACUN*)calloc(broj , sizeof(RACUN));
	for (temp = lista; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->racun.kupac, kupac) == 0)
			niz[i++] = temp->racun;
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("Kupac:%s \n", niz[0].kupac);
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("ARTIKAL\t\tSIFRA\t\tCIJENA\t\t\tKOLICINA\tUKUPNO\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	for (j = 0; j<broj; j++)
	{
		for (k = 0; k<niz[j].brojArtikala; k++)
		{
			printf("%s\t\t%d\t\t%.2lf %s\t\t%.2lf\t\t%.2lf %s\n", niz[j].nizA[k].naziv, niz[j].nizA[k].sifra, niz[j].nizA[k].cijena*niz[j].valuta.koeficijent,niz[j].valuta.oznaka, niz[j].nizA[k].kolicina, niz[j].nizA[k].ukupno*niz[j].valuta.koeficijent, niz[j].valuta.oznaka);
		}
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("Datum:%s", niz[j].datum);
		printf(" Ukupno(racun): %.2lf %s", niz[j].ukupno*niz[j].valuta.koeficijent, niz[j].valuta.oznaka);
		printf(" PDV: %.2lf %s", niz[j].pdv*niz[j].valuta.koeficijent,niz[j].valuta.oznaka);
		printf(" Ukupno za placanje: %.2lf %s\n", niz[j].ukupnoPl*niz[j].valuta.koeficijent, niz[j].valuta.oznaka);
		printf("-------------------------------------------------------------------------------------------------\n");
	}
	free(niz);
}