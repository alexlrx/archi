#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void codeop(char code[]){
	char tab[32][4]={"OR","XOR","AND","ADD","SUB","MUL","DIV","SHR",
			  "LDB","LDH","LDW","STB","STH","STW",
			  "","","","","","",
			  "JMP","JZS","JZC","JCS","JCC","JNS","JNC","",
			  "IN","OUT","RND","HLT"};
	int i=0;
	while (i<32) {
		int a=strcmp(code, tab[i]);
		if (a==0) printf("%d\n", 1);   // Binaire(tab[i]);
		// printf("Ce n'est pas un code op\n", );
		i++;

	}
}
////////////////////////////////////////////////////////////////////////////////////////////

// Met l'étiquette dans le tableau et son numéro de ligne dans l'autre tableau
void etiquette( char etiquette[], int i, char tabetiq[100][50], int numetiq[100]){
	int k=0;
	numetiq[i]=i;
	while(etiquette[k]!='\0'){
		tabetiq[i][k] = etiquette[k];
		k++;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui récupère la sous chaine de i à j d'une chaîne passée en paramètre 
void deiaj ( char c[], char a[],int i, int j){
	int b=0;
	while (b<=j){
		a[b]=c[i];
		b++;
		i++;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////

// Met les étiquettes dans un tableau et le numéro de la ligne de l'étiquette dans un autre 
void premierelecture(char* argv, char tabetiq[100][50],int numetiq[100]){ 
	FILE * f=fopen(argv, "r");
	char ligne[50]={""};
	int compteur=0;
	while (fgets(ligne, 50, f) != NULL) {
		int i=0;
		while(ligne[i] == ' ') i++;// on avance au premier caractère de la ligne
		int j=i;
		while(ligne[j] != ' ') j++; // on récupère l'indice de la fin du mot 
		j--;
		if ( ligne[j]==':') { // si c'est une étiquette
			char a[50]={""};
			deiaj(ligne, a,i, j-i-1); // on récupère l'etiquette dans une chaine
			etiquette( a, compteur,tabetiq, numetiq); // on enregistre l'étiquette dans un tableau et on index la ligne 
		}
		compteur++;
	}
	fclose(f);
}
///////////////////////////////////////////////////////////////////////////////////////

void deuxiemelecture(char* argv){
	FILE * f=fopen(argv, "r");
	char ligne[50]={""};
	int compteur=0;
	while (fgets(ligne, 50, f) != NULL) {
		int i=0;
		while(ligne[i] == ' ') i++;// on avance au premier caractère de la ligne
		int j=i;
		while(ligne[j] != ' ' && ligne[j]!="") j++;  // on récupère l'indice de la fin du mot 
		j--;
		if ( ligne[j]==':') { // si c'est une étiquette on récupère l'opcode qui suit 
			j++;
			i=j;
			while(ligne[i] == ' ') i++;
			j=i;
			while(ligne[j] != ' ') j++;
			j--;
		}
		char a[50]={""};
		deiaj(ligne, a, i, j-i); // on récupère le code op dans une chaine
		printf("%s\n",a ); 
		codeop(a);
		compteur++;
	}
	fclose(f);
}

int main (int argc, char* argv[]){
	char tabetiq[100][50]={""}; // tableau d'étiquettes 
	int numetiq[100]={0}; // tableau des numéros des lignes des étiquettes
	int instrubin[32]={0};
	char instruhexa[11]={""};
	premierelecture(argv[1], tabetiq, numetiq);
	deuxiemelecture(argv[1]);
	int tab[32];
	return 0;
}