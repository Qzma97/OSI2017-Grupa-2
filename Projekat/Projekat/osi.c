#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "osi.h"
#include "Formati.h"
#include "Pretraga.h"
#include "valuta.h"
#include "korisnici.h"



int prijava(KORISNIK* nizNaloga, int velicinaNiza)
{
	int check = 0;
	char ime[16], pin[5], pom[31] = { 0 };
	printf("KORISNICKO IME:"); scanf("%s", ime);
	printf("PIN:"); 
	do { 
		//Provjera da li je uneseni PIN broj ili je korisnik upisivao druge znakove.
		//Radi sve dok korisnik ne unese tacan PIN.
		if (check) {
			printf("PIN smije samo cifre sadrzati!\n");
			printf("Molim vas unesite ponovo vas PIN: ");
		}
		scanf("%s", pom);
		strncpy(pin, pom, 5);
		check++;
	} while (pin[0] < 48 || pin[0]>57);
	KORISNIK korisnik;
	int ispravno=0,neispravno=0;//Broj ispravnih i neispravnih racuna koji ce se ucitati.
	if ((search(nizNaloga, velicinaNiza, &korisnik, ime, pin)) == 1)
	{
		//Uspjesna prijava.
		printf("USPJESNA PRIJAVA!\n");
		Sleep(1000);
		system("cls");
		//Tip korisnika Analiticar.
		if (korisnik.tip == 0)
		{
			VALUTA val = ucitajValutu();
			int format = 0;
			WIN32_FIND_DATA findFileData;
			HANDLE hFind;
			FILE* f,*f1=0, *dat;
			NODE* head=NULL;
			RACUN racun;
			int br = 0;
			//Ukoliko imamo vec obradjenje racune, ucitavaju se. Ucitavanje obradjenih informacija iz fajla "racuni.txt" .
			if (dat = fopen("racuni.txt", "r"))
			{
				fseek(dat, 12, SEEK_SET);
				fscanf(dat, "%d\n", &br);
				for (int i = 0; i < br; i++)
				{
					fscanf(dat, "%s %s %d\n", racun.datum, racun.kupac, &racun.brojArtikala);
					racun.nizA = (ARTIKAL*)malloc(racun.brojArtikala * sizeof(ARTIKAL));
					for (int j = 0; j < racun.brojArtikala; j++)
						fscanf(dat, "%s %d %lf %lf %lf\n", racun.nizA[j].naziv, &racun.nizA[j].sifra, &racun.nizA[j].cijena, &racun.nizA[j].kolicina, &racun.nizA[j].ukupno);
					fscanf(dat, "%lf %lf %lf %lf %s\n", &racun.ukupno, &racun.pdv, &racun.ukupnoPl,&racun.valuta.koeficijent,racun.valuta.oznaka);
					racun.valuta.koeficijent = val.koeficijent;
					strcpy(racun.valuta.oznaka, val.oznaka);
					insert(&head, &racun);
					fseek(dat, 77, SEEK_CUR);
				}
				fclose(dat);
			}
			char* inputDir = "./input/"; //direktorijum do input foldera.
			hFind = FindFirstFile("./input/*", &findFileData); //Trazenje prvog fajla u folderu input. Otvaranje HANDLE-a.
			if (hFind != INVALID_HANDLE_VALUE)
			{
				do {
					//Trazenje putanje do fajla.
					char*nazivFajla = (char*)calloc(strlen(findFileData.cFileName), sizeof(char));
					strcpy(nazivFajla, findFileData.cFileName);
					char*putanja = (char*)calloc(strlen(nazivFajla) + strlen(inputDir), sizeof(char));
					strcat(putanja, inputDir);
					strcat(putanja, nazivFajla);

					//Otvranje i obrada racuna(fajla).
					f = fopen(putanja, "r");
					if (f != NULL)
					{
						//Provjera da li je racun formata 5.
						if (findFileData.cFileName[strlen(findFileData.cFileName) - 1] == 'v'&&findFileData.cFileName[strlen(findFileData.cFileName) - 2] == 's'&&findFileData.cFileName[strlen(findFileData.cFileName) - 3] == 'c')
							format = 5;
						else
						{
							//Provjera za ostale formate.
							format=checkFormat(f);
							fclose(f);
							f = fopen(putanja, "r");
						}
						//Obrada zavisno od formata.
						switch (format)
						{
						case 1:
							racun=format1(f, putanja);//Obrada racuna koji su formata 1.
							if (verifikacija(&racun))// Verifikacija ispravnosti racuna.
							{
								//Ispravan racun.
								//Kopiranje fajla iz input foldera u memory folder.
								racun.valuta.koeficijent = val.koeficijent;
								strcpy(racun.valuta.oznaka, val.oznaka);
								insert(&head, &racun);
								memory(f, putanja, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//Neispravan racun.
								//Kopiranje fajla iz input foldera u error folder.
								neispravno++;
								error(f, putanja, findFileData.cFileName);
							}
							break;
						case 2:
							racun = format2(f, putanja);//Obrada racuna koji su formata 2.
							if (verifikacija(&racun))// Verifikacija ispravnosti racuna.
							{
								//Ispravan racun.
								//Kopiranje fajla iz input foldera u memory folder.
								racun.valuta.koeficijent = val.koeficijent;
								strcpy(racun.valuta.oznaka, val.oznaka);
								insert(&head, &racun);
								memory(f, putanja, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//Neispravan racun.
								//Kopiranje fajla iz input foldera u error folder.
								neispravno++;
								error(f, putanja, findFileData.cFileName);
							}
							break;
						case 3:
							racun = format3(f, putanja);//Obrada racuna koji su formata 3.
							if (verifikacija(&racun))// Verifikacija ispravnosti racuna.
							{
								//Ispravan racun.
								//Kopiranje fajla iz input foldera u memory folder.
								racun.valuta.koeficijent = val.koeficijent;
								strcpy(racun.valuta.oznaka, val.oznaka);
								insert(&head, &racun);
								memory(f, putanja, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//Neispravan racun.
								//Kopiranje fajla iz input foldera u error folder.
								neispravno++;
								error(f, putanja, findFileData.cFileName);
							}
							break;
						case 4:
							racun=format4(f,putanja);//Obrada racuna koji su formata 1.
							if (verifikacija(&racun))// Verifikacija ispravnosti racuna.
							{
								//Ispravan racun.
								//Kopiranje fajla iz input foldera u memory folder.
								racun.valuta.koeficijent = val.koeficijent;
								strcpy(racun.valuta.oznaka, val.oznaka);
								insert(&head, &racun);
								memory(f, putanja, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//Neispravan racun.
								//Kopiranje fajla iz input foldera u error folder.
								neispravno++;
								error(f, putanja, findFileData.cFileName);
							}
							break;
						case 5:
							racun = format5(f, putanja, findFileData.cFileName);//Obrada racuna koji su formata 5.
							if (verifikacija(&racun))// Verifikacija ispravnosti racuna.
							{
								//Ispravan racun.
								//Kopiranje fajla iz input foldera u memory folder.
								racun.valuta.koeficijent = val.koeficijent;
								strcpy(racun.valuta.oznaka, val.oznaka);
								f = fopen(putanja, "r");
								insert(&head, &racun);
								memory(f, putanja, findFileData.cFileName);
								ispravno++;
							}
							else
							{
								//Neispravan racun.
								//Kopiranje fajla iz input foldera u error folder.
								f = fopen(putanja, "r");
								neispravno++;
								error(f, putanja, findFileData.cFileName);
							}
							break;
						}
						fclose(f);//Zatvaranje fajla.
						remove(putanja);//Brisanje fajla u input folderu i kraj obrade jednog racuna.
					}
				} while (FindNextFile(hFind, &findFileData) != 0);
				FindClose(hFind);//Zatvaranje HADLE-a.
			}
			//Cuvanje obradjenih informacija u fajl "racuni.txt" .
			if (dat = fopen("racuni.txt", "w"))
			{
				fprintf(dat, "Broj racuna:%d\n", br + ispravno);
				for (NODE *temp = head; temp; temp = temp->next)
				{
					fprintf(dat, "%s %s %d\n", temp->racun.datum, temp->racun.kupac, temp->racun.brojArtikala);
					for (int i = 0; i < temp->racun.brojArtikala; i++)
					{
						fprintf(dat, "%s %d %.2lf %.2lf %.2lf\n", temp->racun.nizA[i].naziv, temp->racun.nizA[i].sifra, temp->racun.nizA[i].cijena, temp->racun.nizA[i].kolicina, temp->racun.nizA[i].ukupno);

					}
					fprintf(dat, "%.2lf %.2lf %.2lf %.2lf %s\n", temp->racun.ukupno, temp->racun.pdv, temp->racun.ukupnoPl,temp->racun.valuta.koeficijent,temp->racun.valuta.oznaka);
					fprintf(dat, "___________________________________________________________________________\n");
				}
				fclose(dat);
			}
			printf("Broj novih ispravnih racuna: %d\n", ispravno);//Ispis broja ispravnih racuna koji su obradjeni u ovom pokretanju programa,
			printf("Broj novih neispravnih racuna: %d\n", neispravno);//Ispis broja neispravnih racuna koji su obradjeni u ovom pokretanju programa,
			int found;
			char unos[20],pom[31] = { 0 };// pom - pomocna promjenljiva za upis naziva artikla,mjeseca ili  kupca.
			do {
				//Meni sa opcijama za analiticara.
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("IZABERITE OPCIJU:\n");
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("\t1.Pregled svih podataka za odredjenog kupca\n");
				printf("\t2.Pregled svih podataka za odredjeni proizvod\n");
				printf("\t3.Pregled ukupne prodaje za odredjeni mjesec\n");
				printf("\t0.Izlaz iz programa\n");
				printf("-------------------------------------------------------------------------------------------------\n");
				scanf("%s", unos);//Izbor opcije.
				system("cls");
				if (unos[0] == '1')
				{
					//Pregled svih podataka za odredjenog kupca.
					printf("Unesite naziv trazenog kupca: ");
					scanf("%s", pom);
					if (found = trazi_po_kupcu(head, pom))
					{
						kupac(head, pom, found);
					}
					else
						printf("Nema trazenog kupca!\n");
				}
				else if (unos[0] == '2')
				{
					//Pregled svih podataka za odredjeni proizvod.
					printf("Unesite trazeni proizvod: ");
					scanf("%s", pom);
					if (found = trazi_po_artiklu(head, pom))
					{
						artikal(head, found, pom);
					}
					else
						printf("Nema trazenog artikla!\n");
				}
				else if (unos[0] == '3')
				{
					//Pregled ukupne prodaje za odredjeni mjesec.
					printf("Pregled ukupne prodaje za mjesec(2 cifre):");
					scanf("%s", pom);
					int broj = trazi_po_datumu(head, pom);
					if (broj == 0)
						printf("Nema podataka za taj mjesec!\n");
					else
						mjesec(head, pom, broj);
				}
				
			} while (unos[0] != '0');
			brisi_listu(&head);
		}
		//Tip korisnika Administrator.
		else if (korisnik.tip == 1)
		{
			CVOR* lista_naloga = ucitaj_naloge_iz_fajla(); //Ucitavanje liste korisnic
			char unos[20];
			do
			{
				//Meni sa opcijama za Administratora.
				printf("-----------------------------------------------------------------------------------------------------------------------\n");
				printf("IZABERITE OPCIJU:\n");
				printf("-----------------------------------------------------------------------------------------------------------------------\n");
				printf("\t1.Podesavanje valute\n");
				printf("\t2.Prikaz liste korisnickih naloga\n");
				printf("\t3.Promjena tipa korisnickog naloga\n");
				printf("\t4.Brisanje korisnickog naloga\n");
				printf("\t0.Izlaz iz programa\n");
				printf("-----------------------------------------------------------------------------------------------------------------------\n");
				scanf("%s", unos);//Izbor opcije.
				system("cls");
				if (unos[0] == '1')
				{
					//Podesavanja valute.
					izborValute();
				}
				else if (unos[0] == '2')
				{
					//Formatirani ispis liste korisnickih naloga.
					ispis_korisnika(lista_naloga);
				}
				else if (unos[0] == '3')
				{
					//Promjena tipa korisnickog naloga.
					int redniBrojNaloga, tipNaloga, provjera = 0,vel=listSize(lista_naloga);
					printf("Moguci korisnicki tipovi su:\n [1] Admin\n [0] Analiticar\n");
					printf("Unesite redni broj korisnickog naloga i u koji tip mijenjate dati nalog (2 broja sa razmakom izmedju): ");
					do
					{
						if (provjera) //U slucaju neispravnog unosa ispisace se sljedece poruke.
						{
							printf("Ukucali ste nepostojeci redni broj ili ste ukucali nepostojeci tip korisnika!\n");
						}
						scanf("%d %d",&redniBrojNaloga,&tipNaloga);
						provjera++;
					} while (((tipNaloga != 0) && (tipNaloga != 1))||((redniBrojNaloga<0)||(redniBrojNaloga>=vel)));
					promjenaTipa(redniBrojNaloga, tipNaloga, &lista_naloga);
				}
				else if (unos[0] == '4')
				{
					//Brisanje korisnickog naloga
					int redniBrojNaloga, provjera = 0, velicinaListe = listSize(lista_naloga);
					printf("Unesite redni broj korisnickog naloga koji zelite obrisati: ");
					do
					{
						if (provjera)
						{
							printf("Ukucali ste nepostojeci redni broj!\n");
						}
						scanf("%d", &redniBrojNaloga);
						provjera++;
					} while ((redniBrojNaloga<0) || (redniBrojNaloga>=velicinaListe));
					deleteNode(&lista_naloga, redniBrojNaloga);
				}
			} while (unos[0] != '0');	
			FILE* f = fopen("korisnici.dat", "wb");
			while (lista_naloga)//Cuvanje izmjena korisnickih naloga i oslobadjanje memorije.
			{
				CVOR* temp = lista_naloga;
				lista_naloga = lista_naloga->sljedeci;
				fwrite(&temp->k, sizeof(KORISNIK), 1, f);
				free(temp);
			}
			fclose(f);
		}
		return 1;//KRAJ USPJESNE PRIJAVE	
	}
	else
	{
		//Neuspjesna prijava.
		printf("NEUSPJESNA PRIJAVA!\n");
		return 0;
	}
	return 0;
}

void registracija(KORISNIK* niz, int n, FILE *f)
{

	KORISNIK temp;
	char pom1[16], pom2[5];
	printf("UNESITE PODATKE:\n");
	int i = 1;
	do
	{
		//Unos korisnickog imena i provjera da li je vec ime u upotrebi.
		printf("\tKorisnicko ime (bez upotrebe razmaka):");
		scanf("%s", pom1);
		i = search_(niz, n, pom1);
		if (i == 1)
			printf("Korisnik sa tim imenom vec postoji.\n");
	} while (i == 1);
	strcpy(temp.korisnicko_ime, pom1);
	do
	{
		//Unos PIN-a.
		printf("\tPIN(4 broja):");
		scanf("%s", pom2);
		i = strlen(pom2);int j;
		for ( j = 0; j < sizeof(pom2) - 1; j++)
			if (pom2[j] < 48 || pom2[j]>57)//Provjera da li je PIN u odgovarajucem formatu.
				i = 5;
		if (i != 4)
			printf("PIN se mora sastojati od 4 broja!\n");
	} while (i != 4);
	strcpy(temp.PIN, pom2);
	printf("\tIme:"); scanf("%s", temp.ime);//Unos imena.
	printf("\tPrezime:"); scanf("%s", temp.prezime);//Unos prezimena.
	printf("\tEmail adresa:");scanf("%s", temp.email);//Unos E-mail adrese.
	temp.tip = 0;
	niz = (KORISNIK *)realloc(niz, (++n) * sizeof(KORISNIK));
	niz[n - 1] = temp;
	f = fopen("korisnici.dat", "wb");
	fwrite(niz, sizeof(KORISNIK), n, f);//Cuvanje novog korisnika.
	fclose(f);
	printf("PRIJAVA:\n");
	prijava(niz, n);//Pokretanje prijave.
}

int search(KORISNIK* niz, int n, KORISNIK *k, char *ime, char *pin)
{
    int i;
	for ( i = 0; i < n; i++)
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
    int i;
	for ( i = 0; i < n; i++)
	{
		if ((strcmp(ime, niz[i].korisnicko_ime) == 0))
			return 1;
	}
	return 0;
}

int checkFormat(FILE *f)
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
