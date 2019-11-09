#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*SENARIO 1: ANASFALHS DIELEYSH ME SYGKROUSEIS.*/

#define threadsNum 4 /*ARITHMOS NHMATWN(AYTOKINHTWN) POU THELW NA DHMIOURGHSW*/

typedef struct {
    int *counter; /*DEIKTHS STON KOINO METRHTH.*/
    long *bDelay; /*DEIKTHS GIA TON APAITOUMENO  XRONO DIELEFDHS THS GEFYRAS. */
    pthread_t tID; /*KATAXWRHSH TOU NHMATOS(AYTOKINHTO) STO SYSTHMA ME TO ID TOU.*/
} thread_data;

/*SYNARTHSH: KOKKINA AYTOKINHTA STHN GEFYRA.*/
static void *redCarFunc(void *vargp)
{
    thread_data *data = (thread_data *)vargp; /*DHLWSH DEIKTH STHN DOMH 'thread_data'.*/

    printf("Red Car %d arrived at time %d.\n", data->tID, *data->counter); /*TO AYTOKINHTO FTANEI STHN AKRH THS GEFYRAS.*/
    ++*data->counter;
    printf("Red Car %d passing at time %d.\n", data->tID, *data->counter); /*TO AYTOKINHTO DIASXIZEI THN GEFYRA.*/
    *data->counter+=*data->bDelay;
    printf("Red Car %d passed at time %d.\n", data->tID, *data->counter); /*TO AYTOKINHTO FTANEI STHN ALLH AKRH THS GEFYRAS.*/
    ++*data->counter;

	return NULL;
}

/*SYNARTHSH: MPLE AYTOKINHTA STHN GEFYRA.*/
static void *blueCarFunc(void *vargp)
{
    thread_data *data = (thread_data *)vargp; /*DHLWSH DEIKTH STHN DOMH 'thread_data'.*/

    printf("%55s %d %15s %d.\n", "Blue Car", data->tID, "arrived at time", *data->counter); /*TO AYTOKINHTO FTANEI STHN AKRH THS GEFYRAS.*/
    ++*data->counter;
    printf("%55s %d %15s %d.\n", "Blue Car", data->tID, "passing at time", *data->counter); /*TO AYTOKINHTO DIASXIZEI THN GEFYRA.*/
    *data->counter+=*data->bDelay;
    printf("%55s %d %14s %d.\n", "Blue Car", data->tID, "passed at time", *data->counter); /*TO AYTOKINHTO FTANEI STHN ALLH AKRH THS GEFYRAS.*/
    ++*data->counter;

	return NULL;
}


/*KYRIWS PROGRAMMA*/
int main(int argc, char *argv[])
{
    int i;
    int cnt;
    long delay;

    /*DHLWSH NHMATWN(KOKKINA KAI MPLE AYTOKINHTA).*/
	thread_data threadDataCar[threadsNum];

	cnt=0; /*ARXIKOPOIHSH KOINOU METRHTH.*/
	delay=10; /*ARXIKOPOIHSH XRONOU POU APAITHTAI GIA THN DIASXISH THS GEFYRAS.*/

	/*BASIKES EKTYPWSEIS.*/
	printf("%40s\n", "Bridge");
	printf("%20s", "Left Side");
	printf("%45s\n", "Right Side");

	/*DHMIOURGIA NHMATWN KAI KLHSH THS KATALLHLHS SYNARTHSHS ANALOGA ME THN SYNTHIKH POU ISXUEI.*/
	for (i=0; i<threadsNum; i++){

        void *thread_func; /*PROSWRINH SYNARTHSH*/

        /*SYSXETISH METRHTWN ME THN DOMH TWN NHMATWN.*/
        threadDataCar[i].counter=&cnt;
        threadDataCar[i].bDelay=&delay;
        threadDataCar[i].tID = i;

		if (threadDataCar[i].tID%2!=0) {
			thread_func = redCarFunc; /*AN TO AYTOKINHTO EINAI KOKKINO.*/
		}
		else {
			thread_func = blueCarFunc; /*AN TO AYTOKINHTO EINAI MPLE.*/
		}
		/*DHMIOURGIA NHMATOS KAI KLHSH THS KATALLHLHS SYNARTHSHS.*/
        pthread_create(&threadDataCar[i].tID, NULL, thread_func, &threadDataCar[i]);
	}

	/*ANAMONH GIA TERMATISMO OLWN TWN NHMATWN.*/
	for (i=0; i<threadsNum; i++){
        pthread_join(threadDataCar[i].tID, NULL);
	}

    /*TERMATISMOS PROGRAMMATOS.*/
	exit(0);
}

