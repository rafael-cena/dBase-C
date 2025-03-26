union TpValor {
	int valorN; // num
    char valorD[11]; // dd/mm/aaaa
    char valorL; // true false
    char valorC[51]; // string
    char valorM[51]; // memoria
};

struct tpdados {
	union TpValor valor;
	struct tpdados *prox;
};
typedef struct tpdados TpDados;

struct tpstatus {
	char status;
	struct tpstatus *prox;
};
typedef struct tpstatus TpStatus;

struct tpcampos {
	TpDados *PAtual, *PDados;
	char nomeCampo[30];
	char tipo;
	int tamanho, dec;
	struct tpcampos *prox;
};
typedef struct tpcampos TpCampos;

struct tparq {
	struct tparq *ant, *prox;
	TpStatus *status;
	TpCampos *campos;
	char nome[30], data[11], hora[6];
};
typedef struct tparq TpArq;

struct tpund {
	struct tpund *ant, *prox;
	char und[3];
	TpArq *arqs;
};
typedef struct tpund TpUnd;

void initUnd (TpUnd **und) {
	*und = NULL;
	*und = (TpUnd*)malloc(sizeof(TpUnd));
	(*und)->ant = (*und)->prox = NULL;
	(*und)->arqs = NULL;
}

void initArq (TpArq **arq) {
	*arq = NULL;
	*arq = (TpArq*)malloc(sizeof(TpArq));
	(*arq)->ant = (*arq)->prox = NULL;
	(*arq)->status = NULL;
	(*arq)->campos = NULL;
}

void initCp (TpCampos **cp) {
	*cp = NULL;
	*cp = (TpCampos*)malloc(sizeof(TpCampos));
	(*cp)->PAtual = (*cp)->PDados = NULL;
	(*cp)->prox = NULL;
}

void initSt (TpStatus **st) {
	*st = NULL;
	*st = (TpStatus*)malloc(sizeof(TpStatus));
	(*st)->prox = NULL;
	(*st)->status = 1;
}

void initDt (TpDados **dt) {
	*dt = NULL;
	*dt = (TpDados*)malloc(sizeof(TpDados));
	(*dt)->prox = NULL;
}

void inserirUnd (TpUnd **unidade, char desc[]) {
	TpUnd *nova;
	initUnd(&nova);
	
	strcpy(nova->und, desc);
	if (*unidade == NULL)
		*unidade = nova;
	else {
		nova->prox = *unidade;
		(*unidade)->ant = nova;
		*unidade = nova;
	}
}

void inserirArq (TpUnd **unidade, TpArq **arq) {
	TpArq *aux;
	if ((*unidade)->arqs == NULL)
		(*unidade)->arqs = *arq;
	else {
		aux = (*unidade)->arqs;
		while(aux->prox != NULL)
			aux=aux->prox;
		aux->prox = *arq;
		(*arq)->ant = aux;
	}
}

char getTipo (char *str) {
	if (stricmp(str, "NUMERIC") == 0)
		return 'N';
	if (stricmp(str, "DATE") == 0)
		return 'D';
	if (stricmp(str, "LOGICAL") == 0)
		return 'L';
	if (stricmp(str, "CHARACTER") == 0)
		return 'C';
	return 'M';
}

char *getData () {
	char *data;
	int dia, mes, ano;
	
	struct tm *date;
	time_t segundos;
	
	time(&segundos);
	date = localtime(&segundos);
	
	data = (char*)malloc(sizeof(11));
	
	dia = date->tm_mday;
	mes = date->tm_mon + 1;
	ano = date->tm_year + 1900;
	
	data[0] = '0' + dia / 10;
	data[1] = '0' + dia % 10;
	data[2] = '/';
	data[3] = '0' + mes / 10;
	data[4] = '0' + mes % 10;
	data[5] = '/';
	data[6] = '0' + (ano / 1000) % 10;
	data[7] = '0' + (ano / 100) % 10;
	data[8] = '0' + (ano / 10) % 10;
	data[9] = '0' + ano % 10;
	data[10] = '\0';
	
	return data;
}

char *getHora () {
	char *hora;
	int hr, min;
	
	struct tm *date;
	time_t segundos;
	
	time(&segundos);
	date = localtime(&segundos);
	
	hora = (char*)malloc(sizeof(6));
	
	hr = date->tm_hour;
	min = date->tm_min;
	
	hora[0] = '0' + hr / 10;
	hora[1] = '0' + hr % 10;
	hora[2] = ':';
	hora[3] = '0' + min / 10;
	hora[4] = '0' + min % 10;     
	hora[5] = '\0';
	
	return hora;
}
