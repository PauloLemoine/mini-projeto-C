#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_DEPENDENTES 10

	typedef struct { 
    	int CPF_Titular;
    	char nome[21]; 
    	int sexo;
    	char email[50];
    	int idade_titular;
    	char telefone[15];
    	int CPF_Terceiro[MAX_DEPENDENTES];
    	char nome_terceiro[MAX_DEPENDENTES][21];
    	int sexo_terceiro[MAX_DEPENDENTES];
    	int idade_terceiro[MAX_DEPENDENTES];
    	int qtd_dependentes;
    	char tipo_plano[10];
    	float valor_plano;
    	float valor_plano_terceiro[MAX_DEPENDENTES];
    	int dia_vencimento;
        int mes_vencimento;
        int ano_vencimento;
	} Cliente;

Cliente cliente_aux, cliente_nulo;
FILE *pcliente;

	void linha(){
    	int i;
		for ( i = 0; i < 40; i++){
		printf("_");
		}
	}
	
	void sublinha_a(){
    	int i;
		for (i = 0; i < 112; i++){
		printf("_");
		}
	}
	void sublinha_b(){
    	int i;
		for ( i = 0; i < 112; i++){
		printf("_");
		}
	}

	void cabec() {
		
    	system("cls");
    	linha();
    	printf(" NUCLEO SEGUROS ");
    	linha();
	}
	void abre_arquivo(){
		pcliente = fopen("cliente.txt", "r+b");
		if (pcliente == NULL){
			pcliente = fopen("cliente.txt", "w+b");
		}
	}
	
	int calcular_idade(int nasc) {
    	return 2024 - nasc;
	}

float calcula_plano(){
	float valor_plano;
	int i;
	
	if(strcmp(cliente_aux.tipo_plano,"Ouro") ==0){
		valor_plano= 300.00;
	}
	else if(strcmp(cliente_aux.tipo_plano,"Diamante") ==0){
		valor_plano= 400.00;
	}
	else if(strcmp(cliente_aux.tipo_plano,"Prata") ==0){
		valor_plano= 200.00;
	}
	else if(strcmp(cliente_aux.tipo_plano,"Esmeralda") ==0){
		valor_plano= 500.00;
	}

	cliente_aux.valor_plano=valor_plano;
	 
		// Aplica ajustes de valor conforme a idade e sexo do titular
    	if ((cliente_aux.idade_titular >= 13) && (cliente_aux.idade_titular < 35) && (cliente_aux.sexo == 1)) {
        	cliente_aux.valor_plano *= 1.30; 
    	}
		else if (cliente_aux.idade_titular < 13) {
        	cliente_aux.valor_plano *= 0.70;
    	}
		else if (cliente_aux.idade_titular >= 60) {
        	cliente_aux.valor_plano *= 1.40;
    	}

    // Aplica ajustes de valor para cada dependente
    for (i = 0; i < cliente_aux.qtd_dependentes; i++) {
        cliente_aux.valor_plano_terceiro[i] = valor_plano;

        if ((cliente_aux.idade_terceiro[i] >= 13) && (cliente_aux.idade_terceiro[i] < 35) && (cliente_aux.sexo_terceiro[i] == 1)) {
            cliente_aux.valor_plano_terceiro[i] *= 1.30; 
        }
		else if (cliente_aux.idade_terceiro[i] < 13) {
            cliente_aux.valor_plano_terceiro[i] *= 0.70;
        }
		else if (cliente_aux.idade_terceiro[i] >= 60) {
            cliente_aux.valor_plano_terceiro[i] *= 1.40;
        }
    }

    // Calcula o valor total do plano com todos os ajustes
    //float valor_total = cliente_aux.valor_plano; 
    for (i = 0; i < cliente_aux.qtd_dependentes; i++) {
        cliente_aux.valor_plano += cliente_aux.valor_plano_terceiro[i];
    }	

    // Aplica desconto de 20% se houver mais de um dependente
    if (cliente_aux.qtd_dependentes > 1) {
        cliente_aux.valor_plano *= 0.80;
    }

    return cliente_aux.valor_plano;
}

	void Planos(){
  		char ouro[5]="Ouro";
  		char trezentos[9]="R$300,00";
  		char diamante[9]="Diamante";
  		char quatrocentos[9]="R$400,00";
  		char prata[6]="Prata";
  		char duzentos[9]="R$200,00";
  		char esmeralda[10]="Esmeralda";
		char quinhentos[9]="R$500,00";
		int resp;
		int i;
		float valor_antes_dep;
  		printf("\n\nTipo de Plano de Saude           Valor Base para o Seguro\n");
  		printf("------------------------------------------------------------\n");
		printf("[1]%-10s %30s\n",ouro, trezentos);
  		printf("[2]%-10s %30s\n",diamante, quatrocentos);
		printf("[3]%-10s %30s\n",prata, duzentos);
 		printf("[4]%-10s %30s\n",esmeralda, quinhentos);
 		printf("\nQual o plano que desejas:");
 		scanf("%d",&resp);
			switch(resp){
  				case 1: 
  					cliente_aux.valor_plano= 300.00;
  					strcpy(cliente_aux.tipo_plano, ouro);
  					valor_antes_dep= 300.00;
  					break;
  				case 2:
  					cliente_aux.valor_plano= 400.00;
  					strcpy(cliente_aux.tipo_plano, diamante);
  					valor_antes_dep= 400.00;
  					break;
  				case 3: 
  					cliente_aux.valor_plano= 200.00;
  					strcpy(cliente_aux.tipo_plano, prata);
  					valor_antes_dep= 200.00;
  					break;
  				case 4:
  					cliente_aux.valor_plano= 500.00;
  					strcpy(cliente_aux.tipo_plano, esmeralda);
  					valor_antes_dep= 500.00;
  					break;
  				default:
  					printf("\nPlano invalido!\n");
  					return;
			}
			//calcula_plano();
			float result_total=calcula_plano();
		
	printf("-------------------------------------\n");
    printf("O seu plano e %-5s no valor de R$%.2f\n",cliente_aux.tipo_plano, result_total);
    cliente_aux.valor_plano = result_total;
}
	
