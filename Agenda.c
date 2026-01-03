#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct agenda{
    char nome[40];
    int idade;
    unsigned long int telefone;
    char cidade[40];

}pessoa[MAX];

void adicionar_contato(int registro){
    char dados[50];
    char city[40];		 ///
    printf("\tNome do contato: ");
    fgets(dados, sizeof(dados), stdin);//gravando dados e limpando a entrada de forma eficiente e segura
    dados[strcspn(dados, "\n")] = 0; // retirando o caracter enter evitando lixo
    strncpy(pessoa[registro].nome, dados, 40);/// e aqui sim nós copiamos o valor de uma para outra

    printf("\n\tIdade do contato: ");
    scanf("%d", &pessoa[registro].idade);
    int c;
    while((c = getchar()) != '\n' && c != EOF); //fazendo a limpeza do buffer para que o próximo dado possa ser armazenado
						//algo interessante a ressaltar é que na memória do programa o sistema
						//converte 25 para inteiro 25 (se a idade for 25) e armazena em 
						// &pessoa[registro].idade e no buffer de entrada(stdin) fica sobrando
						// o enter '\n', que se caso ele não for limpo o sistema irá pular 
						// a cidade devido esse "enter" estar no stdin ainda, deixando vazio

    printf("\n\tCidade do contato: ");
    fgets(city, sizeof(city), stdin);
    city[strcspn(city, "\n")] = 0;
    strncpy(pessoa[registro].cidade, city, 40);

    printf("\n\tTelefone do contato: ");
    scanf("%li", &pessoa[registro].telefone);
    
}
void mostrar_agenda(int qnt_contatos){
    int i;
    int contagem = 1;
    for(i=0; i < qnt_contatos; i++){
        printf("\n\tN do contato: %d", contagem++);
        printf("\n\tNome do contato: %s", pessoa[i].nome);
        printf("\n\tIdade do contato: %d", pessoa[i].idade);
        printf("\n\tTelefone do contato: %ld", pessoa[i].telefone);
        printf("\n\tCidade do contato: %s\n\n", pessoa[i].cidade);
    }
    printf("\n");
}

void listar_contato(int indice){
    printf("\n\tnome do contato %s", pessoa[indice].nome);
    printf("\n\tIdade do contato %d", pessoa[indice].idade);
    printf("\n\tTelefone do contato %ld", pessoa[indice].telefone);
    printf("\n\tCidade do contato %s\n", pessoa[indice].cidade); 
}

int pesquisar_contato(int qnt_contatos, char* nomebuscado){
    int i;
    for(i=0; i < qnt_contatos; i++){
        if(strcmp(nomebuscado, pessoa[i].nome) == 0){ //if true
            return i;
        }
    }
    return -1;
}

void alterar_contato(int indice){
    int idade;
    unsigned long int telefone;
    char cidade[50];
    char nome[40];
    char dados[50];

    printf("\tDigite o nome do contato: ");
    fgets(dados, sizeof(dados), stdin);
    dados[strcspn(dados, "\n")] = 0; 
    strncpy(pessoa[indice].nome, dados,39);//secure function

    printf("\tDigite a idade do contato: ");
    scanf("%d", &idade);
    pessoa[indice].idade = idade;
    

    printf("\tDigite o telefone do contato: ");
    scanf("%ld", &telefone);
    pessoa[indice].telefone = telefone; 
    int c;
    while((c = getchar()) != '\n' && c != EOF);//fazendo a limpeza do buffer para que o próximo dado possa ser armazenado


    printf("\tDigite o nome da cidade do contato: ");
    fgets(dados, sizeof(dados), stdin);
    dados[strcspn(dados, "\n")] = 0; 
    strncpy(pessoa[indice].cidade, dados, 40);
}

void menu(){
    printf("\n\n\tDigite -1- para mostrar agenda\n"
           "\tDigite -2- para adicionar contato\n"
           "\tDigite -3- para pesquisar contato\n"
           "\tDigite -4- para alterar um contato\n"
           "\tDigite -100- para fechar o programa\n\n");
}
int leitor(){
    int op;

    printf("\n\tDigite a sua opcao:\t");
    scanf("%d", &op);
    setbuf(stdin, NULL);

    return op;
}

int main(){

    char nome[MAX];
    int NRegistro = 0;
    int indice;
    int op;
    do{
        menu();
        op = leitor();
        switch (op)
        {
        case 1:
            mostrar_agenda(NRegistro);
            break;
        case 2:
            adicionar_contato(NRegistro++);
            break;
        case 3:
            printf("\ndigite o nome do contato\n");
            scanf("%[^\n]s", nome);
            setbuf(stdin, NULL);
            indice = pesquisar_contato(NRegistro, nome);
            if(indice >= 0 && indice <=99){
                listar_contato(indice);
            }else{
                printf("\nContato não existente\n");
                
            }
            break;
        case 4:
            printf("\n\tDigite o numero do contato [1-99]\n");
            scanf("%d", &indice);
            setbuf(stdin, NULL);
            indice-=1; //por conta do zero
            if(indice >= 0 && indice <=99){
                alterar_contato(indice);
            }else{
                printf("\n\tcontato inexistente\n");
            }   
        break;
        case 100:
            printf("\n\n\tsaindo do programa\n");
            break;
        default:
        printf("\n\tOpcao invalida!\n");
            break;
        }

    }while (op != 100);
    
    return 0;

