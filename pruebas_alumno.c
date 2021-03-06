#include "lista.h"
#include "testing.h"
#include "pila.h"
#include "cola.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CANT_ELEM 1000
#define RANGO_RAND 100 //rango del random.
#define POSICION 20
#define CANT_VECTOR_AUX 5 //cantidad de valores que tendra el vector
                          //utilizado para encolar y apilar elementos

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

/*Recibe una lista y un puntero.
Devuelve true si el dato esta en la lista, en caso contrario false.*/
bool lista_pertenece(lista_t* lista, void* dato){
  lista_iter_t* l_iter = lista_iter_crear(lista);
  while(!lista_iter_al_final(l_iter)){
    if(lista_iter_ver_actual(l_iter) == dato){
      lista_iter_destruir(l_iter);
      return true;
    }
    lista_iter_avanzar(l_iter);
  }
  return false;
}

/*Recibe una lista y una posicion de la misma.
Devuelve el dato esta en la posicion especificada de la lista.
Devuelve NULL si la posicion no es valida.*/
void* lista_obtener_externo(lista_t* lista, int pos){
  if(pos < 0 || pos >= lista_largo(lista)) return NULL;
  lista_iter_t* l_iter = lista_iter_crear(lista);
  if(!l_iter) return NULL;
  for(int i = 0; i <= lista_largo(lista); i++){
    if(i == pos){
      void *dato = lista_iter_ver_actual(l_iter);
      lista_iter_destruir(l_iter);
      return dato;
    }
    lista_iter_avanzar(l_iter);
  }
  return NULL;
}


/*Recibe una lista.
Devuelve elimina la ultima posicion de la lista y devuelve el dato.*/
void* eliminar_ultimo_elemento(lista_t* lista){
  lista_iter_t* l_iter = lista_iter_crear(lista);
  void* dato;
  while(!lista_iter_al_final(l_iter)){
    if(lista_iter_ver_actual(l_iter) == lista_ver_ultimo(lista)){
      dato = lista_iter_borrar(l_iter);
      lista_iter_destruir(l_iter);
      return dato;
    }
    lista_iter_avanzar(l_iter);
  }
  return NULL;
}

/*Recibe una lista, un puntero y una posicion.
Devuelve true si se pudo insertar el dato en la posicion especificada de la lista, en caso contrario false.*/
bool insertar_en_lista(lista_t* lista, void* dato, size_t pos){
  if(pos >= lista_largo(lista)) return false;
  lista_iter_t* l_iter = lista_iter_crear(lista);
  if(!l_iter) return false;
  bool insercion_valida = false;
  for(int i = 0; i <= lista_largo(lista); i++){
    if(i == pos){
      insercion_valida = lista_iter_insertar(l_iter, dato);
      break;
    }
    lista_iter_avanzar(l_iter);
  }
  lista_iter_destruir(l_iter);
  return insercion_valida;
}

/*Llena un vector con valores enteros aleatorios entre 0 y 100.*/
void llenar_vector(int* vector, int largo){
  srand((int)time(NULL));
  for (int i = 0; i < largo; i++){
    vector[i] = rand() % (RANGO_RAND +1);
  }
  vector[rand() % (RANGO_RAND +1)] = RANGO_RAND + 1; // le coloco el valor maximo.
}

/*Agrega una cierta cantidad de valores enteros aleatorios a una lista*/
bool agregar_valores_lista(lista_t *lista, int *vector, int largo){
  if(!lista || !vector){
    return false;
  }
  for(int i = 0; i < largo; i++){
    if(!lista_insertar_ultimo(lista, &vector[i])){
      return false;
    }
  }
  return true;
}


/**********************FUNCIONES ITERADOR INTERNO********************************/

/*Obtiene el valor en una posicion de la lista*/
bool lista_obtener_interno(void *dato , void *extra){
  int *numero = dato, *vec_buscar = extra;
  if(vec_buscar[0] == 0){
     vec_buscar[1] = *numero;
    return false;
  }
  vec_buscar[0]--;
  return true;
}

