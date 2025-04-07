// SET DEFAULT 
void setDefault (Unidade **unidade, char *str) {
	if (stricmp(str, "SET DEFAULT TO C:") == 0) {
		if (stricmp((*unidade)->Und, "D:") == 0)
			*unidade = (*unidade)->Bottom;
	}
	else if (stricmp(str, "SET DEFAULT TO D:") == 0) {
		if (stricmp((*unidade)->Und, "C:") == 0)
			*unidade = (*unidade)->Top;
	}
}

// CREATE
void create (Unidade *unidade, char *nome) {
	Arquivo *arquivo, *aux;
	
	if (strlen(nome) > 4) {
		criaArquivo(&arquivo, nome);
		
		if (arquivo != NULL) {
			criarCampos(&arquivo, unidade->Und);
			insereStatus(&arquivo, criaStatus(1));
			
			if (unidade->Arqs == NULL)
				unidade->Arqs = arquivo;
			else {
				aux = unidade->Arqs;
				while (aux->Prox != NULL)
					aux = aux->Prox;
				aux->Prox = arquivo;
			}
		}
		else {
			printf("Erro ao criar o arquivo!");
		}
	}
	else {
		printf("O nome deve ser [NOME].DBF\n");
	}
}

// DIR
void dir (Unidade *unidade, int *y, int *yBar) {
	int i, size, count;
	Arquivo *arquivo;
	Campo *campo;
	Dados *dados;
	arquivo = unidade->Arqs;
	count =0;
	if (arquivo == NULL) {
		gotoxy(1, *y); printf("Nenhum arquivo encontrado!\n");
		*y+=1;
	}
	else {
		gotoxy(1, *y); printf("Database File\t # Records \t Last Update\t Size\n"); *y+=1;
		while (arquivo != NULL) {
			count++;
			i = 1; size = 0;
			campo = arquivo->Campos;
			dados = campo->Pdados;
			
			while (campo != NULL ) {
				size += campo->Width;
				campo = campo->Prox;
			}
			while (dados != NULL) {
				i++;
				dados=dados->Prox;
			}
			gotoxy(1, *y); printf("                                                 ");
			gotoxy(1, *y); printf("%s", arquivo->NomeDBF);
			gotoxy(26, *y); printf("%d", i-1);
			gotoxy(34, *y); printf("%s", arquivo->Data);
			gotoxy(51, *y); printf("%d", size*i); *y+=1;
			arquivo = arquivo->Prox;
		}
		*y+=2;
	}
	*yBar+=count;
}

// QUIT


// USE
void use (Unidade *unidade, Arquivo **arquivo, char *nome) {
	Arquivo *aux;
	aux = NULL;
	
	if (unidade != NULL && unidade->Arqs != NULL) {
		aux = unidade->Arqs;
		
		while (aux!=NULL && strcmp(aux->NomeDBF, nome) != 0)
			aux = aux->Prox;
	}
	
	if (aux != NULL && strcmp(aux->NomeDBF, nome) == 0) {
		*arquivo = aux;
		printf("%s selecionado\n", nome);
	}
	else {
		*arquivo = NULL;
		printf("%s nao encontrado!\n", nome);
	}
}

