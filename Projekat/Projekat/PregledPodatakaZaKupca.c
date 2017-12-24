#include "PregledPodatakaZaKupca.h"
void pregledPodatakaKupac(NODE* lista, char* kupac, int broj)
{
    NODE* temp;
    int i=0,j,k;
    RACUN* niz=(RACUN*)malloc(broj * sizeof(RACUN));
    for(temp=lista; temp != NULL; temp=temp->next)
    {
        if(strcmp(temp->racun.kupac, kupac) == 0)
            niz[i++]=temp->racun;
    }
    for(j=0; j<broj; j++)
    {
        printf("Kupac:%s\n", niz[i].kupac);
        printf("Datum:%s", niz[i].datum);
        printf("Na ovom racunu ima %d artikala.\n", niz[i].brojArtikala);
        printf("Artikli:\n");
        for(k=0; k<niz[i].brojArtikala; k++)
        {
            printf("Naziv artikla:%s\n",niz[i].nizA[k].naziv);
            printf("Sifra artikla:%d\n", niz[i].nizA[k].sifra);
            printf("Cijena artikla:%lf\n", niz[i].nizA[k].cijena);
            printf("Kolicina artikla:%lf\n", niz[i].nizA[k].kolicina);
            printf("Ukupno:%lf\n", niz[i].nizA[k].ukupno);
        }
        printf("Ukupno(racun):%lf\n", niz[i].ukupno);
        printf("PDV:%lf\n", niz[i].pdv);
        printf("Ukupno za placanje:%lf\n", niz[i].ukupnoPl);
    }
    free(niz);
}