void inicializa_cliente_nulo() {
    memset(&cliente_nulo, 0, sizeof(Cliente));
}

int procura(int CPFp){
		int p;
		p = 0;
		rewind(pcliente);
		fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
		while (feof(pcliente)==0){
			if (cliente_aux.CPF_Titular == CPFp){
				return p;
			}
			else{
				fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
				p++;
			}
		}
	return -1;
}

void mostre(int pos){
	fseek(pcliente, pos*sizeof(Cliente), SEEK_SET);
	fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
	char sexo[5];
	if (cliente_aux.sexo==1){
		strcpy(sexo, "Fem");
	}
	else {
		strcpy(sexo, "Masc");
	}
	printf("\n\n");
	sublinha_a();
	printf("\nCPF    NOME    SEXO    FONE      EMAIL           IDADE    PLANO    DEPENDENTE    VALOR PLANO    VENCIMENTO PLANO\n");
	sublinha_b();
	printf("\n");
	printf("\n%d    %s   %s     %s    %s %5d      %s         %d          R$%.2f       %d/%d/%d\n", 
                cliente_aux.CPF_Titular, cliente_aux.nome, sexo, cliente_aux.telefone, cliente_aux.email, 
                cliente_aux.idade_titular, cliente_aux.tipo_plano, cliente_aux.qtd_dependentes, cliente_aux.valor_plano, 
                cliente_aux.dia_vencimento,cliente_aux.mes_vencimento, cliente_aux.ano_vencimento);
	sublinha_b();
}

