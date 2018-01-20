#include "Pretraga.h"
#include <string.h>
#include <stdlib.h>

int traziPoArtiklu(NODE* glava, char* naziv)
{
	int brojac = 0;
	NODE* temp = glava;
	if (temp == NULL)
		return 0;
	while (temp != NULL)
	{
		int i = 0, n = temp->racun.brojArtikala;
		while (n--)
		{
			if (strcmp(naziv, temp->racun.nizArtikala[i].naziv) == 0)
				brojac++;
			i++;
		}
		temp = temp->sljedeci;
	}
	return brojac;
}

void pregledArtikla(NODE* glava, int brRacunaSaArt, char*nazivArtikla)
{
	double ukupno=0 ,kolicina = 0;
	int index = 0;
	NODE* temp=glava;
	RACUN* racuni = (RACUN*)calloc(brRacunaSaArt, sizeof(RACUN));
	while (brRacunaSaArt-index)
	{
		int i=0,n = temp->racun.brojArtikala;
		while (n--)
		{
			if (strcmp(nazivArtikla, temp->racun.nizArtikala[i].naziv) == 0)
			{
				racuni[index].nizArtikala = &temp->racun.nizArtikala[i];
				strcpy(racuni[index].datum, temp->racun.datum);
				ukupno += temp->racun.nizArtikala[i].ukupno;
				kolicina += temp->racun.nizArtikala[i].kolicina;
				racuni[index].valuta = temp->racun.valuta;
				index++;
			}
			i++;
		}
		temp = temp->sljedeci;
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("NAZIV: %s SIFRA: %d\n", nazivArtikla,racuni->nizArtikala->sifra);
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("DATUM\t\tKOLICINA\t\tCIJENA\t\t\tUKUPNO\n");
	for(int i=0;i<index;i++)
	{
		printf("%s\t%.2lf\t\t\t%.2lf %s\t\t%.2lf %s\n", racuni[i].datum, racuni[i].nizArtikala->kolicina, racuni[i].nizArtikala->cijena*racuni[i].valuta.koeficijent,racuni[i].valuta.oznaka, racuni[i].nizArtikala->ukupno*racuni[i].valuta.koeficijent,racuni[i].valuta.oznaka);
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("UKUPNA KOLICINA: %.2lf			UKUPNA CIJENA: %.2lf %s\n", kolicina, ukupno*racuni[0].valuta.koeficijent, racuni[0].valuta.oznaka);
	printf("PDV: %.2lf %s			UKUPNO ZA PLACANJE: %.2lf %s\n", ukupno*racuni[0].valuta.koeficijent*0.17, racuni[0].valuta.oznaka, ukupno*racuni[0].valuta.koeficijent*0.17+ ukupno*racuni[0].valuta.koeficijent, racuni[0].valuta.oznaka);
	ispisZaArtikal(racuni, index, kolicina, ukupno, nazivArtikla);
	free(racuni);
}

void ispisZaArtikal(RACUN *racuni, int index, double kolicina, double ukupno, char*naziv)
{
	FILE* file = 0;
	if (file = fopen("Pregled_svih_podataka_za_artikal.txt", "w"))
	{
		fprintf(file,"-------------------------------------------------------------------------------------------------\n");
		fprintf(file,"NAZIV: %s SIFRA: %d\n", naziv, racuni->nizArtikala->sifra);
		fprintf(file,"-------------------------------------------------------------------------------------------------\n");
		fprintf(file,"DATUM\t\tKOLICINA\t\tCIJENA\t\t\tUKUPNO\n");
		for (int i = 0; i < index; i++)
		{
			fprintf(file,"%s\t%.2lf\t\t\t%.2lf %s\t\t%.2lf %s\n", racuni[i].datum, racuni[i].nizArtikala->kolicina, racuni[i].nizArtikala->cijena*racuni[i].valuta.koeficijent, racuni[i].valuta.oznaka, racuni[i].nizArtikala->ukupno*racuni[i].valuta.koeficijent, racuni[i].valuta.oznaka);
		}
		fprintf(file,"-------------------------------------------------------------------------------------------------\n");
		fprintf(file,"UKUPNA KOLICINA: %.2lf			UKUPNA CIJENA: %.2lf %s\n", kolicina, ukupno*racuni[0].valuta.koeficijent, racuni[0].valuta.oznaka);
		fprintf(file,"PDV: %.2lf %s			UKUPNO ZA PLACANJE: %.2lf %s\n", ukupno*racuni[0].valuta.koeficijent*0.17, racuni[0].valuta.oznaka, ukupno*racuni[0].valuta.koeficijent*0.17 + ukupno*racuni[0].valuta.koeficijent, racuni[0].valuta.oznaka);
		fclose(file);
	}
	else printf("Neusjesno otvaranej fajla!\n");
}

void brisiListu(NODE**glava)
{
    NODE*temp=*glava;
    while(temp)
    {
        *glava=(*glava)->sljedeci;
        free(temp->racun.nizArtikala);
        free(temp);
        temp=*glava;
    }
}

int traziPoKupcu(NODE*glava,char*kupac)
{
    NODE*p=glava;
	if (p == NULL)
		return 0;
    int br=0;
    for(;p!=NULL;p=p->sljedeci)
    {
        if(strcmp(p->racun.kupac,kupac)==0)
            br++;
    }
    return br;
}

int traziPoDatumu(NODE*glava, char*datum)
{
	int broj = 0;
	NODE *p = glava;
	if (p == NULL)
		return 0;
	for (; p; p = p->sljedeci)
	{
		if (p->racun.datum[3] == datum[0] && p->racun.datum[4] == datum[1])
			broj++;
	}
	return broj;
}

void pregledMjeseca(NODE *glava, char* datum, int brojRacuna)
{
	RACUN *niz = (RACUN*)calloc(brojRacuna, sizeof(RACUN));
	double ukupno = 0, pdv = 0;
	int i = 0;
	NODE *p = glava;
	if (p == NULL)
		return;
	for (; p; p = p->sljedeci)
	{
		if (p->racun.datum[3] == datum[0] && p->racun.datum[4] == datum[1])
			niz[i++] = p->racun;
	}
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("DATUM\t\t\tKUPAC\t\tARTIKAL\t\tSIFRA\t\tCIJENA\t\tKOLICINA\tUKUPNO\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < brojRacuna; i++)
	{
		for (int j = 0; j < niz[i].brojArtikala; j++)
			printf("%s\t\t%s\t\t%s\t\t%d\t\t%.2lf %s\t%.2lf\t\t%.2lf %s\n", niz[i].datum, niz[i].kupac, niz[i].nizArtikala[j].naziv, niz[i].nizArtikala[j].sifra, niz[i].nizArtikala[j].cijena*niz[i].valuta.koeficijent,niz[i].valuta.oznaka, niz[i].nizArtikala[j].kolicina, niz[i].nizArtikala[j].ukupno*niz[i].valuta.koeficijent, niz[i].valuta.oznaka);
		ukupno += niz[i].ukupno;
		pdv += niz[i].pdv;

	}
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("UKUPNO: %.2lf %s\n", ukupno*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
	printf("PDV: %.2lf %s\n", pdv*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
	printf("UKUPNO ZA PLACANJE: %.2lf %s\n", pdv*niz[0].valuta.koeficijent+ ukupno*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	ispisZaMjesec(niz, brojRacuna, ukupno, pdv);
	free(niz);

}

void ispisZaMjesec(RACUN *niz, int brojRacuna, double ukupno, double pdv)
{
	FILE*file=NULL;
	if (file = fopen("Pregled_ukupne_prodaje_za_mjesec.txt", "w"))
	{
		fprintf(file,"---------------------------------------------------------------------------------------------------------------------\n");
		fprintf(file,"DATUM\t\t\tKUPAC\t\tARTIKAL\t\tSIFRA\t\tCIJENA\t\tKOLICINA\tUKUPNO\n");
		fprintf(file,"---------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < brojRacuna; i++)
		{
			for (int j = 0; j < niz[i].brojArtikala; j++)
				fprintf(file,"%s\t\t%s\t\t%s\t\t%d\t\t%.2lf %s\t%.2lf\t\t%.2lf %s\n", niz[i].datum, niz[i].kupac, niz[i].nizArtikala[j].naziv, niz[i].nizArtikala[j].sifra, niz[i].nizArtikala[j].cijena*niz[i].valuta.koeficijent, niz[i].valuta.oznaka, niz[i].nizArtikala[j].kolicina, niz[i].nizArtikala[j].ukupno*niz[i].valuta.koeficijent, niz[i].valuta.oznaka);
			ukupno += niz[i].ukupno;
			pdv += niz[i].pdv;

		}
		fprintf(file,"---------------------------------------------------------------------------------------------------------------------\n");
		fprintf(file,"UKUPNO: %.2lf %s\n", ukupno*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
		fprintf(file,"PDV: %.2lf %s\n", pdv*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
		fprintf(file,"UKUPNO ZA PLACANJE: %.2lf %s\n", pdv*niz[0].valuta.koeficijent + ukupno*niz[0].valuta.koeficijent, niz[0].valuta.oznaka);
		fprintf(file,"---------------------------------------------------------------------------------------------------------------------\n");
		fclose(file);
	}
	else printf("Neusjesno otvaranej fajla!\n");
}

void dodajUListu(NODE** glava, RACUN* racun)
{
	NODE* noviNode = (NODE*)malloc(sizeof(NODE));
	noviNode->racun = *racun;
	noviNode->sljedeci = 0;
	if (*glava != 0)
		noviNode->sljedeci = *glava;
	*glava = noviNode;
}

void pregledKupca(NODE* lista, char* kupac, int brojRacuna)
{
	NODE* temp;
	int i = 0, j, k;
	RACUN* nizRacuna = (RACUN*)calloc(brojRacuna , sizeof(RACUN));
	for (temp = lista; temp != NULL; temp = temp->sljedeci)
	{
		if (strcmp(temp->racun.kupac, kupac) == 0)
			nizRacuna[i++] = temp->racun;
	}
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("Kupac:%s \n", nizRacuna[0].kupac);
	printf("-------------------------------------------------------------------------------------------------\n");
	printf("ARTIKAL\t\tSIFRA\t\tCIJENA\t\t\tKOLICINA\tUKUPNO\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	for (j = 0; j<brojRacuna; j++)
	{
		for (k = 0; k<nizRacuna[j].brojArtikala; k++)
		{
			printf("%s\t\t%d\t\t%.2lf %s\t\t%.2lf\t\t%.2lf %s\n", nizRacuna[j].nizArtikala[k].naziv, nizRacuna[j].nizArtikala[k].sifra, nizRacuna[j].nizArtikala[k].cijena*nizRacuna[j].valuta.koeficijent,nizRacuna[j].valuta.oznaka, nizRacuna[j].nizArtikala[k].kolicina, nizRacuna[j].nizArtikala[k].ukupno*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
		}
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("Datum:%s", nizRacuna[j].datum);
		printf(" Ukupno(racun): %.2lf %s", nizRacuna[j].ukupno*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
		printf(" PDV: %.2lf %s", nizRacuna[j].pdv*nizRacuna[j].valuta.koeficijent,nizRacuna[j].valuta.oznaka);
		printf(" Ukupno za placanje: %.2lf %s\n", nizRacuna[j].ukupnoZaPlatiti*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
		printf("-------------------------------------------------------------------------------------------------\n");
	}
	ispisZaKupca(nizRacuna, brojRacuna);
	free(nizRacuna);
}

void ispisZaKupca(RACUN *nizRacuna, int brojRacuna)
{
	FILE* fajl = 0;
	if (fajl = fopen("Pregled_podataka_za_kupca.txt", "w"))
	{
		fprintf(fajl,"-------------------------------------------------------------------------------------------------\n");
		fprintf(fajl,"Kupac:%s \n", nizRacuna[0].kupac);
		fprintf(fajl,"-------------------------------------------------------------------------------------------------\n");
		fprintf(fajl,"ARTIKAL\t\tSIFRA\t\tCIJENA\t\t\tKOLICINA\tUKUPNO\n");
		fprintf(fajl,"-------------------------------------------------------------------------------------------------\n");
		for (int j = 0; j < brojRacuna; j++)
		{
			for (int k = 0; k < nizRacuna[j].brojArtikala; k++)
			{
				fprintf(fajl,"%s\t\t%d\t\t%.2lf %s\t\t%.2lf\t\t%.2lf %s\n", nizRacuna[j].nizArtikala[k].naziv, nizRacuna[j].nizArtikala[k].sifra, nizRacuna[j].nizArtikala[k].cijena*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka, nizRacuna[j].nizArtikala[k].kolicina, nizRacuna[j].nizArtikala[k].ukupno*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
			}
			fprintf(fajl,"-------------------------------------------------------------------------------------------------\n");
			fprintf(fajl,"Datum:%s", nizRacuna[j].datum);
			fprintf(fajl," Ukupno(racun): %.2lf %s", nizRacuna[j].ukupno*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
			fprintf(fajl," PDV: %.2lf %s", nizRacuna[j].pdv*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
			fprintf(fajl," Ukupno za placanje: %.2lf %s\n", nizRacuna[j].ukupnoZaPlatiti*nizRacuna[j].valuta.koeficijent, nizRacuna[j].valuta.oznaka);
			fprintf(fajl,"-------------------------------------------------------------------------------------------------\n");
		}
		fclose(fajl);
	}
	else printf("Neusjesno otvaranej fajla!\n");
}
