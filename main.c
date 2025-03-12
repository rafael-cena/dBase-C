#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>

#include "tad.h"
#include "strdin.h"

void defaultInst (StrDin **str) {
	reinicia(&*str);
	
	insere(&*str, 'C'); insere(&*str, 'o'); insere(&*str, 'm'); insere(&*str, 'm'); insere(&*str, 'a'); insere(&*str, 'n'); insere(&*str, 'd'); insere(&*str, ' '); insere(&*str, 'L'); insere(&*str, 'i'); insere(&*str, 'n'); insere(&*str, 'e'); 
}

void tela (int *x, int *y, int *yBar, char dir[], StrDin *inst) {
	gotoxy(*x, *y);
	printf(".");
	gotoxy(*x, *yBar);
	printf("                                                     ");
	
	*yBar = *y+2;
	gotoxy(1, *yBar);
	textcolor(0);
	textbackground(8);
	exibe(inst);
	printf("\t||<%s>||\t||Rec: none", dir);
	
	textcolor(15);
	textbackground(0);
	printf("\n\t\t\tEnter dBASE command");
}

void telaCampos (int *x, int *y, int *yBar, char dir[], StrDin *inst, StrDin *nome) {
	gotoxy(*x, *y);
	printf("\tNome Campo \tTipo \t\t Tamanho \t Dec"); *y++;
	gotoxy(*x, *y);
	printf("==================================================="); *y++;
	
	*yBar = *y+4;
	gotoxy(*x, *yBar);
	textcolor(0);
	textbackground(8);
	exibe(inst);
	printf("\t||<%s>||", dir);
	exibe(nome);
	
	textcolor(15);
	textbackground(0);
	printf("\n\t\t\tInsira o campo");
}

