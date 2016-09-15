// CalculadoraPosFixada.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


typedef enum operation {
	SUN,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	EXPONENTIATION
} OPERATION;

typedef struct lista {
	float value;
	struct lista *next;
} Lista;

typedef struct pilha {
	Lista *top;
}Pilha;

Pilha* FactoryStack()
{
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	p->top = NULL;
	return p;
}

void Push(Pilha* pilha, float newValue) {
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->value = newValue;
	novo->next = pilha->top;
	pilha->top = novo;
}

bool IsEmptyStack(Pilha* pilha) {
	return (pilha->top == NULL);
}

int Count(Pilha * stack) {

	Lista* element;
	int count = 0;

	if (IsEmptyStack(stack)) {
		printf("Pilha esta Vazia!");
	}
	else {

		for (element = stack->top; element != NULL; element = element->next) {
			count++;
		}
	}
	return count;
}

float Pop(Pilha* pilha) {
	Lista* t;
	float topValue;

	if (IsEmptyStack(pilha)) {
		printf("Pilha vazia.\n");
		system("pause");
		return 0; /* aborta programa ainda nao pensei em como fazer isso */
	}
	else {
		t = pilha->top;
		topValue = t->value;
		pilha->top = t->next;
		free(t);
		return topValue;
	}
}

void ClearStack(Pilha* pilha) {
	if (!IsEmptyStack(pilha)) {

		Lista* currentTop = pilha->top;

		while (currentTop != NULL) {
			Lista* nextTop = currentTop->next;
			free(currentTop);
			currentTop = nextTop;
		}
		free(pilha);
	}
}

void PrintStack(Pilha* stack) {
	Lista* element;

	if (IsEmptyStack(stack)) {
		printf("Pilha esta Vazia!");
	}
	else {
		printf(" === Pilha ===\n");
		for (element = stack->top; element != NULL; element = element->next) {

			printf("|%6.2f      |\n", element->value);
		}
		printf(" =============\n");
	}
}

void ClearScreen() {
	system("cls");//So funciona Windows, mudar isso 
}

void ReadNumber(Pilha* stack) {
	printf("Digite um numero: \n");
	float num;
	scanf_s("%f", &num);
	Push(stack, num);
}

OPERATION ReadOperation() {
	ClearScreen();
	printf("Escolha uma das operações: \n");
	printf(" + : para Soma\n");
	printf(" - : para Soma\n");
	printf(" * : para Soma\n");
	printf(" / : para Soma\n");
	printf(" q : para eleva ao quadrado\n");
	char op;
	scanf_s("%c", &op);
	fflush(stdin);

	switch (toupper(op))
	{
	case '+':
		return SUN;
	case '-':
		return SUBTRACTION;
	case '*':
		return MULTIPLICATION;
	case '/':
		return DIVISION;
	case 'Q':
		return EXPONENTIATION;
	default:
		printf("Operação Invalida!\n");
		ReadOperation();
		break;
	}

}

void Sun(Pilha *stack) {

	if (Count(stack) < 2) {
		printf("Elementos insuficientes pra calcular\n");
	}
	else {
		float num1, num2;
		num1 = Pop(stack);
		num2 = Pop(stack);
		Push(stack, (num1 + num2));
	}
}

void Subtraction(Pilha* stack) {

	if (Count(stack) < 2) {
		printf("Elementos insuficientes pra calcular\n");
	}
	else {
		float num1, num2;
		num1 = Pop(stack);
		num2 = Pop(stack);
		Push(stack, (num1 - num2));
	}
}

void Multiplication(Pilha* stack) {
	if (Count(stack) < 2) {
		printf("Elementos insuficientes pra calcular\n");
	}
	else {
		float num1, num2;

		num1 = Pop(stack);
		num2 = Pop(stack);

		Push(stack, (num1 * num2));

	}
}

void Division(Pilha * stack) {
	if (Count(stack) < 2) {
		printf("Elementos insuficientes pra calcular\n");
	}
	else {
		float num1, num2;
		num1 = Pop(stack);
		num2 = Pop(stack);
		if (num2 == 0) {
			printf("Divisao por zero nao permitida, operacao anulada\n");
			Push(stack, num2);
			Push(stack, num1);
		}
		else
		{
			Push(stack, (num1 / num2));
		}
	}
}

void Exponentiation(Pilha* stack) {
	if (Count(stack) < 1) {
		printf("Elementos insuficientes pra calcular\n");
	}
	else {
		float num1;

		num1 = Pop(stack);

		Push(stack, (num1 * num1));

	}
}

void Calculate(Pilha * stack, OPERATION op) {
	switch (op)
	{
	case SUN:
		Sun(stack);
		break;
	case SUBTRACTION:
		Subtraction(stack);
		break;
	case MULTIPLICATION:
		Multiplication(stack);
		break;
	case DIVISION:
		Division(stack);
		break;
	case EXPONENTIATION:
		Exponentiation(stack);
		break;

	default:
		printf("Operação nao encontrada, heheh");
		break;
	}
}

void Menu() {

	ClearScreen();
	printf("|================= Calculadora HP ==========================|\n");
	printf("| Escolha uma das Opçoes:                                   |\n");
	printf("| A - Adicionar numero.                                     |\n");
	printf("| O - Escolher operacao.                                    |\n");
	printf("| C - Retirar numero.                                       |\n");
	printf("| I - Inicializar.                                          |\n");
	printf("| V - Visualizar pilha.                                     |\n");
	printf("| S - Sair.                                                 |\n");
	printf("|===========================================================|\n");
}


bool ReadOptionMenu(Pilha* stack) {
	Menu();
	char option;
	OPERATION op;
	scanf_s("%c", &option);
	fflush(stdin);

	switch (toupper(option))
	{
	case 'A':
		ReadNumber(stack);
		system("pause");
		return true;
	case 'O':
		op = ReadOperation();
		Calculate(stack, op);
		system("pause");
		return true;
	case 'C':
		Pop(stack);
		system("pause");
		return true;
	case 'I':
		ClearStack(stack);
		system("pause");
		return true;
	case 'V':
		PrintStack(stack);
		system("pause");
		return true;
	case 'S':
		return false;
	default:
		ReadOptionMenu(stack);
		break;
	}
}

int main()
{
	Pilha * myStack = FactoryStack();
	bool run = true;
	do
	{
		run = ReadOptionMenu(myStack);

	} while (run);

	system("pause");
	return 0;
}

