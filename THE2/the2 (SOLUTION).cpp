#include "the2.h"

// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/

int countingSort(std::string* A, int &size, int &index) {
    
    int iters = 0;
    std::string *B = new std::string[size];
    int *C = new int[27]();
    
    //second loop
    for (int j = 0; j < size; j++) {
        iters++;
        if (A[j].size() > index) //if not smaller word
            C[A[j][index]-64]++;
        else C[0]++;
    }
    
    //third loop
    for (int i = 1; i < 27; i++) {
        iters++;
        C[i] = C[i] + C[i-1];
    }
    
    //fourth loop
    for (int j = size-1; j >= 0; j--) {
        iters++;
        if (A[j].size() > index) { //if not smaller word
            B[C[A[j][index]-64]-1] = A[j];
            C[A[j][index]-64]--;
        }
        else {
            B[C[0]-1] = A[j];
            C[0]--;
        }
    }
    
    
    //copying B to A
    for (int i = 0; i < size; i++) {
        iters++;
        A[i] = B[i];
    }
    
    
    delete[] B;
    delete[] C;
    return iters;
    
}

int radix_string_sort(std::string* arr, int size, bool ascending){
    
    int maxLen = 0, iters = 0;
    for (int i = 0; i < size; i++)
        if (arr[i].size() > maxLen) maxLen = arr[i].size();
    
    for (int i = (maxLen - 1); i >= 0; i--)
        iters += countingSort(arr, size, i);
    
    //reversing the array if descending
    if (!ascending) {
        for (int i = 0; i < size/2; i++) std::swap(arr[i], arr[size-1-i]);
    }
    
    return iters; 
    
}




















