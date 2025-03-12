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
