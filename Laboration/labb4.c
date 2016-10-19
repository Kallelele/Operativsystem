#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int FCFS(int parked, int vector[], int size) {
	int i, now, sum;
	sum = abs(vector[0] - parked);
	now = vector[0];
	for (i = 1; i < size; i++) {
		sum = sum + abs(vector[i] - now);
		now = vector[i];
	}
	return sum;
}

void sort(int vector[], int size) {
	int i,j,temp;
	for (i = 1; i < size; i++) {
		for (j = 0; j < size - i; j++) {
			if (vector[j] > vector[j + 1]) {
				temp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = temp;
			}
		}	
	}
}
int SSTF(int parked, int vector[], int size) {
	int i, now, sum, beenthere[100] = { 0 };    /* beenthere = 0, vi har inte varit där än */
	int ready = 0, distance, nearest;
	sum = 0;
	now = parked;
	while (!ready) {
		/* look up the nearest among the ones we have not visited */
		distance = INT_MAX;
		for (i = 0; i < size; i++) {
			if (!beenthere[i]) {
				if (distance > abs(now - vector[i])) {
					distance = abs(now - vector[i]);
					nearest = i;
				}
			}
		}
		/* move */
		now = vector[nearest];
		/* sum travel */
		sum = sum + distance;
		/* set beenthere */
		beenthere[nearest] = 1;
		/* ready yet? */
		ready = 1;
		for (i = 0; i < size; i++) {
			if (beenthere[i] == 0) {
				ready = 0;
			}
		}
	}
	return sum;
}

int SCAN(int parked, int vector[], int size) {
	int i, sum = 0, now, distance = INT_MAX, nearest, beenthere[100] = { 0 };
	now = parked;
	sort(vector,size); // Sortera vektorn i egen funktion
	if(parked > vector[size-1]) {
		sum = abs(parked-199);
	} else {	
	for (i = 0; i < size; i++) {
		if (vector[i] > now) {
			distance = abs(now - vector[i]);
			sum = sum + distance;
			nearest = i;
			now = vector[nearest];
			beenthere[nearest] = 1;
		}
	}
	sum = sum + abs(vector[size - 1] - 199);
	}  
	now = 199;
	for (i = size-1; i >= 0; i--) {
		if (vector[i] < now) {
			if (beenthere[i] == 0) {
				distance = abs(now - vector[i]);
				sum = sum + distance;
				nearest = i;
				now = vector[nearest];
			}
		}
	}
	return sum;
}

int CSCAN(int parked, int vector[], int size) {
	int i, sum = 0, now, distance = INT_MAX, nearest, beenthere[100] = { 0 };
	now = parked;
	sort(vector,size); // Sortera vektorn i egen funktion
	if(parked > vector[size-1]) {
		sum = abs(parked-199);
	} else {	
	for (i = 0; i < size; i++) {
		if (vector[i] >= now) {
			distance = abs(now - vector[i]);
			sum = sum + distance;
			nearest = i;
			now = vector[nearest];
			beenthere[nearest] = 1;
		}
	}
	sum = sum + abs(vector[size - 1] - 199);
	}  
	
	now = 0;
	for (i = 0; i < size; i++) {
		if (vector[i] > now) {
			if (beenthere[i] == 0) {
				distance = abs(now - vector[i]);
				sum = sum + distance;
				nearest = i;
				now = vector[nearest];
			}
		}
	}
	return sum;
}

int LOOK(int parked, int vector[], int size) {
	int i, sum = 0, now, distance = INT_MAX, nearest, beenthere[100] = { 0 };
	now = parked;
	sort(vector,size); // Sortera vektorn i egen funktion
	for (i = 0; i < size; i++) {
		if (vector[i] > now) {
			distance = abs(now - vector[i]);
			sum = sum + distance;
			nearest = i;
			now = vector[nearest];
			beenthere[nearest] = 1;
		}
	}
	for (i = size-1; i >= 0; i--) {
		if (vector[i] < now) {
			if (beenthere[i] == 0) {
				distance = abs(now - vector[i]);
				sum = sum + distance;
				nearest = i;
				now = vector[nearest];
			}
		}
	}
	return sum;
}

