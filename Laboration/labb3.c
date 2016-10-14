#include "gg.h"


void getfile(int *arrfile) {
	FILE *Program1;
	Program1 = fopen("Program1.txt", "r");
	int i;
	for(i=0;i<1097;i++){
		fscanf(Program1,"%d,", &arrfile[i]);
	}	
}

void virtualmemory(char vm [][VMHEI]) {
	int i,j;
	int k = 0;
	for(i=0;i<VMHEI;i++){
		for(j=0;j<VMWID;j++){
			vm[i][j]=(char)('a' + k);
			k++;
		}
	}
	vm[6][2] = ' ';
	vm[6][3] = '.';
}

void addToPm(int fifo[], int n, Pagetable Page[], char pm[][PMHEI],char vm[][VMHEI]) {
	int i,j;
	int vmrad  = n/4;
	int kolumn = n % 2;
	int  pmrad = fifomax(fifo);
	for(j=0;j<VMHEI;j++) {
		if(Page[j].pages == pmrad) {
			Page[j].valid = FALSE;
			Page[j].pages = -1;
		}
	}
	
	for(i=0;i<PMWID;i++) {
		pm[pmrad][i] = vm[vmrad][i];
	}
	
	fifo[pmrad] = 0;
	Page[vmrad].pages = pmrad;
	Page[vmrad].valid = TRUE;
	printf("%c",pm[pmrad][kolumn]);
}

void CheckVm(int fifo[], int n, Pagetable Page[],char pm[][PMHEI],char vm[][VMHEI]) {
	int rad = n/4; // %2 för att hitta tecken på raden
	int kolumn = n % 2;
	// finns raden i pm? 
	if (Page[rad].valid == TRUE) {
		int pmrad = Page[rad].pages;
		printf("%c",pm[pmrad][kolumn]);
	} else if (Page[rad].valid == FALSE) {
		addToPm(fifo,n,Page,pm,vm); // skicka radnummer för att kunna lägga in raden i pm
	}
}		

int fifomax(int fifo[]){
	int max=fifo[0];
	int i,j;
	int temp = 0;
	for(i=0;i<4;i++){
		if(fifo[i]>max){
			max = fifo[i];
			temp = i;
		}
	}
	for(j=0;j<PMWID;j++) {
		fifo[j]++;
	}
	
	return temp;
}

void printPage(Pagetable Page[7]) {
	int i;
	printf("\n");
	for(i=0;i<VMHEI;i++) {
		printf("%d %d \n",Page[i].pages,Page[i].valid);
	}	
	
}
void PrintPM(char pm[PMWID][PMHEI]){
	int i,j;
	for(i=0;i<PMHEI;i++){
		for(j=0;j<PMWID;j++){
			printf("%c",pm[i][j]);
		}
	}
}

int main() {
	int arrfile[1094] = {0};
	int i;
	int fifo[4] = {0};
	char vm [VMWID][VMHEI] = {{0}};
	char pm [PMWID][PMHEI] = {{0}};
	Pagetable Page[7];
	for(i=0;i<VMHEI;i++) {		
		Page[i].valid = FALSE;
		Page[i].pages = -1;
	}
	getfile(arrfile);
	printPage(Page); // Skriv ut pagetable
	PrintPM(pm);	 // Skriv ut physical memory
	virtualmemory(vm); // initiera virtuellt minne
	for(i=0;i<1094;i++) {
		int n = arrfile[i];
		CheckVm(fifo,n,Page,pm,vm); // Skicka med fil,pagetable, pm och vm
	}
	printPage(Page); // skriv ut pagetable
	PrintPM(pm);
	return 0;
}
