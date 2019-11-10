#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*Scenario 2: Safe transit, but without justice.(Whoever catches up, passes by.)*/

#define threadsNum 4 /*Total number of threads*/

pthread_mutex_t mutex; /*Global lock variable*/

typedef struct {
    int *counter; /*Pointer to shared counter*/
    long *bDelay; /*Pointer to the required time(delay) to cross the bridge*/
    pthread_t tID; /*Threads ID(number)*/
} thread_data;

/*Function: Red cars on the bridge*/
static void *redCarFunc(void *vargp)
{
    thread_data *data = (thread_data *)vargp; /*Pointer to struct: 'thread_data'*/

    pthread_mutex_lock(&mutex); /*Lock critical section. Runs only one thread at a time.*/
    printf("Red Car %d arrived at time %d.\n", data->tID, *data->counter); /*The car reaches the edge of the bridge.*/
    ++*data->counter;
    printf("Red Car %d passing at time %d.\n", data->tID, *data->counter); /*The car is crossing the bridge.*/
    *data->counter+=*data->bDelay;
    printf("Red Car %d passed at time %d.\n", data->tID, *data->counter); /*The car reaches the other edge of the bridge.*/
    ++*data->counter;
    pthread_mutex_unlock(&mutex); /*Unlock critical section.*/

	return NULL;
}

/*Function: Blue cars on the bridge*/
static void *blueCarFunc(void *vargp)
{
    thread_data *data = (thread_data *)vargp; /*Pointer to struct: 'thread_data'*/

    pthread_mutex_lock(&mutex); /*Lock critical section. Runs only one thread at a time.*/
    printf("%55s %d %15s %d.\n", "Blue Car", data->tID, "arrived at time", *data->counter); /*The car reaches the edge of the bridge.*/
    ++*data->counter;
    printf("%55s %d %15s %d.\n", "Blue Car", data->tID, "passing at time", *data->counter); /*The car is crossing the bridge.*/
    *data->counter+=*data->bDelay;
    printf("%55s %d %14s %d.\n", "Blue Car", data->tID, "passed at time", *data->counter); /*The car reaches the other edge of the bridge.*/
    ++*data->counter;
    pthread_mutex_unlock(&mutex); /*Unlock critical section.*/

	return NULL;
}


/*Main Program*/
int main(int argc, char *argv[])
{
    int i;
	int cnt;
	long delay;
	int nRed, nBlue;

    /*Threads declaration(Red & Blue cars)*/
	thread_data threadDataCar[threadsNum];

	cnt=0; /*Initialization of shared counter*/
	delay=10; /*Initialization of the required time(delay) to cross the bridge*/
	nRed=nBlue=0; /*Initialization of the total red & blue cars reaching the bridge*/

	/*Print Bridge Information*/
	printf("%40s\n", "Bridge");
	printf("%20s", "Left Side");
	printf("%45s\n", "Right Side");

	/*Create threads and call the appropriate function, by the if() condition*/
	for (i=0; i<threadsNum; i++){

        void *thread_func; /*Temporary function*/

        /*Correlating local variables with struct's(thread_data) variables*/
        threadDataCar[i].counter=&cnt;
        threadDataCar[i].bDelay=&delay;
        threadDataCar[i].tID = i;

		if (threadDataCar[i].tID%2!=0) {
            /*To avoid collisions, if a red car arrives and there is a blue car on the bridge(nBlue>0),
            then the red waits(nRed++) for a time equal to the required crossing time(delay).*/
            while (nBlue>0){
                nRed++;
                usleep(delay);
            }
			thread_func = redCarFunc; /*If car is red, choose redCarFunc*/
            /*When a red car crosses the bridge, the counter of red cars(nRed) becomes 0.*/
            nRed--;
            if (nRed==0) break;
		}
		else {
            /*To avoid collisions, if a blue car arrives and there is a red car on the bridge(nRed>0),
            then the blue waits(nBlue++) for a time equal to the required crossing time(delay).*/
            while (nRed>0){
            nBlue++;
            usleep(delay);
            }
			thread_func = blueCarFunc; /*If car is blue, choose blueCarFunc*/
            /*When a blue car crosses the bridge, the counter of blue cars(nBlue) becomes 0.*/
            nBlue--;
            if (nBlue==0) break;
		}
		/*Create thread and call the correct function*/
        pthread_create(&threadDataCar[i].tID, NULL, thread_func, &threadDataCar[i]);
	}

	/*Wait all threads to end*/
	for (i=0; i<threadsNum; i++){
        pthread_join(threadDataCar[i].tID, NULL);
	}

    /*Close program*/
	exit(0);
}


