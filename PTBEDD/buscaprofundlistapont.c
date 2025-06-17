/* Ziviani - Projeto de Algoritmos
7.9 - Grafos usando listas de adjacências
Busca em Profundidade
*/
#include<stdlib.h>
#include<stdio.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   100
#define TRUE            1
#define FALSE           0

typedef int TipoValorVertice;
typedef int TipoValorAresta;
typedef struct TipoItem {
  TipoValorVertice Vertice;
  TipoValorAresta Aresta;
} TipoItem;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct TipoLista {
  TipoApontador Primeiro, Ultimo;
} TipoLista;
typedef struct TipoGrafo {
  TipoLista Adj[MAXNUMVERTICES + 1];
  TipoValorVertice NumVertices;
  TipoValorAresta NumArestas;
} TipoGrafo;
typedef short TipoValorTempo;
typedef enum {
  branco, cinza, preto
} TipoCor;

//short i;
//int FimListaAdj;
TipoGrafo Grafo; // Vetores ficam melhor fora da pilha
TipoValorTempo d[MAXNUMVERTICES + 1], t[MAXNUMVERTICES + 1];
TipoCor Cor[MAXNUMVERTICES+1];
short Antecessor[MAXNUMVERTICES+1];

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}  /* FLVazia */

char Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}  /* Vazia */

void Insere(TipoItem *x, TipoLista *Lista)
{ /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
}  /* Insere */

/*-- Entram aqui os operadores do Programa 6.2 --*/
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
             TipoValorAresta *Aresta, TipoGrafo *Grafo)
{ TipoItem x;
  x.Vertice = *V2;
  x.Aresta = *Aresta;
  Insere(&x, &Grafo->Adj[*V1]);
}  /* InsereAresta */

void FGVazio(TipoGrafo *Grafo)
{ short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++)
    FLVazia(&Grafo->Adj[i]);
}  /* FGVazio */

char ExisteAresta(TipoValorVertice Vertice1,
                TipoValorVertice Vertice2, TipoGrafo *Grafo)
{ TipoApontador Aux;
  char EncontrouAresta = FALSE;
  Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE) 
    { if (Vertice2 == Aux->Item.Vertice)
      EncontrouAresta = TRUE;
      Aux = Aux->Prox;
    }
  return EncontrouAresta;
}  /* ExisteAresta */

char ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}  /* ListaAdjVazia */

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro->Prox);
}  /* PrimeiroListaAdj */

void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj,
            TipoValorAresta *Aresta, TipoApontador *Prox,
            char *FimListaAdj)
{ /* --Retorna Adj apontado por Prox--*/
  *Adj = (*Prox)->Item.Vertice;
  *Aresta = (*Prox)->Item.Aresta;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL) *FimListaAdj = TRUE;
}  /* ProxAdj- */

void ImprimeLista(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) 
    { printf("%3d (%d)", Aux->Item.Vertice, Aux->Item.Aresta);
      Aux = Aux->Prox;
    }
}  /* ImprimeLista */

void ImprimeGrafo(TipoGrafo *Grafo)
{ short i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++) 
    { printf("Vertice%2d:", i);
      if (!Vazia(Grafo->Adj[i])) ImprimeLista(Grafo->Adj[i]);
      putchar('\n');
    }
}  /* ImprimeGrafo */

void VisitaDfs(TipoValorVertice u, TipoGrafo *Grafo, 
               TipoValorTempo* Tempo, TipoValorTempo* d, 
	       TipoValorTempo* t, TipoCor* Cor, short* Antecessor) 
{ char FimListaAdj;
  TipoValorAresta Peso;
  TipoApontador Aux; 
  TipoValorVertice v;
  
  Cor[u] = cinza;
  (*Tempo)++; 
  d[u] = (*Tempo);
  printf("Visita%2d Tempo descoberta:%2d cinza\n", u, d[u]);
  getchar();
  if (!ListaAdjVazia(&u, Grafo)) 
  { Aux = PrimeiroListaAdj(&u, Grafo);
    FimListaAdj = FALSE;
    while (!FimListaAdj) 
      { ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
        if (Cor[v] == branco) 
        { Antecessor[v] = u;
          VisitaDfs(v, Grafo, Tempo, d, t, Cor, Antecessor);
        }
      }
  }
  Cor[u] = preto; (*Tempo)++; t[u] = (*Tempo);
  printf("Visita%2d Tempo termino:%2d preto\n", u, t[u]);
  getchar();
} 

