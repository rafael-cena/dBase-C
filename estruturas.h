struct unidade {
	struct unidade *Top, *Bottom;
	char Und[3];
	struct arquivo *Arqs;
};
typedef struct unidade Unidade;

struct arquivo {
	struct arquivo *Ant, *Prox;
	char NomeDBF[50], Data[11], Hora[6];
	struct status *Status;
	struct campo *Campos;
};
typedef struct arquivo Arquivo;

struct campo {
	struct dados *Patual, *Pdados;
	char FieldName[16], Type;
	int Width, Dec;
	struct campos *Prox;
};
typedef struct campo Campo;

struct status {
	char Status;
	struct status *Prox;
};
typedef struct status Status;

union tipo {
	float valorN;
	char valorD[10], valorL, valorC[50], valorM[50];
};

struct dados {
	union tipo Valor;
	struct dados *Prox;
	char setDelet;
};
typedef struct dados Dados;

void criaUnidade (Unidade **unidade, char und[]) {
	Unidade *nova;
	
	nova = (Unidade*)malloc(sizeof(Unidade));
	strcpy(nova->Und, und);
	nova->Arqs = NULL;
	nova->Bottom = NULL;
	
	if (*unidade == NULL) {
		*unidade = nova;
		nova->Top = NULL;
	}
	else {
		(*unidade)->Bottom = nova;
		nova->Top = *unidade;
	}
}

void criaArquivo (Arquivo **arquivo, char *nome) {
	*arquivo = (Arquivo*)malloc(sizeof(Arquivo));
	
	if (*arquivo != NULL) {
		(*arquivo)->Ant = (*arquivo)->Prox = NULL;
		strcpy((*arquivo)->NomeDBF, nome);
		strcpy((*arquivo)->Data, getData());
		strcpy((*arquivo)->Hora, getHora());
		(*arquivo)->Status = NULL;
		(*arquivo)->Campos = NULL;
	}
}

Campo* criaCampo (char *FieldName, char Type, int Width, int Dec) {
	Campo *campo;
	campo = (Campo*)malloc(sizeof(Campo));
	
	if (campo != NULL) {
		campo->Patual = campo->Pdados = NULL;
		strcpy(campo->FieldName, FieldName);
		campo->Type = Type;
		campo->Width = Width;
		campo->Dec = Dec;
		campo->Prox = NULL;
	}
	return campo;
}

Status* criaStatus (char status) {
	Status *novo;
	novo = (Status*)malloc(sizeof(Status));
	
	if (novo != NULL) {
		novo->Status = status;
		novo->Prox = NULL;
	}
	return novo;
}

void criaDados (Dados **dados, union tipo valor, char Type) {
	*dados = (Dados*)malloc(sizeof(Dados));

	if (*dados != NULL) {
		
		(*dados)->Prox = NULL;
		
		if (Type == 'N')
			(*dados)->Valor.valorN = valor.valorN;
		else if (Type == 'D')
			strcpy((*dados)->Valor.valorD, valor.valorD);
		else if (Type == 'L')
			(*dados)->Valor.valorL = valor.valorL;
		else if (Type == 'C')
			strcpy((*dados)->Valor.valorC, valor.valorC);
		else
			strcpy((*dados)->Valor.valorM, valor.valorM);
	}
}

void insereArquivo (Unidade **unidade, Arquivo **arquivo) {
	Arquivo *aux;
	
	if ((*unidade)->Arqs == NULL)
		(*unidade)->Arqs = *arquivo;
	else {
		aux = (*unidade)->Arqs;
		while (aux->Prox != NULL)
			aux = aux->Prox;
		
		aux->Prox = *arquivo;
		(*arquivo)->Ant = aux;
	}
}

void insereCampo (Arquivo **arquivo, Campo *campo) {
	Campo *aux;
	if ((*arquivo)->Campos == NULL)
		(*arquivo)->Campos = campo;
	else {
		aux = (*arquivo)->Campos;
		while (aux->Prox != NULL)
			aux = aux->Prox;
		
		aux->Prox = campo;
	}
}

void insereDados (Campo **campo, Dados *dados) {
	if ((*campo)->Pdados == NULL) {
		(*campo)->Pdados = dados;
		(*campo)->Patual = dados;
	} 
	else {
		while ((*campo)->Patual->Prox != NULL)
			(*campo)->Patual = (*campo)->Patual->Prox;
			
		(*campo)->Patual->Prox = dados;
		(*campo)->Patual = dados;
	}
}

void insereStatus (Arquivo **arquivo, Status *status) {
	Status *aux;
	if ((*arquivo)->Status == NULL) {
		(*arquivo)->Status = status;
	}
	else {
		aux = (*arquivo)->Status;
		while (aux->Prox != NULL)
			aux = aux->Prox;
		aux->Prox = status;
	}
}