void Remover(){ 
	int cpf_Remover, conf, resp, posicao;
	
	do{ cabec();
		printf("\n\nRemover Cliente\n\n\n");
		printf("CPF: ");
		scanf("%d", &cpf_Remover);
		posicao = procura(cpf_Remover);
		
		if (posicao == -1){
			printf("\nCliente não encontrado!!\n");
		}else { 
			mostre(posicao);
			printf("\n\nDeseja remover o cliente(1-sim/0-nao): ");
			scanf("%d", &conf);
			if (conf == 1){ 
				fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
				fwrite( &cliente_nulo,sizeof(Cliente), 1, pcliente);
				printf("\n\nCliente removido com sucesso!");
			}
			else{
				printf("\nRemocao cancelada!");
			}
	}
	printf("\n\n\nDeseja remover outro(1-sim/0-nao)? ");
	scanf("%d", &resp);
	
	rewind(pcliente);
	} while (resp == 1);
}

void Cadastro(){ 
    int resp, ano;
    int dia, mes, i;
    do { 
        cabec();
        printf("\n\nCadastrar novo Cliente\n\n");
        printf("\nCPF (Somente numeros): ");
        scanf("%d", &cliente_aux.CPF_Titular);
	
        printf("\nNome: ");
        fflush(stdin);
        gets(cliente_aux.nome);

        printf("\nSexo (1-Fem/2-Masc): ");
        scanf("%d", &cliente_aux.sexo);

        printf("\nEmail: ");
        fflush(stdin);
        gets(cliente_aux.email);

        printf("\n Qual o dia do seu aniversario [DD]: ");
        scanf("%d", &dia);

        printf("\n Qual o mes do seu aniversario [MM]: ");
        scanf("%d", &mes);

        printf("\nAno de nascimento [AAAA]: ");
        scanf("%d", &ano);

        cliente_aux.idade_titular = calcular_idade(ano);

        printf("\nA sua idade e: %d\n", cliente_aux.idade_titular); 
        printf("\nTelefone: ");
        fflush(stdin);
        gets(cliente_aux.telefone);

        printf("\nQuantos dependentes voce tem (Ate 10!): ");
        scanf("%d", &cliente_aux.qtd_dependentes);
        
        for (i = 0; i < cliente_aux.qtd_dependentes; i++) {
        	printf("----------------------------------------------------------");
            printf("\n\nDigite o CPF do %do. dependente (Somente numeros): ", i+1);
            scanf("%d", &cliente_aux.CPF_Terceiro[i]);

            printf("\nNome do %do. dependente: ", i+1);
            fflush(stdin);
            gets(cliente_aux.nome_terceiro[i]);

            printf("\nSexo (1-Fem/2-Masc): ");
            scanf("%d", &cliente_aux.sexo_terceiro[i]);

            printf("\n Qual o dia do aniversario do %do. dependente [DD]: ", i+1);
            scanf("%d", &dia);

            printf("\n Qual o mes do seu aniversario do %do. dependente [MM]: ", i+1);
            scanf("%d", &mes);

            printf("\nAno de nascimento do %do. dependente [AAAA]: ", i+1);
            scanf("%d", &ano);

            cliente_aux.idade_terceiro[i] = calcular_idade(ano);
            printf("\nA idade do seu dependente %d e: %d\n", i+1, cliente_aux.idade_terceiro[i]); 
        }

        
        Planos();

        printf("\nDigite o dia do vencimento do plano [DD]: ");
        scanf("%d",&cliente_aux.dia_vencimento);

        printf("\nDigite o mes do vencimento do plano [MM]: ");
    	scanf("%d", &cliente_aux.mes_vencimento);

        printf("\nDigite o ano do vencimento do plano [AAAA]: ");
        scanf("%d", &cliente_aux.ano_vencimento);

        fseek(pcliente, 0, SEEK_END);
		fwrite(&cliente_aux, sizeof(Cliente), 1, pcliente);
        

        printf("\n\nCliente cadastrado com sucesso!\n\n");
        printf("\nDeseja cadastrar outro: (1-sim/0-nao)? ");
        scanf("%d", &resp);
    } while (resp == 1);
}