int CLOOK(int parked, int vector[], int size) {
	int i, sum = 0, now, distance = INT_MAX, nearest, beenthere[100] = { 0 };
	now = parked;
	sort(vector,size); // Sortera vektorn i egen funktion
	for (i = 0; i < size; i++) {
		if (vector[i] >= now) {
			distance = abs(now - vector[i]);
			sum = sum + distance;
			nearest = i;
			now = vector[nearest];
			beenthere[nearest] = 1;
		}
	}
	now = vector[0];
	for (i = 0; i < size; i++) {
		if (vector[i] >= now) {
			if (beenthere[i] == 0) {
				distance = abs(now - vector[i]);
				sum = sum + distance;
				nearest = i;
				now = vector[nearest];
			}
		}
	}
	return sum;
}
main() {
	int v[] = { 98, 183, 37, 122, 14, 124, 65, 67 };
	int v2[] = { 183, 37, 122, 14, 124, 65, 67, 98 };
	int v3[] = { 37, 122, 14, 124, 65, 67, 98, 182 };
	int v4[] = { 122, 14, 124, 65, 67, 98, 183, 38 };
	int v5[] = { 98, 183, 37, 122, 14, 124, 65, 199 };
	printf("KÖ 1: \n");
	printf("FCFS: %d\n", FCFS(53, v, sizeof(v) / sizeof(int)));
	printf("SSTF: %d\n", SSTF(53, v, sizeof(v) / sizeof(int)));
	printf("SCAN: %d\n", SCAN(53, v, sizeof(v) / sizeof(int)));
	printf("CSCAN: %d\n", CSCAN(53, v, sizeof(v) / sizeof(int)));
	printf("LOOK: %d\n", LOOK(53, v, sizeof(v) / sizeof(int)));
	printf("CLOOK: %d\n", CLOOK(53, v, sizeof(v) / sizeof(int)));
	
	printf("KÖ 2: \n");
	printf("FCFS: %d\n", FCFS(98, v2, sizeof(v) / sizeof(int)));
	printf("SSTF: %d\n", SSTF(98, v2, sizeof(v) / sizeof(int)));
	printf("SCAN: %d\n", SCAN(98, v2, sizeof(v) / sizeof(int)));
	printf("CSCAN: %d\n", CSCAN(98, v2, sizeof(v) / sizeof(int)));
	printf("LOOK: %d\n", LOOK(98, v2, sizeof(v) / sizeof(int)));
	printf("CLOOK: %d\n", CLOOK(98, v2, sizeof(v) / sizeof(int)));
	
	printf("\nKÖ 3: \n");
	printf("FCFS: %d\n", FCFS(183, v3, sizeof(v) / sizeof(int)));
	printf("SSTF: %d\n", SSTF(183, v3, sizeof(v) / sizeof(int)));
	printf("SCAN: %d\n", SCAN(183, v3, sizeof(v) / sizeof(int)));
	printf("CSCAN: %d\n", CSCAN(183, v3, sizeof(v) / sizeof(int)));
	printf("LOOK: %d\n", LOOK(183, v3, sizeof(v) / sizeof(int)));
	printf("CLOOK: %d\n", CLOOK(183, v3, sizeof(v) / sizeof(int)));
	
	printf("\nKÖ 4: \n");
	printf("FCFS: %d\n", FCFS(37, v4, sizeof(v) / sizeof(int)));
	printf("SSTF: %d\n", SSTF(37, v4, sizeof(v) / sizeof(int)));
	printf("SCAN: %d\n", SCAN(37, v4, sizeof(v) / sizeof(int)));
	printf("CSCAN: %d\n", CSCAN(37, v4, sizeof(v) / sizeof(int)));
	printf("LOOK: %d\n", LOOK(37, v4, sizeof(v) / sizeof(int)));
	printf("CLOOK: %d\n", CLOOK(37, v4, sizeof(v) / sizeof(int)));
	
	printf("\nKÖ 5: \n");
	printf("FCFS: %d\n", FCFS(122, v5, sizeof(v) / sizeof(int)));
	printf("SSTF: %d\n", SSTF(122, v5, sizeof(v) / sizeof(int)));
	printf("SCAN: %d\n", SCAN(122, v5, sizeof(v) / sizeof(int)));
	printf("CSCAN: %d\n", CSCAN(122, v5, sizeof(v) / sizeof(int)));
	printf("LOOK: %d\n", LOOK(122, v5, sizeof(v) / sizeof(int)));
	printf("CLOOK: %d\n", CLOOK(122, v5, sizeof(v) / sizeof(int)));
	system("PAUSE");
}
