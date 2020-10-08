/* As 0-X game with computer pathner */
/* Game & Service Functions */

#include <stdlib.h>
#include <stdio.h>

static unsigned** pos;   /* Marker position (NYx2) array address */
static unsigned NX;      /* Default Boxes' number in each row */
static unsigned NY;      /* Default Row's number in game desk */

/* dynamic memory allocation for all game desk array */

int alloc(unsigned _nx, unsigned _ny) {
void** p;               /* position array pointer */
void* r;                /* row array pointer */
void** b;               /* box array pointer */
int i;                  /* row & position array index */
NX = _nx; NY = _ny; 
p = calloc(NY, sizeof(unsigned*));
r = calloc(NY, sizeof(unsigned long));
b = calloc(NY, sizeof(void*));
for(i=0; i < NY; i++) {
  b[i] = calloc(NX,  sizeof(unsigned long));
  p[i] = calloc(2, sizeof(unsigned));
} /* for */
relink(p, r, b);        /* link to xpat0 */
for(i=0, pos = (unsigned**) p; i < NY; i++) { /* init gamblers' */
  pos[i][0] = 0; pos[i][1] = NX - 1;          /* markers */
}                                             /* positions */
return(0);
} /* alloc */

/* free allocated memory */

int dealloc(void** p, void** b, void* r) {
int i;   /* row index */
for(i=0; i < NY; i++) {
  free(b[i]); free(p[i]);
} /* for */
free(p); free(b); free(r);
return(0);
} /* dealloc */

/* restore initial markers' positions */