// LIST STRUCTURE
void listStructure (Unidade *unidade, Arquivo *arquivo, int *pos) {
	Campo *campo;
	Dados *dados;
	int y, i, size;
	y=1; i=size=0;
	
	if (arquivo != NULL) {
		campo = arquivo->Campos;
		if (campo != NULL) {
			dados = campo->Pdados;
			while (dados != NULL) {
				i++;
				dados = dados->Prox;
			}
			
			gotoxy(1, *pos); printf("                                                                          ");
			gotoxy(1, *pos); printf("Structure for database: %s%s\n", unidade->Und, arquivo->NomeDBF); *pos+=1;
			gotoxy(1, *pos); printf("                                                                          ");
			gotoxy(1, *pos); printf("Number of data records: %d\n", i); *pos+=1;
			gotoxy(1, *pos); printf("                                                                          ");
			gotoxy(1, *pos); printf("Date of last update   : %s\n", arquivo->Data); *pos+=1;
			gotoxy(1, *pos); printf("                                                                          ");
			gotoxy(1, *pos); printf("Field \tField Name \t\tType \t\tWidth  \tDec\n"); *pos+=1;
			while (campo != NULL) {
				gotoxy(1, *pos); printf("    %d", y);
				gotoxy(9, *pos); printf("%s", campo->FieldName);
				gotoxy(33, *pos); printf("%s", getType(campo->Type));
				gotoxy(49, *pos); printf("%d", campo->Width);
				gotoxy(57, *pos); printf("%d", campo->Dec);
				
				y++; *pos+=1;
				size+=campo->Width;
				campo = campo->Prox;
			}
			gotoxy(1, *pos); printf("** Total **"); 
			gotoxy(49, *pos); printf("%d", size);
			*pos+=1;
		}
	}
	else {
		gotoxy(1, *pos); printf("                                                                          ");
		gotoxy(1, *pos); printf("Selecione um arquivo [USE 'NOME.DBF']"); *pos+=1;
	}
}

// APPEND
void append (Arquivo *arquivo, int *pos) {
	Campo *campo;
	union tipo valor;
	Dados *dados;
	int y;
	y=1;
	
	if (arquivo != NULL) {
		campo = arquivo->Campos;
		
		while (campo != NULL) {
			dados = (Dados*)malloc(sizeof(Dados));
			dados->Prox = NULL;
			dados->setDelet = 0;
			gotoxy(60, y); 
			printf("%s\t", campo->FieldName);
			if (campo->Type == 'N')
				scanf("%f", &dados->Valor.valorN);
			else if (campo->Type == 'D')
				gets(dados->Valor.valorD);
			else if (campo->Type == 'L')
				scanf("%c", &dados->Valor.valorL);
			else if (campo->Type == 'C')
				gets(dados->Valor.valorC);
			else
				gets(dados->Valor.valorM);
			
			y++;
			insereDados(&campo, dados);
			campo = campo->Prox;
		}
	}
	else {
		gotoxy(1, *pos); printf("                                                                          ");
		gotoxy(1, *pos); printf("Selecione um arquivo [USE 'NOME.DBF']"); *pos+=1;
		*pos+=1;
	}
}

// LIST
void list (Arquivo *arquivo, int *pos, int *yBar) {
	Campo *campo, *auxC;
	int x, i=1;
	
	if (arquivo != NULL) {
		campo = arquivo->Campos;
		//	exibe cabecalho
		x=17;
		gotoxy(1, *pos); printf("Record#");
		while (campo != NULL) {
			gotoxy(x, *pos);
			printf("%s", campo->FieldName);
			x+=campo->Width;
			campo->Patual = campo->Pdados;
			campo = campo->Prox;
		}
		*yBar+=1;
		*pos+=1;
		//	exibe dados
		campo = arquivo->Campos;
		while (campo->Patual != NULL) {
			gotoxy(1, *pos);
			printf("      %d                                                                                ", i);
			x=17;
			while (campo != NULL) {
				gotoxy(x, *pos);
				if (campo->Type == 'N')
					printf("%f\t", campo->Patual->Valor.valorN);
				else if (campo->Type == 'D')
					printf("%s\t", campo->Patual->Valor.valorD);
				else if (campo->Type == 'L')
					if (campo->Patual->Valor.valorL) printf("TRUE\t");
					else printf("FALSE\t");
				else if (campo->Type == 'C')
					printf("%s\t", campo->Patual->Valor.valorC);
				else
					printf("%s\t", campo->Patual->Valor.valorM);
				
				x+=campo->Width;
				campo->Patual = campo->Patual->Prox;
				campo = campo->Prox;
			}
			*pos+=1;
			i++;
			campo = arquivo->Campos;
			*yBar+=1;
		}
	}
	else {
		gotoxy(1, *pos); printf("                                                                          ");
		gotoxy(1, *pos); printf("Selecione um arquivo [USE 'NOME.DBF']"); *pos+=1;
	}
	
	*pos+=1;
}

