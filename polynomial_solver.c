#include <stdio.h>
#include <stdlib.h>

#define POW(x, exp) ({ int res = 1; \
                        int temp = exp; \
                        while(temp--) \
                            res *= x; \
                        res; \
                    })

#define MEMSET(array, value, length)  ({ \
										int tmp = length; \
										while (tmp--) \
										{ \
										array[tmp] = value; \
										} \
										})

typedef struct polynomial{
    int _degree;
    int (*getDegree)(struct polynomial *this);
    void (*setDegree)(struct polynomial *this);
    void (*readPolynomial)(struct polynomial *this, int *coefficients);
    void (*solvePolynomial)(struct polynomial *this, int *coefficients, int *res);
}polynomial_t;

void _readPolynomial(polynomial_t *this, int *coefficients){
    int degree = this->getDegree(this);
    for(int i=degree; i>=0; i--){
        printf("Enter coefficient for x to the power of %d :- ", i);
        scanf("%d", &coefficients[degree - i]);
        getchar();
    }
}

void _solvePolynomial(polynomial_t *this, int *coefficients, int *res){
    int degree = this->getDegree(this);
    int x = 0;
    printf("Enter the value of x :- ");
    scanf("%d", &x);
    getchar();
    for(int i=degree; i>=0; i--){
        *res += coefficients[degree - i] * POW(x, i);
    }
}

/* static inline */
int _getDegree(polynomial_t *this){
    return this->_degree;    
}

void _setDegree(polynomial_t *this){
    printf("Enter the degree of polynomial :- ");
    scanf("%d", &(this->_degree));
    getchar();
    // ptr->readPolynomial(ptr);
}

int main()
{
	//can use a pointer to struct or can also use a struct object directly
    polynomial_t *polynomialPtr = malloc(sizeof(polynomial_t));
    polynomialPtr->setDegree = _setDegree;
    polynomialPtr->getDegree = _getDegree;
    polynomialPtr->readPolynomial = _readPolynomial;
    polynomialPtr->solvePolynomial = _solvePolynomial;
    polynomialPtr->setDegree(polynomialPtr);
    int degree = polynomialPtr->getDegree(polynomialPtr);
    int coefficients[degree];
    MEMSET(coefficients, 0, degree);
    polynomialPtr->readPolynomial(polynomialPtr, coefficients);
    int res = 0;
    polynomialPtr->solvePolynomial(polynomialPtr, coefficients, &res);
    printf("res -> %d\n", res);
    return 0;
}
