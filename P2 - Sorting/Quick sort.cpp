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

// rearrange array function (find partition point)
int partition(int array[], int left, int right) {
    
  // select the rightmost element as pivot
  int pivot = array[right];
  
  // pointer for greater element
  int i = (left - 1);

  // traverse each element of the array and compare them with the pivot
  for (int j = left; j < right; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found then swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }
  
  // swap pivot with the greater element at i
  swap(&array[i + 1], &array[right]);
  
  // return the partition point
  return (i + 1);
}

//quick sort function
void quickSort(int array[], int left, int right) {
  if (left < right) {
      
    // find the pivot element such that elements smaller than pivot are on left of pivot
	//elements greater than pivot are on right of pivot
    int pi = partition(array, left, right);

    // recursive call on the left of pivot
    quickSort(array, left, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, right);
  }
}

int main(){
	int seed, size;
	cin >> seed >> size;
	int data[size];
	cout << "Arrar not sorted: "; 
	generateArray(seed, size, data);
	clock_t sortStart = clock();
	quickSort(data, 0, size - 1);
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
