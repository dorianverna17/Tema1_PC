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
//Functie de citire a textului
void citire(char*** line, int* n)
{
	//Se citesc numarul de linii
	scanf("%d", n);
	getchar();
	int i;
	char* str;
	//Se ia un sir auxiliar
	str = (char*)malloc(200 * sizeof(char));
	//Se aloca dinamic nr de linii ale textului
	(*line) = (char**)malloc((*n) * sizeof(char*));
	for(i = 0; i < (*n); i++)
	{
		//Se citeste fiecare linie in auxiliar, se aloca fiecare linie cu necesarul
		fgets(str, 200, stdin);
		(*line)[i] = (char*)malloc((strlen(str) + 1) * sizeof(char));
		//Se copiaza din auxiliar in linie
		strcpy((*line)[i], str);
	}
	//Eliberare memorie auxiliar
	free(str);
}
//Functie care returneaza 1 daca un sir este numar si 0 daca nu este
int numar(char* str)
{
	int i;
	//Se verifica daca primul element este intre 1 si 9
	if(str[0] >= '1' && str[0] <= '9')
	{
	for(i = 1; i < strlen(str); i++)
	{
			//Se verifica daca urmatoarele elemente sunt intre 0 si 9
			if(!(str[i] >= '0' && str[i] <= '9'))
			{
				return 0;
			}
	}
	return 1;
	}
	return 0;
}
//Functie care cripteaza un sir
void criptare(char* str)
{
	int i;
	for(i = 1; i < strlen(str); i++)
	{
		str[i] = (str[i] + str[0]) % 256;
	}
}
//Functie care ia fiecare cuvant si il cripteaza cu ajutorul functiei precedente, apoi afiseaza textul
void modificare(char*** line, int n)
{
	char* sep = " \n";	
	char* cuv;
	//Declarare vector de siruri auxiliar care se aloca dinamic
	char** line2 = (char**)malloc(n * sizeof(char*));
	int i;
	char* str = (char*)malloc(1 * sizeof(char));
	//Un for in care se ia fiecare linie si se sparge in cuvinte
	for(i = 0; i < n; i++)
	{
		//Se realoca exact atata memorie cat trebuie
		str = (char*)realloc(str, (strlen((*line)[i]) + 1) * sizeof(char));
		strcpy(str, (*line)[i]);
		cuv = strtok(str, sep);
		line2[i] = (char*)malloc((strlen((*line)[i]) + 1) * sizeof(char));
		strcpy(line2[i], "");
		//In while se verifica daca ccuvintele din text sunt numere sau nu
		while(cuv != NULL)
		{
			//Daca sunt numere atunci se cripteaza
			if(!numar(cuv))
				criptare(cuv);
			strcat(line2[i], cuv);
			strcat(line2[i], " ");
			cuv = strtok(0, sep);
		}
		strdel((line2)[i] + strlen((line2)[i]) - 1, 1);
		printf("%s\n", line2[i]);
	}
	//Eliberare memorie sir auxiliar
	free(str);
	//Eliberare memorie sir de vectori auxiliar
	for(i = 0; i < n; i++)
	{
		free(line2[i]);
	}
	free(line2);
}
int main()
{
	//Declarare si apel functie citire si modificare
	char** line;
	int n;
	citire(&line, &n);
	modificare(&line, n);
	//Eliberare memorie text
	int i;
	for(i=0; i<n; i++)
	{
		free(line[i]);
	}
	free(line);
	return 0;
}