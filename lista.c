#include "lista.h"


typedef struct nodo nodo_t;
struct nodo{
  void* dato;
  nodo_t* proximo;
};

struct lista{
  nodo_t* primero;
  nodo_t* ultimo;
  size_t largo;
};

struct lista_iterador{
	nodo_t* actual;
  nodo_t* anterior;
	lista_t* lista;
};

nodo_t *nodo_crear(void* dato){
  nodo_t* nodo = malloc(sizeof(nodo_t));
  if(!nodo){
    return NULL;
  }
  nodo->dato = dato;
  nodo->proximo = NULL;
  return nodo;
}

lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));

	if(!lista){
		return NULL;
	}
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	if(!lista || !lista->primero){
		return true;
	}
	return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if(!lista || !nodo_nuevo){
		free(nodo_nuevo);
		return false;
	}
	nodo_nuevo->proximo = lista->primero;
	lista->primero = nodo_nuevo;
	lista->largo += 1;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo_nuevo = nodo_crear(dato);
	if(!lista || !nodo_nuevo){
		free(nodo_nuevo);
		return false;
	}
	if(lista_esta_vacia(lista)){
		lista->primero = nodo_nuevo;
		lista->ultimo = nodo_nuevo;
	}
	else{
		lista->ultimo->proximo = nodo_nuevo;
	}
	lista->largo += 1;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	nodo_t* nodo_aux = lista->primero;;
	void* dato = lista->primero->dato;;
  lista->primero = lista->primero->proximo;
	free(nodo_aux);
	if(lista_esta_vacia(lista)){
		lista->ultimo = NULL;
	}
	lista->largo -= 1;
	return dato;
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return 0;
	}
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	void* dato;
	while(!lista_esta_vacia(lista)){
		dato = lista_borrar_primero(lista);
		if(destruir_dato){
			destruir_dato(dato);
		}
	}
	free(lista);
}
/* ***************************************************************************
 *                          PRIMITIVAS DEL ITERADOR
 * ***************************************************************************/

 lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(!lista || !iter){
		free(iter);
		return NULL;
	}
	iter->lista = lista;
	if(lista_esta_vacia(lista)){
		iter->actual = lista->ultimo;
	}
	else{
		iter->actual = lista->primero;
	}
  iter->anterior = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(!iter || lista_iter_al_final(iter)){
		return false;
	}
  iter->anterior = iter->actual;
  iter->actual = iter->actual->proximo;
  return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(!iter){
		return NULL;
	}
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	if(!iter || iter->actual->proximo){
		return false;
	}
	return true;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void* dato){
	nodo_t* nodo_nuevo = nodo_crear(dato);
  if(!iter || !nodo_nuevo){
    free(nodo_nuevo);
    return false;
  }
  nodo_nuevo->proximo = iter->actual;
  iter->actual = nodo_nuevo;
  iter->anterior->proximo = nodo_nuevo;
  iter->lista->largo += 1;
  return true;
}

void* lista_iter_borrar(lista_iter_t *iter){
  if(!iter){
    return NULL;
  }
  void* dato= iter->actual->dato;
  iter->anterior->proximo = iter->actual->proximo;
  free(iter->actual);
  iter->actual = iter->anterior->proximo;
  iter->lista->largo -= 1;
  return dato;
}
