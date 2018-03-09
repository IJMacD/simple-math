#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "lexer.h"
#include "parser.h"

int fVerbose = 0;

void printMatrix_2_2 (struct matrix_2_2 m) {
    printf("\t[ %lf %lf ]\n\t[ %lf %lf ]\n", m.val[0][0], m.val[1][0], m.val[0][1], m.val[1][1]);
}

void printVector_2 (struct vector_2 v) {
    printf("\t[ %lf ]\n\t[ %lf ]\n", v.val[0], v.val[1]);
}

void dotMatrix_2_2_Vector_2 (struct vector_2* out, struct matrix_2_2 m, struct vector_2 v) {
    const double tmp = v.val[0];

    out->val[0] = m.val[0][0] * v.val[0] + m.val[1][0] * v.val[1];
    out->val[1] = m.val[0][1] * tmp      + m.val[1][1] * v.val[1];
}

double detMatrix_2_2 (struct matrix_2_2 m) {
    return m.val[0][0] * m.val[1][1] - m.val[0][1] * m.val[1][0];
}

void invMatrix_2_2 (struct matrix_2_2 *out, struct matrix_2_2 m) {
    double invDet = 1.0 / detMatrix_2_2(m);
    const double tmp = m.val[0][0];

    out->val[0][0] = invDet * m.val[1][1];
    out->val[0][1] = invDet * -m.val[0][1];
    out->val[1][0] = invDet * -m.val[1][0];
    out->val[1][1] = invDet * tmp;
}

void dotMatrix_2_2_Matrix_2_2 (struct matrix_2_2 *out, struct matrix_2_2 m1, struct matrix_2_2 m2) {
    const double a1 = m1.val[0][0];
    const double b1 = m1.val[0][1];
    const double c1 = m1.val[1][0];
    const double d1 = m1.val[1][1];
    const double a2 = m2.val[0][0];
    const double b2 = m2.val[0][1];
    const double c2 = m2.val[1][0];
    const double d2 = m2.val[1][1];

    out->val[0][0] = a2 * a1 + b2 * c1;
    out->val[0][1] = a2 * b1 + b2 * d1;
    out->val[1][0] = c2 * a1 + d2 * c1;
    out->val[1][1] = c2 * b1 + d2 * d1;
}

void rotMatrix_2_2 (struct matrix_2_2 *out, double theta) {
    out->val[0][0] = cos(theta);
    out->val[0][1] = sin(theta);
    out->val[1][0] = -sin(theta);
    out->val[1][1] = cos(theta);
}

void addVector_2_Vector_2 (struct vector_2 *out, struct vector_2 a, struct vector_2 b) {
    out->val[0] = a.val[0] + b.val[0];
    out->val[1] = a.val[1] + b.val[1];
}

int main (int argc, char *argv[]) {
	if (argc == 1) {
		struct matrix_2_2 m = { .val = {{1.414214, 0}, {-1.414214, 1.414214}} };
		struct vector_2 v = { .val = {1, 1} };
		struct vector_2 t;
		struct vector_2 w;
		struct matrix_2_2 n;
		struct matrix_2_2 i;
		struct matrix_2_2 r;

		printf("m = \n");
		printMatrix_2_2(m);

		printf("v = \n");
		printVector_2(v);

		dotMatrix_2_2_Vector_2(&t, m, v);
		printf("m . v = \n");
		printVector_2(t);

		printf("Det(m) = %lf\n", detMatrix_2_2(m));

		invMatrix_2_2(&n, m);
		printf("m^-1 = \n");
		printMatrix_2_2(n);

		dotMatrix_2_2_Vector_2(&v, n, t);
		printf("m^-1 . (m . v) = \n");
		printVector_2(v);

		dotMatrix_2_2_Matrix_2_2(&i, n, m);
		printf("(m^-1 . m) = \n");
		printMatrix_2_2(i);

		rotMatrix_2_2(&r, M_PI / 4.0);
		printf("r = \n");
		printMatrix_2_2(r);

		dotMatrix_2_2_Vector_2(&w, r, v);
		printf("rot(pi/4) . v = \n");
		printVector_2(w);

		addVector_2_Vector_2(&v, v, t);
		printf("v + (m . v) = \n");
		printVector_2(v);
	}
	
	struct matrix_2_2 *curr = NULL;
	
    for (int i = 1; i < argc; i++) {
    	if (argv[i][0] == '-') {
    		if (argv[i][1] == 'v') fVerbose = 1;
    	}
    	else {
		
		    token_list *list = parse_tokens(argv[i]);
		    if (fVerbose) {
			    debug_tokens(list);
		    }

		    Matrix2x2 * m = parseMatrix2x2(list);
		    if (m != NULL) {
		        printf("Matrix (2x2): \n");
		        printMatrix_2_2(*m);
		        
		        if (curr == NULL) {
		        	curr = m;
	        	} else {
	        		dotMatrix_2_2_Matrix_2_2 (curr, *curr, *m);
					printf("Cuml. Transform:\n");
					printMatrix_2_2(*curr);
        		}
		        
		        continue;
		    }
		    
		    Vector2 * v = parseVector2(list);
		    if (v != NULL) {
		        printf("Vector (2): \n");
		        printVector_2(*v);
		        
				if (curr != NULL) {
					struct vector_2 v2;
					dotMatrix_2_2_Vector_2(&v2, *curr, *v);
					printf("Transform:\n");
					printVector_2(v2);
				}	
		    }
	    }
    }
    
}

