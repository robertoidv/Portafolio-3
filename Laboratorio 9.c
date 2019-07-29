#include "hash_L9.h"

int main(void) {
    FILE *fp;
    int a=1, contador=0;
    char buff[100];
    int distancia = 0;
    TablaHash *tabla;
    tabla = creaTablaHash(100);
    if(tabla == NULL) {
        return 1;
    }
    fp = fopen("listado-palabras.txt","r");
    while(a!=0){
    	printf("\n1.-imprimir detalle tabla\n");
    	printf("\n2.-buscar palabra en lista\n");
    	printf("\n0.-salir\n");
    	scanf("%i",&a);
    	if(a==1){
    		while(fscanf(fp,"%[^\n]",buff) != EOF){
     			printf("data: %s\n",buff);
        		distancia += strlen(buff) + 1;
        		fseek(fp, distancia, SEEK_SET);
        		contador=contador+1;
    		}
    		printf("se procesaron: %i palabras",contador);
    	}
    	if(a==2){
    		
    	}
    }
    fclose(fp);
    return 1;
}