void Listagem_mes(){ 
		char sexo[5];
		int mes_list, resp;
		do{
		system("cls");
		cabec();
		printf("\n\nListagem por MES\n\n\n");
		printf("--------------------------------------------------------");
		printf("\nDigite o mes de vencimento do plano que deseja listar: ");
		scanf("%d", &mes_list);
		
		sublinha_a();
		printf("\nCPF    NOME    SEXO    FONE      EMAIL           IDADE    PLANO    DEPENDENTE    VALOR PLANO    VENCIMENTO PLANO\n");
		sublinha_b();
		rewind(pcliente);
		fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
			while (feof(pcliente)==0){
					if ((cliente_aux.mes_vencimento==mes_list) && (cliente_aux.CPF_Titular != 0)) {
						if(cliente_aux.sexo==1){
							strcpy(sexo, "Fem");
						}
						else {
							strcpy(sexo, "Masc");
						}
						printf("\n");
						printf("\n%d    %s   %s     %s    %s %5d      %s         %d          R$%.2f       %d/%d/%d\n",
           	    		cliente_aux.CPF_Titular, cliente_aux.nome, sexo, cliente_aux.telefone, cliente_aux.email,
           	    		cliente_aux.idade_titular, cliente_aux.tipo_plano, cliente_aux.qtd_dependentes, cliente_aux.valor_plano, 
                		cliente_aux.dia_vencimento,cliente_aux.mes_vencimento, cliente_aux.ano_vencimento);
					}
				fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
			}
			printf("\n\nDeseja procurar outro mes(1-sim/0-nao)? ");
			scanf("%d", &resp);			
		} while(resp ==1);
}

void Listagem_plano(){ 
		char sexo[5];
		int resp, r;
		char plano_list[10];
		char ouro[5]="Ouro";
  		char diamante[9]="Diamante";
  		char prata[6]="Prata";
  		char esmeralda[10]="Esmeralda";
		do{
		system("cls");
		cabec();
		printf("\n\nListagem por Tipo de PLANO SAUDE\n\n");
		printf("--------------------------------------------------------\n");
		printf("Digite o plano que deseja listar: ");
  		printf("\n---------------------------\n");
		printf("[1]%-10s\n",ouro);
  		printf("[2]%-10s\n",diamante);
		printf("[3]%-10s\n",prata);
 		printf("[4]%-10s\n",esmeralda);
 		printf("\nQual o plano que desejas:");
 		scanf("%d",&r);
			switch(r){
  				case 1: 
  					strcpy(plano_list, ouro);				
  					break;
  				case 2:  					
  					strcpy(plano_list, diamante);  				
  					break;
  				case 3:   					
  					strcpy(plano_list, prata); 					
  					break;
  				case 4:  					
  					strcpy(plano_list, esmeralda);					
  					break;
  				default:
  					printf("\nPlano invalido!\n");
  					return;
			}
		
		sublinha_a();
		printf("\nCPF    NOME    SEXO    FONE      EMAIL           IDADE    PLANO    DEPENDENTE    VALOR PLANO    VENCIMENTO PLANO\n");
		sublinha_b();
		rewind(pcliente);
		fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
			while (feof(pcliente)==0){ 
					if ((strcmp(cliente_aux.tipo_plano, plano_list) == 0) && (cliente_aux.CPF_Titular != 0)){
						if(cliente_aux.sexo==1){
							strcpy(sexo, "Fem");
						}
						else {
							strcpy(sexo, "Masc");
						}
						printf("\n");
						printf("\n%d    %s   %s     %s    %s %5d      %s         %d          R$%.2f       %d/%d/%d\n", 
           	    		cliente_aux.CPF_Titular, cliente_aux.nome, sexo, cliente_aux.telefone, cliente_aux.email, 
           	    		cliente_aux.idade_titular, cliente_aux.tipo_plano, cliente_aux.qtd_dependentes, cliente_aux.valor_plano, 
                		cliente_aux.dia_vencimento,cliente_aux.mes_vencimento, cliente_aux.ano_vencimento);				
					}
				fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
			}
			printf("\n\nDeseja procurar outro plano(1-sim/0-nao)? ");
			scanf("%d", &resp);			
		} while(resp ==1);
}

