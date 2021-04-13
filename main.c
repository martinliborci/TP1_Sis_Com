#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "cdecl.h"

// CDECL: utilizar convención de llamadas estándar (código llamador quita los parámetros de la pila)
int PRE_CDECL resta( int, int) POST_CDECL;
int PRE_CDECL suma( int, int) POST_CDECL;
char * PRE_CDECL decimalABinarioASM(int decimal, char *binario, unsigned int longitud) POST_CDECL;
	
#define DOBLE_WORD 32

int sumarDecimales(char *op1, char *op2);
int restarDecimales(char *op1, char *op2);
int sumarBinarios(char *op1, char *op2);
int restarBinarios(char *op1, char *op2);

void imprimirExplicacionComando();
int esBinario(char * binario);
int esDecimal(char * decimal);
int esValidaLaEntrada( int argc, char *argv[] );

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

// Valida que la entrada sea correcta. Retorna 0 si lo es y -1 si es inválida
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
		} else if (strlen(argv[2]) > 31){
			printf ("La longitud del operando %s supera la máxima permitida de 31 dígitos binarios\n", argv[2]);
			imprimirExplicacionComando();
			return -1;
		} else if (strlen(argv[4]) > 31){
			printf ("La longitud del operando %s supera la máxima permitida de 31 dígitos binarios\n", argv[4]);
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
		} else if (strtoll(argv[2], '\0', 10) > 2147483647){
			printf ("El operando %s excede el valor máximo permito para ser representando en 31 bits (2.147.483.647)\n", argv[2]);
			imprimirExplicacionComando();
			return -1;
		} else if (strtoll(argv[4], '\0', 10) > 2147483647){
			printf ("El operando %s excede el valor máximo permito para ser representando en 31 bits (2.147.483.647)\n", argv[4]);
			imprimirExplicacionComando();
			return -1;
		}
	}
	return 0;
}

// Imprime la explicación de lo que hace el programa
void imprimirExplicacionComando()
{
	printf("Formato del comando: b/d op1 +/- op2\n");
	printf("Donde:\n");
	printf("\tb/d: indica si los operandos op1 y op2 se encuentran en binario (b) o en decimal (d)\n");
	printf("\t     La longitud máxima permitida de los operandos binarios es de 31 dígitos\n");
	printf("\t     El valor máximo permitido de los operandos decimales es 2.147.483.647\n");
	printf("\t+/-: indica la operación a realizar: suma (+) o resta (-)\n");
}

// Comprueba que el string sea una representación binaria. Si lo es devulve 0. En caso contrario: 1
int esBinario(char * binario)
{
	for(char *pbin = binario; *pbin != '\0'; pbin++)
		if(*pbin!='0' && *pbin!='1')
			return 1;
	return 0;
}

// Comprueba que el string sea una representación decimal. Si lo es devulve 0. En caso contrario: 1
int esDecimal(char * decimal)
{
	for(char *pbin = decimal; *pbin != '\0'; pbin++)
		if(!isdigit(*pbin))
			return 1;
	return 0;
}

// Suma 2 decimales en cadenas de texto. Imprime el resultado en pantalla y retorna 0 si ha salido todo bien
int sumarDecimales(char *op1, char *op2)
{
		unsigned int n, m, result;
		n = strtol(op1, '\0', 10); // convertir el 1er operando de string a entero
		m = strtol(op2, '\0', 10); // convertir el 2do operando de string a entero
		result = suma(n, m);
		printf("%u", result);

		printf("\n");

		return 0;
}

// Resta 2 decimales en cadenas de texto. Imprime el resultado en pantalla y retorna 0 si ha salido todo bien
int restarDecimales(char *op1, char *op2)
	{
		unsigned int n, m, result;
		
		n = strtol(op1, '\0', 10); // convertir el 1er operando de string a entero
		m = strtol(op2, '\0', 10); // convertir el 2do operando de string a entero
		result = resta(n, m);
		printf("%d", result);
		printf("\n");	
		return 0;
	}

// Suma 2 binarios en cadenas de texto. Imprime el resultado en pantalla y retorna 0 si ha salido todo bien
int sumarBinarios(char *op1, char *op2)
	{
		unsigned int n, m, result;
		char salida[DOBLE_WORD+1];
		
		n = strtol(op1, '\0', 2); // convertir el 1er operando de string a entero
		m = strtol(op2, '\0', 2); // convertir el 2do operando de string a entero
		
		result = suma(n, m);

		decimalABinarioASM(result, salida, DOBLE_WORD+1); // convertir el resultado a string
		printf("%s", salida);
		printf("\n");
		return 0;
	}

// Resta 2 binarios en cadenas de texto. Imprime el resultado en pantalla y retorna 0 si ha salido todo bien
int restarBinarios(char *op1, char *op2)
	{
		int n, m, result;
		char salida[DOBLE_WORD+1];

		n = strtol(op1, '\0', 2); // convertir el 1er operando de string a entero
		m = strtol(op2, '\0', 2); // convertir el 2do operando de string a entero
		
		result = resta(n, m);
		
		decimalABinarioASM(result, salida, DOBLE_WORD+1); // convertir el resultado a string
		printf("%s", salida);
		printf("\n");
		return 0;
	}
