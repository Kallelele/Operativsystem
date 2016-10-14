#include "gg.h"


void getfile(int arrfile[]) {
	FILE *Program1;
	Program1 = fopen("Program1.txt", "r");
	int i;
	for(i=0;i<1095;i++){
		fscanf(Program1,"%d,", &arrfile[i]);
	}
	fclose(Program1);
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

void virtualmemory(char vm [][VMWID]) {
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

void addToPm(int fifo[], int n, Pagetable Page[], char pm[][PMWID],char vm[][VMWID]) {
	int i,j;
	int vmrad  = n/4;
	int kolumn = n % 4;
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

void CheckVm(int fifo[], int n, Pagetable Page[],char pm[][PMWID],char vm[][VMWID]) {
	int rad = n/4; 
	int kolumn = n % 4;
	// finns raden i pm? 
	if (Page[rad].valid == TRUE) {
		int pmrad = Page[rad].pages;
		printf("%c",pm[pmrad][kolumn]);
	} else if (Page[rad].valid == FALSE) {
		addToPm(fifo,n,Page,pm,vm); // skicka radnummer för att kunna lägga in raden i pm
	}
}		


void PrintPage(Pagetable Page[7]) {
	int i;
	printf("\n");
	printf(" PAGE TABLE \n");
	for(i=0;i<VMHEI;i++) {
		printf(" %d\t%d\n",Page[i].pages,Page[i].valid);
	}	
	
}
void PrintPM(char pm[PMHEI][PMWID]){
	int i,j;
	printf("\n    PHYSICAL MEMORY \n");
	for(i=0;i<PMHEI;i++){
		for(j=0;j<PMWID;j++){
			printf("%c\t",pm[i][j]);
		}
		printf("\n");
	}
}

void meny(int arrfile[],int fifo[],Pagetable Page[],char pm[][PMWID],char vm[][VMWID]) {
	int val,i;
	int n = 0;
	
	do{
		printf("\n MENY \n");
		printf("1. Load file \n");
		printf("2. Enter a number of you choise \n");
		printf("3. Print the page table and the physical memory \n");
		printf("4. Exit \n");
		
		scanf("%d", &val);
		
		switch(val) {
			case 1:
				getfile(arrfile);
				for(i=0;i<1095;i++) {
					int n = arrfile[i];
					CheckVm(fifo,n,Page,pm,vm); // Skicka med fil,pagetable, pm och vm
				}
				break;
			case 2:
				printf("Enter a number: ");
				
				scanf("%d",&n);
				if(n<0 || n>26) {
					printf("Wrong input, enter a number between 0-26 \n");
				} else 
				CheckVm(fifo,n,Page,pm,vm); // Skicka med fil,pagetable, pm och vm
				break;
			case 3:
				PrintPage(Page);
				PrintPM(pm);
				break;
		
		} 
	} while(val!=4);
}
int main() {
	int arrfile[1094] = {0};
	int i;
	int fifo[PMWID] = {0};
	char vm [VMHEI][VMWID] = {{0}};
	char pm [PMHEI][PMWID] = {{0}};
	Pagetable Page[7];
	for(i=0;i<VMHEI;i++) {		
		Page[i].valid = FALSE;
		Page[i].pages = -1;
	}
	virtualmemory(vm); // initiera virtuellt minne
	meny(arrfile,fifo,Page,pm,vm);
	return 0;
}