/*Calcula el maximo entre dos numeros*/
bool calcular_maximo(void *dato , void *extra){
  int *numero = dato, *maximo = extra;
  if(*numero > *maximo){
    *maximo = *numero;
  }
  return true;
}

/*Cuenta la cantidad de caracteres de una palabra*/
bool cantidad_caracteres(void *dato, void *extra){
  char *palabra = dato;
  int *total_caracteres = extra;
  *total_caracteres += (int)strlen(palabra);
  return true;
}

/************************FUNCIONES AUXILIARES PILA **********************/

void llenar_pila(pila_t* pila, int* vector){

  for(int i=0; i<CANT_VECTOR_AUX; i++){
    vector[i] = i + 1;
    pila_apilar(pila, &vector[i]);
  }
}

void wrapper_pila_destruir(void* pila){
  pila_destruir((pila_t*)pila);
}

/************************FUNCIONES AUXILIARES COLA **********************/

void llenar_cola(cola_t* cola, int* vector){

  for(int i=0; i<CANT_VECTOR_AUX; i++){
    vector[i] = i + 1;
    cola_encolar(cola, &vector[i]);
  }
}

void wrapper_cola_destruir(void* cola){
  cola_destruir((cola_t*)cola, NULL);
}


/* ******************************************************************
 *                        PRUEBAS DE LA LISTA
 * *****************************************************************/


void pruebas_lista_no_creada(void){
  lista_t* lista = NULL;
  int valor = 5;

  printf("\n***PRUEBAS LISTA NO CREADA***\n");
  print_test("Insertar primero en una lista no creada(false)", !lista_insertar_primero(lista, &valor));
  print_test("Borrar primero en una lista no creada(NULL)", !lista_borrar_primero(lista));
  print_test("Ver primero en una lista no creada(NULL)", !lista_ver_primero(lista));
  print_test("Ver ultimo en una lista no creada(NULL)", !lista_ver_ultimo(lista));
  print_test("Obtener el largo de una lista no creada(0)", lista_largo(lista) == 0);
  print_test("Ver si esta vacia en una lista no creada(true)", lista_esta_vacia(lista));
  print_test("Insertar primero en una lista no creada(false)", !lista_insertar_primero(lista, &valor));
  print_test("Insertar ultimo en una lista no creada(false)", !lista_insertar_ultimo(lista, &valor));

}


void pruebas_iterador_lista_no_creada(void){
  lista_t* lista = NULL;
  int valor = 5;
  lista_iter_t* l_iter = lista_iter_crear(lista);

  printf("\n***PRUEBAS ITERADOR LISTA NO CREADA***\n");
  print_test("Intentar crear iterador sin una lista creada(NULL)", !l_iter);
  print_test("Avanzar sin un iterador creado", !lista_iter_avanzar(l_iter));
  print_test("Ver si el iterador esta al final(true)", lista_iter_al_final(l_iter));
  print_test("Ver elemento actual(NULL)", !lista_iter_ver_actual(l_iter));
  print_test("Borrar un elemento de la lista no creada(NULL)", !lista_iter_borrar(l_iter));
  print_test("Insertar un elemento en una lista no creada(false)", !lista_iter_insertar(l_iter, &valor));
}


