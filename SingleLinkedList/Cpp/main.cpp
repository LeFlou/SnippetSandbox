#include "SingleLinkedList.h"

int main()
{
    SingleLinkedList<int> myList;

    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_back(4);

    myList.walk();

    return 0;
}