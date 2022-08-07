#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 500 // LIMITANDO O NUMERO DE CARACTERES DE ENTRADA

typedef struct arv {
  int info;
  struct arv* esq;
  struct arv* dir;
}TArv;

typedef TArv *PArv;

PArv cria_no(int c, PArv sae, PArv sad);
void imprimeIn (PArv a, int nivel);
PArv libera (PArv a);
PArv criar_arvore(char exp[],int recomeco);
void resultado(PArv p);



int main(void) {

  char exp_string[MAX];
  PArv no;

  printf("Digite a expressao: ");
  scanf("%[^\n]s",exp_string); // LEIO A ENTRADA POR TECLADO

  no = criar_arvore(exp_string, strlen(exp_string)-1); //  CHAMANDO A FUNCAO QUE CRIA A ARVORE

  printf("Arvore digitada:\n\n");
  imprimeIn(no,0); // CHAMANDO A FUNCAO QUE IMPRIME

  resultado(no); // NESTA FUNCAO, A ARVORE SERA "REGREDIDA" A UM UNICO ELEMENTO(VALOR)

  printf("\nA solucao da expressao eh %d.\n",no->info); // IMPRIMO O VALOR ENCONTRADO NO PONTEIRO 

  libera(no); // CHAMADA DA FUNCAO QUE LIBERA O NO

  return 0;
}


PArv cria_no(int c, PArv sae, PArv sad){ // FUNCAO QUE CRIA A ARVORE

  PArv p = (PArv)malloc(sizeof(TArv)); // ALOCA DINAMICAMENTE O NO RAIZ DA ARVORE
  p->info = c; // ATRIBUI A VALOR "c" PARA A INFORMACAO DO NO
  p->esq = sae;
  p->dir = sad;

return p;
}

void imprimeIn (PArv a, int nivel) { // FUNCAO QUE IMPRIME O NO DE FORMA RECURSIVA
  
  if (a!=NULL) {

    imprimeIn(a->dir, nivel+1);
    for(int i = 0; i < nivel; i++){
      printf("\t"); // ESTE PRINT FAZ COM QUE SE ACERTE O "NIVEL" DAS SUBARVORES, ISSO PORQUE SE TRATA DA IMPRESSAO HORIZONTAL
    }
    
    if(a->info == -2){
      printf("+\n"); // COMO NA IMPLEMENTACAO DA ARVORE EU ATRIBUI OS OPERADORES "+" E "-" IGUAIS A -2 E -1, RESPECTIVAMENTE, CASO ENCONTRE O -2, IMPRIMIREI O "+" E CASO -1, IMPRIMIREI O "-"

    } else if(a->info == -1){
      printf("-\n");

    } else {
    printf("%d\n", a->info); // CASO SIMPLISMENTE ENCONTRE O INTEIRO

    }
    imprimeIn(a->esq, nivel+1);
  }

}

PArv libera (PArv a){ // FUNCAO QUE LIBERA O NO DE FORMA RECURSIVA

  if (a!=NULL) {
    libera(a->esq); // LIBERA SAE
    libera(a->dir); // LIBERA SAD
    free(a); // LIBERA RAIZ

  }
  return NULL;

}

PArv criar_arvore(char exp[], int recomeco){

  int i;
  int j = recomeco; // "j" ASSUME O TAMANHO DA SUBSTRING (OU STRING- NO PRIMEIRO CASO) PARA PERCORRER DE FORMA RECURSIVA A PARTIR DO NOVO RECOMECO
  int soma = 0;
  int cont=0;
  char sinal;
  int chave = 0; // A CHAVE RECEBERA 1 QUANDO NAO HOUVER MAIS SINAIS PARA SEREM LIDOS. E QUANDO ISSO ACONTECE, JOGAREI O QUE ESTA SENDO LIDO NA STRING DIRETO PARA O ULTIMO FILHO A ESQUERDA

  PArv no;

    while(j != 0){ // ESSE WHILE LE OS ELEMENTOS DAS SUBSTRINGS ATE ENCONTRAR UM OPERADOR. AO ENCONTRAR UM OPERADOR, O VALOR DA VARIAVEL "sinal" MUDARA E EU COLOCAREI ESTE VALOR DIRETO NO NO

      if(exp[j] == '+'){
        sinal = -2;
        cont++;
        break; // CASO ENCONTRE UM SINAL, O BREAK PARARA O LACO WHILE PARA QUE SEJA LIDO OS ELEMENTOS A DIREITA DA STRING
      }

      else if(exp[j] == '-'){
        sinal = -1;
        cont++;
        break; // ANALOGO AO ESCRITO ACIMA
      }

      j--;
      cont++; // ESTE CONTADOR TAMBEM ESTA PRESENTE NOS CASOS DOS "if" ACIMA PARA SABER QUANTO EU DEVO RETROCEDER PARA LER NOVAMENTE A STRING, SENDO ESSA LEITURA DE FORMA RECURSIVA

    }

    if(j==0){ // SE ESSA CONDICAO FOR VERDADEIRA, QUER DIZER QUE NAO HA MAIS SINAIS PARA SEREM LIDOS E DECREMENTAREI 1 DE j, PARA O LACO FOR ABAIXO
      j--;
      chave = 1;
    }

    for( i = j+1 ; exp[i] != '\0' && exp[i] != '+' && exp[i] != '-' ; i++){

      if(exp[i] != ' '){
        soma = 10*soma + (exp[i] - '0'); // ISSO FAZ COM QUE EU "ARMAZENE" A SOMA SEMPRE, POIS O "10*soma" SEMPRE FARA COM QUE EU AUMENTE UMA CASA INTEIRA
      }
    }

    if(chave == 1){ // ESSA CONDICAO SOMENTE SERA VERDADEIRA, CASO NAO EXISTA MAIS OPERADORES NA LEITURA DA STRING.
      no = cria_no(soma,NULL,NULL);
      return no;
    }

    no = cria_no(sinal,NULL,cria_no(soma,NULL,NULL)); // 

    int reco = recomeco - cont; // A PARTIR DAQUI VOU PERCORRER A STRING NOVAMENTE. A VARIAVEL "reco", ARMAZENA O NUMERO EM QUE EU TOMAREI COMO PARTIDA NA LEITURA DA STRING INICIAL

    no->esq = criar_arvore(exp, reco); // AQUI EH ONDE ENTRA A RECURSIVIDADE

  return no;
}

void resultado(PArv p){ // ESTA FUNCAO "regride" A ARVORE PARA APENAS UM ELEMENTO INTEIRO. MAS SIM, ELA PERCORRE TODA ARVORE.

  if( p != NULL){ // CONDICAO DE PARADA FAZ COM QUE O ULTIMO ELEMENTO A ESQUERDA SEJA ANALISADO E UM "limite" PARA PERCORRER NA ARVORE

    resultado(p->esq); // CHAMADA RECURSIVA DA FUNCAO

    if(p->info == -2){ // COMO DEFINI QUE O SINAL "+" EH IGUAL AO VALOR NUMERICO -2, ENTAO SE ALGUM NO TIVER O CONTEUDO DE -2, SABEREI QUE ESSE NO EH PAI E FAREI A SOMA DO SEU FILHO A ESQUERDA COM O SEU FILHO A DIREITA
    p->info = p->esq->info + p->dir->info;
    }

    if(p->info == -1){ // ANALOGO AO CASO ACIMA, MAS FARIA A SUBTRACAO DOS FILHOS
    p->info = (p->esq->info - p->dir->info);
    }

  }
}