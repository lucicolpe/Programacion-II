#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "maze.h"
#include "elequeue.h"
#include "queue.h"

Status print_colas(Queue* q1, Queue* q2, Queue* q3) {
    int tam, ret;
    if(!q1 || !q2 || !q3) return ERROR;
    
    tam = queue_size(q1);
    if (tam == 0) printf("Cola 1: Queue vacía\n");
    else if (tam > 0) {
        printf("Cola 1: Cola con %d elementos\n", tam);
        ret = queue_print(stdout, q1);
        if (ret < 0) return ERROR;
    } else return ERROR;
        
    tam = queue_size(q2);
    if (tam == 0) printf("Cola 2: Queue vacía\n");
    else if (tam > 0) {
        printf("Cola 2: Cola con %d elementos\n", tam);
        ret = queue_print(stdout, q2);
        if (ret < 0) return ERROR;
    } else return ERROR;
        
    tam = queue_size(q3);
    if (tam == 0) printf("Cola 3: Queue vacía\n");
    else if (tam > 0) {
        printf("Cola 3: Cola con %d elementos\n", tam);
        ret = queue_print(stdout, q3);
        if (ret < 0) return ERROR;
    } else return ERROR;
    
    return OK;
}

int main(int argc, char** argv) {
    int num, ret, x, y, i;
    char buff[MAXQUEUE], sym;
    Point* punto = NULL;
    EleQueue* ele = NULL;
    Queue *cola1 = NULL, *cola2 = NULL, *cola3 = NULL;
    FILE *f = NULL;

    f = fopen(argv[1], "r");
    if (!f){
        printf("Error al abrir el fichero");
        goto ERROR;
    }
    
    cola1 = queue_ini();
    if (!cola1){
        printf("Error al inicializar la primera cola");
        goto ERROR;
    }
    
    cola2 = queue_ini();
    if (!cola2){
        printf("Error al inicializar la segunda cola");
        goto ERROR;
    }
    
    cola3 = queue_ini();
    if (!cola3){
        printf("Error al inicializar la tercera cola");
        goto ERROR;
    }
    
    ret = print_colas(cola1, cola2, cola3);
    if (ret == ERROR) {
        printf("Error al imprimir las colas");
        goto ERROR;
    }
    
    fscanf(f, "%d\n", &num);
    for (i = 0; i < num; i++) {
        fgets(buff, MAXQUEUE, f);
        sscanf(buff, "%d,%d,%c", &x, &y, &sym);
        if(x < 0 || y < 0 || (sym != INPUT && sym != OUTPUT && sym != BARRIER && sym != SPACE)){
            printf("Las coordenadas del punto o el símbolo leídos no son válidos");
            goto ERROR;
        }
        
        punto = point_ini();
        if (!punto){
            printf("Error al inicializar el punto");
            goto ERROR;
        }
        
        punto = point_setCoordinateX(punto, x);
        punto = point_setCoordinateY(punto, y);
        punto = point_setSymbol(punto, sym);

        ele = elequeue_ini();
        if (!ele){
            printf("Error al inicializar el elemento");
            goto ERROR;
        }
        
        ele = elequeue_setInfo(ele, punto);        
        if (!ele){
            printf("Error al introducir el punto en el elemento");
            goto ERROR;
        }
        
        ret = queue_insert(cola1, ele);
        if (ret == ERROR){
            printf("Error al insertar el elemento en la cola 1");
            goto ERROR;
        }
        
        ret = print_colas(cola1, cola2, cola3);
        if (ret == ERROR) {
            printf("Error al imprimir las colas");
            goto ERROR;
        }
        
        elequeue_free(ele);
        point_free(punto);
    }

    printf("Pasando la primera mitad de Cola 1 a Cola 2\n");
    for (i = 0; i < num / 2; i++) {
        ele = queue_extract(cola1);
        if (!ele){
            printf("Error al extraer el elemento de la cola 1");
            goto ERROR;
        }
        
        ret = queue_insert(cola2, ele);
        if (ret == ERROR){
            printf("Error al insertar el elemento en la cola 2");
            goto ERROR;
        }
        
        elequeue_free(ele);

        ret = print_colas(cola1, cola2, cola3);
        if (ret == ERROR) {
            printf("Error al imprimir las colas");
            goto ERROR;
        }
    }

    printf("Pasando la segunda mitad de Cola 1 a Cola 3\n");
    for (; i < num; i++) {
        ele = queue_extract(cola1);
        if (!ele){
            printf("Error al extraer el elemento de la cola 1");
            goto ERROR;
        }
        
        ret = queue_insert(cola3, ele);
        if (ret == ERROR){
            printf("Error al insertar el elemento en la cola 3");
            goto ERROR;
        }
        
        elequeue_free(ele);

        ret = print_colas(cola1, cola2, cola3);
        if (ret == ERROR) {
            printf("Error al imprimir las colas");
            goto ERROR;
        }
    }

    ret = print_colas(cola1, cola2, cola3);
    if (ret == ERROR) {
        printf("Error al imprimir las colas");
        goto ERROR;
    }

    queue_free(cola1);
    queue_free(cola2);
    queue_free(cola3);
    fclose(f);
    return 0;

ERROR:
    if (punto) point_free(punto);
    if (ele) elequeue_free(ele);
    if (cola1) queue_free(cola1);
    if (cola2) queue_free(cola2);
    if (cola3) queue_free(cola3);
    fclose(f);
    return -1;
}