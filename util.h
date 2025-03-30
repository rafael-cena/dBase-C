#include "estruturas.h"

char* getData () {
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

char* getHora () {
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

char *getType (char type) {
	if (type == 'N') 
		return "NUMERIC";
	else if (type == 'D')
		return "DATE";
	else if (type == 'L')
		return "LOGICAL";
	else if (type == 'C')
		return "CHARACTER";
	else if (type == 'M')
		return "MEMO";
	return "TIPO INVÁLIDO";
}

int buscaSubstring(char str[], char inst[]) {
	int i;
	for (i=0; str[i] != '\0' && inst[i] != '\0' && i < strlen(inst); i++)
		if (str[i] != inst[i])
			return -1;
	
	if (inst[i] == '\0' && str[i] == ' ' && i == strlen(inst))
		return 0;
	return -1;
}

Campo *criarCampos (Arquivo **arquivo) {
	Campo *campo;
	char *aux;
	int i;
	
	i=1;
	
	aux = (char*)malloc(20);
	
	printf("   Field Name\tType \t Width\tDec\n");
	printf("=================================================\n");
	printf(" %d  ", i); i++;
	gets(aux);
	while (aux != NULL) {
		campo = (Campo*)malloc(sizeof(Campo));
		strcpy(aux, campo->FieldName);
		printf("\t");
		do {
			gets(aux);
			campo->Type = toupper(aux[0]);
		} while (campo->Type != 'N' && campo->Type != 'D' && campo->Type != 'L' && campo->Type != 'C' && campo->Type != 'M');
		
		printf("\t");
		scanf("%d", &campo->Width);
		
		printf("\t");
		if (campo->Type == 'N') {
			scanf("%d", &campo->Dec);
		}
		else {
			campo->Dec = 0;
			printf("%d", campo->Dec);
		}
		printf("\n");
		
		insereCampo(&(*arquivo), &campo);
		
		printf(" %d  ", i); i++;
		gets(aux);
	}
	free(aux);
}






