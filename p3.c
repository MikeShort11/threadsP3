#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int trial_division_helper(int dividend){
	for (int divisor = 2; divisor <= sqrt(dividend); divisor++){
		if ((dividend % divisor) == 0){
			return divisor;
		}
	}
	return 0;
}

void* trial_division(void* arg) {
	int number = *(int*)arg;
	int* result = (int *)malloc(10*sizeof(int)); //no need for realloc, max factors is ten
	int factor_counter = 0;
	int factor = trial_division_helper(number);
	if (factor != 0) {
		result[factor_counter] = factor;
		factor_counter++;
		trial_division_helper(number / factor);
	} else {
		return result;
	}
}


int main(){
	//create the array
	int *arr[25]:
	scanf("%d", &arr[i]);
	length = sizeof(arr) / sizeof(arr[0]);
	//create threads based on the size of the array
	pthread_t *threads = malloc(length * sizeof(pthread_t));
	int *ids = malloc(length * sizeof(int));
	

	for (int i=0; i < length; i++){
		ids[i] = i;
		pthread_create(&threads[i], NULL, trial_division, arr[i]);
	}
	for (int i = 0; i < n; i++) {
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free(ids);
	return 0;
}
