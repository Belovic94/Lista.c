#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define CANT_ELEM 1000
#define RANGO_RAND 100 //rango del random.

void pruebas_lista_no_creada(void){
  lista_t* lista = NULL;
  int valor = 5;
  lista_iter_t* l_iter = NULL;

  print_test("Insertar primero en una lista no creada(false)", !lista_insertar_primero(lista, &valor));
  print_test("Borrar primero en una lista no creada(NULL)", !lista_borrar_primero(lista));
  print_test("Ver primero en una lista no creada(NULL)", !lista_ver_primero(lista));
  l_iter = lista_iter_crear(lista);
  print_test("Intentar crear iterador sin una lista creada(NULL)", !l_iter);
  print_test("Obtener el largo de una lista no creada(0)", lista_largo(lista) == 0);
  print_test("Insertar ultimo en una lista no creada(false)", !lista_insertar_ultimo(lista, &valor));
}

void pruebas_lista_vacia(void){
  lista_t* lista = lista_crear();
  int valor1 = 5;
  lista_iter_t* l_iter;

  print_test("Lista creada exitosamente", lista);
  print_test("Ver primero en una lista vacia(NULL)", !lista_ver_primero(lista));
  l_iter = lista_iter_crear(lista);
  print_test("Crear iterador en lista vacia(iter)", l_iter);
  lista_iter_destruir(l_iter);
  print_test("Destruir iterador creado anteriormente(true)", true);
  print_test("Insertar primero en una lista vacia(true)", lista_insertar_primero(lista, &valor1));
  print_test("Ver primero en una lista(valor)", *(int*)lista_ver_primero(lista) == valor1);
  print_test("Obtener el largo de una lista(1)", lista_largo(lista) == 1);
  l_iter = lista_iter_crear(lista);
  print_test("Crear iterador en lista no vacia(iter)", l_iter);
  print_test("Iterador apunta al primer elemento de la lista(true)",
                  *(int*)lista_iter_ver_actual(l_iter) == *(int*)lista_ver_primero(lista));
  print_test("Borrar primero en una lista (valor1)", lista_borrar_primero(lista));
  print_test("Obtener el largo de una lista vacia(0)", lista_largo(lista) == 0);
  lista_iter_destruir(l_iter);
  print_test("Destruir iterador creado anteriormente(true)", true);
  print_test("Insertar ultimo en una lista (true)", lista_insertar_ultimo(lista, &valor1));
  print_test("Obtener el largo de una lista(1)", lista_largo(lista) == 1);
  lista_destruir(lista, NULL);
  print_test("Destruyo la lista con datos adentro", true);
}

/*Recibe una lista y un puntero.
Devuelve true si el dato esta en la lista, en caso contrario false.*/
bool buscar_con_iterador(lista_t* lista, void* dato){
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
  lista_iter_t* l_iter = lista_iter_crear(lista);
  bool insercion_valida = false;
  for(int i=0; !lista_iter_al_final(l_iter); i++){
    if(i == pos){
      insercion_valida = lista_iter_insertar(l_iter, dato);
      break;
    }
    lista_iter_avanzar(l_iter);
  }
  lista_iter_destruir(l_iter);
  return insercion_valida;
}


void pruebas_lista_elementos_distintos(void){
  lista_t* lista = lista_crear();
  //lista_iter_t* l_iter;
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

  print_test("Lista creada exitosamente", lista);
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valordou1));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valordou2));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valorlon1));
  print_test("Insertar primero en una lista (true)", lista_insertar_primero(lista, valorlon2));
  print_test("Insertar primero en una lista (true)", lista_insertar_ultimo(lista, valorcha1));
  print_test("Insertar primero en una lista (true)", lista_insertar_ultimo(lista, valorcha2));
  print_test("Insertar primero en una lista (true)", lista_insertar_ultimo(lista, valorint1));
  print_test("Insertar primero en una lista (true)", lista_insertar_ultimo(lista, valorint2));
  //pruebo el iterador externo
  print_test("Pruebo buscar un elemento en la lista con el iterador(true)",
                                  buscar_con_iterador(lista, valorcha1));
  print_test("Pruebo borrar el ultimo elemento en la lista con el iterador(valorint2)",
                              *(int*)eliminar_ultimo_elemento(lista) == *valorint2);
  print_test("Veo si el largo de la lista cambio (7)", lista_largo(lista) == 7);
  print_test("Pruebo insertar un elemento en una posicion de la lista(true)",
                                insertar_en_lista(lista, valor_ingresado, 4));
  print_test("Veo si el largo de la lista cambio (8)", lista_largo(lista) == 8);
  print_test("Pruebo buscar el elemento recien ingresado a la lista con el iterador(true)",
                                  buscar_con_iterador(lista, valor_ingresado));
  free(valorint2); // libero el elemento borrado de la lista.
  lista_destruir(lista, free);//pruebo la funcion destructora
  print_test("Destruyo la lista con datos adentro", true);
}
/*Llena un vector con valores enteros aleatorios entre 0 y 100.*/
void llenar_vector(int* vector, int largo){
  srand((int)time(NULL));
  for (int i = 0; i < largo; i++){
    vector[i] = rand() % (RANGO_RAND +1);
  }
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
/*Vacia la lista por medio de un iterador externo*/
void vaciar_lista(lista_t *lista){
  lista_iter_t *iter = lista_iter_crear(lista);
  while(!lista_iter_al_final(iter)){
    lista_iter_borrar(iter);
  }
  lista_iter_destruir(iter);
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

  for(int i=0; palabra[i] != '\0'; i++){
    *total_caracteres += 1;
  }
  return true;
}

void pruebas_iterardor_interno(void){
  lista_t* lista = lista_crear();
  //coloco el maximo en -1 ya que todos los valores del vector son numeros positivos.
  int vector[CANT_ELEM], maximo = -1, cant_caracteres = 0;
  char materia1[] = "Algebra",
       materia2[] = "Análisis Matemático",
       materia3[] = "Física",
       materia4[] = "Probabilidad y Estadística",
       materia5[] = "Algoritmos y Programación";

  /*Pruebas para calcular el maximo valor de una lista*/
  llenar_vector(vector, CANT_ELEM);
  print_test("Lleno la lista con los datos del vector", agregar_valores_lista(lista, vector, CANT_ELEM));
  lista_iterar(lista, calcular_maximo, &maximo);
  print_test("Determino el maximo valor de la lista", maximo > -1);
  vaciar_lista(lista);
  print_test("Verifico que la lista este vacia", lista_esta_vacia(lista));
  /*Pruebas para determinar la cantidad de caracteres en la lista*/
  print_test("Agrego la materia 1", lista_insertar_ultimo(lista, materia1));
  print_test("Agrego la materia 2", lista_insertar_ultimo(lista, materia2));
  print_test("Agrego la materia 3", lista_insertar_ultimo(lista, materia3));
  print_test("Agrego la materia 4", lista_insertar_ultimo(lista, materia4));
  print_test("Agrego la materia 5", lista_insertar_ultimo(lista, materia5));
  lista_iterar(lista, cantidad_caracteres, &cant_caracteres);
  print_test("Determino la cantidad de caracteres en la lista", cant_caracteres != 0);
  lista_destruir(lista, NULL);
  print_test("Destruyo la lista", true);

}
void pruebas_lista_alumno(void){
  pruebas_lista_no_creada();
  pruebas_lista_vacia();
  pruebas_lista_elementos_distintos();
  pruebas_iterardor_interno();
}
