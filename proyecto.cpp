/**
 * Andres De Armas
 * Tomas El Fakih
 * Robert Gonzalez
 */
#include <stdio.h>

#define MAX 10

void main() {
	int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX], salir = 0, op = -1;
	int offset_fila = 0, dim = 0;
	while (!salir) {
		op = -1;
		printf("Que desea hacer?\n");
		printf("1. Leer A y B\n");
		printf("2. Mostrar Matrices A y B\n");
		printf("3. Calcular A + B en B\n");
		printf("4. Calcular A - B en A\n");
		printf("5. Multiplicar A x B y dejar resultado en C\n");
		printf("6. Mostrar matriz auxiliar\n"); 
		printf("0. Salir\n");
		while (op == -1) {
			scanf("%i", &op);
			if (op < 0 || op > 6) {
				op = -1;
				printf("Opcion no reconocida. Ingrese una opcion valida\n");
			}
		}
		
		switch (op) {
		case 1:
			printf("Ingrese la dimension de las matrices\n");
			while (!dim) {
				scanf("%i", &dim);
				if (dim < 1 || dim > MAX) {
					dim = 0;
					printf("Numero invalido. Ingrese un valor entre 1 y 10\n");
				}
			}
			offset_fila = dim * MAX;
			printf("Llenando Matriz A\n");
			for (int i = 0; i < dim; i++) {
				for (int j = 0; j < dim; j++) {
					printf("Ingrese el valor para A[%d, %d] ", i, j);
					scanf("%i", &(A[i][j]));
				}
			}
			printf("Llenando Matriz B\n");
			for (int i = 0; i < dim; i++) {
				for (int j = 0; j < dim; j++) {
					printf("Ingrese el valor para B[%d, %d] ", i, j);
					scanf("%i", &(B[i][j]));
				}
			}
			break;
		case 2:
			if (dim) {
				printf("Mostrando matriz A\n");
				for (int i = 0; i < dim; i++) {
					for (int j = 0; j < dim; j++) {
						printf("%d ", A[i][j]);
					}
					printf("\n");
				}
				printf("Mostrando matriz B\n");
				for (int i = 0; i < dim; i++) {
					for (int j = 0; j < dim; j++) {
						printf("%d ", B[i][j]);
					}
					printf("\n");
				}
			}
			else {
				printf("No ha llenado las matrices\n");
			}
			break;
		case 3:
			printf("Calculando A + B, dejando resultado en B\n");
			if (dim) {
				int i, j;
				__asm
				{
					mov i, 0
					jinit:
					mov j, 0
					sumar:
					mov eax, i
					add eax, j
					mov ebx, B[eax*4]
					add ebx, A[eax*4]
					mov B[eax*4], ebx
					add j, 1
					mov eax, j
					cmp eax, dim
					jl sumar
					add i, 10
					mov eax, i
					cmp eax, offset_fila
					jl jinit
				}
			}
			else {
				printf("No ha llenado las matrices\n");
			}
			break;
		case 4:
			printf("Calculando A - B, dejando resultado en A\n");
			if (dim) {
				int i, j;
				__asm
				{
					mov i, 0
					jinit1:
					mov j, 0
						restar :
						mov eax, i
						add eax, j
						mov ebx, A[eax * 4]
						sub ebx, B[eax * 4]
						mov A[eax * 4], ebx
						add j, 1
						mov eax, j
						cmp eax, dim
						jl restar
						add i, 10
						mov eax, i
						cmp eax, offset_fila
						jl jinit1
				}
			}
			else {
				printf("No ha llenado las matrices\n");
			}
			break;
		case 5:
			printf("Calculando A x B, dejando resultado en C\n");
			if (dim) {
				int i, j, col, fila;
				__asm 
				{
					mov i, 0
					jinit2:
					mov j, 0
					multi:
					mov eax, i
						add eax, j
						mov ebx, 0
						mov C[eax*4], ebx
						mov col, 0
						mov fila, 0
						prodvec:
						mov ecx, i
						mov edx, j
						add ecx, col
						add edx, fila
						mov ebx, A[ecx * 4]
						mov eax, B[edx * 4]
						mul ebx
						mov ebx, i
						add ebx, j
						add C[4 * ebx], eax
						add col, 1
						add fila, 10
						mov eax, col
						cmp eax, dim
						jl prodvec
						add j, 1
						mov ecx, j
						cmp ecx, dim
						jl multi
						add i, 10
						mov ecx, i
						cmp ecx, offset_fila
						jl jinit2
				}
			}
			else {
				printf("No ha llenado las matrices\n");
			}
			break;
		case 6:
			if (dim) {
				printf("Mostrando matriz C\n");
				for (int i = 0; i < dim; i++) {
					for (int j = 0; j < dim; j++) {
						printf("%d ", C[i][j]);
					}
					printf("\n");
				}
			}
			else {
				printf("No ha llenado las matrices\n");
			}
			break;
		case 0:
		default:
			salir = 1;
		}
	}
	printf("Hasta luego\n");
}