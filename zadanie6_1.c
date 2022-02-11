//BIBLIOTEKI
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

//WARTOŚCI
#define N_AGENTS 20
#define N_ITEMS 20
#define OPENING_BID 100
#define NOMINAL_RAISE 1
#define BIDDING_ROUNDS 10000

int main(void)
{
//"PRAWDZIWA" LOSOWOŚĆ
	srand(time(NULL));
	
//PAMIĘĆ
	long int* OFERTY = malloc(N_ITEMS*sizeof(int));
		
//WYPEŁNIANIE POCZĄTKOWE
	for(int i=0;i<N_ITEMS;i++)
	{
		OFERTY[i] = OPENING_BID;
	}
	
//PRZEBIEG LICYTACJI
	clock_t START = clock();
	for(int i=0;i<BIDDING_ROUNDS;i++)
	{
		OFERTY[rand()%N_ITEMS]+=NOMINAL_RAISE;
	}
	clock_t STOP = clock();
	printf("Czas CPU[s]: %f\n",(double)(STOP - START) / CLOCKS_PER_SEC);
	
//WYSWIETLANIE WYNIKÓW KONCOWYCH
	long int SUMA=0;
	for(int i=0;i<N_ITEMS;i++)
	{
		SUMA+=OFERTY[i];
		printf("Cena: %d\n",OFERTY[i]);
	}
	printf("Suma: %d\n",SUMA);
}
