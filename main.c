#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <string.h>
 
#include "util.h"
#include "estruturas.h"
#include "dbase.h"

void tela (int *x, int *y, int *yBar, char dir[], char inst[], Arquivo *arquivo) {
 	int total,i;
 	Dados *dados;
 	total=i=0;
	gotoxy(*x, *y);
 	printf("                                                     ");
 	gotoxy(*x, *y);
 	printf(".");
 	gotoxy(*x, *yBar);
 	printf("                                                     ");
 	
 	*yBar = *y+2;
 	gotoxy(1, *yBar);
 	textcolor(0);
 	textbackground(8);
 	if (arquivo == NULL)
 		printf("%s\t||<%s>||\t||Rec: none", inst, dir);
	else {
		dados = arquivo->Campos->Pdados;
		while (dados != NULL && dados != arquivo->Campos->Patual) {
			if (!dados->setDelet) {
				i++;
				total++;
			}
			dados = dados->Prox;
		}
		if (dados != NULL) {
			while (dados != NULL) {
				if (!dados->setDelet)
					total++;
				dados = dados->Prox;
			}
			printf("%s\t||<%s>||%s\t||Rec: %d/%d", inst, dir, arquivo->NomeDBF, i+1, total);
		}
		else
			printf("%s\t||<%s>||%s\t||Rec: EOF/%d", inst, dir, arquivo->NomeDBF, total);
 	}
	textcolor(15);
 	textbackground(0);
 	printf("\n\t\t\tEnter dBASE command");
}

void executar () {
	Unidade *unidade;
	Arquivo *arquivo;
	int key, x, y, yBar;
	char setDel, *instrucao;
	setDel = 1;
	key = -1; x=y=yBar=1;
	unidade = NULL;
	criaUnidade(&unidade, "D:");
	criaUnidade(&unidade, "C:");
	instrucao = (char*)malloc(50);
	arquivo = NULL;
	
	do {
		tela(&x, &y, &yBar,unidade->Und,"Command Line",arquivo);
		x++; gotoxy(x, y); x--;
		gets(instrucao);
		getInstrucao(instrucao, &key);
		y++;
		
		switch (key) {
			case 1:
				setDefault(&unidade, instrucao);
				arquivo = NULL;
				break;
				
			case 2:
				create(unidade, getNome(instrucao, "CREATE"));
				break;
				
			case 3:
				dir(unidade, &y, &yBar);
				break;
				
			case 4:
				gotoxy(x, yBar+1);
				break;
			
			case 5:
				use(unidade, &arquivo, getNome(instrucao, "USE"));
				y+=1;
				break;
				
			case 6:
				listStructure(unidade, arquivo, &y);
				break;
			
			case 7:
				append(arquivo, &y);
				break;
			
			case 8:
				list(arquivo, &y, &yBar);
				break;
			
			case 9:
				y=1;
				clear();
				break;
				
			case 10:
				locate(arquivo, getField(instrucao, "LOCATE"), instrucao);
				y+=1;
				break;
				
			case 11:
				go_to(arquivo, getPos(instrucao, "GOTO"));
				break;
			
			case 12:
				display(arquivo, &y, &yBar);
				break;
			
			case 13:
				edit(arquivo, &y);
				break;
				
			case 14:
				delete_reg(arquivo, &y);
				break;
				
			case 15:
				recall(arquivo, instrucao, setDel, &y);
				break;
				
			case 16:
				setDeleted(&setDel, instrucao);
				break;
			
			case 17:
				pack(arquivo);
				break;
			
			case 18:
				zap(arquivo);
				break;
		}
	} while (key != 4 && strcmp(instrucao, "QUIT") != 0);
}

int main() {
	executar();
	return 0;
}
