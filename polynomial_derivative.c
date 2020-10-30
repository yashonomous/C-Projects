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
    void (*solvePolynomial)(struct polynomial *this, int x, int *res);    
    void (*solvePolynomialDerivative)(struct polynomial *this, int x, int *res);
    int coefficients[];
}polynomial_t;

int _getDegree(polynomial_t *this){
    return this->_degree;    
}

void _setDegree(polynomial_t *this){
    printf("Enter the degree of polynomial :- ");
    scanf("%d", &(this->_degree));
    getchar();
}

void _readPolynomial(polynomial_t *this){    
    int degree = this->getDegree(this);
    MEMSET(this->coefficients, 0, degree+1);
    for(int i=degree; i>=0; i--){
        printf("Enter coefficient for x to the power of %d :- ", i);
        scanf("%d", &(this->coefficients[degree - i]));
        getchar();
    }
}

void _solvePolynomial(polynomial_t *this, int x, int *res){    
    int degree = this->getDegree(this);
    for(int i=degree; i>=0; i--){
        *res += this->coefficients[degree - i] * POW(x, i);
    }
}

void _solvePolynomialDerivative(polynomial_t *this, int x, int *res){    
    int degree = this->getDegree(this);
    for(int i=degree; i>=0; i--){
        if(i == 0);
        else{
            *res += i * this->coefficients[degree - i] * POW(x, i-1);
            printf("res is -> %d\n", *res);
        }
    }
}

int main()
{
    polynomial_t *polynomialPtr = malloc(sizeof(polynomial_t));
    polynomialPtr->setDegree = _setDegree;
    polynomialPtr->getDegree = _getDegree;
    polynomialPtr->readPolynomial = _readPolynomial;
    polynomialPtr->solvePolynomial = _solvePolynomial;
    polynomialPtr->solvePolynomialDerivative = _solvePolynomialDerivative;

    polynomialPtr->setDegree(polynomialPtr);
    int degree = polynomialPtr->getDegree(polynomialPtr);
    polynomialPtr = realloc(polynomialPtr, sizeof(*polynomialPtr)+((degree+1)*sizeof(int)));
    polynomialPtr->readPolynomial(polynomialPtr);

    int res=0, x=0, der=0;
    if(degree > 0){
        printf("Enter the value of x :- ");
        scanf("%d", &x);
        getchar();
    }

    polynomialPtr->solvePolynomial(polynomialPtr, x, &res);    
    polynomialPtr->solvePolynomialDerivative(polynomialPtr, x, &der);
    printf("value of polynomial at x = %d is -> %d\n", x, res);
    printf("value of derivative of polynomial at x = %d is -> %d\n", x, der);

    free(polynomialPtr);
    return 0;
}
