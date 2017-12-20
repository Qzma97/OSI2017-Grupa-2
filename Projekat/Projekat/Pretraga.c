#include "Pretraga.h"
#include <string.h>
#include <stdlib.h>

int trazi_po_artiklu(NODE* head, char* naziv)
{
	int count = 0;
	NODE* temp = head;
	if (temp == NULL)
		return 0;
	while (temp->next != NULL)
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
				index++;
			}
			i++;
		}
		temp = temp->next;
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("%s\n", pom);
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("DATUM\t\tKOLICINA\t\tCIJENA\t\tUKUPNO\n");
	for(int i=0;i<index;i++)
	{
		printf("%s\t%.2lf\t\t\t%.2lf\t\t%.2lf\n", racuni[i].datum, racuni[i].nizA->kolicina, racuni[i].nizA->cijena, racuni[i].nizA->ukupno);
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("UKUPNA KOLICINA:%.2lf			UKUPNA CIJENA:%.2lf\n", kolicina, ukupno);
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

int trazi_po_datumu(NODE*head, char*datum_novi)
{
	NODE*p=head;
	if (p == NULL)
		return 0;
	int br = 0;
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->racun.datum, datum_novi) == 0)
			br++;
	}
	return br;
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