void pruebas_lista_vacia(void){
  lista_t* lista = lista_crear();
  int valor1 = 5;
  int valor2 = 10;

  printf("\n***PRUEBAS LISTA VACIA***\n");
  print_test("Lista creada exitosamente", lista);
  print_test("Ver primero en una lista vacia(NULL)", !lista_ver_primero(lista));
  print_test("Ver ultimo en una lista vacia(NULL)", !lista_ver_ultimo(lista));
  print_test("Borrar primero en una lista vacia(NULL)", !lista_borrar_primero(lista));
  print_test("Ver si esta vacia en una lista vacia(true)", lista_esta_vacia(lista));
  print_test("Largo de una lista vacia(0)", lista_largo(lista) == 0);

  print_test("Insertar primero en una lista vacia(true)", lista_insertar_primero(lista, &valor1));
  print_test("Ver primero en una lista(valor)", *(int*)lista_ver_primero(lista) == valor1);
  print_test("Ver último en una lista(valor)", *(int*)lista_ver_ultimo(lista) == valor1);
  print_test("Obtener el largo de una lista(1)", lista_largo(lista) == 1);
  print_test("Borrar primero en una lista (valor)", *(int*)lista_borrar_primero(lista) == valor1);
  print_test("Obtener el largo de una lista(0)", lista_largo(lista) == 0);
  print_test("Ver primero en una lista vacia(NULL)", !lista_ver_primero(lista));
  print_test("Ver ultimo en una lista vacia(NULL)", !lista_ver_ultimo(lista));

  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, &valor2));
  print_test("Ver primero en una lista(valor)", *(int*)lista_ver_primero(lista) == valor2);
  print_test("Ver último en una lista(valor)", *(int*)lista_ver_ultimo(lista) == valor2);
  print_test("Obtener el largo de una lista(1)", lista_largo(lista) == 1);
  print_test("Borrar primero en una lista (valor)", *(int*)lista_borrar_primero(lista) == valor2);
  print_test("Obtener el largo de una lista(0)", lista_largo(lista) == 0);
  print_test("Ver primero en una lista vacia(NULL)", !lista_ver_primero(lista));
  print_test("Ver ultimo en una lista vacia(NULL)", !lista_ver_ultimo(lista));

  lista_destruir(lista, NULL);
  print_test("Destruyo la lista vacia", true);


}


void pruebas_iterador_lista_vacia(void){
  lista_t* lista = lista_crear();
  int valor = 5;
  lista_iter_t* l_iter = lista_iter_crear(lista);

  printf("\n***PRUEBAS ITERADOR LISTA VACIA***\n");
  print_test("Crear iterador en lista vacia(iter)", l_iter);
  print_test("Avanzar iterador en lista vacia(false)", !lista_iter_avanzar(l_iter));
  print_test("Ver si el iterador esta al final(true)", lista_iter_al_final(l_iter));
  print_test("Ver elemento actual(NULL)", !lista_iter_ver_actual(l_iter));
  print_test("Borrar un elemento de la lista vacia con iterador(NULL)", !lista_iter_borrar(l_iter));
  print_test("Insertar elemento en la lista vacia con iterador(true)", lista_iter_insertar(l_iter, &valor));

  lista_iter_destruir(l_iter);
  print_test("Destruir iterador de lista vacia(true)", true);
  lista_destruir(lista, NULL);
  print_test("Destruyo la lista vacia", true);
}

void pruebas_lista_destructor(void){
  lista_t* lista = lista_crear();
  pila_t* pila = pila_crear();
  cola_t* cola = cola_crear();
  int vector[CANT_VECTOR_AUX];

  double *valordou = malloc(sizeof(double));
  long *valorlon = malloc(sizeof(long));
  char *valorcha = malloc(sizeof(char));
  int *valorint = malloc(sizeof(int));
  *valordou = 14.54;
  *valorlon = 3000000000;
  *valorcha = 'a';
  *valorint = 84;

  printf("\n***PRUEBAS LISTA DESTRUCTOR***\n");
  llenar_pila(pila, vector);
  print_test("Insertar a la lista una pila de números enteros", lista_insertar_primero(lista, pila));
  lista_destruir(lista, wrapper_pila_destruir);
  print_test("Lista con pila adentro destruida", true);

  lista = lista_crear();
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valordou));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valorlon));
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, valorcha));
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, valorint));
  lista_destruir(lista, free);
  print_test("Lista con elementos pedidos con malloc destruida", true);

  lista = lista_crear();
  llenar_cola(cola, vector);
  print_test("Insertar a la lista una cola de números enteros", lista_insertar_primero(lista, cola));
  lista_destruir(lista, wrapper_cola_destruir);
  print_test("Lista con cola adentro destruida", true);
}


