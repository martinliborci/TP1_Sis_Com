#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "cdecl.h"

// CDECL: utilizar convención de llamadas estándar (código llamador quita los parámetros de la pila)
void PRE_CDECL resta( int, int, int * ) POST_CDECL;
void PRE_CDECL suma( int, int, int * ) POST_CDECL;
int PRE_CDECL binarioADecimalASM(char *binario, unsigned int longitud) POST_CDECL;
char * PRE_CDECL decimalABinarioASM(int decimal, char *binario, unsigned int longitud) POST_CDECL;
	
#define DOBLE_WORD 32

int binarioADecimal(char *binario, unsigned int longitud);
char * decimalABinario(int decimal, char *binario, unsigned int longitud);

int sumarDecimales(char *op1, char *op2);
int restarDecimales(char *op1, char *op2);
int sumarBinarios(char *op1, char *op2);
int restarBinarios(char *op1, char *op2);

void imprimirExplicacionComando();
int esBinario(char * binario);
int esDecimal(char * decimal);
int esValidaLaEntrada( int argc, char *argv[] );

#define ARGC (int)5
/*
	argv[0]: nombre del programa
	argv[1]: b/d
	argv[2]: op1
	argv[3]: +/-
	argv[4]: op2                   */
int main( int argc, char *argv[] )
{
	if(esValidaLaEntrada(argc, argv)){
		return -1;
	}else if (!strcmp(argv[1],"b") && !strcmp(argv[3],"+")){
		sumarBinarios(argv[2], argv[4]);
		return 0;
	}else if (!strcmp(argv[1],"b") && !strcmp(argv[3],"-")){
		restarBinarios(argv[2], argv[4]);
		return 0;
	}else if (!strcmp(argv[1],"d") && !strcmp(argv[3],"+")){
		sumarDecimales(argv[2], argv[4]);
		return 0;
	}else if (!strcmp(argv[1],"d") && !strcmp(argv[3],"-")){
		restarDecimales(argv[2], argv[4]);
		return 0;
	}
}

int esValidaLaEntrada( int argc, char *argv[] )
{
	if (argc != 5){
		printf("%d no es un número de argumentos inválido.\n", argc);
		imprimirExplicacionComando();
		return -1;
	} else if( strcmp(argv[3],"+") && strcmp(argv[3],"-")){
		printf("%s no es una operación válida\n", argv[3]);
		imprimirExplicacionComando();
		return -1;
	} else if( strcmp(argv[1],"b") && strcmp(argv[1],"d")){
		printf("%s no es una opción válida\n", argv[1]);
		imprimirExplicacionComando();
		return -1;
	} else if (!strcmp(argv[1],"b")){							// Entrada binaria
		if( esBinario(argv[2]) ){
			printf ("%s no es un operando binario\n", argv[2]);
			imprimirExplicacionComando();
			return -1;	
		} else if( esBinario(argv[4]) ){
			printf ("%s no es un operando binario\n", argv[4]);
			imprimirExplicacionComando();
			return -1;	
		} else if (strlen(argv[2]) > 32){
			printf ("La longitud del operando %s supera la máxima permitida de 32 dígitos binarios\n", argv[2]);
			imprimirExplicacionComando();
			return -1;
		} else if (strlen(argv[4]) > 32){
			printf ("La longitud del operando %s supera la máxima permitida de 32 dígitos binarios\n", argv[4]);
			imprimirExplicacionComando();
			return -1;
		}
	} else if (!strcmp(argv[1],"d")){							// Entrada decimal
		if( esDecimal(argv[2]) ){
			printf ("%s no es un operando decimal\n", argv[2]);
			imprimirExplicacionComando();	
			return -1;
		} else if( esDecimal(argv[4]) ){
			printf ("%s no es un operando decimal\n", argv[4]);
			imprimirExplicacionComando();
			return -1;
		} else if (strtoll(argv[2], '\0', 10) > 4294967295){
			printf ("El operando %s excede el valor máximo permito para ser representando en 32 bits (4.294.967.295)\n", argv[2]);
			imprimirExplicacionComando();
			return -1;
		} else if (strtoll(argv[4], '\0', 10) > 4294967295){
			printf ("El operando %s excede el valor máximo permito para ser representando en 32 bits (4.294.967.295)\n", argv[4]);
			imprimirExplicacionComando();
			return -1;
		}
	}
	return 0;
}

void imprimirExplicacionComando()
{
	printf("Formato del comando: b/d op1 +/- op2\n");
	printf("Donde:\n");
	printf("\tb/d: indica si los operandos op1 y op2 se encuentran en binario (b) o en decimal (d)\n");
	printf("\t     La longitud máxima permitida de los operandos binarios es de 32 dígitos\n");
	printf("\t     El valor máximo permitido de los operandos decimales es 4.294.967.295\n");
	printf("\t+/-: indica la operación a realizar: suma (+) o resta (-)\n");
}

int esBinario(char * binario)
{
	for(char *pbin = binario; *pbin != '\0'; pbin++)
		if(*pbin!='0' && *pbin!='1')
			return 1;
	return 0;
}

int esDecimal(char * decimal)
{
	for(char *pbin = decimal; *pbin != '\0'; pbin++)
		if(!isdigit(*pbin))
			return 1;
	return 0;
}

int sumarDecimales(char *op1, char *op2)
{
		unsigned int n, m, result;
		
		printf("\n");
		n = strtoll(op1, '\0', 10);
		m = strtoll(op2, '\0', 10);
		suma(n, m, &result);
		printf("%d", result);
		return 0;
}

int restarDecimales(char *op1, char *op2)
	{
		unsigned int n, m, result;
		
		printf("\n");
		n = strtoll(op1, '\0', 10);
		m = strtoll(op2, '\0', 10);
		resta(n, m, &result);
		printf("%d", result);
		return 0;
	}

int sumarBinarios(char *op1, char *op2)
	{
		unsigned int n, m, result;
		char salida[DOBLE_WORD+1];
		
		printf("\n");
		n = binarioADecimalASM(op1, strlen(op1));
		m = binarioADecimalASM(op2, strlen(op2));
		suma(n, m, &result);

		decimalABinarioASM(result, salida, DOBLE_WORD+1);

		printf("%s", salida);
		return 0;
	}

int restarBinarios(char *op1, char *op2)
	{
		unsigned int n, m, result;
		char salida[DOBLE_WORD+1];

		printf("\n");
		n = binarioADecimalASM(op1, strlen(op1));
		m = binarioADecimalASM(op2, strlen(op2));
		resta(n, m, &result);

		decimalABinarioASM(result, salida, DOBLE_WORD+1);

		printf("%s", salida);
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
		unsigned int i;
		char *pbinario;

		// Si es 0
		if(!decimal){
			binario[0] = '0';
			binario[1] = '\0';
			return binario;
		}

		// Saltar los 0s hasta encontrar el 1er 1
		for(i=0x8000; !(decimal & i); i >>= 1)
				;

		// 
		for(pbinario = binario  ; i > 0 ;  i >>= 1, pbinario++)
			if(decimal & i)
				*pbinario = '1';
			else
				*pbinario = '0';
		*pbinario = '\0';

		return binario;
	}
