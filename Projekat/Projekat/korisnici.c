#include "korisnici.h"

void promjenaTipa(int pozicija, int tip, CVOR* glava)
 {
	int i = 1;
	CVOR * temp = glava;
	while (temp && i < pozicija) {

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
