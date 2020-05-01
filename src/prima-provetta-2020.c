#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

// https://www.random.org/integers/?num=256&min=-100&max=100&col=1&base=10&format=html&rnd=new

/*
 *

scrivere la funzione:


typedef struct {
   int * even_numbers;
   unsigned int even_numbers_len;

   int * odd_numbers;
   unsigned int odd_numbers_len;
} even_odd_split_result;


even_odd_split_result * split_even_odd_numbers(int * array, unsigned int array_len);

//   2271, 80, -9517, -6895, -5389, -5764, -357, -3652, -6164, 9309, 8467, 1073, -2427, 9940, 7031, -5629, 436, 1326, 9882, 622, 8178, -295, -5638, -4526, 1755, -289, 3627, 9796, 1553, -8979, -3671, 7616, 9202, -5343, -9970, -7094, -1017, 2607, -5720, -6675, 9637, 9011, -9739, 503, 9216, 2162, 4118, -2715, -9766, -7032, -6972, 2973, -7015, 1380, -6558, -3698, -2364, 8682, -7756, -8279, -2799, 365, -9214, -6677, 9928, -1374, -8407, -4041, -2005, 9524, -7641, 1042, -7707, -4506, -7341, 2307, 8752, 7550, -1642, 3638, -6126, -6560, 3535, -1659, -5532, 4804, -2242, -5830, 2188, -8414, 6342, 771, -4323, -3534, -8127, 4073, -1030, 4785, -4103, 5606, 5617, -6273, -7138, -8293, 9751, 5170, -4141, -459, 1911, 1384, 9933, -1484, -3321, 7257, 6908, -2243, 2332, -3802, 736, -8540, -1848, -2006, 5057, 3960, 5140, -3201, -1041, -5906, -4084, -9757, -5192, -2850, 7926, -6888, -7815, -6819, 9972, -5346, -6037, -5045, -7346, 8181, -7091, 5494, -2860, -8474, -6661, 6632, 7137, 466, -8077, 7974, 5497, -9265, -1850, -7850, 8383, -1698, 7886, 7784, -3780, -6550, -32, 8085, -3162, -2983, 9818, -2572, 9097, 4594, -4202, -1335, 8357, 9183, -2203, -1628, 7751, 6015, -5527, -7586, -7805







scrivere un programma in C seguendo queste specifiche:

*INSERITE TUTTI gli header files necessari (#include ...)*



è dato un array di int inizializzato con i seguenti valori:

// definitela come variabile globale

int work_array[] = {

   7788, -7066, -6641, -2324, 7799, 3530, -8426, 267, -569, -4432, -217, 1761, 4885, 274, -6318, 3527, 4346, 1710, 2562, 7932, -8472, 7351, 354, -7463, 1657, -4285, 3926, -7771, -4498, -3430, -5992, 2488, 658, -6352, -7909, 188, 3005, -8457, 4242, 1259, 3662, 32, 7910, 1252, 3067, -5430, 6794, 3550, -3073, 2204, -821, 6769, 390, -2097, 1685, -2996, -6410, 3972, -4800, 4674, -2337, 1897, -1160, -7987, -8890, -2197, 938, -6302, -5909, 3723, 8615, 7096, 3080, -5511, 6339

};



// è dato questo tipo dati:

typedef struct {

   int splitter_value; // valore "separatore"

   int * less_than_array; // array dei valori <= splitter_value

   unsigned int less_than_array_len; // lunghezza di less_than_array

   int * larger_than_array; // array dei valori > splitter_value

   unsigned int larger_than_array_len; // lunghezza di larger_than_array

} split_result;



implementare la seguente funzione:



split_result splitter(int * param_array, unsigned int array_len, int splitter_value);



splitter divide in due parti param_array, dove array_len è il numero di celle:

*alloca* due nuovi array (chiamiamoli array1 ed array2) dove

in array1 vengono copiati i valori di param_array che sono minori o uguali di splitter_value

mentre in array2 vengono copiati i valori di param_array che sono maggiori di splitter_value

utilizza il tipo dati split_result per restituire i due nuovi array, con le loro dimensioni, e splitter_value



i due array creati hanno dimensione "esatta", cioè non ci devono essere celle non utilizzate.



potete fare un primo passaggio e contare quanti valori sono <= splitter_value

poi fate un secondo passaggio e popolate i due array



esempio d'uso di splitter():

int array [] = { 0,1,2,3,4,5,6,7,8,9 };

split_result r;

r = split_result(array, 10, 5);

// il primo array conterrà i valori 0,1,2,3,4,5

// l'altro array conterrà i valori 6,7,8,9



nel main():

- scrivere la dimensione di work_array

- "splittare" work_array per splitter_value = 0

- scrivete il numero di celle dei due array restituiti



poi, il processo padre crea due processi figli:



il primo processo figlio lavorerà sull'array less_than_array (quello con valori <= 0) per cercare e scrivere:

valore minimo, massimo di less_than_array



quando il primo processo figlio ha terminato, allora il processo padre avvia il secondo processo figlio:



il secondo processo figlio lavorerà sull'array larger_than_array (quello con valori > 0) per cercare e scrivere:

valore minimo, massimo di larger_than_array



quando il secondo processo figlio ha terminato, allora il processo padre scrive il messaggio "bye!" e può terminare.







il risultato su stdout del programma sarà del tipo:



dimensione di work_array: <scrivete il numero di celle...>

less_then_len=<nn> larger_then_len=<mm>

esecuzione primo processo:

min = -...., max = .....

esecuzione secondo processo:

min = ...., max = ....

bye!







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


