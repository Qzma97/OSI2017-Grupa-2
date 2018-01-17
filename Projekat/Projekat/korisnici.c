#include "korisnici.h"

void promjenaTipa(int pozicija, int tip, CVOR** glava)
 {
	int i = 0;
	CVOR * temp = *glava;
	while (i != pozicija)
	{

		temp = temp->sljedeci;
		i++;
	}
	temp->k.tip = tip;
}

CVOR* ucitaj_naloge_iz_fajla()
{
    FILE* dat;
    KORISNIK k;
    CVOR* head=0;
    int p;
    if((dat=fopen("korisnici.dat", "rb")) != NULL)
    {
        do
        {
           p=(fread(&k, sizeof(KORISNIK), 1, dat));
           if(p)
           {
               if(head==0)
               {
                   CVOR* novi=(CVOR*)malloc(sizeof(CVOR));
                   novi->k=k;
                   novi->sljedeci=0;
                   head=novi;
               }
               else
                {
                    CVOR* temp;
                    CVOR* novi=(CVOR*)malloc(sizeof(CVOR));
                    for(temp=head; temp->sljedeci != 0; temp=temp->sljedeci);
                    temp->sljedeci=novi;
                    novi->k=k;
                    novi->sljedeci=0;
                }
           }
        }while(p);
        fclose(dat);
    }
     else
        printf("Greska prilikom otvaranja datoteke.\n");
    return head;
}


void deleteNode(CVOR**head_ref, int position)
{
	
		if (*head_ref == NULL)
		 return;
	
		
		CVOR* temp = *head_ref;
	
		
		if (position == 0)
		 {
		*head_ref = temp->sljedeci;
		free(temp);
		return;
		}
	
		
		for (int i = 0; temp != NULL && i < position - 1; i++)
		 temp = temp->sljedeci;
		
		if (temp == NULL || temp->sljedeci == NULL)
		 return;
		CVOR *next = temp->sljedeci->sljedeci;
	
		free(temp->sljedeci);
	
		temp->sljedeci = next;
	}

int listSize(CVOR *head)
{
	int size = 0;
	while (head)
	{
		head = head->sljedeci;
		size++;
	}
	return size;
}

void ispis_korisnika(CVOR *glava)
{
	int rb = 0;
	printf("RB. KORISNICKI NALOG\tIME\t\tPREZIME\t\t\tTIP KORISNIKA\t\tEMAIL\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	while (glava)
	{
		printf("%d.  %-s\t\t%-s\t\t%-s\t\t", rb++, glava->k.korisnicko_ime, glava->k.ime, glava->k.prezime);
		if ((glava->k.tip) == 0) printf("Analiticar\t\t");
		if ((glava->k.tip) == 1) printf("Admin     \t\t");
		printf("%s\n", glava->k.email);
		glava = glava->sljedeci;
	}
}

