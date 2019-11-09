#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*SENARIO 2: ASFALHS DIELEYSH XWRIS DIKAIWSINH.*/

#define threadsNum 4 /*ARITHMOS NHMATWN(AYTOKINHTWN) POU THELW NA DHMIOURGHSW*/

pthread_mutex_t mutex; /*GLOBAL METABLHTH KLEIDWMATOS.*/

typedef struct {
    int *counter; /*DEIKTHS STON KOINO METRHTH.*/
    long *bDelay; /*DEIKTHS GIA TON APAITOUMENO  XRONO DIELEFDHS THS GEFYRAS. */
    pthread_t tID; /*KATAXWRHSH TOU NHMATOS(AYTOKINHTO) STO SYSTHMA ME TO ID TOU.*/
} thread_data;

/*SYNARTHSH: KOKKINA AYTOKINHTA STHN GEFYRA.*/
static void *redCarFunc(void *vargp)
{
    thread_data *data = (thread_data *)vargp; /*DHLWSH DEIKTH STHN DOMH 'thread_data'.*/

    pthread_mutex_lock(&mutex);
    printf("Red Car %d arrived at time %d.\n", data->tID, *data->counter); /*TO AYTOKINHTO BRISKETAI STHN AKRH THS GEFYRAS.*/
    ++*data->counter;
    printf("Red Car %d passing at time %d.\n", data->tID, *data->counter); /*TO AYTOKINHTO DIASXIZEI THN GEFYRA.*/
    *data->counter+=*data->bDelay;
    printf("Red Car %d passed at time %d.\n", data->tID, *data->counter); /*TO AYTOKINHTO FTANEI STHNN ALLH AKRH THS GEFYRAS.*/
    ++*data->counter;
    pthread_mutex_unlock(&mutex);

	return NULL;
}

/*SYNARTHSH: MPLE AYTOKINHTA STHN GEFYRA.*/
static void *blueCarFunc(void *vargp)
{
    thread_data *data = (thread_data *)vargp; /*DHLWSH DEIKTH STHN DOMH 'thread_data'.*/

    pthread_mutex_lock(&mutex); /*KLEIDWMA KRISIMOU SHMEIOU. MONO ENA NHMA TH FORA MPOREI NA EKTELESEI.*/
    printf("%55s %d %15s %d.\n", "Blue Car", data->tID, "arrived at time", *data->counter); /*TO AYTOKINHTO BRISKETAI STHN AKRH THS GEFYRAS.*/
    ++*data->counter;
    printf("%55s %d %15s %d.\n", "Blue Car", data->tID, "passing at time", *data->counter); /*TO AYTOKINHTO DIASXIZEI THN GEFYRA.*/
    *data->counter+=*data->bDelay;
    printf("%55s %d %14s %d.\n", "Blue Car", data->tID, "passed at time", *data->counter); /*TO AYTOKINHTO FTANEI STHNN ALLH AKRH THS GEFYRAS.*/
    ++*data->counter;
    pthread_mutex_unlock(&mutex); /*KSEKLEIDWMA KRISIMOU SHMEIOU.*/

	return NULL;
}


/*KYRIWS PROGRAMMA*/
int main(int argc, char *argv[])
{
    int i;
	int cnt;
	long delay;
	int nRed, nBlue;

    /*DHLWSH NHMATWN(KOKKINA KAI MPLE AYTOKINHTA).*/
	thread_data threadDataCar[threadsNum];

	cnt=0; /*ARXIKOPOIHSH KOINOU METRHTH.*/
	delay=10; /*ARXIKOPOIHSH XRONOU POU APAITHTAI GIA THN DIASXISH THS GEFYRAS.*/
	nRed=nBlue=0; /*SYNOLA APO KOKKINA KAI MPLE AYTOKINHTA POU FTANOUN STHN GEFYRA.*/

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
            /*GIA THN APOFYGH SUGROUSEWN, EAN FTASEI KOKKINO AYTOKINHTO KAI YPARXEI MPLE STHN GEFYRA(nBlue>0),
            TOTE TO KOKKINO PERIMENEI(nRed++) GIA XRONO ISO ME TO XRONO DIELEFSHS(delay).*/
            while (nBlue>0){
                nRed++;
                usleep(delay);
            }
			thread_func = redCarFunc; /*AN TO AYTOKINHTO EINAI KOKKINO.*/
            /*OTAN ENA KOKKINO AYTOKINHTO DIASXISEI THN GEFYRA O METRHTHS(nRed) MHDENIZETAI.*/
            nRed--;
            if (nRed==0) break;
		}
		else {
            /*GIA THN APOFYGH SUGROUSEWN, EAN FTASEI MPLE AYTOKINHTO KAI YPARXEI KOKKINO STHN GEFYRA(nRed>0),
            TOTE TO MPLE PERIMENEI(nBlue++) GIA XRONO ISO ME TO XRONO DIELEFSHS(delay).*/
            while (nRed>0){
            nBlue++;
            usleep(delay);
            }
			thread_func = blueCarFunc; /*AN TO AYTOKINHTO EINAI MPLE.*/
            /*OTAN ENA MPLE AYTOKINHTO DIASXISEI THN GEFYRA O METRHTHS(nBlue) MHDENIZETAI.*/
            nBlue--;
            if (nBlue==0) break;
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


