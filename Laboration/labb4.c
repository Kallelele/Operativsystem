/* Program som simulerar olika algoritmer för diskarmsrörelser
Se Silberschatz/Galvin/Gagne sid 493 och framåt */

/*   För alla funktioner gäller:
pre: size är storleken av vector och större än 0. size < 100.
post: returnerar summan av rörelserna från parked genom hela vektorn */

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
		printf("visit %d\n", now);
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

	int i, j, sum = 0, now, zero = 0, distance = INT_MAX, nearest, ready = 0, fromzero = 0, beenthere[100] = { 0 };
	int max = 0, temp;
	now = parked;
	for (i = 1; i < size; i++) {
		for (j = 0; j < size - i; j++) {
			if (vector[j] > vector[j + 1]) {
				temp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < size; i++) {
		if (vector[i] > now) {
			distance = abs(now - vector[i]);
			sum = sum + distance;
			nearest = i;
			now = vector[nearest];
			beenthere[nearest] = 1;
			printf("visit %d\n", now);
		}
		
	}
	sum = sum + abs(vector[size - 1] - 199);
	now = 199;
	for (i = size-1; i >= 0; i--) {
		if (vector[i] < now) {
			if (beenthere[i] == 0) {
				distance = abs(now - vector[i]);
				sum = sum + distance;
				nearest = i;
				now = vector[nearest];
				printf("visit %d\n", now);
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
	printf("FCFS: %d\n", FCFS(53, v, sizeof(v) / sizeof(int)));
	printf("SSTF: %d\n", SSTF(53, v, sizeof(v) / sizeof(int)));
	printf("SCAN: %d\n", SCAN(53, v, sizeof(v) / sizeof(int)));
	system("PAUSE");
}
