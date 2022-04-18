#pragma once

//functions
void print_all(int* data, int num); //출력 연산
void swap(int* data, int index1, int index2); //swap 연산



//sorting algorithm
void ExchangeSort(int* data, int num); //Exchange Sort

void Merge(int* data, int left, int mid, int right); //Merge
void MergeSort(int* data, int left, int right); // Merge Sort

int Divide(int* data, int left, int right); //Divide
void QuickSort(int* data, int left, int right); //Quick Sort

void HeapSort(int* data, int num); //Heap Sort

void RadixSort(int* data, int num, int maxlength); //Radix Sort



