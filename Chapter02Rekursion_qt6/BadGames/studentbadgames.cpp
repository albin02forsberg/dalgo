#include "studentbadgames.h"
#include <iostream>
#include <string>

using namespace std;

bool ragnarsTest1();

string nameOfStudent(){
    return "Albin Forsberg";
}

/**********************************************************
ANROP:   uint elva = oneMore( tio );
UPPGIFT: Returnerar inparametern+1
***********************************************************/
int oneMore(int a){
   return a+1;
}
/**********************************************************
ANROP:   uint nio = oneLess( tio );
UPPGIFT: Returnerar inparametern-1
***********************************************************/
int oneLess(int a){
   return a-1;
}

/**********************************************************
ANROP:   int s = sum(a,b);
UPPGIFT: Returnerar a+b;
***********************************************************/
int sum(int a, int b){
    if(b == 0){
        return a;
    }
    return sum(oneMore(a), oneLess(b));
}

/**********************************************************
ANROP:   int d = diff(a,b);
UPPGIFT: Returnerar a-b;
***********************************************************/
int diff(int a, int b){
    if(b == 0){
        return a;
    }
    return diff(oneLess(a), oneLess(b));
}

/**********************************************************
ANROP:   int prod = product(a,b);
UPPGIFT: Returnerar a*b;
***********************************************************/
int product(int a, int b){
    if(b == 0){
        return 0;
    }
    return sum(a, product(a, oneLess(b)));
}

/**********************************************************
ANROP:   int result = pow(a,b);
UPPGIFT: Returnerar a upphöjt till b;
***********************************************************/
int pow(int a, int b){
    if(b == 0){
        return 1;
    }
    return product(a,pow(a,oneLess(b)));
}

/**********************************************************
ANROP:   int factorial = fac(a);
UPPGIFT: Returnerar a!
***********************************************************/
int fac(int a){
    if(a == 0){
        return 1;
    }

    return product(a, fac(oneLess(a)));
}


void studentsTest(){

    // testa alla funktiner här
    // Men skriv bara mycket små tal ( < 5 )
    // Annars kanske programmet kraschar pga
    // stackoverflow

    int summa = sum(5,5);

    std::cout << "Sum 5+5 = " << summa << std::endl;

    assert(sum(5,5) == 10);

    int diffe = diff(5,4);

    std::cout << "Dif 5-4 = " << diffe << std::endl;

    assert(diff(5,4) == 1);

    int prod = product(3,10);

    std::cout << "Product 3*10: " << prod << std::endl;

    assert(product(3,10) == 30);

    int po = pow(3,5);

    std::cout << "Pow 3^5: " << po << std::endl;

    assert(pow(3,5) == 243);

    int fa = fac(4);

    std::cout << "4!: " << fa << std::endl;

    assert(fac(4) == 24);


}

int main()
{

    studentsTest();

    ragnarsTest1();

}