void instruction (StrDin **str, int *key, TpUnd **unidade, StrDin **nome) {
	StrDin *aux, *set_default_to_c, *set_default_to_d, *create, *dir, *quit, *use, *list_structure, *append, *list, *clear, *go_to, *display, *edit, *delete_reg, *recall, *set_deleted, *pack, *zap;
	int i=0;
	
	init(&set_default_to_c);
	insere(&set_default_to_c, 'S'); insere(&set_default_to_c, 'E'); insere(&set_default_to_c, 'T'); insere(&set_default_to_c, ' '); insere(&set_default_to_c, 'D'); insere(&set_default_to_c, 'E'); insere(&set_default_to_c, 'F'); insere(&set_default_to_c, 'A'); insere(&set_default_to_c, 'U'); insere(&set_default_to_c, 'L'); insere(&set_default_to_c, 'T'); insere(&set_default_to_c, ' '); insere(&set_default_to_c, 'T'); insere(&set_default_to_c, 'O'); insere(&set_default_to_c, ' '); insere(&set_default_to_c, 'C'); insere(&set_default_to_c, ':'); 
	
	init(&set_default_to_d);
	insere(&set_default_to_d, 'S'); insere(&set_default_to_d, 'E'); insere(&set_default_to_d, 'T'); insere(&set_default_to_d, ' '); insere(&set_default_to_d, 'D'); insere(&set_default_to_d, 'E'); insere(&set_default_to_d, 'F'); insere(&set_default_to_d, 'A'); insere(&set_default_to_d, 'U'); insere(&set_default_to_d, 'L'); insere(&set_default_to_d, 'T'); insere(&set_default_to_d, ' '); insere(&set_default_to_d, 'T'); insere(&set_default_to_d, 'O'); insere(&set_default_to_d, ' '); insere(&set_default_to_d, 'D'); insere(&set_default_to_d, ':'); 
		
	init(&create);
	insere(&create, 'C'); insere(&create, 'R'); insere(&create, 'E'); insere(&create, 'A'); insere(&create, 'T'); insere(&create, 'E');
	
	init(&dir);
	insere(&dir, 'D'); insere(&dir, 'I'); insere(&dir, 'R');
	
	init(&quit);
	insere(&quit, 'Q'); insere(&quit, 'U'); insere(&quit, 'I'); insere(&quit, 'T');
	
	init(&use);
	insere(&use, 'U'); insere(&use, 'S'); insere(&use, 'E');
	
	init(&list_structure);
	insere(&list_structure, 'L'); insere(&list_structure, 'I'); insere(&list_structure, 'S'); insere(&list_structure, 'T'); insere(&list_structure, ' '); insere(&list_structure, 'S'); insere(&list_structure, 'T'); insere(&list_structure, 'R'); insere(&list_structure, 'U'); insere(&list_structure, 'C'); insere(&list_structure, 'T'); insere(&list_structure, 'U'); insere(&list_structure, 'R'); insere(&list_structure, 'E');
	
	init(&append);
	insere(&append, 'A'); insere(&append, 'P'); insere(&append, 'P'); insere(&append, 'E'); insere(&append, 'N'); insere(&append, 'D');
	
	init(&list);
	insere(&list, 'L'); insere(&list, 'I'); insere(&list, 'S'); insere(&list, 'T');
	
	init(&clear);
	insere(&clear, 'C'); insere(&clear, 'L'); insere(&clear, 'E'); insere(&clear, 'A'); insere(&clear, 'R');
	
	init(&go_to);
	insere(&go_to, 'G'); insere(&go_to, 'O'); insere(&go_to, 'T'); insere(&go_to, 'O');
	
	init(&display);
	insere(&display, 'D'); insere(&display, 'I'); insere(&display, 'S'); insere(&display, 'P'); insere(&display, 'L'); insere(&display, 'A'); insere(&display, 'Y');
	
	init(&edit);
	insere(&edit, 'E'); insere(&edit, 'D'); insere(&edit, 'I'); insere(&edit, 'T');
	
	init(&delete_reg);
	insere(&delete_reg, 'D'); insere(&delete_reg, 'E'); insere(&delete_reg, 'L'); insere(&delete_reg, 'E'); insere(&delete_reg, 'T'); insere(&delete_reg, 'E'); 
	
	init(&recall);
	insere(&recall, 'R'); insere(&recall, 'E'); insere(&recall, 'C'); insere(&recall, 'A'); insere(&recall, 'L'); insere(&recall, 'L');
	
	init(&set_deleted);
	insere(&set_deleted, 'S'); insere(&set_deleted, 'E'); insere(&set_deleted, 'T'); insere(&set_deleted, ' '); insere(&set_deleted, 'D'); insere(&set_deleted, 'E'); insere(&set_deleted, 'L'); insere(&set_deleted, 'E'); insere(&set_deleted, 'T'); insere(&set_deleted, 'E'); insere(&set_deleted, 'D');
	
	init(&pack);
	insere(&pack, 'P'); insere(&pack, 'A'); insere(&pack, 'C'); insere(&pack, 'K');
	
	init(&zap);
	insere(&zap, 'Z'); insere(&zap, 'A'); insere(&zap, 'P');
	
	if (iguais(str, set_default_to_c)) {
		*key = 0;
		if (strcmp((*unidade)->und, "D:") == 0)
			*unidade = (*unidade)->ant;
	}
	else if (iguais(str, set_default_to_d)) {
		*key = 0;
		if (strcmp((*unidade)->und, "C:") == 0)
			*unidade = (*unidade)->prox;
	}
	else if (buscaSubs(str, create, &i)) {
		if (i == 0) {
			aux = *str;
			printf("\n");
			exibe(aux);
			getch();
			for (i=0; i<7; i++) {
				printf("\n%c -> ", aux->letra);
				aux=aux->prox;
			}
			copia(aux, &*nome);
			exibe(*nome);
			getch();
			reinicia(&*str);
			copia(create, &*str);
			*key = 1;
		}
		else *key = -1;
	}
	else if (iguais(str, dir)) *key = 2;
	else if (iguais(str, quit)) *key = 3;
	else if (iguais(str, use)) *key = 4;
	else if (iguais(str, list_structure)) *key = 5;
	else if (iguais(str, append)) *key = 6;
	else if (iguais(str, list)) *key = 7;
	else if (iguais(str, clear)) *key = 8;
	else if (iguais(str, go_to)) *key = 9;
	else if (iguais(str, display)) *key = 10;
	else if (iguais(str, edit)) *key = 11;
	else if (iguais(str, delete_reg)) *key = 12;
	else if (iguais(str, recall)) *key = 13;
	else if (iguais(str, set_deleted)) *key = 14;
	else if (iguais(str, pack)) *key = 15;
	else if (iguais(str, zap)) *key = 16;
	else *key = -1;

}

void inserirCampos (TpCampos **campos, TpUnd *unidade, StrDin *str, StrDin *nome) {
	int x, y, yBar;
	
	x=50; y=1; yBar=y+4;
	telaCampos(&x, &y, &yBar, unidade->und, str, nome);
}

void novoArq (TpUnd **unidade, StrDin *str, StrDin *nome) {
	TpArq *arq;
	TpStatus *status;
	TpCampos *campos;
	struct tm *data_hora_atual;
	time_t segundos;
	
	time(&segundos);
	data_hora_atual = localtime(&segundos);
	
	initArq(&arq);
	initSt(&status);
	
	
	strcpy(arq->data, ("%d/%d/%d", data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900));
	strcpy(arq->hora, ("%d:%d", data_hora_atual->tm_hour, data_hora_atual->tm_min));
	arq->status = status;
	inserirCampos(&campos, *unidade, str, nome);
	arq->campos = campos;
	
	inserirArq(&*unidade, &arq);
}

void execute () {
	int key, x, y, yBar;
	char c;
	StrDin *inst, *nome;
	TpUnd *unidade;
	
	initUnd(&unidade);
	init(&inst); init(&nome);
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
		c = toupper(getche());
		while (c != '\r') {
			insere(&inst, c);
			c = toupper(getche());
		}
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
				reinicia(&inst);
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
