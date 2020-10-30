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
    void (*readPolynomial)(struct polynomial *this);    
    void (*solvePolynomial)(struct polynomial *this, int *res);    
    int coefficients[];
}polynomial_t;

void _readPolynomial(polynomial_t *this){    
    int degree = this->getDegree(this);
    MEMSET(this->coefficients, 0, degree+1);
    for(int i=degree; i>=0; i--){
        printf("Enter coefficient for x to the power of %d :- ", i);
        scanf("%d", &(this->coefficients[degree - i]));
        getchar();
    }
}

void _solvePolynomial(polynomial_t *this, int *res){    
    int degree = this->getDegree(this);
    int x = 0;
    printf("Enter the value of x :- ");
    scanf("%d", &x);
    getchar();
    for(int i=degree; i>=0; i--){
        // *res += coefficients[degree - i] * POW(x, i);
        *res += this->coefficients[degree - i] * POW(x, i);
    }
}

int _getDegree(polynomial_t *this){
    return this->_degree;    
}

void _setDegree(polynomial_t *this){
    printf("Enter the degree of polynomial :- ");
    scanf("%d", &(this->_degree));
    getchar();
}

int main()
{
    polynomial_t *polynomialPtr = malloc(sizeof(polynomial_t));
    polynomialPtr->setDegree = _setDegree;
    polynomialPtr->getDegree = _getDegree;
    polynomialPtr->readPolynomial = _readPolynomial;
    polynomialPtr->solvePolynomial = _solvePolynomial;
    polynomialPtr->setDegree(polynomialPtr);
    int degree = polynomialPtr->getDegree(polynomialPtr);
    polynomialPtr = realloc(polynomialPtr, sizeof(*polynomialPtr)+((degree+1)*sizeof(int)));
    polynomialPtr->readPolynomial(polynomialPtr);
    int res = 0;
    polynomialPtr->solvePolynomial(polynomialPtr, &res);    
    printf("res -> %d\n", res);
    return 0;
}
