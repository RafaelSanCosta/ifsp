#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//estrutura do nó
typedef struct A_no{
    int cpf;
    char nome[50];
    struct A_no *esq, *dir;
} A_no;

//struct para armazenar o valor raiz da arvore
typedef struct{
    A_no *raiz;
} Arvore;

//função pra inserir na arvore
A_no* inserir(A_no *raiz, char *nome, int cpf){
    //caso o nó passado esteja vazio
    if(raiz == NULL){
        //aloca memoria
        A_no *novo = (A_no*)malloc(sizeof(A_no));
        //copia nome passado pro no
        strcpy(novo->nome, nome);
        novo->cpf = cpf;
        //seta no esquerda e direita nulos
        novo->esq = NULL;
        novo->dir = NULL;
        //mensagem de confirmação de inserção
        printf("Inseriu %s %d\n",novo->nome, novo->cpf);
        return novo;
    } else {
        //caso nao
        //pra manter ordenado pelo cpf
        //caso o cpf passado seja menor que o do no atual, vai pra esquerda
        if (cpf < raiz->cpf){
            //passa como retorno, pra não ter erro e ficar num loop infinito
            raiz->esq = inserir(raiz->esq, nome, cpf);
        } 
        else if(cpf > raiz->cpf) {
            //caso maior vai pra direita
            raiz->dir = inserir(raiz->dir, nome, cpf);
        }
        //se for igual não faz nada, nao insere duplicados
    }
    return raiz;
}

//raiz e remove buscando pelo cpf
A_no* remover_No(A_no *raiz, int cpf){
    //caso a arvore esteja vazia, não faz nada
    if(raiz == NULL){
        return NULL;
    }

    //caso encontrou o cpf
    if(raiz->cpf == cpf){
        //armazena o nome a ser removido, no caso do no ter dois filhos
        //como ele é "subtituido" e oq substitui é removido
        char nome_removido[50];
        strcpy(nome_removido, raiz->nome);
        //caso não tenha filho, seja uma folha
        if(raiz->esq == NULL && raiz->dir == NULL){
            //confirmação da remoção
            printf("Removeu %s %d\n",nome_removido, cpf);
            free(raiz);//morre
            return NULL;//e retorna nulo pro no(pai) q apontava pra ele
        }
        //pra caso tenha filho na direita e na esquerda não
        else if (raiz->esq == NULL) {
            A_no *temp = raiz->dir; //para armazenar o nó filho
            printf("Removeu %s %d\n",nome_removido, cpf);
            free(raiz); //mata
            return temp; //agr o pai do nó removido aponta para o filho da direita
        }
        //o oposto do ultimo, filho na esq e dir nao
        else if (raiz->dir == NULL) {
            A_no *temp = raiz->esq;
            printf("Removeu %s %d\n",nome_removido, cpf);
            free(raiz);
            return temp;//aqui acontece a mesma coisa, sóq com o filho da esquerda
        } 
        else
        {
            //aqui é caso o nó tenha dois filhos
            //a lógica é:
            //procurar o nó mais na esquerda possível, do nó a direita doq está sendo removido
            //assim o nó continua sendo pai, mas o dados agr serão os do nó com cpf sucessor ao dele(removido)
            
            //no q vai suceder o pai de dois filhos/nos removido
            //pra direita por conta de ordem
            A_no *sucessor = raiz->dir;
            while(sucessor != NULL && sucessor->esq != NULL){
                //enquanto ele não for nulo e tiver no na esquerda
                //ele vai apontar pro no a esquerda
                //pra esquerda pq é menor doq o maior q o pai(se tiver)
                sucessor = sucessor->esq;
            }

            //copia os dados do sucessor para o no pai
            raiz->cpf = sucessor->cpf;
            strcpy(raiz->nome, sucessor->nome);

            //chama recursivamente agr pra direita do no a ser removido
            //os dados a serem removidos foram substituidos pelo sucessor
            //então os dados do sucessor(original, antes da cópia) devem ser removidos
            raiz->dir = remover_No(raiz->dir, sucessor->cpf);
        }
    } else {
        //caso seja menor vai pra esquerda
        if(cpf < raiz->cpf){
            raiz->esq = remover_No(raiz->esq, cpf);
        } 
        //caso maior direita
        if(cpf > raiz->cpf) {
            raiz->dir = remover_No(raiz->dir, cpf);
        }
    }
    return raiz;
}

//busca pelo cpf e imprime a pessoa
void buscar(A_no *raiz, int cpf){
    if(raiz == NULL){
        //caso esteja vazio, ou não encontre o cpf
        printf("CPF %d nao localizado\n",cpf);
        return;//pra sair
    }

    //se for igual
    if(raiz->cpf == cpf){
        //imprime
        printf("Encontrou: %s %d\n",raiz->nome, raiz->cpf);
    } else {
        //caso seja menor, vai pra esquerda
        if(cpf < raiz->cpf){
            buscar(raiz->esq, cpf);
        } 
        //caso maior vai pra direita
        if(cpf > raiz->cpf) {
            buscar(raiz->dir, cpf);
        }
    }
}