void Listagem(){ 
		char sexo[5];
		cabec();
		printf("\n\nListagem Geral\n\n\n");
		sublinha_a();
		printf("\nCPF    NOME    SEXO    FONE      EMAIL           IDADE    PLANO    DEPENDENTE    VALOR PLANO    VENCIMENTO PLANO\n");
		sublinha_b();
		rewind(pcliente);
		fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
		while (feof(pcliente)==0){ 
			
			if (cliente_aux.CPF_Titular != 0){
				if(cliente_aux.sexo==1){
					strcpy(sexo, "Fem");
				}
				else {
					strcpy(sexo, "Masc");
				}
				printf("\n");
				printf("\n%d    %s   %s     %s    %s %5d      %s         %d          R$%.2f       %d/%d/%d\n", 
                cliente_aux.CPF_Titular, cliente_aux.nome, sexo, cliente_aux.telefone, cliente_aux.email, 
                cliente_aux.idade_titular, cliente_aux.tipo_plano, cliente_aux.qtd_dependentes, cliente_aux.valor_plano, 
                cliente_aux.dia_vencimento,cliente_aux.mes_vencimento, cliente_aux.ano_vencimento);

				//mover o fread para fora do else
			}
			fread(&cliente_aux, sizeof(Cliente), 1, pcliente);
		}
		sublinha_b();
		printf("\nTecle enter para voltar ao menu...");
		getche();
	}

