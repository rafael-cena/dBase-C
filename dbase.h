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
	Arquivo *arquivo;
	criaArquivo(&arquivo, nome);
	
	if (arquivo != NULL) {
		arquivo->Campos = criarCampos(&arquivo, unidade->Und);
		insereStatus(&arquivo, criaStatus(1));
	}
	else {
		printf("Erro ao criar o arquivo!");
	}
}

// DIR
void dir (Unidade *unidade, int *y) {
	int i, size;
	Arquivo *arquivo;
	Campo *campo;
	Dados *dados;
	arquivo = unidade->Arqs;
	
	printf("Database File\t # Records \t Last Update\t Size\n"); *y++;
	while (arquivo != NULL) {
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
		printf("                                            ");
		printf("%s \t\t%d \t%s \t%d\n", arquivo->NomeDBF, i, arquivo->Data, size*i); *y++;
	}
	*y+=2;
}

// QUIT


// USE
void use (Unidade *unidade, Arquivo **arquivo, char *nome) {
	Arquivo *aux;
	
	if (unidade != NULL && unidade->Arqs != NULL) {
		aux = unidade->Arqs;
		
		while (aux!=NULL && strcmp(aux->NomeDBF, nome) != 0)
			aux = aux->Prox;
	}
	
	if (aux != NULL && strcmp(aux->NomeDBF, nome) == 0) *arquivo = aux;
	else *arquivo = NULL;
}

// LIST STRUCTURE
void listStructure (Unidade *unidade, Arquivo *arquivo) {
	Campo *campo;
	Dados *dados;
	int y, i, size;
	y=1; i=size=0;
	
	campo = arquivo->Campos;
	if (campo != NULL) {
		dados = campo->Pdados;
		while (dados != NULL) {
			i++;
			dados = dados->Prox;
		}
		
		printf("Structure for database: %s%s\n", unidade->Und, arquivo->NomeDBF);
		printf("Number of data records: %d\n", i);
		printf("Date of last update   : %s\n", arquivo->Data);
		printf("Field  Field Name  Type  Width  Dec\n");
		while (campo != NULL) {
			printf("   %d \t%s \t%s \t%d \t%d\n", y, campo->FieldName, getType(campo->Type), campo->Width, campo->Dec);
			y++;
			size+=campo->Width;
		}
		printf("** Total ** \t\t%d\n", size);
	}
}

// APPEND
void append (Arquivo *arquivo) {
	Campo *campo;
	union tipo valor;
	Dados *dados;
	
	campo = arquivo->Campos;
	
	while (campo != NULL) {
		dados = (Dados*)malloc(sizeof(Dados));
		printf("\n%s\t", campo->FieldName);
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
		
		insereDados(&campo, dados);
	}
}

// LIST
void list (Arquivo *arquivo) {
	Campo *campo, *auxC;
	
	campo = arquivo->Campos;
	printf("Record#\t");
	while (campo != NULL) {
		printf("%s\t", campo->FieldName);
		campo->Patual = campo->Pdados;
		campo = campo->Prox;
	}
	campo = arquivo->Campos;
	while (campo->Patual != NULL) {
		if (campo->Type == 'N')
			printf("%f\t", campo->Patual->Valor.valorN);
		else if (campo->Type == 'D')
			printf("%s\t", campo->Patual->Valor.valorD);
		else if (campo->Type == 'L')
			printf("%c\t", campo->Patual->Valor.valorL);
		else if (campo->Type == 'C')
			printf("%s\t", campo->Patual->Valor.valorC);
		else
			printf("%s\t", campo->Patual->Valor.valorM);
			
		campo->Patual = campo->Patual->Prox;
	}
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
		printf("\nNenhum registro encontrado!");
	else 
		printf("\nRecord = \t %d", pos);
}

// GOTO
void go_to (Arquivo *arquivo, int go) {
	Campo *campo;
	int i;
	
	campo = arquivo->Campos;
	
	while (campo != 0) {
		campo->Patual = campo->Pdados;
		
		for (i=0;i<go;i++)
			campo->Patual = campo->Patual->Prox;
		
		campo=campo->Prox;
	}
}

// DISPLAY
void display (Arquivo *arquivo) {
	Campo *campo, *auxC;
	Dados *dados;
	
	campo = arquivo->Campos;
	printf("Record#\t");
	while (campo != NULL) {
		printf("%s\t", campo->FieldName);
		campo->Patual = campo->Pdados;
		campo = campo->Prox;
	}
	campo = arquivo->Campos;
	while (campo != NULL) {
		if (campo->Type == 'N')
			printf("%f\t", campo->Patual->Valor.valorN);
		else if (campo->Type == 'D')
			printf("%s\t", campo->Patual->Valor.valorD);
		else if (campo->Type == 'L')
			printf("%c\t", campo->Patual->Valor.valorL);
		else if (campo->Type == 'C')
			printf("%s\t", campo->Patual->Valor.valorC);
		else
			printf("%s\t", campo->Patual->Valor.valorM);
			
		campo = campo->Prox;
	}
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
