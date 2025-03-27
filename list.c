#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * lista = (List*) malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
     return lista;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL) //caso tambien donde la lista está vacía
        return NULL;
    return list->head->data;
}

void * nextList(List * list) {
    /* head, current, y tail es de lista 
    el nodo es el que tiene prev, next y data;*/
    if(list->current == NULL || list == NULL) //intento de hacerlo al revez
        return NULL;

    list->current = list->current->next; //se actualiza el current

    if(list->current == NULL)
        return NULL;

    return list->current->data;

}

void * lastList(List * list) {
    if(list == NULL || list->tail == NULL) //caso tambien donde la lista está vacía
        return NULL;

    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL || list->current->prev == NULL) //acede a todos los casos
        return NULL;
    
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if(list == NULL)
        return; //al parecer si retorno NULL me da error, quisas sea porque es una accion?
    Node * newNodo = createNode(data);
    newNodo->data = data;
    newNodo->prev = NULL; //se va a insertar al primero pss, antes no hay nada
    newNodo->next = list->head; //y el siguiente va a pasar a ser el antiguo primero
    if(list->head)
        list->head->prev = newNodo; // aqui se termina de elazar el antiguo primero con el actual
    //caso de lista vacia
    else
        list->tail = newNodo; //al estar vacia, pasa a ser el priemro y el ultimo;
    
    list->head = newNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list == NULL || list->current == NULL)
        return; //creo que al no ser "punteros" a void no puedo retornar null porf ejemplo
    Node * newNodo = createNode(data);

    newNodo->prev = list->current;
    newNodo->next = list->current->next;
    list->current->next = newNodo;

    if(newNodo->next != NULL) // si hay un nodo despues
        newNodo->next->prev = newNodo;
    else
        list->tail = newNodo; //si no, es el ultimo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL || list->current == NULL )
        return NULL;

    Node * actual = list->current; //bastante util para guiarse

    void *data = actual->data;

    //Head
    if(actual->prev == NULL) //si esta en el head// leelo de derecha a isquierda para entender mejor
    {
        list->head = actual->next;
        if(list->head != NULL) //si no tiene 1 solo nodo
            list->head->prev = NULL;
    }
    else
        actual->prev->next = actual->next;

    //Tail
    if(actual->next != NULL) //si no esta al final
        actual->next->prev = actual->prev;
    else
        list->tail = actual->prev;//entender esto mejor

    //debo mover el current
    if(actual->next != NULL)
        list->current = actual->next;
    else
        list->current = actual->prev;

    //pero debo ver si queda vacia
    if(list->head == NULL)
    {
        list->tail = NULL; //actualizo todo
        list->current = NULL;
    }
    free(actual->data);
    free(actual);

    /*
    Node * izq = list->current->prev;
    Node* der = list->current->next;

    izq->next = der;
    der->prev = izq;

    free(list->current);
    list->current = NULL;*/
    return data;//preguntar porque devo retonar data
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}