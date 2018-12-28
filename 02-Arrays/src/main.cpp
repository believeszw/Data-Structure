#include <iostream>
#include "MyArray/MyArray.h"

using namespace std;

int main()
{
    //cout << boolalpha;// 将bool值正常显示

    MyArray<int> arr;
    for(int i = 0; i < 10; ++i)
        arr.pushBack(i);
    cout << arr << endl;

    arr.pushFront(100);
    cout << arr << endl;

    arr.pushFront(-1);
    cout << arr << endl;

    arr.remove(2);
    cout << arr << endl;

    arr.removeElement(4);
    cout << arr << endl;

    arr.removeFront();
    cout << arr << endl;

    for(int i = 0; i < 5; ++i){
        arr.removeBack();
        cout << arr << endl;
    }

    return 0;
}

