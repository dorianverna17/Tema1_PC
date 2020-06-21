#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Functie care sterge un numar de caractere de la o pozitie anume
void strdel(char *d, int n)
{
	char aux[200];
	if(n < strlen(d))
	{
		strcpy(aux, d+n);
		strcpy(d, aux);
	}
	else *d = '\0';
}
//Functie de citire
void citire(char*** line, int* n)
{
	//Aici citesc numarul de linii al matricei
	scanf("%d", n);
	getchar();
	//Aloc dinamic numarul de linii
	(*line) = (char**)malloc((*n) * sizeof(char*));
	char* str;
	//Am luat un sir auxiliar
	str = (char *)malloc(200 * sizeof(char));
	int i;
	//Citesc liniile intr-un for unde le si aloc dinamic
	for(i = 0; i < (*n); i++)
	{
		(*line)[i] = (char*)malloc(200 * sizeof(char));
		strcpy((*line)[i], "");
		scanf("%s", str);
		//Citesc elementele unei linii pana la intalnirea caracterului "0"
		while(strcmp(str, "0") != 0)
		{	
		//Formez din nou linia, dar fara caracterul 0
		strcat((*line)[i], str);
		strcat((*line)[i], " ");	
		scanf("%s", str);
		}
		//Realoc dinamic fiecare linie cu exact cat imi trebuie
		(*line)[i] = (char*)realloc((*line)[i], (strlen((*line)[i]) + 1) * sizeof(char));
		strdel((*line)[i] + strlen((*line)[i]) - 1, 100);
	}
	//Eliberez sirul auxiliar
	free(str);
}
//Functie in care calculez media de pe fiecare linie
void calcul_medie(char*** line, int n, float medie[])
{
	int i, x, S, nr;
	char *sep = " \n";
	char *str;
	//Ma folosesc de un sir auxiliar pentru a nu strica liniile de note
	for(i = 0; i < n; i++)
	{
		S = 0; nr = 0;
		medie[i] = 0;
		//Aloc dinamic sirul auxiliar si copiez continutul unei linii in el(incerc sa nu stric continutul liniei)
		str = (char*)malloc((strlen(((*line)[i])) + 1) * sizeof(char));
		strcpy(str, (*line)[i]);
		//Folosesc strtok
		char* p = strtok(str, sep);
		//Iau caracterele care compun notele si le fac numere intregi
		while(p != NULL)
		{
			x = atoi(p);
			//Calculez suma si aflu si nr lor
			S = S + x;
			nr++;
			p = strtok(0, sep);
		}
		//Fac mediile si le pun intr-un vector de medii
		if(nr != 0)
			medie[i] = (float) S/nr;
		free(str);
	}
}
//Functie care construieste un vector auxiliar in care sunt copiate toate mediile din vectorul de la functia precedenta
void val_v(int n,float v[],float medie[])
{
	int i;
	for(i = 0; i < n; i++)
	{
		v[i] = medie[i];
	}
}
//Functie care sorteaza elementele unui vector(bubblesort)
void sortare_medii(char*** line, int n, float v[])
{
	int schimb, i;
	float aux;
	do{
		schimb = 0;
		for(i = 0; i < n-1; i++)
			if(v[i] < v[i+1])
			{
				aux = v[i];
				v[i] = v[i+1];
				v[i+1] = aux;
				schimb = 1;	
			}
	}while(schimb == 1);
}
//Functie de afisare a liniilor in ordinea mediilor
void afisare(char*** line, int n, float medie[], float v[])
{
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			//Daca elementul din vectorul sortat corespunde elementului din vectorul de medii atunci se afiseaza lina
			if(v[i] == medie[j])
			{
				printf("%-10.3f", medie[j]);
				//Daca a fost afisata linia, atunci media nu mai conteaza si o facem negativa
				medie[j] = -1;
				//Afisare
				if(i != n-1)
				printf("%-s\n", (*line)[j]);
				else printf("%s\n", (*line)[j]);		
			}
}
int main()
{
	//Declarare matrice si apeluri ale functiilor
	char** line;
	int n;
	citire(&line, &n);
	float medie[n], v[n];
	calcul_medie(&line, n, medie);
	val_v(n, v, medie);
	sortare_medii(&line, n, v);
	afisare(&line, n, medie, v);
	//Eliberare memorie de pe heap
	int i;
	for(i = 0; i < n; i++)
	{
		free(line[i]);
	}
	free(line);
	return 0;
}