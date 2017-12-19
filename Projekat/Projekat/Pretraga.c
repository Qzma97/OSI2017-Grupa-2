#include "Pretraga.h"
#include <string.h>
#include <stdlib.h>

int trazi_po_artiklu(NODE* head, char* naziv)
{
	int count = 0;
	NODE* temp = head;
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