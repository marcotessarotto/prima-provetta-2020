#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
/*

output:


dimensione di work_array: 75
less_then_len=33 larger_then_len=42
esecuzione primo processo:
min = -8890, max = -217
esecuzione secondo processo:
min = 32, max = 8615
bye!


 */


int work_array[] = {
 		7788, -7066, -6641, -2324, 7799, 3530, -8426, 267, -569, -4432, -217, 1761, 4885, 274, -6318, 3527, 4346, 1710, 2562, 7932, -8472, 7351, 354, -7463, 1657, -4285, 3926, -7771, -4498, -3430, -5992, 2488, 658, -6352, -7909, 188, 3005, -8457, 4242, 1259, 3662, 32, 7910, 1252, 3067, -5430, 6794, 3550, -3073, 2204, -821, 6769, 390, -2097, 1685, -2996, -6410, 3972, -4800, 4674, -2337, 1897, -1160, -7987, -8890, -2197, 938, -6302, -5909, 3723, 8615, 7096, 3080, -5511, 6339
};

typedef struct {

   int splitter_value; // valore "separatore"

   int * less_than_array; // array dei valori <= splitter_value

   unsigned int less_than_array_len; // lunghezza di less_than_array

   int * larger_than_array; // array dei valori > splitter_value

   unsigned int larger_than_array_len; // lunghezza di larger_than_array

} split_result;


split_result splitter(int * array, unsigned int array_len, int splitter_value) {

	unsigned int count = 0;

	if (array == NULL) {
		printf("splitter: array == NULL\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < array_len; i++) {
		if (array[i] <= splitter_value)
			count++;
	}

	split_result result;

	result.less_than_array = malloc(count * sizeof(int));
	result.less_than_array_len = count;

	if (result.less_than_array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	result.larger_than_array = malloc((array_len - count) * sizeof(int));
	result.larger_than_array_len = array_len - count;

	if (result.larger_than_array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	unsigned int less_counter = 0, larger_counter = 0;

	for (int i = 0; i < array_len; i++) {
		if (array[i] <= splitter_value) {
			result.less_than_array[less_counter] = array[i];
			less_counter++;
		} else {
			result.larger_than_array[larger_counter] = array[i];
			larger_counter++;
		}
	}

	// oppure:
//	unsigned int counter = 0;
//	for(int k = 0; k < array_len; k++) {
//		if(array[k] > splitter_value) {
//			result.larger_than_array[counter] = array[k];
//			counter++;
//		} else {
//			result.less_than_array[k-counter] = array[k];
//		}
//	}

	return result;
}


void analyze_array(int * array, unsigned int array_len) {
	// trova valore minimo, massimo

	if (array == NULL) {
		printf("analyze_array: array == NULL\n");
		exit(EXIT_FAILURE);
	}

	if (array_len == 0) {
		printf("analyze_array(): array_len == 0 niente da analizzare\n");
		return;
	}

	int min = INT_MAX; // oppure: array[0], visto che se siamo qui array_len > 0
	int max = INT_MIN; // come sopra

    for (unsigned int i = 0; i < array_len; i++) {
    	if (array[i] < min) {
    		min = array[i];
    	} else if (array[i] > max) {
    		max = array[i];
    	}
    }

    printf("min = %d, max = %d\n", min, max);

}


int main(int argc, char * argv[]) {

	split_result r;

	// test: splitter funziona correttamente per array_len == 0
	// r = splitter(work_array, 0, 123);
	// printf("less_then_len=%u larger_then_len=%u\n", r.less_then_len, r.larger_then_len);

	printf("dimensione (numero di elementi) di work_array: %lu\n", sizeof(work_array) / sizeof(int));

	r = splitter(work_array, sizeof(work_array) / sizeof(int), 0);

	printf("less_than_array_len=%u larger_than_array_len=%u\n", r.less_than_array_len, r.larger_than_array_len);

	printf("esecuzione primo processo:\n");
	switch(fork()) {
		case 0:
			analyze_array(r.less_than_array, r.less_than_array_len);

			exit(EXIT_SUCCESS);
		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);
		default:

			if (wait(NULL) == -1) {
				perror("wait error");
			}
	}

	printf("esecuzione secondo processo:\n");
	switch(fork()) {
		case 0:
			analyze_array(r.larger_than_array, r.larger_than_array_len);

			exit(EXIT_SUCCESS);
		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);
		default:

			if (wait(NULL) == -1) {
				perror("wait error");
			}
	}


	printf("bye!\n");

	return 0;
}


