// C++ program to demostrate how to take input to array
// using scanf()
#include <cstdio>
#include <iostream>

using namespace std;

// driver code
int main()
{
    // creating an array of size "size"
    int size = 5;
    int arr[size];

    // going to each element and assigning the value entered
    // by the user
    cout << "Enter the element: ";
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // printing the array
    cout << "The Array elements are: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }

    return 0;
}