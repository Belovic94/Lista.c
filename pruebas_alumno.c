#include "lista.h"
#include "testing.h"
#include <stdio.h>

void pruebas_lista_no_creada(void){
  lista_t* lista;
  int valor = 5;

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
  int valor = 5;
  lista_iter_t* l_iter;

  print_test("Lista creada exitosamente", lista);
  print_test("Ver primero en una lista vacia(NULL)", !lista_ver_primero(lista));
  l_iter = lista_iter_crear(lista);
  print_test("Crear iterador en lista vacia(iter)", l_iter);
  lista_iter_destruir(l_iter);
  print_test("Destruir iterador creado anteriormente(true)", true);
  print_test("Insertar primero en una lista vacia(true)", lista_insertar_primero(lista, &valor));
  print_test("Ver primero en una lista(valor)", *(int*)lista_ver_primero(lista) == valor);
  l_iter = lista_iter_crear(lista);
  print_test("Crear iterador en lista no vacia(iter)", l_iter);
  print_test("Iterador apunta al primer elemento de la lista", l_iter)
  print_test("Borrar primero en una lista (NULL)", lista_borrar_primero(lista));
  print_test("Obtener el largo de una lista no creada(0)", lista_largo(lista) == 0);
  print_test("Insertar ultimo en una lista no creada(false)", !lista_insertar_ultimo(lista, &valor));
}

void pruebas_lista_elementos(void){

}

void pruebas_lista_alumno(void){

}
