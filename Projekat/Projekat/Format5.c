#include "Format5.h"
#include <stdlib.h>
#include <string.h>

RACUN format5(FILE *f, char *dir,char*nazivf)
{
	double ukupno = 0;
	RACUN racun;
	char pom[256], sifra[25] = {0};
	int i = 5,j=0,n=10;
	do {
		racun.kupac[j] = nazivf[i];
		j++;
		i++;
	} while (nazivf[i] != '#');
	racun.kupac[j] = 0;
	i++;
	j = 0;
	while (n--)
	{
		racun.datum[j] = nazivf[i];
		j++;
		i++;
	}
	racun.datum[2] = racun.datum[5] = '/';
	racun.datum[10] = 0;
	n = racun.brojArtikala=countf5(f);
	racun.nizA = (ARTIKAL*)calloc(n, sizeof(ARTIKAL));
	f = fopen(dir, "r");
	fgets(pom,sizeof(pom), f);
	i = 0;
	pom[1] = 0;
	while (n--)
	{
		j = 0;
		while (pom[0]=fgetc(f))
			if (pom[0] < 48 || pom[0]>57)
				j++;
			else
				break;
		fseek(f, -(j+1), SEEK_CUR);
		int e = 0;
		while (j--)
		{
			racun.nizA[i].naziv[e] = fgetc(f);
			e++;
		}
		fscanf(f, "%d,%lf,%lf,%lf\n", &racun.nizA[i].sifra, &racun.nizA[i].kolicina, &racun.nizA[i].cijena, &racun.nizA[i].ukupno);
		ukupno += racun.nizA[i].ukupno;
		i++;
	}
	racun.pdv = ukupno * 0.17;
	racun.ukupno = ukupno;
	racun.ukupnoPl = racun.pdv + racun.ukupno;
	return racun;
}

int countf5(FILE *f)
{
	int count = 0;
	char pom[256];
	fgets(pom, sizeof(pom), f);
	while (fgets(pom, sizeof(pom), f))
		count++;
	return count;
}
