#include "studentstest.h"
#include "ragnarstest.h"
#include <iostream>

#include "student3_listque.h"
#include "student4_arrayque.h"
#include "student5_adeque.h"

using namespace std;


void studentstest(){

    // skriv din egen testkod här

    cout << "Haer boer studentens testrsultat synas" << endl;

//    AQue que;
//    LQue que;
    ADeque que;

    std::cout << "Size: " << que.size() << std::endl;

    for(int i = 1; i <= 8; i++){
        que.pushBack(i);
//        std::cout << i-1 << " back: " << que.back() << " Front: " << que.front() << std::endl;
    }

    std::cout << "Size: " << que.size() << std::endl << std::endl;

    que.popFront();
    std::cout << "Back: " << que.back() << std::endl;
    std::cout << "Front: " << que.front() << std::endl;

    std::cout << "Size: " << que.size() << std::endl << std::endl;

    que.popBack();
    que.popFront();

    std::cout << "Back: " << que.back() << std::endl;
    std::cout << "Front: " << que.front() << std::endl;

    std::cout << "Size: " << que.size() << std::endl;

    que.print();

    que.pushFront(5);
    std::cout << "Front: " << que.front() << std::endl;

    que.print();

}

