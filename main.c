#include <stdio.h>
#include <string.h>

#include "cdecl.h"

// CDECL: utilizar convención de llamadas estándar (código llamador quita los parámetros de la pila)
void PRE_CDECL resta( int, int, int * ) POST_CDECL;
void PRE_CDECL suma( int, int, int * ) POST_CDECL;

#define DOBLE_WORD 32

int binarioADecimal(char *binario, unsigned int longitud);
char * decimalABinario(int decimal, char *binario, unsigned int longitud);

int sumar_enteros();
int restar_enteros();
int sumar_binarios();
int restar_binarios();

int main( void )
	{
		int opcion;

		while(1)
		{
			printf("\nOPCIONES: \n");
			printf("\t1) Sumar 2 enteros \n");
			printf("\t2) Restar 2 enteros \n");
			printf("\t3) Sumar 2 binarios \n");
			printf("\t4) Restar 2 binarios \n");
			printf("\t5) Salir \n");
			scanf("%d", &opcion);
			
			if(opcion == 1)
				sumar_enteros();
			else if (opcion == 2)
				restar_enteros();
			else if (opcion == 3)
				sumar_binarios();
			else if (opcion == 4)
				restar_binarios();
			else if (opcion == 5)
				return 0;
			else
				printf("Opcion no valida\n");
		}
		
	}

int sumar_enteros()
	{
		int n, m, result;
		printf("Se sumaran los 2 numeros enteros introducidos: \n");
		printf("Primer operando: ");
		scanf("%d", &n);
		printf("Segundo operando: ");
		scanf("%d", &m);
		suma(n, m, &result);
		printf("El resultado de la suma es %d\n", result);
		return 0;
	}

int restar_enteros()
	{
		int n, m, result;
		printf("Se restaran los 2 numeros enteros introducidos: \n");
		printf("Primer operando: ");
		scanf("%d", &n);
		printf("Segundo operando: ");
		scanf("%d", &m);
		resta(n, m, &result);
		printf("El resultado de la resta es %d\n", result);
		return 0;
	}

int sumar_binarios()
	{
		int n, m, result;
		char entrada1[DOBLE_WORD+1];
		char entrada2[DOBLE_WORD+1];
		char salida[DOBLE_WORD+1];

		printf("Se sumaran los 2 numeros binarios introducidos: \n");
		printf("Primer operando: ");
		scanf("%s", entrada1);
		printf("Segundo operando: ");
		scanf("%s", entrada2);
		n = binarioADecimal(entrada1, strlen(entrada1));
		m = binarioADecimal(entrada2, strlen(entrada2));
		suma(n, m, &result);

		decimalABinario(result, salida, DOBLE_WORD+1);

		printf("El resultado de la suma es %s\n", salida);
		return 0;
	}


int restar_binarios()
	{
		int n, m, result;
		char entrada1[DOBLE_WORD+1];
		char entrada2[DOBLE_WORD+1];
		char salida[DOBLE_WORD+1];

		printf("Se restaran los 2 numeros binarios introducidos: \n");
		printf("Primer operando: ");
		scanf("%s", entrada1);
		printf("Segundo operando: ");
		scanf("%s", entrada2);
		n = binarioADecimal(entrada1, strlen(entrada1));
		m = binarioADecimal(entrada2, strlen(entrada2));
		resta(n, m, &result);

		decimalABinario(result, salida, DOBLE_WORD+1);

		printf("El resultado de la resta es %s\n", salida);
		return 0;
	}


int binarioADecimal(char *binario, unsigned int longitud)
	{
		int decimal = 0;
		int i;
		for (i=0; i < longitud; i++)
			if(binario[longitud-1-i] == '1')
				decimal |= 1 << i;

		return decimal;
	}


char * decimalABinario(int decimal, char *binario, unsigned int longitud)
	{
		int i,j;

		for(i=DOBLE_WORD-1; !(decimal & 1<<i) ;i--)
			if(i==0){
				binario[0] = '0';
				binario[1] = '\0';
				return binario;
			}


		for (i=i,j=0 ; i >=0 ; i--,j++)
			if(decimal & 1<<i)
				binario[j] = '1';
			else
				binario[j] = '0';
		binario[j] = '\0';

		return binario;
	}