#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <string.h>

#include "tad.h"

void defaultInst (char **str) {
	strcpy(*str, "Command Line");
}

void reinicia (char **str) {
	strcpy(*str, " ");
}

void tela (int *x, int *y, int *yBar, char dir[], char inst[]) {
	gotoxy(*x, *y);
	printf(".");
	gotoxy(*x, *yBar);
	printf("                                                     ");
	
	*yBar = *y+2;
	gotoxy(1, *yBar);
	textcolor(0);
	textbackground(8);
	printf("%s\t||<%s>||\t||Rec: none", inst, dir);
	
	textcolor(15);
	textbackground(0);
	printf("\n\t\t\tEnter dBASE command");
}

void telaCampos (int *x, int *y, char dir[], char inst[], char *nome) {
	*x+=4;
	gotoxy(*x, *y); printf("Field Name"); *x=72;
	gotoxy(*x, *y); printf("Type"); *x=80;
	gotoxy(*x, *y); printf("Width"); *x=88;
	gotoxy(*x, *y); printf("Dec"); *y+=1;
	*x=54;
	while (*x < 90) {
		gotoxy(*x, *y); printf("%c", 205); *x+=1;
	}
	*y+=1;
	*x=50;
	
	gotoxy(*x, 14);
	textcolor(0);
	textbackground(8);
	while (*x < 86) {
		gotoxy(*x, 14); printf(" "); *x+=1;
	}
	*x=50;
	gotoxy(*x, 14); *x+=14;
	printf("%s\t\t||<%s>||%s", inst, dir, nome);
	*x+=strlen(nome);
	printf("      ");
	
	textcolor(15);
	textbackground(0);
	gotoxy(*x, 15); printf("Enter the field");
}

void clearCampos (int x, int y, int xMax, int yMax) {
	int i = y;
	while (x < xMax) {
		while (y < yMax) {
			gotoxy(x, y);
			printf(" ");
			y++;
		}
		x++;
		y = i;
	}
}

int buscaSubs(char str[], char inst[]) {
	int i;
	for (i=0; str[i] != '\0' && inst[i] != '\0' && i < strlen(inst); i++)
		if (str[i] != inst[i])
			return -1;
	
	if (inst[i] == '\0' && str[i] == ' ' && i == strlen(inst))
		return 0;
}

void instruction (char *str, int *key, TpUnd **unidade, char **nome) {
	char *aux;
	int i=0;
	
	if (stricmp(str, "SET DEFAULT TO C:") == 0) {
		*key = 0;
		if (stricmp((*unidade)->und, "D:") == 0)
			*unidade = (*unidade)->ant;
	}
	else if (stricmp(str, "SET DEFAULT TO D:") == 0) {
		*key = 0;
		if (stricmp((*unidade)->und, "C:") == 0)
			*unidade = (*unidade)->prox;
	}
	else if (buscaSubs(str, "CREATE") == 0) {
		*key = 1;
		// *nome = str[8-...]														Pegar o nome
		// remover(&*str, 50, 7);													Remover o nome da instrucao, deixar 'CREATE' apenas
	}
	else if (stricmp(str, "DIR") == 0) *key = 2;
	else if (stricmp(str, "QUIT") == 0) *key = 3;
	else if (stricmp(str, "USE") == 0) *key = 4;
	else if (stricmp(str, "LIST STRUCTURE") == 0) *key = 5;
	else if (stricmp(str, "APPEND") == 0) *key = 6;
	else if (stricmp(str, "LIST") == 0) *key = 7;
	else if (stricmp(str, "CLEAR") == 0) *key = 8;
	else if (stricmp(str, "GOTO") == 0) *key = 9;
	else if (stricmp(str, "DISPLAY") == 0) *key = 10;
	else if (stricmp(str, "EDIT") == 0) *key = 11;
	else if (stricmp(str, "DELETE") == 0) *key = 12;
	else if (stricmp(str, "RECALL") == 0) *key = 13;
	else if (stricmp(str, "SET DELETED") == 0) *key = 14;
	else if (stricmp(str, "PACK") == 0) *key = 15;
	else if (stricmp(str, "ZAP") == 0) *key = 16;
	else *key = -1;

}

