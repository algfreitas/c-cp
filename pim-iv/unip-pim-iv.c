#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    // INICIO DECLARACAO VARIAVEIS E FUNCOES
    // Declara login
    static const char usuarioID[]="usuario", passwd[]="passwd";
    char id[8], p[7];
    int n=1, x, y;
    //
    // Define tamanho max char
    #define MAX 256
    //
    // Dec dados para cadastro - tipo string
	char nome[MAX][100], cpf[MAX][100], telefone[MAX][100], numero[MAX][100], cep[MAX][100], email[MAX][100], rua[MAX][100], bairro[MAX][100], cidade[MAX][100], uf[MAX][100], dia_diag[MAX][100], mes_diag[MAX][100], dia_nascimento[MAX][100], mes_nascimento[MAX][100];
    // Dec dados para cadastro - tipo inteiro
    int comorbidade, ano_diag, ano_nascimento, ano_atual;
    //
    // Função - Recupera ano atual
    time_t data_ano;
    time(&data_ano);  
    struct tm *data = localtime(&data_ano);
    ano_atual = (data->tm_year+1900);
    // 
    // FIM DECLARACAO VARIAVEIS E FUNCOES
    //
    // Limpa a tela na execucao
    system("cls");
    //
    // INICIO LOGIN
    printf("%lu %lu:", strlen(id), strlen(usuarioID));

    do{
        puts("\nUsuario_ID:");
        scanf("%s", &id);
        fflush(stdout);

        puts("\nPasswd:");
        scanf("%s", &p);
        fflush(stdout);

        x=strcmp(id, usuarioID);
        y=strcmp(p, passwd);
        fflush(stdin);

        if(x==0 && y==0){
            printf("Login efetuado com sucesso \n");
            // LOGIN EFETIVADO - INICIO ROTINA CADASTRO            
            // INICIO CRIAÇÃO DE ARQUIVO PARA CADASTROS
            // Cria variável ponteiro para o arquivo
            FILE *pont_cad; 
            malloc(sizeof(pont_cad));             
	        // Abrindo o arquivo com tipo de abertura A
	        pont_cad = fopen("dados_cadastro.txt", "a");	
	        //testando se o arquivo foi realmente criado
	        if(pont_cad == NULL) {
	            puts("Erro na abertura do arquivo!");
	            return 1;
	        }
            // FIM CRIAÇÃO DE ARQUIVO PARA CADASTROS
            // INICIO CRIAÇÃO DE ARQUIVO DE RETORNO COMORBIDADE   
            // cria variável ponteiro para o arquivo
            FILE *pont_ret;
            malloc(sizeof(pont_ret));
	        // Abrindo o arquivo com tipo de abertura A
	        pont_ret = fopen("dados_retorno.txt", "a");	
	        // Testando se o arquivo foi realmente criado
	        if(pont_ret == NULL) {
	            puts("Erro na abertura do arquivo!");
	            return 1;
	        }
            // FIM CRIAÇÃO DE ARQUIVO DE RETORNO COMORBIDADES
            // INICIO ROTINA DE CADASTRO

            // Utilizano scanf para receber stdin parametrizado para finalizar apenas na quebra de linha, aceitar espaços nos tipos char
            // Uilizando fprintf para armazenar dados no arquivo (pont_cad)
            // Utilizando fflush para esvaziar buffer do scanf

            // Dados referentes ao paciente
            //
	        puts("Nome:\n");
	        scanf( "%[^\n]", &nome);
            fprintf(pont_cad, "Nome: " "%s\n", nome);
            fflush(stdin);

            puts("CPF - Apenas numeros:\n");            
            scanf( "%[^\n]", &cpf);
            fprintf(pont_cad, "CPF: " "%s\n", cpf);
            fflush(stdin);
            
            puts("Dia de nascimento - Formato: xx:\n");
            scanf(" %[^\n]", &dia_nascimento);

            puts("Mes de nascimento - Formato: xx:\n");
            scanf(" %[^\n]", &mes_nascimento);           
 
            puts("Ano de nascimento - Formato: xxxx:\n");
            scanf("%d", &ano_nascimento);

            fprintf(pont_cad, "Data de nascimento: " " %s/%s/%d\n", dia_nascimento, mes_nascimento, ano_nascimento);
            fflush(stdin);

            // Dados referentes ao contato
            //
            puts("e-Mail:\n");
            scanf( "%[^\n]", &email); 
            fprintf(pont_cad, "e-Mail: " "%s\n", email);
            fflush(stdin);

            puts("Telefone - Apenas numeros:\n");
            scanf( "%[^\n]", &telefone); 
            fprintf(pont_cad, "Telefone: " "%s\n", telefone);
            fflush(stdin);

            // Dados referentes ao endereco
            //
            puts("Rua:\n");
            scanf( "%[^\n]", &rua);  
            fprintf(pont_cad, "Rua: " "%s\n", rua); 
            fflush(stdin);

            puts("Numero - Apenas numeros:\n");
            scanf( "%[^\n]", &numero);
            fprintf(pont_cad, "Numero: " "%s\n", numero);
            fflush(stdin);

            puts("Bairro:\n");
            scanf( "%[^\n]", &bairro);  
            fprintf(pont_cad, "Bairro: " "%s\n", bairro);  
            fflush(stdin);

            puts("Cidade:\n");
            scanf( "%[^\n]", &cidade); 
            fprintf(pont_cad, "Cidade: " "%s\n", cidade); 
            fflush(stdin);

            puts("UF:\n");
            scanf( "%[^\n]", &uf);
            fprintf(pont_cad, "UF: " "%s\n", uf);
            fflush(stdin);

            puts("CEP - Apenas numeros:\n");
            scanf( "%[^\n]", &cep);
            fprintf(pont_cad, "CEP: " "%s\n", cep);
            fflush(stdin);

            // Dados referentes ao diagnostico
            //
            puts("Dia do diagnostico - Formato: xx:\n");
            scanf(" %[^\n]", &dia_diag);

            puts("Mes do diagnostico - Formato: xx:\n");
            scanf(" %[^\n]", &mes_diag);           

            puts("Ano do diagnostico - Formato: xxxx:\n");
            scanf("%d", &ano_diag);

            fprintf(pont_cad, "Data do diagnostico: " " %s/%s/%d\n", dia_diag, mes_diag, ano_diag);
            fflush(stdin);
            //
            // Verifica se há comorbidade e ou grupo de risco:
            //
            // Se comorbidade for igual a zero e idade (ano_atual - ano_nascimento) menor que 65:
            // Grava (pont_cad), informando não haver comorbidade e não pertencer ao grupo de risco
            // Ignora (pont_ret)
            //
            // Se comorbidade for igual a zero e idade (ano_atual - ano_nascimento) maior que 65:
            // Grava (pont_cad), informando não haver comorbidade 
            // Grava (pont_ret) Informando pertencer ao grupo de risco
            // 
            // Se comorbidade for maior que zero ou menor ou igual a cinco e se idade (ano_atual - ano_nascimento) for menor que 65:
            // Grava informações referentes a comorbidade e a não pertencer ao grupo de risco (pont_cad)
            // Grava dados do paciente para retorno (pont_ret)
            // 
            // Se comorbidade for maior que zero ou menor ou igual a cinco e se idade (ano_atual - ano_nascimento) for maior que 65:
            // Grava informações referentes a comorbidade e pertencer ao grupo de risco (pont_cad)
            // Grava dados do paciente para retorno (pont_ret)
            // 
            // Se comorbidade for maior que cinco, retorna valor inválido
            // 
            puts("Selecione o tipo de comorbidade:\n \n \t 0 = Nenhuma, 1 = Diabetes, 2 = Obesidade, 3 = Hipertensao, 4 = Tuberculose, 5 = Outros:\n");

            scanf("%d", &comorbidade);

             if ( (comorbidade == 0) && (ano_atual - ano_nascimento < 65) ) {
                    fprintf(pont_cad, "Não apresenta comorbidades - Não pertence ao grupo de risco\n \n");
                    fflush(stdin);
             }
             else if ( (comorbidade == 0) && (ano_atual - ano_nascimento > 65) ) {
                    fprintf(pont_cad, "Não apresenta comorbidades - Pertence ao grupo de risco\n \n");
                    fflush(stdin);
             }
             else if ( (comorbidade > 0) && (comorbidade <= 5) && (ano_atual - ano_nascimento < 65) ) {
                    fprintf(pont_cad, "Apresenta comorbidades - Não pertence ao grupo de risco\n \n");
                    fprintf(pont_ret, "%s\n", cep);
                    fprintf(pont_ret, "%d\n \n", ano_atual - ano_nascimento);     
                    fflush(stdin);        
             }
             else if ( (comorbidade > 0) && (comorbidade <= 5) && (ano_atual - ano_nascimento > 65) ) {
                    fprintf(pont_cad, "Apresenta comorbidades - Pertence ao grupo de risco\n \n");
                    fprintf(pont_ret, "%s\n", cep);
                    fprintf(pont_ret, "%d\n \n", ano_atual - ano_nascimento);
                    fflush(stdin);
             }
             else if ( (comorbidade > 5)  ) {
                 puts("Valor invalido %d\n");  
                 fflush(stdin);               
             }
            //
            // Finaliza fluxo, limpa buffer e limpa tela 
            //
        	printf("Dados gravados com sucesso, tecle ENTER para finalizar");
	        fflush(stdin);
	        getch();
            system("cls");
	        return(0);
            //
            // FIM ROTINA CADASTRO
            // FIM CADASTRO - FINALIZAR SISTEMA
            // FECHAR ARQUIVOS DE CADASTRO E RETORNO COMORBIDADES
	        fclose(pont_cad);
            fclose(pont_ret);
        //
        // LOOP FALHA LOGIN - 3 TENTATIVAS
        }else {
            printf("\nLogin incorreto, Tente novamente.", 3-n);
            getchar();
            n++;}
        // FALHA LOGIN - NEGA ACESSO
        if(n>3){
            printf("\nAcesso negado, tente novamente");
            getchar();
        }
    // FALHA LOGIN - FINALIZA APLICAÇÃO
    }while (n<=3);

}
   