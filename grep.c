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
//Functie care insereaza la adresa data un sir de caractere
void strins(char *d, char *s)
{
	char aux[200];
	strcpy(aux, d);
	strcpy(d, s);
	strcat(d, aux);
}
//Functie care citeste sirul de colorat si numarul de linii ale textului
void citire_sir_nr(char s1[],int* b)
{
	//Aici citesc sirul de colorat
	fgets(s1, 30, stdin);
	//Ii sterg caracterul enter
	strdel(s1 + strlen(s1) - 1, 1);
	//citesc numarul de linii
	scanf("%d", b);
	//dau un getchar ca sa scap de enterul de dupa numar
	getchar();
}
//Functie de citire a textului
void citire_text(char*** line, int b)
{
	int i;
	//Aici aloc dinamic numarul de linii ale textului intr-o matrice de pointeri
	*line = (char**)malloc((b) * sizeof(char*));
	//Declar un sir auxiliar
	char* str;
	//Aloc dinamic sirul auxiliar
	str=(char *)malloc(200 * sizeof(char));
	//Fac un for pentru citirea fiecarei linii
	for(i = 0; i < b; i++)
	{
		//Citesc linia in sirul auxiliar
		fgets(str, 200, stdin);
		//Aloc dinamic linia cu size-ul necesar pe care il stiu din str
		(*line)[i] = (char*)malloc((strlen(str) + 1 ) * sizeof(char));
		//Copiez ce am in str in linie
		strcpy((*line)[i], str);
	}
	//Eliberez memoria retinuta in sirul auxiliar
	free(str);
}
//Functie de determinare a numarului de aparitii a sirului de colorat intr-o linie
int nr_aparitii(char* line, char s1[])
{
	//x este variabila care contorizeaza nr de aparitii
	int x = 0;
	//p este un pointer la adresa primului element al primei aparitii a sirului de colorat in linie
	char* p = strstr((line), s1);
	//Eu numar aparitiile si deci introduc aceste lucruri intr-o structura repetitiva while
	while(p != NULL)
	{
		//maresc x
		x++;
		//Dau pointerului valoarea urmatoarei aparitii a sirului in linie
		p = strstr(p + strlen(s1), s1);
	}
	//Returnez numarul de aparitii
	return x;
}
//Functie de realocare a memoriei pe care o ocupa o linie, marind acesta memorie cu nr de aparitii ori nr de caractere speciale
void realocare(char*** line,int b,char s1[])
{
	int i;
	//Fac totul pentru fiecare linie intr-un for
	for(i = 0; i < b; i++)
		{
		//Aici fac realocarea pt linia i, apeland si functia anterioara ca sa obtin nr de aparitii al sirului
		(*line)[i] = (char*)realloc((*line)[i], ((strlen((*line)[i]) + 10 * nr_aparitii(((*line)[i]), s1)) + 1) * sizeof(char));
		}
}
//Functia in care modific textul
void modificare(char*** line, int b, char s1[])
{
	//p este un pointer catre adresa primului element al primei aparitii a sirului de gasit in linie
	char* p;
	int i;
	//structura repetitiva pt fiecare linie
	for(i = 0; i < b; i++)
	{
		//Pointerul p ia o valoare de inceput la fiecare linie
		p = strstr((*line)[i], s1);
		//structura repetitiva pt a colora toate aparitiile de pe o linie
		while(p != NULL)
			{
				//Inserare a secventei de inceput (prefixului) pt schimbul culorii
				strins(p, "\e[0;31m");
				//Inserare a secventei de final (sufixului) pt schimbul culorii
				strins(strlen(s1) + 7 + p, "\e[m");
				//Se da o noua valoare pentru p, cea a urmatoarei aparitii a sirului in linie
				p = strstr(p + strlen(s1) + 10, s1);
			}
	}
}
//Functie pentru afisarea textului
void afisare(char*** line, int b, char s1[])
{
	int i;
	//Fiecare linie cu aparitii se afiseaza in for
	for(i = 0; i < b; i++)
	{
		//Conditie pt a afisa doar liniile ce au cuvinte de colorat
		if(strstr((*line)[i], s1) != NULL)
		//Afisare a liniei respective
		printf("%s", (*line)[i]);
	}
}
//Functie de eliberare a memoriei ocupate de text
void eliberare_memorie(char** line, int b)
{
	int i;
	//Prima oara se elibereaza memoria fiecarei linii in for
	for(i = 0; i < b; i++)
	{
		//Eliberare a memoriei liniei
		free((void*)line[i]);
	}
	//Se elibereaza si numarul de linii
	free(line);
}
int main()
{
	//Declaratie a sirului de colorat
	char s1[30];
	//Declaratie a numarului de linii
	int b;
	//Declaratie a textului(dublu pointer)
	char** line;
	//Apelul primei functii de citire
	citire_sir_nr(s1, &b);
	//Apelul celei de-a doua functii de citire
	citire_text(&line, b);
	//Apelul functiei de realocare. Prima oara realoc, apoi modific
	realocare(&line, b, s1);
	//Apelul functiei de modificare
	modificare(&line, b, s1);
	//Apelul functiei de afisare
	afisare(&line, b, s1);
	//Eliberarea memoriei la final
	eliberare_memorie(line, b);
	return 0;
}