#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "osi.h"
#include "Formati.h"
#include "Pretraga.h"



int prijava(KORISNIK* niz, int n)
{
	char ime[16], pin[5];
	printf("KORISNICKO IME:"); scanf("%s", ime);
	printf("PIN:"); scanf("%s", pin);
	KORISNIK k;
	int d,ispravno=0,neispravno=0;
	if ((search(niz, n, &k, ime, pin)) == 1)
	{
		printf("USPJESNA PRIJAVA!\n");
		Sleep(1000);
		system("cls");
		if (k.tip == 0)
		{
			int format = 0;
			WIN32_FIND_DATA findFileData;
			HANDLE hFind;
			FILE* f,*f1=0;
			NODE* head=NULL;
			RACUN racun;
			char gk=0,*c = "./input/",*g="./memory/";
			hFind = FindFirstFile("./input/*", &findFileData);
			if (hFind != INVALID_HANDLE_VALUE)
			{
				do {
					char*d = (char*)calloc(strlen(findFileData.cFileName), sizeof(char));
					strcpy(d, findFileData.cFileName);
					char*e = (char*)calloc(strlen(d) + strlen(c), sizeof(char));
					strcat(e, c);
					strcat(e, d);


					f = fopen(e, "r");
					if (f != NULL)
					{
						if (findFileData.cFileName[strlen(findFileData.cFileName) - 1] == 'v'&&findFileData.cFileName[strlen(findFileData.cFileName) - 2] == 's'&&findFileData.cFileName[strlen(findFileData.cFileName) - 3] == 'c')
							format = 5;
						else
						{
							format=chechkFormat(f);
							fclose(f);
							f = fopen(e, "r");
						}
						switch (format) 
						{
						case 1:
							racun=format1(f, e);
							if (verifikacija(&racun))
							{
								//f = fopen(e, "r");
								insert(&head, &racun);
								memory(f, e, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//f = fopen(e, "r");
								neispravno++;
								error(f, e, findFileData.cFileName);
							}
							break; 
						case 2:
							racun = format2(f, e);
							if (verifikacija(&racun))
							{
								//f = fopen(e, "r");
								insert(&head, &racun);
								memory(f, e, findFileData.cFileName);
								ispravno++;
							}
							else
							{
							//	f = fopen(e, "r");
								neispravno++;
								error(f, e, findFileData.cFileName);
							}
							break;
						case 3:
							racun = format3(f, e);
							if (verifikacija(&racun))
							{
								//f = fopen(e, "r");
								insert(&head, &racun);
								memory(f, e, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//f = fopen(e, "r");
								neispravno++;
								error(f, e, findFileData.cFileName);
							}
							break;
						case 4:
							racun=format4(f,e);
							if (verifikacija(&racun))
							{
							//	f = fopen(e, "r");
								insert(&head, &racun);
								memory(f, e, findFileData.cFileName);
								ispravno++;
							}
							else
							{
							//	f = fopen(e, "r");
								neispravno++;
								error(f, e, findFileData.cFileName);
							}
							break;
						case 5:
							racun = format5(f, e, findFileData.cFileName);
							if (verifikacija(&racun))
							{
								f = fopen(e, "r");
								insert(&head, &racun);
								memory(f, e, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								f = fopen(e, "r");
								neispravno++;
								error(f, e, findFileData.cFileName);
							}
							break;
						default: 
							break;	
						}
						fclose(f);
						remove(e);
					}
				} while (FindNextFile(hFind, &findFileData) != 0);

				FindClose(hFind);
			}
			printf("Broj ispravnih racuna: %d\n", ispravno);
			printf("Broj neispravnih racuna: %d\n", neispravno);
			int found;
			char d[3],pom[31] = { 0 };
			do {
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("IZABERITE OPCIJU:\n");
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("\t1.Pregled svih podataka za odredjenog kupca\n");
				printf("\t2.Pregled svih podataka za odredjeni proizvod\n");
				printf("\t3.Pregled ukupne prodaje za odredjeni mjesec\n");
				printf("\t0.Izlaz iz programa\n");
				printf("-------------------------------------------------------------------------------------------------\n");
				scanf("%s", d);
				system("cls");
				if (d[0] == '1');
				//pregled_kupca();
				else if (d[0] == '2')
				{
					printf("Unesite trazeni proizvod: ");
					scanf("%s", pom);
					if (found = trazi_po_artiklu(head, pom))
					{
						artikal(head, found, pom);
					}
					else
						printf("Nema trazenog artikla!\n");
				}

				/*
				else if (d[0] == '3')
				ukupna_prodaja();
				else
				printf("Greska!");*/
			} while (d[0] != '0');
			brisi_listu(&head);
		}
		else if (k.tip == 1)
		{
			printf("\t1.Podesavanje valute\n");
			printf("\t2.Upravljanje korisnickim nalozima\n");
			scanf("%d", &d);
			printf("-------------------------------------------------------------------------------------------------\n");
			/*if (d == 1)
			podesavanje_valute();
			else if (d == 2)
			upravljanje_nalozima();
			else
			printf("Greska!\n");*/
		}
		return 1;

	}
	else
	{
		printf("NEPOSTOJECI KORISNIK!\n");
		return 0;
	}

}

void registracija(KORISNIK* niz, int n, FILE *f)
{

	KORISNIK temp;
	char pom1[16], pom2[5];
	printf("UNESITE PODATKE:\n");
	int i = 1;
	do
	{
		printf("\tKorisnicko ime:");
		scanf("%s", pom1);
		i = search_(niz, n, pom1);
		if (i == 1)
			printf("Korisnik sa tim imenom vec postoji.\n");
	} while (i == 1);
	strcpy(temp.korisnicko_ime, pom1);
	do
	{
		printf("\tPIN(4 broja):");
		scanf("%s", pom2);
		i = strlen(pom2);
		for (int j = 0; j < sizeof(pom2) - 1; j++)
			if (pom2[j] < 48 || pom2[j]>57)
				i = 5;
		if (i != 4)
			printf("PIN se mora sastojati od 4 broja!\n");
	} while (i != 4);
	strcpy(temp.PIN, pom2);
	printf("\tIme:"); scanf("%s", temp.ime);
	printf("\tPrezime:"); scanf("%s", temp.prezime);
	temp.tip = 0;
	niz = (KORISNIK *)realloc(niz, (++n) * sizeof(KORISNIK));
	niz[n - 1] = temp;
	f = fopen("korisnici.dat", "wb");
	fwrite(niz, sizeof(KORISNIK), n, f);
	fclose(f);
	printf("PRIJAVA:\n");
	prijava(niz, n);
}

int search(KORISNIK* niz, int n, KORISNIK *k, char *ime, char *pin)
{
	for (int i = 0; i < n; i++)
	{
		if ((strcmp(ime, niz[i].korisnicko_ime) == 0) && (strcmp(pin, niz[i].PIN) == 0))
		{
			*k = niz[i];
			return 1;
		}
	}
	return 0;

}

int search_(KORISNIK* niz, int n, char* ime)
{
	for (int i = 0; i < n; i++)
	{
		if ((strcmp(ime, niz[i].korisnicko_ime) == 0))
			return 1;
	}
	return 0;
}

int chechkFormat(FILE *f)
{
	int n = 7,m=5;
	char c[36], ignore[1024];
	fscanf(f, "%6c", c);
	c[6] = '\0';
	if (strcmp(c, "Kupac:") == 0)
	{//format 1 i 4

		while (n--)
			fgets(ignore, sizeof(ignore), f);
		if (strcmp(ignore, "---------------------------------------\n") == 0)
			return 4;
		else return 1;
	}
	else
	{//format 2 i 3
		while(m--)
			fgets(ignore, sizeof(ignore), f);
		fscanf(f, "%6c", c);
		c[6] = '\0';
		if (strcmp(c, "Kupac:") == 0)
			return 2;
		else return 3;
	}
}