// CLEAR
void clear() {
	clrscr();
}

// LOCATE
void locate (Arquivo *arquivo, char *Field, char instrucao[]) {
	Campo *campo;
	Dados *dados;
	union tipo Content;
	int pos;
	
	campo = arquivo->Campos;
	pos = -1;
	while (campo != NULL && strcmp(campo->FieldName, Field) != 0)
		campo = campo->Prox;
	
	if (campo != NULL && strcmp(campo->FieldName, Field) == 0) {
		dados = campo->Pdados;
		
		if (campo->Type == 'N') {
			getContent(instrucao, &Content, 'N');
			while (dados != NULL && dados->Valor.valorN != Content.valorN) {
				pos++;
				dados = dados->Prox;
			}
			if (dados != NULL)
				pos++;
			else 
				pos = -1;
		}
		else if (campo->Type == 'D') {
			getContent(instrucao, &Content, 'D');
			while (dados != NULL && strcmp(dados->Valor.valorD, Content.valorD) != 0) {
				pos++;
				dados = dados->Prox;
			}
			if (dados != NULL)
				pos++;
			else 
				pos = -1;
		}
		else if (campo->Type == 'L') {
			getContent(instrucao, &Content, 'L');
			while (dados != NULL && dados->Valor.valorL != Content.valorL) {
				pos++;
				dados = dados->Prox;
			}
			if (dados != NULL)
				pos++;
			else 
				pos = -1;
		}
		else if (campo->Type == 'C') {
			getContent(instrucao, &Content, 'C');
			while (dados != NULL && strcmp(dados->Valor.valorC, Content.valorC) != 0) {
				pos++;
				dados = dados->Prox;
			}
			if (dados != NULL)
				pos++;
			else 
				pos = -1;
		}
		else {
			getContent(instrucao, &Content, 'M');
			while (dados != NULL && strcmp(dados->Valor.valorM, Content.valorM) != 0) {
				pos++;
				dados = dados->Prox;
			}
			if (dados != NULL)
				pos++;
			else 
				pos = -1;
		}
	}
	else
		pos = -1;
		
	if (pos == -1)
		printf("Nenhum registro encontrado!");
	else 
		printf("Record = \t %d", pos+1);
}

// GOTO
void go_to (Arquivo *arquivo, int go) {
	Campo *campo;
	int i;
	
	campo = arquivo->Campos;
	
	while (campo != NULL) {
		campo->Patual = campo->Pdados;
		
		for (i=1;i<go;i++)
			campo->Patual = campo->Patual->Prox;
		
		campo=campo->Prox;
	}
}

// DISPLAY
void display (Arquivo *arquivo, int *pos, int *yBar) {
	Campo *campo;
	Dados *dados;
	int x, i=1;
	
	if (arquivo != NULL && arquivo->Campos->Patual != NULL) {
		campo = arquivo->Campos;
		//	exibe cabecalho
		x=17;
		gotoxy(1, *pos); printf("Record#");
		while (campo != NULL) {
			gotoxy(x, *pos);
			printf("%s", campo->FieldName);
			x+=campo->Width;
			campo = campo->Prox;
		}
		*yBar+=1;
		*pos+=1;
		
		campo = arquivo->Campos;
		dados = campo->Pdados;
		while (dados != NULL && dados != campo->Patual) {
			i++;
			dados = dados->Prox;
		}
		
		//	exibe dados
		campo = arquivo->Campos;
		gotoxy(1, *pos);
		printf("      %d                                                                                ", i);
		x=17;
		while (campo != NULL) {
			gotoxy(x, *pos);
			if (campo->Type == 'N')
				printf("%f\t", campo->Patual->Valor.valorN);
			else if (campo->Type == 'D')
				printf("%s\t", campo->Patual->Valor.valorD);
			else if (campo->Type == 'L')
				if (campo->Patual->Valor.valorL) printf("TRUE\t");
				else printf("FALSE\t");
			else if (campo->Type == 'C')
				printf("%s\t", campo->Patual->Valor.valorC);
			else
				printf("%s\t", campo->Patual->Valor.valorM);
			
			x+=campo->Width;
			campo = campo->Prox;
		}
		*pos+=1;
	}
	else {
		gotoxy(1, *pos); printf("                                                                          ");
		gotoxy(1, *pos); printf("Selecione um arquivo [USE 'NOME.DBF'] e um Registro [GOTO 1]"); *pos+=1;
	}
	
	*pos+=1;
}

