#include "the1.h"
//You may write your own helper functions here

bool median;
long swapG;
double avg_distG, max_distG;


int abs(int i) {
    if (i < 0) return -i;
    else return i;
}

int min(unsigned short a, unsigned short b) {
    if (a < b) return a;
    else return b;
}

int max(unsigned short a, unsigned short b) {
    if (a > b) return a;
    else return b;
}

void swapF(unsigned short* arr, int i, int j) {
    //swapping first
    unsigned short temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    
    // setting the variables
    swapG++;
    int dist = abs(j - i);
    avg_distG += dist;
    if (dist > max_distG) max_distG = dist;
}


void medianL(unsigned short* arr, int size) {
    
    if (!median) return;
    int midI = (size-1)/2;
    unsigned short first = arr[0], mid = arr[midI], last = arr[size-1];
    
    if (first > min(mid, last) && first < max(mid, last)) swapF(arr, 0, size - 1);
    
    else if (mid > min(first, last) && mid < max(first, last)) swapF(arr, midI, size - 1);
    
}

void medianH(unsigned short* arr, int size) {
    
    if (!median) return;
    int midI = (size-1)/2;
    unsigned short first = arr[0], mid = arr[midI], last = arr[size-1];
    
    if (first > min(mid, last) && first < max(mid, last)) swapF(arr, 0, midI);
    
    else if (last > min(first, mid) && last < max(first, mid)) swapF(arr, size - 1, midI);
    
}


int partition(unsigned short* arr, int size) {
    
    unsigned short X = arr[size-1];
    int i = -1;
    for (int j = 0; j < size - 1; j++)
        if (arr[j] >= X) swapF(arr, ++i, j);
    
    swapF(arr, i+1, size-1);
    return i+1;
    
}

int quickClassical(unsigned short* arr, int size) {
    
    if (size > 1) {
        medianL(arr, size);
        int P = partition(arr, size);
        return quickClassical(arr, P++) + quickClassical(arr+P, (size-P)) + 1;
    }
    
    else return 1;
}

int hoare(unsigned short* arr, int size) {
    
    unsigned short X = arr[(size-1)/2];
    int i = -1;
    int j = size;
    while (true) {
        
        do j--; while (arr[j] < X);
        do i++; while (arr[i] > X);
        
        if (i < j) {
            swapF(arr, i, j);
        }
        else return j;
    }
    
}


int quickHoare(unsigned short* arr, int size) {
    
    if (size > 1) {
        medianH(arr, size);
        int P = hoare(arr, size);
        return quickHoare(arr, ++P) + quickHoare(arr+P, (size-P)) + 1;
    }
    
    else return 1;
}



int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){
    
    median = median_of_3;
    swapG = 0;
    avg_distG = max_distG = 0;
    int rec;
    
    if (hoare) rec = quickHoare(arr, size);
    else rec = quickClassical(arr, size);
    
    swap = swapG;
    if (swap) avg_dist = avg_distG/swap;
    max_dist = max_distG;
    return rec;
}


