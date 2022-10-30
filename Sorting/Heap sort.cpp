#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

// print array function
void printArray(int array[], int size){
	for(int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
} 

// generate array function
void generateArray(int seed, int size, int array[]){
	srand(seed);
	for(int i = 0; i < size; i++){
		array[i] = rand();
		cout << array[i] << " ";
	}
	cout << endl; 
}

//check sorted result function
int checkSorted(int array[], int size){
	for(int i = 0; i < size - 1; i++){
		if(array[i + 1] < array[i]){
			return 0;
		}
	}
	return 1;
}

//swap elements
void swap(int *n, int *m) {
  int temporary = *n;
  *n = *m;
  *m = temporary;
}

void heapify(int array[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
  
    if (l < n && array[l] > array[largest])
      largest = l;
  
    if (r < n && array[r] > array[largest])
      largest = r;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(array[i], array[largest]);
      heapify(array, n, largest);
    }
  }
  
// main function to do heap sort
void heapSort(int array[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--){
    	heapify(array, n, i);
	}
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(array[0], array[i]);
  
      // Heapify root element to get highest element at root again
      heapify(array, i, 0);
    }
  }

int main(){
	int seed, size;
	cin >> seed >> size;
	int data[size];
	cout << "Arrar not sorted: "; 
	generateArray(seed, size, data);
	clock_t sortStart = clock();
	heapSort(data, size);
	cout << "Sorted array: ";
	printArray(data, size);
	clock_t sortEnd = clock();
	long double passTime = 1000.0 * (sortEnd - sortStart) / CLOCKS_PER_SEC;
	if(checkSorted(data,size) == 1){
		cout << "sorted" << endl;
	}
	else{
		cout << "GG" << endl;
	}
	cout << "Time used: " << passTime / 1000.0 << "sec" <<endl;
}
