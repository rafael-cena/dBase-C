struct stringdin {
	char letra;
	struct stringdin *prox;
};
typedef struct stringdin StrDin;

void init (StrDin **str) {
	*str = NULL;
}

void reinicia (StrDin **str) {
	if (*str != NULL) {
		reinicia(&(*str)->prox);
		free(*str);
		*str = NULL;
	}
}

void exibe (StrDin *str) {
	while (str != NULL) {
		printf("%c", str->letra);
		str = str->prox;
	}
}

void exibeInv (StrDin *str) {
	if (str != NULL) {
		exibeInv(str->prox);
		printf("%c", str->letra);
	}
}

int tamanho (StrDin *str) {
	if (str == NULL)
		return 0;
	return tamanho(str->prox) +1;
}

void insere (StrDin **str, char c) {
	StrDin *aux, *nova;
	nova = (StrDin *)malloc(sizeof(StrDin));
	nova->prox = NULL;
	nova->letra = c;
	
	if (*str == NULL) {
		*str = nova;
	}
	else {
		aux = *str;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = nova;
	}
}

void copia (StrDin *str1, StrDin **str2) {
	StrDin *aux, *nova;
	
	if (str1 != NULL) {
		if (*str2 == NULL) {
			nova = (StrDin *)malloc(sizeof(StrDin));
			nova->prox = NULL;
			nova->letra = str1->letra;
			*str2 = nova;
			aux = *str2;
			str1 = str1->prox;
		}
		
		while (str1 != NULL) {
			nova = (StrDin *)malloc(sizeof(StrDin));
			nova->prox = NULL;
			nova->letra = str1->letra;
			aux->prox = nova;
			str1 = str1->prox;
			aux = aux->prox;
		}
	}
}

void concat (StrDin *str1, StrDin *str2, StrDin **str3) {
	copia(str1, &*str3);
	copia(str2, &*str3);
}

void remover (StrDin **str, int nro, int start) {
	StrDin *ant, *aux;
	int tam;
	
	if (*str != NULL) {
		if (start == 0)
			for (nro; nro>0; nro--) {
				aux = *str;
				*str = (*str)->prox;
				free(aux);
			}
		else {
			aux = *str;
			for (tam = 1; tam < start; tam++)
				aux = aux->prox;
			ant = aux;
			aux = aux->prox;
			
			for (nro; nro>0; nro--) {
				ant->prox = aux->prox;
				free(aux);
				aux=ant->prox;
			}
		}
	}
}

void insereSubs (StrDin **str, StrDin *subs, int start) {
	StrDin *aux, *auxSubs;
	
	if (*str != NULL && start < tamanho(*str)) {
		aux = *str;
		for (start; start>1; start--) 
			aux = aux->prox;
		
		auxSubs = subs;
		while (auxSubs->prox != NULL)
			auxSubs = auxSubs->prox;
			
		auxSubs->prox = aux->prox;
		aux->prox = subs;
	}
}

char menor (StrDin *str1, StrDin *str2) {
	return tamanho(str1) < tamanho(str2);
}

char iguais (StrDin *str1, StrDin *str2) {
	if (str1 == NULL && str2 == NULL)
		return 1;
	else if (str1->letra == str2->letra)
		return iguais(str1->prox, str2->prox);
	else return 0;
}

char buscaSubs (StrDin *str, StrDin *subs, int *local) {
	StrDin *auxStr, *auxSubs;
	
	auxSubs = subs;
	while (auxSubs != NULL && str != NULL) {
		auxStr = str;
		while (auxSubs != NULL && str != NULL && str->letra == auxSubs->letra) {
			str = str->prox;
			auxSubs = auxSubs->prox;
		}
		if (auxSubs != NULL && str != NULL && str->letra != auxSubs->letra) {
			auxSubs = subs;
			str = auxStr->prox;
			*local += 1;
		}
	}
	
	if (auxSubs != NULL) {
		*local = -1;
		return 0;
	}
	return 1;
}

char* toString (StrDin *str, int start) {
	char *string;
	int i;
	
	while (start > 0) {
		str = str->prox;
		start--;
	}
	
	string = (char*)malloc(sizeof(tamanho(str)+1));
	
	for (i=0; str != NULL; i++) {
		string[i] = str->letra;
		str = str->prox;
	}
	string[i] = '\0';
	
	return string;
}
