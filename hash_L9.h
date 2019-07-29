#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoLista{
        char *clave;
        char *valor;
        struct NodoLista *sig;
} NodoLista;

typedef struct TablaHash{
        int size;
        NodoLista **arreglo; // arreglo de punteros a NodoLista
} TablaHash;

TablaHash *creaTablaHash(int size){
        TablaHash *ht;
        ht = malloc(sizeof(TablaHash));
        ht->arreglo = (NodoLista**)malloc(size * sizeof(NodoLista));
        ht->size = size;
        return ht;
}
//---------------------------------------------------------------------------------------
int hash(char *clave, int size){
        int hash = 0;
        int i = 0;
        while(clave && clave[i]) {
                hash = (hash + clave[i]) % size;
                ++i;
        }
        return (hash);
}
//--------------------------------------------------------------------------------------
void insertaNodo(TablaHash *TablaHash, NodoLista *nodo){
        int i = hash(nodo->clave, TablaHash->size);
        printf("hash i: %i\n",i);
        NodoLista *tmp = TablaHash->arreglo[i];
        if (TablaHash->arreglo[i] != NULL) {
                tmp = TablaHash->arreglo[i];
                while (tmp != NULL) {
                        if (strcmp(tmp->clave, nodo->clave) == 0) {
                                break;
                        }
                        tmp = tmp->sig;
                }
                if (tmp == NULL) {
                        nodo->sig = TablaHash->arreglo[i];
                        TablaHash->arreglo[i] = nodo;
                } else {
                        free(tmp->valor);
                        tmp->valor = strdup(nodo->valor);
                        free(nodo->valor);
                        free(nodo->clave);
                        free(nodo);
                }
        } 
        else {
                nodo->sig = NULL;
                TablaHash->arreglo[i] = nodo;
        }
}
//-----------------------------------------------------------------------------------
int insertaClave(TablaHash *TablaHash, char *clave, char *valor){
        NodoLista *nodo;
        nodo = malloc(sizeof(NodoLista));
        nodo->clave = strdup(clave); //crea una copia dinamica de clave 
        nodo->valor = strdup(valor);
        insertaNodo(TablaHash, nodo); //modulo para insertar el nodo donde corresponda
        return 0;
}
//-----------------------------------------------------------------------------------
char *buscaClave(TablaHash *TablaHash, char *clave){
        char *clave_cp;
        int i;
        NodoLista *tmp;
        clave_cp = strdup(clave);
        i = hash(clave, TablaHash->size);
        tmp = TablaHash->arreglo[i];
        while (tmp != NULL) {
                if (strcmp(tmp->clave, clave_cp) == 0) {
                break;
                }
                tmp = tmp->sig;
        }
        free(clave_cp);

        if (tmp == NULL) {
                return NULL;
        }
        return tmp->valor;
}
