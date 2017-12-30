#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

// Affiche un tableau1
void printtab(int tab[32]){
	int i=0;
	while (i<32){
		printf("%d",tab[i]);
		i++;
	}
	printf("\n");
}
/////////////////////////////////////////////////////////////////////////////////////

// Convertion decimale to binaire et modifie directement l'instruction écrite en binaire
void binaire(int a,int instrubin[32], int k){
	int i=0;
	int t[5]={0};
	while (a>=0 && i<5){
		t[i]=a%2;
		a=a/2;
		i++;
	}
	int j,l=0;
	for(j=(i-1);j>=0;j--) {
		instrubin[j+k]=t[l];
		l++;
	}
}
///////////////////////////////////////////////////////////////////////

// Code en binaire le codeop
int codeop(char code[], int instrubin[32]){
	char tab[32][4]={"OR","XOR","AND","ADD","SUB","MUL","DIV","SHR",
			  "LDB","LDH","LDW","STB","STH","STW",
			  "","","","","","",
			  "JMP","JZS","JZC","JCS","JCC","JNS","JNC","",
			  "IN","OUT","RND","HLT"};
	int i=0,j=0, indice;
	while (i<32) {
		int a=strcmp(code, tab[i]);
		if (a==0) {
			binaire(i,instrubin,0);
			j++;
			indice=i;
		}
		i++;
	}
	if (j==0) printf("Ce n'est pas un codeop\n" ); //break
	return indice;

}
////////////////////////////////////////////////////////////////////////////////////////////

// Code les lignes d'instructions en hexadecimal
void deuxiemelecture(char* argv,int instrubin[32]){
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
		int code;
		code=codeop(a, instrubin);
		printtab(instrubin);
		i=j+1;
		printf("%c :\n",ligne[i] );

		compteur++;
	}
	fclose(f);
}
///////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[]){
	if(argc==1) printf("Il manque le fichier source\n");
	char tabetiq[100][50]={""}; // tableau d'étiquettes 
	int numetiq[100]={0}; // tableau des numéros des lignes des étiquettes
	int instrubin[32]={0};
	char instruhexa[11]={""};
	premierelecture(argv[1], tabetiq, numetiq);
	deuxiemelecture(argv[1], instrubin);
	return 0;
}