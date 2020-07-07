#include<stdio.h> //Blibioteca padrão
#include<string.h> //Para Strings
#include<stdlib.h> //Para funções especiais
#include<locale.h> //Para acentos do Português
#include <dirent.h> //Para diretórios
/*
EscSys v.1.0
****
*/
struct empresa{
	char nome[30]="Javali Souluções Tecnologicas",cnpj[19]="34.225.286/0001-25";
};
struct conta{
	char banco[6]="Banco",caixa[6]="Caixa";
};
void adc_diario (FILE* lvd,struct empresa* A,struct conta* B) {
char fato[100],flag2[5],cred[20];	
int numpag,flag,data;
float valor;
	lvd = fopen("Livro_diario.txt","w");
	
	for(flag=0;flag<20;flag++){
		cred[flag] = ' ';
	}
	printf("\t\tLIVRO DIÁRIO\n");
	fprintf(lvd, "%s\n", A->nome);
	fprintf(lvd, "%s\n", A->cnpj);
	printf("Data da operação (ddmmaa): ");
	scanf("%i", &data);
	printf("Valor: ");
	scanf("%f", &valor);
	printf("Conta a ser debitada: ");
	printf("[%s] [1]  / [%s] [2] \n", B->banco, B->caixa );
	scanf("%i", &flag);
	if(flag=1){
		flag2 == B->banco;
	}else{
		flag2 == B->caixa;
	}
	printf("Conta a ser creditada: ");
	gets(cred);
	getchar();
	printf("Fato: ");
	gets(fato);
	getchar();
	fprintf(lvd,"\n\n%i\t\t%s\t\t%s\t\t%.2f\n", data,flag2,cred,fato,valor);
	fclose(lvd);
	printf("\nPressione uma tecla...");
	getchar();
	system("cls");
}

void mostrar_diario(FILE* lvd, struct empresa* A) {

	system("call H:\\EscSys\\Livro_diario.txt");


}

void livro_diario(FILE* lvd) {
	int i, flag = 1;
	
	struct empresa A;
	struct conta B;
	do {
		do {
			printf("\tLIVRO DIÁRIO\n");
			printf(" ===================================\n");
			printf("| Adicionar fato ao livro	[1]|\n");
			printf("| Mostrar livro			[2]|\n");
			printf("| Voltar			[4]|\n");
			printf(" ===================================\n");
			printf(">>> ");
			scanf("%i", &i);
			system("cls");
		} while(i > 4);
		getchar();
		switch(i){
			case 1:
				adc_diario(lvd, &A,&B);
			break;
			case 2:
				mostrar_diario(lvd, &A);
			break;
			case 4:
				flag = 0;
			break;
		}
	} while(flag == 1);
}

void razao_pag(FILE* lvr) {
	char conta[255], data[255], hist[255];
	int numlinhas, op, linha = 0, flag1 = 1, flag0 = 1;
	float cred, deb;
	
	DIR *dir;
	struct dirent *lsdir;
	
	do {
		printf("Lista de páginas [1]\n");
		printf("Voltar [0]\n");
		printf(">>> ");
		scanf("%i", &op);
		getchar();
	} while(op < 0 && op > 1);
	switch(op) {
		case 1:
			system("cls");
			chdir("H:\\EscSys\\liv_razao\\");
			printf("\tLista de páginas\n\n");
		    dir = opendir("H:\\EscSys\\liv_razao\\");
		    //código da comunidade do hardware
		    //dir = opendir("E:\\");
		    while ((lsdir = readdir(dir)) != NULL) {
				printf("> %s\n", lsdir->d_name);
		    }
		    //
		    printf("\n\nDigite o nome da conta (sem .txt)\n ");
		    scanf("%[^\n]s", &conta);
		    system("cls");
		    printf("%s\n",conta);
			strcat(conta, ".txt");
			lvr = fopen(conta, "a+");
			fscanf(lvr, "%i", &numlinhas);
			linha = 52 - numlinhas;
			getchar();
			do {
				linha++;
				do {
					printf("Registro credor(c) ou devedor(d)? ");
					op = getchar();
					getchar();
				} while(op != 'c' && op != 'd');
				printf("L%i ", linha-2);
				printf("Data (dd/mm/aaaa): ");
				scanf("%[^\n]s", &data);
				getchar();
				printf("Histórico: ");
				scanf("%[^\n]s", &hist);
				getchar();
				if(op == 'c') {
					printf("Crédito (sem pontos): ");
					scanf("%f", &cred);
					getchar();
					fprintf(lvr, "%i %c %s %s %f\n", linha, op, data, hist, cred);
				}
				else {
					if(op == 'd') {
						printf("Débito (sem pontos): ");
						scanf("%f", &deb);
						getchar();
						fprintf(lvr, "%i %c %s %s %f\n", linha, op, data, hist, deb);
					}
				}
				do {
					printf("\nContinuar [0/1]?: ");
					flag1 = getchar();
					getchar();
				} while(flag0 < 0 && flag0 > 1);
			} while(flag1 < 1 && flag1 > 1 && linha < 52);
			system("cls");
			fseek(lvr, 1, SEEK_SET);
			numlinhas = 52 - linha;
			fprintf(lvr, "%i", numlinhas);
			fclose(lvr);
			closedir(dir);
		break;
		case 0:
			flag0 = 0;
			system("cls");
		break;
		} while(flag0 == 1 && linha < 52);				
	}
	