// EDIT
void edit (Arquivo *arquivo) {
	Campo *campo;
	union tipo valor;
	Dados *dados;
	
	campo = arquivo->Campos;
	while (campo != NULL) {
		dados = campo->Patual;
		
		if (campo->Type == 'N') {
			printf("%s[%f]\t", campo->FieldName, dados->Valor.valorN);
			scanf("%f", &dados->Valor.valorN);
		}
		else if (campo->Type == 'D') {
			printf("\n%s[%s]\t", campo->FieldName, dados->Valor.valorD);
			gets(dados->Valor.valorD);
		}
		else if (campo->Type == 'L') {
			if (dados->Valor.valorL) 
				printf("\n%s[TRUE-1]\t", campo->FieldName);
			else
				printf("\n%s[FALSE-0]\t", campo->FieldName);
			scanf("%c", &dados->Valor.valorL); 
		}
		else if (campo->Type == 'C') {
			printf("\n%s[%s]\t", campo->FieldName, dados->Valor.valorC);
			gets(dados->Valor.valorC);
		}
		else {
			printf("\n%s[%s]\t", campo->FieldName, dados->Valor.valorM);
			gets(dados->Valor.valorM);
		}
	}
}

// DELETE
void delete_reg (Arquivo *arquivo) {
	Campo *campo;
	
	campo = arquivo->Campos;
	while (campo != NULL) {
		campo->Patual->setDelet = 1;
		campo = campo->Prox;
	}
}

// RECALL
void recall (Arquivo *arquivo, char str[], char setDeleted) {
	Campo *campo;
	Dados *dados;
	
	if (setDeleted) {
		if (strcmp(str, "RECALL") == 0) {
			campo = arquivo->Campos;
			
			while (campo!=NULL) {
				campo->Patual->setDelet = 0;
				campo = campo->Prox;
			}
		}
		else {
			if (strcmp(str, "RECALL ALL") == 0) {
				campo = arquivo->Campos;
				
				while (campo!=NULL) {
					dados = campo->Pdados;
					
					while (dados!=NULL) {
						dados->setDelet = 0;
						dados=dados->Prox;
					}
					campo=campo->Prox;
				}
			}
		}
	}
}

// SET DELETED
void setDeleted (char *setDeleted, char *str) {
	if (strcmp(str, "SET DELETED OFF") == 0) {
		*setDeleted = 0;
	} 
	else if (strcmp(str, "SET DELETED ON") == 0) {
		*setDeleted = 1;
	}
}

// PACK
void pack (Arquivo *arquivo) {
	Campo *campo;
	Dados *dados, *aux;
	
	campo = arquivo->Campos;
	while (campo != NULL) {
		dados = campo->Pdados;
		while (dados != NULL && dados->setDelet) {
			campo->Pdados = dados->Prox;
			free(dados);
			dados = campo->Pdados;
		}
		while(dados!=NULL && aux->Prox!=NULL) {
			aux = dados;
			dados = aux->Prox;
			if (dados->setDelet) {
				aux->Prox = dados->Prox;
				free(dados);
				dados = aux;
			}
		}
		campo=campo->Prox;
	}
}

// ZAP
void zap (Arquivo *arquivo) {
	Campo *campo, *auxC;
	Dados *dados, *auxD;
	
	campo = arquivo->Campos;
	while (campo!=NULL) {
		dados = campo->Pdados;
		
		while (dados!=NULL) {
			auxD = dados;
			dados = dados->Prox;
			free(auxD);
		}
		
		auxC = campo;
		campo = campo->Prox;
		free(auxC);
	}
}
