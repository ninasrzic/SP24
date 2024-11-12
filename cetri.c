#define _CRT_SECURE_NO_WARNINGS

/*Napisati program za zbrajanje i mno�enje polinoma.*/


#include<stdio.h>
#include<stdlib.h>
struct Polynomial;

typedef struct Polynomial* Polynom;

struct Polynomial
{
	int Coeff;
	int Exp;
	Polynom Next;
};


void ReadPolynomial(Polynom, char*);
void PrintPolynomial(Polynom);
void AddPolynomial(Polynom, Polynom, Polynom);
void MulPolynomial(Polynom, Polynom, Polynom);

int main()
{
	struct Polynomial P1, P2, S, P;

	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	P.Next = NULL;

	ReadPolynomial(&P1, "P1_list.txt");
	PrintPolynomial(&P1);

	ReadPolynomial(&P2, "P2_list.txt");
	PrintPolynomial(&P2);


	AddPolynomial(P1.Next, P2.Next, &S);
	printf("\n\nSuma je:");
	PrintPolynomial(&S);

	MulPolynomial(P1.Next, P2.Next, &P);
	printf("\n\nProdukt je:");
	PrintPolynomial(&P);

	printf("\n");
	return 0;
}


void ReadPolynomial(Polynom P, char* ime_dat)
{
	FILE* dat;
	Polynom q, temp, prev;

	dat = fopen(ime_dat, "r");
	if (NULL == dat)
	{
		printf("Greska u otvaranju datoteke!!!");
		exit(1);
	}
	else
	{
		while (0 == feof(dat))
		{
			q = (Polynom)malloc(sizeof(struct Polynomial));

			fscanf(dat, " %d %d", &q->Coeff, &q->Exp);

			temp = P->Next;
			prev = P;
			while (temp != NULL && temp->Exp > q->Exp)
			{
				prev = temp;
				temp = temp->Next;
			}

			prev->Next = q;

			if (temp != NULL)
				q->Next = temp;
			else
				q->Next = NULL;
		}
	}


}

void PrintPolynomial(Polynom P)
{

	printf("\n");

	P = P->Next;

	while (P != NULL)
	{
		if (P->Coeff > 0)
			printf("\t+%d*x^%d", P->Coeff, P->Exp);
		else
			printf("\t%d*x^%d", P->Coeff, P->Exp);
		P = P->Next;
	}


	printf("\n");

}

void AddPolynomial(Polynom P1, Polynom P2, Polynom S)
{
	Polynom q, temp;

	while (P1 != NULL && P2 != NULL)
	{
		q = (Polynom)malloc(sizeof(struct Polynomial));
		q->Next = NULL;


		if (P1->Exp > P2->Exp)
		{
			q->Exp = P1->Exp;
			q->Coeff = P1->Coeff;
			P1 = P1->Next;
		}
		else if (P1->Exp < P2->Exp)
		{
			q->Exp = P2->Exp;
			q->Coeff = P2->Coeff;
			P2 = P2->Next;
		}
		else  // P1->Exp == P2->Exp
		{
			q->Exp = P1->Exp;
			q->Coeff = P1->Coeff + P2->Coeff;
			P1 = P1->Next;
			P2 = P2->Next;
		}
		S->Next = q;
		S = q;
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		q = (Polynom)malloc(sizeof(struct Polynomial));
		q->Next = NULL;
		q->Exp = temp->Exp;
		q->Coeff = temp->Coeff;
		S->Next = q;
		S = q;
		temp = temp->Next;
	}

}


void MulPolynomial(Polynom P1, Polynom P2, Polynom P)
{
	Polynom q, first = P1, second = P2, temp, prev;
	int n;

	while (first != NULL)
	{
		second = P2;
		while (second != NULL)
		{
			temp = P->Next;
			prev = P;

			n = first->Exp + second->Exp;

			while (temp != NULL && temp->Exp > n)
			{
				prev = temp;
				temp = temp->Next;
			}

			if (temp != NULL && temp->Exp == n)
				temp->Coeff += first->Coeff * second->Coeff;
			else
			{
				q = (Polynom)malloc(sizeof(struct Polynomial));

				q->Exp = n;
				q->Coeff = first->Coeff * second->Coeff;

				prev->Next = q;
				q->Next = temp;
			}

			second = second->Next;
		}
		first = first->Next;
	}

	while (P->Next != NULL)
	{
		if (P->Next->Coeff == 0)
		{
			temp = P->Next;
			P->Next = P->Next->Next;
			free(temp);
		}
		P = P->Next;
	}

}