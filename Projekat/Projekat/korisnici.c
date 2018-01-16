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

void deleteNode(struct Node **head_ref, int position)
{
  
   if (*head_ref == NULL)
      return;
 
   
   struct Node* temp = *head_ref;
 
  
    if (position == 0)
    {
        *head_ref = temp->next;   
        free(temp);             
        return;
    }
 
    
    for (int i=0; temp!=NULL && i<position-1; i++)
         temp = temp->next;
 
   
    if (temp == NULL || temp->next == NULL)
         return;
 
    
    struct Node *next = temp->next->next;
 
    free(temp->next);  
 
    temp->next = next; 
}
