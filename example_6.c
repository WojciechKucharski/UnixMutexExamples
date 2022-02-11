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

struct WSP {
	int OFERTY[N_ITEMS];
	pthread_mutex_t muteks[N_ITEMS];
	pthread_mutexattr_t at;
};

int main(void)
{
	
//"PRAWDZIWA" LOSOWOŚĆ
	srand(time(NULL));
//PAMIĘĆ WSPÓLNA
	void *MEM_WSPOFERTY = (void *)0;
	int shmid;
	struct WSP *WSPOFERTY;
	shmid = shmget(421196, 2*sizeof(struct WSP), 0666 | IPC_CREAT);
	
//SPRAWDZANIE CZY WYSTĄPIŁ BŁĄD
	if (shmid == -1) {
		perror("shmget - error");
		exit(1);
	}
	MEM_WSPOFERTY = shmat(shmid, (void *)0, 0);
	if (MEM_WSPOFERTY == (void *)-1) {
		perror("shmat - error");
		exit(2);
	}
	WSPOFERTY = (struct WSP *)MEM_WSPOFERTY;
	

// OBSŁUGA MUTEXA
		pthread_mutexattr_init(&(WSPOFERTY->at));
		pthread_mutexattr_setpshared(&(WSPOFERTY->at),PTHREAD_PROCESS_SHARED);
		
//WYPEŁNIANIE POCZĄTKOWE
	for(int i=0;i<N_ITEMS;i++)
	{
		WSPOFERTY->OFERTY[i] = OPENING_BID;
pthread_mutex_init(&(WSPOFERTY->muteks[i]), &(WSPOFERTY->at));
	}

//PRZEBIEG LICYTACJI
	clock_t START = clock();
	for(int j=0;j<N_AGENTS;j++)
	{
	if(fork()==0)
	{
		for(int i=0;i<BIDDING_ROUNDS;i++)
		{
			int LOSOWA_OFERTA = rand()%N_ITEMS;
			pthread_mutex_lock(&(WSPOFERTY->muteks[LOSOWA_OFERTA]));	
			WSPOFERTY->OFERTY[LOSOWA_OFERTA]+=NOMINAL_RAISE;
			pthread_mutex_unlock(&(WSPOFERTY->muteks[LOSOWA_OFERTA]));
		}
	exit(0);
	}
	}
	for(int i=0;i<N_AGENTS;i++){wait(NULL);}
	clock_t STOP = clock();
	printf("Czas CPU[s]: %f\n",(double)(STOP - START) / CLOCKS_PER_SEC);
	
//WYSWIETLANIE WYNIKÓW KONCOWYCH
	long int SUMA=0;
	for(int i=0;i<N_ITEMS;i++)
	{
		SUMA+=WSPOFERTY->OFERTY[i];
		printf("Koncowa cena przedmiotu: %4d\n",WSPOFERTY->OFERTY[i]);
	}
	printf("Suma wszystkich cen: %d\n",SUMA);
}


