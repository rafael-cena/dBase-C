char* getData () {
	char *data;
	int dia, mes, ano;
	
	struct tm *date;
	time_t segundos;
	
	time(&segundos);
	date = localtime(&segundos);
	
	data = (char*)malloc(11);
	
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
	
	hora = (char*)malloc(6);
	
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
	
	if (inst[i] == '\0' && (str[i] == ' ' || str[i] == '\0') && i == strlen(inst))
		return i;
	return -1;
}

void getInstrucao (char *instrucao, int *key) {
	if (buscaSubstring(instrucao, "SET DEFAULT TO") != -1) *key = 1;
	else if (buscaSubstring(instrucao, "CREATE") != -1) *key = 2;
	else if (stricmp(instrucao, "DIR") == 0) *key = 3;
	else if (stricmp(instrucao, "QUIT") == 0) *key = 4;
	else if (buscaSubstring(instrucao, "USE") != -1) *key = 5;
	else if (stricmp(instrucao, "LIST STRUCTURE") == 0) *key = 6;
	else if (stricmp(instrucao, "APPEND") == 0) *key = 7;
	else if (buscaSubstring(instrucao, "LIST") != -1) *key = 8;
	else if (stricmp(instrucao, "CLEAR") == 0) *key = 9;
	else if (buscaSubstring(instrucao, "LOCATE") != -1) *key = 10;
	else if (buscaSubstring(instrucao, "GOTO") != -1) *key = 11;
	else if (stricmp(instrucao, "DISPLAY") == 0) *key = 12;
	else if (stricmp(instrucao, "EDIT") == 0) *key = 13;
	else if (stricmp(instrucao, "DELETE") == 0) *key = 14;
	else if (buscaSubstring(instrucao, "RECALL") != -1) *key = 15;
	else if (buscaSubstring(instrucao, "SET DELETED") != -1) *key = 16;
	else if (stricmp(instrucao, "PACK") == 0) *key = 17;
	else if (stricmp(instrucao, "ZAP") == 0) *key = 18;
	else *key = -1;
}

char* getField (char *str, char *instrucao) {
	char *aux;
	int i, j=0;
	aux = (char*)malloc(20);
	for (i=strlen(instrucao)+5; str[i] != ' '; i++, j++)
		aux[j] = str[i];
	aux[j] = '\0';
	return aux;
}

int getPos (char str[], char instrucao[]) {
	char aux[4];
	int i, j=0;
	
	for (i = strlen(instrucao)+1; str[i] != '\0'; i++)
		aux[j] = str[i];
	aux[j+1] = '\0';
	return atoi(aux);
}

char* getNome (char *str, char *instrucao) {
	char *aux;
	int i, j;
	
	i = strlen(str)-strlen(instrucao) + 1;
	aux = (char*)malloc(i);
	for (i=strlen(instrucao)+1, j=0; str[i] != '\0'; i++, j++) {
		aux[j] = str[i];
	}
	aux[j]='\0';
	return aux;
}

void telaCampos (int *y, char dir[], char inst[], char *nome) {
 	int x;
 	x=54;
 	*y=1;
 	gotoxy(x, *y); printf("Field Name"); x=73;
 	gotoxy(x, *y); printf("Type"); x=81;
 	gotoxy(x, *y); printf("Width"); x=89;
 	gotoxy(x, *y); printf("Dec"); *y+=1;
 	x=54;
 	while (x < 93) {
 		gotoxy(x, *y); printf("%c", 205); x+=1;
 	}
 	*y+=1;
 	x=50;
 	
 	gotoxy(x, 14);
 	textcolor(0);
 	textbackground(8);
 	while (x < 86) {
 		gotoxy(x, 14); printf(" "); x+=1;
 	}
 	x=50;
 	gotoxy(x, 14); x+=14;
 	printf("%s\t\t||<%s>||%s", inst, dir, nome);
 	x+=strlen(nome);
 	printf("      ");
 	
 	textcolor(15);
 	textbackground(0);
 	gotoxy(x, 15); printf("Enter the field");
}
