#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h> 

struct Funcionario {
	int cod;
	char nome[50];
	char cpf[15];
	char data_nascimento[11];
	double salario;
};

void gravar(Funcionario *funcionario, char modo[], char arquivo[])
{	
   	FILE* arq;
   	int size = 1;
   	int i;
	for (int i = 0; i < size; i++) {
        printf("\nFuncionarios %d\n", i+1);
        
        printf("Codigo: ");
        scanf("%d", &funcionario[i].cod);

        printf("\nNome: ");
        scanf("%s", &funcionario[i].nome);

        printf("\nCPF: ");
        scanf("%s", &funcionario[i].cpf);
        
        printf("\nData de Nascimento: ");
        scanf("%s", &funcionario[i].data_nascimento);
        
        printf("\nSalario: ");
        scanf("%d", &funcionario[i].salario);
       
        printf("\n");
    }

   	if ((arq = fopen(arquivo, modo)) == NULL) {
        puts("Erro ao abrir o arquivo!");
    } else {
    	if (arquivo == "registros.text") {
	    	for (int i = 0; i < size; i++) {
		    	fprintf(arq,"%d %s %s %s %d",funcionario[i].cod, funcionario[i].nome, funcionario[i].cpf, funcionario[i].data_nascimento, funcionario[i].salario);
			    fprintf(arq, "\n");
			}
		} else {
		    fwrite(funcionario, sizeof(Funcionario), 1, arq);
		}
		fclose(arq);
	    puts("Arquivo gravado com sucesso!");	
	}
}

void ler(char arquivo[], char type[])
{
	FILE* arq;
	Funcionario funcionario;
	int i = 0, i2 = 0;
	char ch1[50], ch2[15], ch3[11];
	int vet[5];
	if (arq != NULL) {
		if (type == "binario") {
			arq =  fopen(arquivo, "rb");
			fread(&funcionario, sizeof(Funcionario), 1, arq);
			do {
		        printf("%d %s %s %s %d", funcionario.cod, funcionario.nome, funcionario.cpf, funcionario.data_nascimento,funcionario.salario);
		        fread(&funcionario, sizeof(Funcionario), 1, arq);
		        printf("\n");
		    } while (!feof(arq));
		} else {
			arq =  fopen(arquivo, "r");
			while( (fscanf(arq,"%d %s %s %s %d\n", &i, &ch1, &ch2, &ch3, &i2))!=EOF )
	   			printf("%d %s %s %s %d\n", i, ch1, ch2, ch3, i2);
	   	}
	}

	fclose(arq);
}

void buscaSequencial()
{
	double time_spent = 0.0;
	clock_t begin = clock();
	
	FILE* arq;
	Funcionario funcionario;
	int cod = 0;
	int exit = 0;
	int comparacoes = 0;
	printf("Informe o codigo: ");
	scanf("%d", &cod);
	arq =  fopen("registros.dat", "rb");
	fread(&funcionario, sizeof(Funcionario), 1, arq);
	do {
		comparacoes++;
		if (funcionario.cod == cod) {
			printf("%d %s %s %s %d", funcionario.cod, funcionario.nome, funcionario.cpf, funcionario.data_nascimento,funcionario.salario);
			exit = 1;
		}
		fread(&funcionario, sizeof(Funcionario), 1, arq);
	} while (!feof(arq) && exit != 1);
	//sleep(3);
	printf("\nNumero de comparacoes: %d\n", comparacoes);
	clock_t end = clock();
	time_spent += (double)(end - begin);
	time_spent = time_spent/1000;
	printf("Tempo: %2.f segundos", time_spent);
}

void buscaBinaria()
{
	//multiplicar para a escala 100
	double time_spent = 0.0;
	clock_t begin = clock();
	int cod;
	FILE* arq;
	Funcionario funcionario;
	arq =  fopen("registros.dat", "r+b");
	int inicio = 0;
	int fim = 58;
	int meio = 0;
	printf("Informe o codigo: ");
	scanf("%d", &cod);
	int stop = 1;
	int comparacoes = 0;
	
	while (inicio < fim && stop) {
		meio = (inicio + fim)/2;
		fseek(arq, meio*sizeof(Funcionario), SEEK_SET);
		fread(&funcionario, sizeof(Funcionario), 1, arq);
		if (cod == funcionario.cod) {
			printf("%d %s %s %s %d", funcionario.cod, funcionario.nome, funcionario.cpf, funcionario.data_nascimento,funcionario.salario);
			stop = 0;
		} else if (cod > funcionario.cod) {
			inicio = meio+1;
		} else {
			fim = meio;
		}
		comparacoes++;
	}
	printf("\nNumero de comparacoes: %d\n", comparacoes);
	clock_t end = clock();
	time_spent += (double)(end - begin);
	time_spent = time_spent/1000;
	printf("Tempo: %2.f segundos", time_spent);
}

void keySorting()
{	
//	FILE* arq;
//	Funcionario funcionario[100];
//	Funcionario *aux;
//	aux = funcionario;
//
//	arq =  fopen("registros.dat", "rb");
//
//	int key[101];
//	int i = 0;
//
//	do {
//		fread(&funcionario[i], sizeof(Funcionario), 1, arq);
//		i++;
//	} while (!feof(arq));
//	int size = i;
//	for (i = 0; i < 100; i++) {
//		if (funcionario[i].cod > funcionario[i+1].cod && i <= size-2) {
//			funcionario[101] = funcionario[i+1];
//			funcionario[i+1] = funcionario[i];
//			funcionario[i] = funcionario[101];
//		}
//	}
//	arq =  fopen("registros.dat", "wb");
//	for (i = 0; i < 100; i++) {
//		fwrite(funcionario, sizeof(Funcionario), 1, arq);
//		fread(&funcionario, sizeof(Funcionario), 1, arq);
//	}
//	fclose(arq);
}

void MSG_MENU(){
    printf("\n******************** MENU ***********************");
    printf("\n\t1. Gravar em texto");
    printf("\n\t2. Gravar em binario");
    printf("\n\t3. Imprimir");
    printf("\n\t4. Busca sequencial");
    printf("\n\t5. Busca binaria");
    printf("\n\t6. Ordenar e imprimir");
    printf("\n\t7. SAIR");
}

int main()
{
	struct Funcionario funcionario[3];
	Funcionario *aux;
	aux = funcionario;
	int opcao = 0;
	do {
        MSG_MENU();
		printf("\n\nDIGITE UMA OPCAO:");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao) {
        	case 1:
        		gravar(aux, "a+", "registros.text");
        		break;
        	case 2:
        		gravar(aux, "a+b", "registros.dat");
            	break;
        	case 3:
        		ler("registros.dat", "binario");
            	break;
        	case 4:
        		buscaSequencial();
            	break;
            case 5:
        		buscaBinaria();
            	break;
            case 6:
            	keySorting();
            	break;
        	default:
        		printf("\nINVALIDO!!!");
        		break;
		}
	} while (opcao != 7);

}
