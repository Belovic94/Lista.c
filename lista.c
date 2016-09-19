#include "lista.h"
struct nodo;

typedef struct nodo nodo_t;
struct nodo{
  void* dato;
  nodo_t proximo;
};


struct lista{
  nodo_t primero;
  nodo_t ultimo;
  size_t largo;
};