void pruebas_iterardor_externo(void){
  lista_t* lista = lista_crear();
  lista_iter_t* l_iter;
  //valores que ocupan memoria dinámica
  double *valordou1 = malloc(sizeof(double)), *valordou2 = malloc(sizeof(double));
  long *valorlon1 = malloc(sizeof(long)), *valorlon2 = malloc(sizeof(long));
  char *valorcha1 = malloc(sizeof(char)), *valorcha2 = malloc(sizeof(char));
  int *valorint1 = malloc(sizeof(int)), *valorint2 = malloc(sizeof(int));
  int *valor_ingresado = malloc(sizeof(int));
  /*le doy valores a los punteros dinamicos*/
  *valordou1 = 3.1415;
  *valorlon1 = 5004500;
  *valorcha1 = 'r';
  *valorint1 = 15;
  *valordou2 = 81.9327;
  *valorlon2 = 3895403;
  *valorcha2 = 's';
  *valorint2 = 34;
  *valor_ingresado = 5;

  printf("\n***PRUEBAS ITERADOR EXTERNO***\n");
  print_test("Lista creada exitosamente", lista);
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valordou1));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valordou2));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valorlon1));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valorlon2));
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, valorcha1));
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, valorcha2));
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, valorint1));
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, valorint2));

  //pruebo el iterador externo
  print_test("Pruebo buscar un elemento en la lista con el iterador(true)",
                                lista_pertenece(lista, valorcha1));
  print_test("Pruebo borrar el ultimo elemento en la lista con el iterador(valorint2)",
                                *(int*)eliminar_ultimo_elemento(lista) == *valorint2);
  print_test("Veo si el largo de la lista cambio (7)", lista_largo(lista) == 7);
  print_test("Pruebo insertar un elemento en una posicion de la lista(true)",
                                insertar_en_lista(lista, valor_ingresado, 6));
  print_test("Veo si el largo de la lista cambio (8)", lista_largo(lista) == 8);
  print_test("Pruebo buscar el elemento recien ingresado a la lista con el iterador(true)",
                                lista_pertenece(lista, valor_ingresado));
  print_test("Busco el elemento en la posicion 5",
                                *(char*)lista_obtener_externo(lista, 5) == *valorcha2);

  l_iter = lista_iter_crear(lista);
  print_test("Creo un iterador de la lista con elementos(true)", l_iter);
  print_test("Avanzo el iterador (true)", lista_iter_avanzar(l_iter));
  print_test("Posicion del iterador se corresponde con la del segundo elemento de la lista(true)",
                                *(long*)lista_iter_ver_actual(l_iter) == *(long*)valorlon1 );
  print_test("Avanzo el iterador (true)", lista_iter_avanzar(l_iter));
  print_test("Avanzo el iterador (true)", lista_iter_avanzar(l_iter));
  print_test("Elimino el valor de la posicion actual del iterador(valordou1)",
                                *(double*)lista_iter_borrar(l_iter) == *(double*)valordou1);
  print_test("Posicion del iterador se corresponde con la del segundo elemento de la lista(true)",
                                *(char*)lista_iter_ver_actual(l_iter) == *(char*)valorcha1 );
  print_test("Avanzo el iterador (true)", lista_iter_avanzar(l_iter));
  print_test("Avanzo el iterador (true)", lista_iter_avanzar(l_iter));
  print_test("Elimino el valor de la posicion actual del iterador(valor_ingresado)",
                                *(int*)lista_iter_borrar(l_iter) == *(int*)valor_ingresado);
  print_test("Veo si el largo de la lista cambio (6)", lista_largo(lista) == 6);
  print_test("Avanzo el iterador (true)", lista_iter_avanzar(l_iter));
  print_test("Veo si el iterador esta al final(true)", lista_iter_al_final(l_iter));
  print_test("Intento eliminar cuando el iterador esta al final(NULL)",
                                !lista_iter_borrar(l_iter));
  print_test("Agrego un valor cuando el iterador esta al final(true)",
                                lista_iter_insertar(l_iter, valordou1));
  print_test("Veo si el iterador esta al final(false)", !lista_iter_al_final(l_iter));
  print_test("El valor actual del iterador se corresponde con el del ultimo dato ingresado(valordou1)",
                                *(double*)lista_iter_ver_actual(l_iter) == *(double*)valordou1);

  free(valorint2); // libero el elemento borrado de la lista.
  free(valor_ingresado);
  lista_iter_destruir(l_iter);
  print_test("Destruir iterador creado anteriormente(true)", true);
  lista_destruir(lista, free);//pruebo la funcion destructora.
  print_test("Destruyo la lista con datos adentro", true);
}