void BuscaEmProfundidade(TipoGrafo *Grafo)
{ TipoValorVertice x; TipoValorTempo Tempo;
  Tempo = 0;
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { Cor[x] = branco; Antecessor[x] = -1; }
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { if (Cor[x] == branco)
      VisitaDfs(x, Grafo, &Tempo, d, t, Cor, Antecessor);
    }
} 

int ciclo(TipoGrafo *Grafo) {
  TipoCor Cor[MAXNUMVERTICES + 1];
  TipoValorVertice u;

  for (u = 0; u < Grafo->NumVertices; u++)
    Cor[u] = branco;

  TipoValorAresta Peso;
  TipoValorVertice v;
  char FimListaAdj;
  TipoApontador Aux;

  for (u = 0; u < Grafo->NumVertices; u++) {
    if (Cor[u] == branco) {
      TipoValorVertice Pilha[MAXNUMVERTICES];
      int topo = -1;
      Pilha[++topo] = u;

      while (topo >= 0) {
        TipoValorVertice atual = Pilha[topo];

        if (Cor[atual] == branco) {
          Cor[atual] = cinza;
          Aux = PrimeiroListaAdj(&atual, Grafo);
        } else {
          Cor[atual] = preto;
          topo--;
          continue;
        }

        FimListaAdj = FALSE;
        while (!FimListaAdj) {
          ProxAdj(&atual, &v, &Peso, &Aux, &FimListaAdj);

          if (Cor[v] == cinza)
            return 1; 

          if (Cor[v] == branco)
            Pilha[++topo] = v;
        }
      }
    }
  }

  return 0;
}


/* ============================================================= */

int main() {
  TipoValorVertice V1, V2;
  TipoValorAresta A;
  TipoItem x;

  for (int teste = 1; teste <= 3; teste++) {
    printf("\n===== Teste %d =====\n", teste);
    if (teste == 1) {
      //com ciclo
      Grafo.NumVertices = 4;
      Grafo.NumArestas = 0;
      FGVazio(&Grafo);
      int arestas[][3] = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 0, 1},
        {2, 3, 1}
      };
      int NArestas = sizeof(arestas) / sizeof(arestas[0]);
      for (int i = 0; i < NArestas; i++) {
        V1 = arestas[i][0];
        V2 = arestas[i][1];
        A = arestas[i][2];
        Grafo.NumArestas++;
        InsereAresta(&V1, &V2, &A, &Grafo);
      }
    } else if (teste == 2) {
      //sem ciclo
      Grafo.NumVertices = 4;
      Grafo.NumArestas = 0;
      FGVazio(&Grafo);
      int arestas[][3] = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1}
      };
      int NArestas = sizeof(arestas) / sizeof(arestas[0]);
      for (int i = 0; i < NArestas; i++) {
        V1 = arestas[i][0];
        V2 = arestas[i][1];
        A = arestas[i][2];
        Grafo.NumArestas++;
        InsereAresta(&V1, &V2, &A, &Grafo);
      }
    } else if (teste == 3) {
      //com ciclo
      Grafo.NumVertices = 6;
      Grafo.NumArestas = 0;
      FGVazio(&Grafo);
      int arestas[][3] = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 0, 1},
        {3, 4, 1},
        {4, 5, 1}
      };
      int NArestas = sizeof(arestas) / sizeof(arestas[0]);
      for (int i = 0; i < NArestas; i++) {
        V1 = arestas[i][0];
        V2 = arestas[i][1];
        A = arestas[i][2];
        Grafo.NumArestas++;
        InsereAresta(&V1, &V2, &A, &Grafo);
      }
    }

    ImprimeGrafo(&Grafo);
    BuscaEmProfundidade(&Grafo);

    if (ciclo(&Grafo))
      printf("O grafo possui ciclo.\n");
    else
      printf("O grafo NAO possui ciclo.\n");
  }

  return 0;
}