void inserirCampos (TpCampos **campos, TpUnd *unidade, char *str, char *nome) {
	int x, y;
	char *aux;
	
	x=50; y=1;
	telaCampos(&x, &y, unidade->und, str, nome);
	x=50;
	
	gotoxy(x, y); printf("%d", y-2); x+=4;
	gotoxy(x, y);
	gets(aux);
	while (aux != NULL && strcmp(aux, "") != 0) {
		x=72;
		strcpy((*campos)->nomeCampo, aux);
		gotoxy(x, y);
		fflush(stdin);
		gets(aux);
		(*campos)->tipo = getTipo(aux);
		x=82;
		gotoxy(x,y); scanf("%d", &(*campos)->tamanho); x=90;
		gotoxy(x,y); 
		if ((*campos)->tipo == 'N') {
			scanf("%d", &(*campos)->dec);
		}
		else {
			printf("0"); (*campos)->dec = 0;
		}
		x=50; y++;
		gotoxy(x, y); printf("%d", y-2); x+=4;
		gotoxy(x, y);
		fflush(stdin);
		gets(aux); 
	}
	clearCampos(50, 1, 100, 17);
}

void novoArq (TpUnd **unidade, char *str, char *nome) {
	TpArq *arq;
	TpStatus *status;
	TpCampos *campos;
	
	initArq(&arq);
	initSt(&status);
	
	strcpy(arq->nome, nome);
	strcpy(arq->data, getData());
	strcpy(arq->hora, getHora());
	arq->status = status;
	inserirCampos(&campos, *unidade, str, nome);
	arq->campos = campos;
	
	inserirArq(&*unidade, &arq);
}

void dir (TpUnd *und, int *y) {
	TpArq *arqs;
	arqs = und->arqs;
	
	printf("\nDatabase Files\t# Records\t Last Update\t Size");
	*y+=1;
	while (arqs != NULL) {
		gotoxy(1, *y); printf("                                            ");
		gotoxy(1, *y); printf("%s\t0\t%s\t100", arqs->nome, arqs->data);
		*y+=1;
		arqs = arqs->prox;
	}
	*y+=1;
}

void execute () {
	int key, x, y, yBar;
	char *inst, *nome;
	TpUnd *unidade;
	inst = (char*)malloc(sizeof(50));
	initUnd(&unidade);
	inserirUnd(&unidade, "D:");
	inserirUnd(&unidade, "C:");
	
	defaultInst(&inst);
	x = 1; y=1;	yBar = y+2;
	do {
		tela(&x, &y, &yBar, unidade->und, inst);
		x++;
		gotoxy(x, y);
		x--;
	
		reinicia(&inst);
		gets(inst);
		instruction(inst, &key, &unidade, &nome);
		y++;
		
		switch (key) {
			case -1:
				reinicia(&inst);
				defaultInst(&inst);
				break;
				
			case 0: // set default to
				reinicia(&inst);
				defaultInst(&inst);
				break;
			
			case 1: //create
				novoArq(&unidade, inst, nome);
				break;
				
			case 2: //dir
				dir(unidade, &y);
				break;
			
			case 3: //quit
				gotoxy(x, yBar+1);
				break;
				
			case 4: //use
			
				break;
				
			case 5: //list structure
			
				break;
				
			case 6: //append
			
				break;
				
			case 7: //list
			
				break;
				
			case 8: //clear
				y=1;
				clrscr();
				defaultInst(&inst);
				break;
				
			case 9: //goto
			
				break;
				
			case 10: //display
			
				break;
				
			case 11: //edit
			
				break;
				
			case 12: //delete
			
				break;
				
			case 13: //recall
			
				break;
				
			case 14: //set deleted
			
				break;
				
			case 15: //pack
			
				break;
				
			case 16: //zap
			
				break;
		}
	} while (key != 3);
}

int main () {
	execute();
	return 0;
}