void adc_razao(FILE* lvr) {
	char conta[255], ext[255], hist[255], data[20], op;
	int flag = 1, linha = 52, pag = 1, i, numlinha = 52;
	float cred, deb;
	
	DIR *dir;
	struct dirent *lsdir;
	
	chdir("H:\\EscSys\\liv_razao\\");
	do {
		printf("\nNome da conta: ");
		scanf("%[^\n]s", &conta);
		getchar();
		for(i = 0; i < 255; i++) {
			if(conta[i] == NULL) {
				i = 300;
			}
			else {
				ext[i] = conta[i];
			}
		}
	    strcat(ext, ".txt");
		
		lvr = fopen(ext, "wt");
		fprintf(lvr, "%i\n", linha);
		fprintf(lvr, "%s\n", conta);
		linha = 1;
		do {
			printf("Registro credor(c) ou devedor(d)? ");
			scanf("%c%*c", &op);
		} while(op != 'c' && op != 'd');
		printf("L%i ", linha);
		printf("Data (dd/mm/aaaa): ");
		scanf("%[^\n]s", &data);
		getchar();
		printf("Histórico: ");
		scanf("%[^\n]s", &hist);
		getchar();
		if(op == 'c') {
			printf("Crédito (sem pontos): ");
			scanf("%f", &cred);
			fprintf(lvr, "%i %c %s %s %f", linha, op, data, hist, cred);
			fclose(lvr);
		}
		else {
			if(op == 'd') {
				printf("Débito (sem pontos): ");
				scanf("%f", &deb);
				fprintf(lvr, "%i %c %s %s %f", linha, op, data, hist, deb);
				fclose(lvr);
			}
		}
		linha++;
		getchar();
		do {
			printf("\nContinuar [0/1]?: ");
			scanf("%i", &flag);
			getchar();
		} while(flag < 0 && flag > 1);
	} while(flag == 1 && linha < 52);
	fseek(lvr, 1, SEEK_SET);
	fprintf(lvr, "%i", 52-linha);
	system("cls");
	closedir(dir);
}

void livro_razao(FILE* lvr) {
	int flag = 1, i;
	
	do {
		do {
			printf("\tLIVRO RAZÃO\n");
			printf(" ===================================\n");
			printf("| Adicionar conta		[1]|\n");
			printf("| Adicionar novo fato		[2]|\n");
			printf("| Voltar			[0]|\n");
			printf(" ===================================\n");
			printf(">>> ");
			scanf("%i", &i);
			getchar();
			system("cls");
		} while(i > 2);
		switch(i) {
			case 1:
				adc_razao(lvr);
			break;
			case 2:
				razao_pag(lvr);
			break;
			case 0:
				flag = 0;
			break;
		}
	} while(flag == 1);
}

main(){
	int i, flag = 1;
	
	struct empresa A;
	
	FILE* lvd;
	FILE* lvr;
	
	setlocale(LC_ALL, "Portuguese");
	do {
		do {
			printf("               EscSys                \n");
			printf(" ===================================\n");
			printf("|    %s  |\n", A.nome);
			printf("|      CNPJ: %s     |\n", A.cnpj);
			printf("|                                   |\n");
			printf("| LIVRO DIÁRIO             [1]      |\n");
			printf("| LIVRO RAZÃO              [2]      |\n");
			printf("| Fechar                   [0]      |\n");
			printf(" ===================================\n");
			printf(">>> ");
			scanf("%i", &i);
			getchar();
			system("cls");
		} while(i > 2);
		switch(i){
			case 1:
				livro_diario(lvd);
			break;
			case 2:
				livro_razao(lvr);
			break;
			case 0:
				flag = 0;
				printf("Parando...[tecle]");
				getchar();
				system("cls");
				printf("Finalizado");
			break;
		}
	} while(flag == 1);
}