//imprime todas as pessoas
void listar(A_no *raiz){
    //se for nulo acaba
    if(raiz != NULL){
        //começa indo pra esquerda, pra ser ordenado
        listar(raiz->esq);
        //imprime
        printf("%s %d\n",raiz->nome, raiz->cpf);
        //depois vai para a direita
        listar(raiz->dir);
    }
}

//chamada após o loop, percorre toda a arvore liberando a memória consumida por cada nó
void liberarMemoriaArvore(A_no *raiz){
    if (raiz == NULL){
        return;
    }
    
    //vai até o final na esquerda
    liberarMemoriaArvore(raiz->esq);
    //e então na direita
    liberarMemoriaArvore(raiz->dir);

    //e libera a memoria
    free(raiz);
}

// Função auxiliar pra leitura bem definida
//faz uma parte doq o sget faz
int ler_linha_limpa(char* buffer, int tamanho_buffer) {
    if (fgets(buffer, tamanho_buffer, stdin)) {
        //aqui remove os \n
        buffer[strcspn(buffer, "\n")] = '\0';
        return 1; // Sucesso
    }
    return 0; // Falha
}

int main(){

    //criação da arvore
    Arvore arv;
    arv.raiz = NULL;
    //sempre que pedir um nó como parametro, vamos passar a raiz dele

    //variaveis pra armazenar conteúdo escrito
    char linha_entrada[100];
    //após seperado, aqui fica armazenado um char, para entrar fazer tal função dependendo do conteúdo
    char chamaFunc = ' ';
    //fica armazenado o nome a ser inserido
    char nome_temp[50];
    //e aqui o cpf a ser inserido, ou buscado, ou removido
    int cpf_temp;

    //enquanto chamaFunc não for S, continua rodando
    while (chamaFunc != 's' && chamaFunc != 'S')
    {
        //aqui recebe o comando do usuário
        if(fgets(linha_entrada, sizeof(linha_entrada),stdin) != NULL) {
            //armazena o comando em linha_entrada
            linha_entrada[strcspn(linha_entrada, "\n")] = '\0';
            if(strlen(linha_entrada) == 0){
                continue;//isso ignora linhas vazias
                //tava com muitos problemas e uma das soluções que encontrei foi essa
            }

            //pega apenas o valor do char, e declara pra função chamaFunc
            if (sscanf(linha_entrada, " %c", &chamaFunc) == 1) { // Espaço antes de %c consome newlines/espaços anteriores
                switch (chamaFunc) {
                    case 'i':
                    case 'I':
                        // %*c ignora o caractere de comando já lido, o espaço consome o espaço após 'i'
                        //%49 vira nome_temp e %d vira cpf_temp
                        if (sscanf(linha_entrada, "%*c %49[^;];%d", nome_temp, &cpf_temp) == 2) {
                            arv.raiz = inserir(arv.raiz, nome_temp, cpf_temp);
                        } else {
                            printf("inserir deu erro\n");
                            //caso dê erro na inserção
                        }
                        break;
                    case 'r':
                    case 'R':
                        //aqui pega apenas o cpf
                        if (sscanf(linha_entrada, "%*c %d", &cpf_temp) == 1) {
                            arv.raiz = remover_No(arv.raiz, cpf_temp);
                        } else {
                            printf("remove deu erro\n");
                            //caso de erro
                        }
                        break;
                    case 'b':
                    case 'B':
                        //mesma lógica aplicada ao remover
                        if (sscanf(linha_entrada, "%*c %d", &cpf_temp) == 1) {
                            buscar(arv.raiz, cpf_temp);
                        } else {
                            printf("busca deu erro\n");
                            //caso de erro
                        }
                        break;
                    case 'l':
                    case 'L':
                        //exibe a arvore completamente e ordenadamente
                        listar(arv.raiz);
                        break;
                    case 's':
                    case 'S':
                        // Sai do loop
                        break; 
                    default:
                        printf("Opcao invalida\n"); 
                        //caso não seja digitado nenhum dos comandos
                        break;
                }
            } else {
                //caso de erro na hora de dividir a string ou declarar um valor para chamaFunc
                printf("Erro ao dividir a string. Formato esperado: <char> <nome_str>;<cpf_int>\n");
                //exibe o que foi lido do comando do usuário
                printf("Linha lida: '%s'\n", linha_entrada);
            }
        } else {
            //erro ao ler o comando do usuário
            printf("Erro ao ler a entrada\n");
        }
    }
    //sai do loop
    //libera memória
    liberarMemoriaArvore(arv.raiz);
    //seta a raiz como nula manualmente por ser uma boa prática
    arv.raiz = NULL;
    //declara encerramento
    printf("Programa encerrado, memoria liberada");
    
    return 0;
}