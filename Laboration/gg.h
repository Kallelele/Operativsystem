#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PMWID 4
#define PMHEI 4
#define VMWID 4
#define VMHEI 7
#define TRUE 1
#define FALSE 0

typedef struct {
    int pages;
    int valid;
} Pagetable;

