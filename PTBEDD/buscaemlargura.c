  /* Ziviani - Projeto de Algoritmos
  Busca em Largura com listas de adjacência
  /* 16/04/03 - Ubu */

  #include <stdio.h>
  #include <stdlib.h>
  #include <limits.h>

  /* Implementacao TAD Grafo com listas/apontadores */

  #define MAXNUMVERTICES  100
  #define MAXNUMARESTAS   100
  #define FALSE           0
  #define TRUE            1
  #define INFINITO        INT_MAX

  /*--Entram aqui os tipos do Programa 7.4 --*/
  typedef int TipoValorVertice;
  typedef int TipoPeso;
  typedef struct TipoItem {
    TipoValorVertice Vertice;
    TipoPeso Peso;
  } TipoItem;

  typedef struct TipoCelula* TipoApontador;
  typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
  } TipoCelula;
  typedef struct TipoLista {
    TipoApontador Primeiro, Ultimo;
  } TipoLista;
  typedef struct TipoFila {
    TipoApontador Frente, Tras;
  } TipoFila;
  typedef struct TipoGrafo {
    TipoLista Adj[MAXNUMVERTICES + 1];
    TipoValorVertice NumVertices;
    int NumArestas;
  } TipoGrafo;
  typedef short  TipoValorTempo;
  typedef enum {
    branco, cinza, preto
  } TipoCor;

  int i, NArestas;
  short FimListaAdj;
  TipoValorVertice V1, V2, Adj;
  TipoPeso Peso;
  TipoGrafo Grafo; // Global, só porque pode ser grande
  TipoValorVertice NVertices;
  TipoItem x;

  /*--Entram aqui os operadores do Programa 2.4--*/
  void FLVazia(TipoLista *Lista)
  { Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
  } 

  short ListaVazia(TipoLista Lista)
  { return (Lista.Primeiro == Lista.Ultimo);
  }

  void Insere(TipoItem *x, TipoLista *Lista)
  { /*-- Insere depois do ultimo item da lista --*/
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
  }

  /* -- Entram aqui os operadores do Programa 2.19 --*/
  void FFVazia(TipoFila *Fila)
  { Fila->Frente = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
  }

  short FilaVazia(TipoFila Fila)
  { return (Fila.Frente == Fila.Tras);
  }

  void Enfileira(TipoItem x, TipoFila *Fila)
  { Fila->Tras->Prox =(TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
  }

  void Desenfileira(TipoFila *Fila, TipoItem *Item)
  { TipoApontador q;
    if (FilaVazia(*Fila)) 
    { printf(" Erro   fila esta  vazia\n");
      return;
    }
    q = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    *Item = Fila->Frente->Item;
    free(q);
  }  

  void ImprimeFila(TipoFila Fila)
  { TipoApontador Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL) 
      { printf("%3d (%d)", Aux->Item.Vertice, Aux->Item.Peso);
        Aux = Aux->Prox;
      }
  }  

  /*-- Entram aqui os operadores do Programa 7.2 --*/
  void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
              TipoPeso *Peso, TipoGrafo *Grafo)
  { TipoItem x;
    x.Vertice = *V2;
    x.Peso = *Peso;
    Insere(&x, &Grafo->Adj[*V1]);
  }

  void FGVazio(TipoGrafo *Grafo)
  { short i;
    for (i = 0; i <= Grafo->NumVertices - 1; i++)
      FLVazia(&Grafo->Adj[i]);
  }

  short ExisteAresta(TipoValorVertice Vertice1,
            TipoValorVertice Vertice2, TipoGrafo *Grafo)
  { TipoApontador Aux;
    short EncontrouAresta = FALSE;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while (Aux != NULL && EncontrouAresta == FALSE) 
      { if (Vertice2 == Aux->Item.Vertice)
          EncontrouAresta = TRUE;
        Aux = Aux->Prox;
      }
    return EncontrouAresta;
  }  

  short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
  { return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
  }

  TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
  { return (Grafo->Adj[*Vertice].Primeiro->Prox);
  }  

  void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj,
              TipoPeso *Peso, TipoApontador* Prox, short *FimListaAdj)
  {  /* --Retorna Adj apontado por Prox--*/
    *Adj = (*Prox)->Item.Vertice;
    *Peso = (*Prox)->Item.Peso;
    *Prox = (*Prox)->Prox;
    if (*Prox == NULL)
      *FimListaAdj = TRUE;
  }

  void ImprimeLista(TipoLista Lista)
  { TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL) 
      { printf("%d (%d)  ", Aux->Item.Vertice, Aux->Item.Peso);
        Aux = Aux->Prox;
      }
  } 

  void ImprimeGrafo(TipoGrafo *Grafo)
  { int i;
    for (i = 0; i <= Grafo->NumVertices - 1; i++) 
      { printf("Vertice %2d: ", i);
        if (!ListaVazia(Grafo->Adj[i]))
          ImprimeLista(Grafo->Adj[i]);
        putchar('\n');
      }
  } 

  void VisitaBfs(TipoValorVertice u, TipoGrafo *Grafo, 
                int *Dist, TipoCor *Cor, int *Antecessor)
  { TipoValorVertice v;
    TipoApontador Aux;
    short FimListaAdj;
    TipoPeso Peso;
    TipoItem Item;
    TipoFila Fila;
    
    Cor[u] = cinza;
    Dist[u] = 0;
    FFVazia(&Fila);
    Item.Vertice = u;
    Item.Peso = 0;
    Enfileira(Item, &Fila);
    printf("Visita origem%2d cor: cinza F:", u);
    ImprimeFila(Fila);
    getchar();
    while (!FilaVazia(Fila)) 
    { Desenfileira(&Fila, &Item);
      u = Item.Vertice;
      if (!ListaAdjVazia(&u, Grafo)) 
      { Aux = PrimeiroListaAdj(&u, Grafo);
        FimListaAdj = FALSE;
        while (FimListaAdj == FALSE) 
        { ProxAdj(&u, &v, &Peso, &Aux, &FimListaAdj);
          if (Cor[v] != branco)
              continue;
          Cor[v] = cinza;
          Dist[v] = Dist[u] + 1;
          Antecessor[v] = u;
          Item.Vertice = v;
          Item.Peso = Peso;
          Enfileira(Item, &Fila);
        }
      }
      Cor[u] = preto;
      printf("Visita%2d Dist%2d cor: preto F:", u, Dist[u]);
      ImprimeFila(Fila);
      getchar();
    }
  }  

  void BuscaEmLargura(TipoGrafo *Grafo, int *Antecessor)
  { TipoValorVertice x;
    int Dist[MAXNUMVERTICES + 1]; // Esses vetores podem ser globais, se forem grandes
    TipoCor Cor[MAXNUMVERTICES + 1];
    for (x = 0; x <= Grafo->NumVertices - 1; x++) 
      { Cor[x] = branco;
        Dist[x] = INFINITO;
        Antecessor[x] = -1;
      }
    for (x = 0; x <= Grafo->NumVertices - 1; x++) 
      { if (Cor[x] == branco)
        VisitaBfs(x, Grafo, Dist, Cor, Antecessor);
      }
  }  

  void ImprimeCaminho(int s, int v, int *Antecessor)
{
  if (s == v)
    printf("%d", s);
  else if (Antecessor[v] == -1)
    printf("Nao existe caminho de %d para %d\n", s, v);
  else {
    ImprimeCaminho(s, Antecessor[v], Antecessor);
    printf(" -> %d", v);
  }
}


  /* ============================================================= */

  int main(int argc, char *argv[])
{
  int Dist[MAXNUMVERTICES + 1];
  TipoCor Cor[MAXNUMVERTICES + 1];
  int Antecessor[MAXNUMVERTICES + 1];

 
  printf("==== GRAFO 1 ====\n");
  NVertices = 5;
  NArestas = 5;
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);

  InsereAresta(&(int){0}, &(int){1}, &(int){1}, &Grafo);
  InsereAresta(&(int){1}, &(int){0}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){0}, &(int){2}, &(int){1}, &Grafo);
  InsereAresta(&(int){2}, &(int){0}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){1}, &(int){3}, &(int){1}, &Grafo);
  InsereAresta(&(int){3}, &(int){1}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){2}, &(int){3}, &(int){1}, &Grafo);
  InsereAresta(&(int){3}, &(int){2}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){3}, &(int){4}, &(int){1}, &Grafo);
  InsereAresta(&(int){4}, &(int){3}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  ImprimeGrafo(&Grafo);
  BuscaEmLargura(&Grafo, Antecessor);
  
  printf("\nCaminhos GRAFO 1:\n");
  ImprimeCaminho(0, 4, Antecessor); printf("\n");  
  ImprimeCaminho(0, 3, Antecessor); printf("\n");  
  ImprimeCaminho(0, 2, Antecessor); printf("\n");  

  
  printf("\n==== GRAFO 2 ====\n");
  NVertices = 6;
  NArestas = 6;
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);

  InsereAresta(&(int){0}, &(int){1}, &(int){1}, &Grafo);
  InsereAresta(&(int){1}, &(int){0}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){0}, &(int){2}, &(int){1}, &Grafo);
  InsereAresta(&(int){2}, &(int){0}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){2}, &(int){3}, &(int){1}, &Grafo);
  InsereAresta(&(int){3}, &(int){2}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){3}, &(int){4}, &(int){1}, &Grafo);
  InsereAresta(&(int){4}, &(int){3}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){1}, &(int){4}, &(int){1}, &Grafo);
  InsereAresta(&(int){4}, &(int){1}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  InsereAresta(&(int){4}, &(int){5}, &(int){1}, &Grafo);
  InsereAresta(&(int){5}, &(int){4}, &(int){1}, &Grafo);
  Grafo.NumArestas++;

  ImprimeGrafo(&Grafo);
  BuscaEmLargura(&Grafo, Antecessor);

  printf("\nCaminhos GRAFO 2:\n");
  ImprimeCaminho(0, 5, Antecessor); printf("\n");  
  ImprimeCaminho(0, 4, Antecessor); printf("\n");  

  return 0;
}