void pruebas_iterardor_interno(void){
  lista_t* lista = lista_crear();
  //coloco el maximo en -1 ya que todos los valores del vector son numeros positivos.
  int vector[CANT_ELEM], maximo = -1, cant_caracteres = 0;
  int vec_buscar[2] = {POSICION};//vector que paso como parametro para buscar el valor en una posicion de la lista.
  char materia1[] = "Algebra",
       materia2[] = "Análisis Matemático",
       materia3[] = "Física",
       materia4[] = "Probabilidad y Estadística",
       materia5[] = "Algoritmos y Programación";

  printf("\n***PRUEBAS ITERADOR INTERNO***\n");
  /*Pruebas para calcular el maximo valor de una lista*/
  llenar_vector(vector, CANT_ELEM);
  print_test("Lleno la lista con los datos del vector", agregar_valores_lista(lista, vector, CANT_ELEM));
  lista_iterar(lista, calcular_maximo, &maximo);
  print_test("Determino el maximo valor de la lista", maximo == RANGO_RAND + 1);

  /*Pruebas para obterner el valor en una posicion de la lista*/
  lista_iterar(lista, lista_obtener_interno, vec_buscar);
  int valor_pos = vector[POSICION];
  print_test("Determino el valor en una posicion de la lista", vec_buscar[1] == valor_pos);

  lista_destruir(lista, NULL);
  lista = lista_crear();
  print_test("Verifico que la lista este vacia", lista_esta_vacia(lista));

  /*Pruebas para determinar la cantidad de caracteres en la lista*/
  print_test("Agrego la materia 1", lista_insertar_ultimo(lista, materia1));
  print_test("Agrego la materia 2", lista_insertar_ultimo(lista, materia2));
  print_test("Agrego la materia 3", lista_insertar_ultimo(lista, materia3));
  print_test("Agrego la materia 4", lista_insertar_ultimo(lista, materia4));
  print_test("Agrego la materia 5", lista_insertar_ultimo(lista, materia5));
  lista_iterar(lista, cantidad_caracteres, &cant_caracteres);
  size_t tot_carac = strlen(materia1) + strlen(materia2) + strlen(materia3)
                    + strlen(materia4) + strlen(materia5);
  print_test("Determino la cantidad de caracteres en la lista", cant_caracteres == tot_carac);
  lista_destruir(lista, NULL);
  print_test("Destruyo la lista", true);

}
void pruebas_lista_alumno(void){
  pruebas_lista_no_creada();
  pruebas_iterador_lista_no_creada();
  pruebas_lista_vacia();
  pruebas_iterador_lista_vacia();
  pruebas_lista_destructor();
  pruebas_iterardor_externo();
  pruebas_iterardor_interno();
}
