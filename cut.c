#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Functie care sterge un numar de caractere de la o pozitie anume
void strdel(char *d, int n)
{
	char aux[200];
	if(n < strlen(d))
	{
		strcpy(aux, d + n);
		strcpy(d, aux);
	}
	else *d = '\0';
}
//Functie de citire
void citire(char*** line, char del[], int *n, int *m, char fields[], char out_del[])
{
	int i;
	//Citire sir de delimitatori
	fgets(del, 10, stdin);
	//Citire a dimensiunii numarului de indici
	scanf("%d", n);
	//Scap de enterul de dupa
	getchar();
	//Citirea sirului campurilor(fields)
	fgets(fields, 200, stdin);
	//Sterg enterul de la sfarsit
	strdel(fields + strlen(fields) - 1, 1);
	//Citirea delimitatorului pe care trebuie sa il introduc
	fgets(out_del, 10, stdin);
	//stergerea delimitatorului
	strdel(out_del + strlen(out_del) - 1, 1);
	//Citirea numarului de linii a textului
	scanf("%d",m);
	//Scap de enterul de dupa
	getchar();
	//Aici aloc dinamic numarul de linii ale textului intr-o matrice de pointeri
	(*line) = (char**)malloc((*m) * sizeof(char*));
	//str e sir auxiliar
	char* str;
	//Aloc dinamic pe str
	str = (char *)malloc(200 * sizeof(char));
	//Fac o structura repetitiva pentru citirea liniilor
	for(i = 0; i < (*m); i++)
	{
		//Citesc in sirul auxiliar
		fgets(str, 200, stdin);
		//Aloc liniei atat memorie cat ii trebuie
		(*line)[i] = (char*)malloc((strlen(str) + 1) * sizeof(char));
		//Copiez continutul sirului auxiliar in linie
		strcpy((*line)[i], str);
		//Conditie pentru a sterge ultimul element al liniei(enter)
		//Daca linia nu e ultima atunci sterg enterul
		if(i != (*m) - 1)strdel((*line)[i] + strlen((*line)[i]) - 1, 1);
		//Daca linia e ultima si are ultimul element enter, atunci il sterg
		else if((*line)[i][strlen((*line)[i]) - 1] == '\n')strdel((*line)[i] + strlen((*line)[i]) - 1, 1);
	}
	//Eliberez memoria de pe heap a sirului auxiliar
	free(str);
}
//Functie care cauta campurile si le afiseaza conform cerintei
void afisare_camp(char*** line, char del[], int k, int v[], int m, char out_del[])
{
	int j, s, i, t;
	//Imi iau un sir auxiliar pentru sirul de separatori
	char *sep;
	//Ii aloc memorie si il copiez
	sep = (char*)malloc((strlen(del) + 1) * sizeof(char));
	strcpy(sep, del);
	//sparg in campuri cu strtok si structura repetitiva aferenta
	char* camp;
	for(i = 0; i < m; i++)
	{
		//Imi iau doua contoare(t imi verifica daca e primul camp gasit iar s imi da numarul campului in linie)
		s = 0;t = 0;
		camp = strtok((*line)[i], sep);
		while(camp != NULL)
		{
			s++;
			for(j = 0; j < k; j++)
				//Daca numarul campului coincide cu numarul din vectorul de campuri atunci se afiseaza
				if(v[j] == s)
				{
					//Daca e primul camp, atunci se afiseaza fara separator inainte 
					if(t == 0)printf("%s", camp);
					//Daca e alt camp atunci se afiseaza cu separator
					else printf("%s%s", out_del, camp);
					t++;
					//Daca s-a afisat ceva atunci se iese din for
					break;
				}
			camp=strtok(0, sep);
		}
		//Se trece la urmatoarea linie
		printf("\n");
	}	
	//Eliberare memorie din sir auxiliar
	free(sep);
}
//Transform sirul de campuri in vector de numere intregi si returnez dimeniunea lui
int vec_fields(char fields[], int v[])
{
	char *sep = ",";
	char* a;
	a = strtok(fields, sep);
	int i = 0;
	//Fiecare element din sirul de campuri este treansformat in intreg cu functia atoi
	while(a != NULL)
	{
		v[i] = atoi(a);
		i++;
		a = strtok(0, sep);
	}
	return i;
}
int main()
{
	//Declarare siruri si variabile
	char del[10];
	char** line;
	char fields[200];
	char out_del[10];
	int v[200];
	int n, m;
	//Citire a celor declarate
	citire(&line, del, &n, &m, fields, out_del);
	//dau lui k dimensiunea vectorului de capmuri
	int k=vec_fields(fields, v);
	//Apelul functiei de afisare a campurilor
	afisare_camp(&line, del, k, v, m, out_del);
	int i;
	//Eliberez memoria liniilor
	for(i = 0; i < m; i++)
	{
		free(line[i]);
	}
	free(line);
	return 0;
}