void Alterar(){
	int CPF_alt, conf, resp, posicao;
	int i, dia, mes, ano, nd;
	float valor_antes_dep;
	do{
		cabec();
		printf("\n\nAlteracao de cliente\n\n\n");
		printf("Digite o CPF do cliente que deseja alterar alguma informacao: ");
		scanf("%d", &CPF_alt);
		posicao = procura(CPF_alt); 
		if (posicao == -1)
			printf("\nCliente, nao encontrado!!");
		else{
			do{
				mostre(posicao);
				printf("\n\nDeseja alterar qual informacao do cliente? \n");
				printf("------------------------------------------------");
				printf("\n\n [1]- CPF\n");
				printf(" [2]- NOME\n");
				printf(" [3]- SEXO\n");
				printf(" [4]- TELEFONE\n");
				printf(" [5]- EMAIL\n");
				printf(" [6]- IDADE\n");
				printf(" [7]- DEPENDENTE\n");
				printf(" [8]- PLANO\n");
				printf(" [9]- VENCIMENTO DO PLANO\n");
				printf(" [0]- NAO QUERO ALTERAR\n");
				printf("------------------------------------------------\n");
				scanf("%d", &conf);
				switch(conf){
					case 1: 
						printf("\nNovo CPF(Somente numeros): ");
        				scanf("%d", &cliente_aux.CPF_Titular);
        				printf("\nCPF alterado com sucesso! \n\n");
						fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
						fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
        			case 2: 
        				printf("\nNovo NOME: ");
        				fflush(stdin);
        				gets(cliente_aux.nome);
        				printf("\nNome alterado com sucesso! \n\n");
        				fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
        			case 3:
        				printf("\nSEXO (1-Fem/2-Masc): ");
        				scanf("%d", &cliente_aux.sexo);
        				printf("\nSEXO alterado com sucesso! \n\n");
        				cliente_aux.valor_plano=calcula_plano();

        				fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
					case 4: 
						printf("\nNovo TELEFONE: ");
        				fflush(stdin);
        				gets(cliente_aux.telefone);
        				fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
					case 5:
						printf("\nEmail: ");
        				fflush(stdin);
        				gets(cliente_aux.email);
        				fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
					case 6:
						printf("\n Qual o dia do seu aniversario [DD]: ");
        				scanf("%d", &dia);

        				printf("\n Qual o mes do seu aniversario [MM]: ");
        				scanf("%d", &mes);

        				printf("\nAno de nascimento [AAAA]: ");
        				scanf("%d", &ano);

        				cliente_aux.idade_titular = calcular_idade(ano);
        				cliente_aux.valor_plano=calcula_plano();

						
						fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
					case 7:
						printf("\nQuantos dependentes voce tem (Ate 10!): ");
        				scanf("%d", &cliente_aux.qtd_dependentes);
        				for (i = 0; i < cliente_aux.qtd_dependentes; i++) {
        					printf("----------------------------------------------------------");
            				printf("\n\nDigite o CPF do %do. dependente (Somente numeros): ", i+1);
        			    	scanf("%d", &cliente_aux.CPF_Terceiro[i]);

       			    		printf("\nNome do %do. dependente: ", i+1);
            				fflush(stdin);
            				gets(cliente_aux.nome_terceiro[i]);

            				printf("\nSexo (1-Fem/2-Masc): ");
            				scanf("%d", &cliente_aux.sexo_terceiro[i]);

            				printf("\n Qual o dia do aniversario do %do. dependente [DD]: ", i+1);
            				scanf("%d", &dia);

            				printf("\n Qual o mes do seu aniversario do %do. dependente [MM]: ", i+1);
            				scanf("%d", &mes);

            				printf("\nAno de nascimento do %do. dependente [AAAA]: ", i+1);
            				scanf("%d", &ano);

            				cliente_aux.idade_terceiro[i] = calcular_idade(ano);
            				printf("\nA idade do seu dependente %d e: %d\n", i+1, cliente_aux.idade_terceiro[i]);                      	
						}
						

    					cliente_aux.valor_plano=calcula_plano();
						printf("\n--------------------------------------\n");
    					printf("O seu plano e %-5s no valor de R$%.2f\n",cliente_aux.tipo_plano, cliente_aux.valor_plano);
    					
						fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
					case 8:
						Planos();
						fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;	
					case 9:
						printf("\nDigite o dia do vencimento do plano [DD]: ");
                        scanf("%d",&cliente_aux.dia_vencimento);

                        printf("\nDigite o mes do vencimento do plano [MM]: ");
                        scanf("%d", &cliente_aux.mes_vencimento);

                        printf("\nDigite o ano do vencimento do plano [AAAA]: ");
                        scanf("%d", &cliente_aux.ano_vencimento);
                        
        				fseek(pcliente,posicao*sizeof(Cliente),SEEK_SET);
        				fwrite(&cliente_aux,sizeof(Cliente), 1,pcliente);
						mostre(posicao);
						break;
					case 0:
						printf("\n\nAlteracao cancelada!\n\n");
						break;
				}		
			} while(conf!=0);
		}
		
		printf("\n\nDeseja alterar outro cliente(1-sim/0-nao)? ");
		scanf("%d", &resp);
	}while (resp ==1);
}

int main() {
    int op;
		abre_arquivo();
		inicializa_cliente_nulo();
		
		do{ 
		cabec();
		printf("\n\nOpcoes: \n\n\n");
		printf(" 1- Cadastrar novo cliente\n\n");
		printf(" 2- Listagem Geral\n\n");
		printf(" 3- Alterar Cliente\n\n");
		printf(" 4- Remover Cliente\n\n");
		printf(" 5- Listagem por MES\n\n");
		printf(" 6- Listagem Listagem por Tipo de PLANO SAUDE\n\n");
		printf(" 0- Sair\n\n");
		linha();
		printf("\nInforme a opcao desejada: ");
		scanf("%d", &op);
			switch(op){ 
			case 1: Cadastro(); break;
			case 2: Listagem(); break;
			case 3: Alterar(); break;
			case 4: Remover(); break;
			case 5: Listagem_mes(); break;
			case 6: Listagem_plano(); break;
			case 0: fclose(pcliente); break;
			default: printf("\n\n\aOpcao invalida!");
			break;
			}
		} while (op != 0);
		return 0;
	}
