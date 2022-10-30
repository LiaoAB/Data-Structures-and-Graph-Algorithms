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

// Merge two subarrays L and R into array
void merge(int array[], int p, int q, int r) {
  
  // Create L ¡öA[p..q] and R ¡öA[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++){
	L[i] = array[p + i];
  }
  for (int j = 0; j < n2; j++){
	R[j] = array[q + j + 1];
  }
  // Maintain current index of sub-arrays and main array
  int i = 0, j = 0, k = p;
  
  // Until we reach either end of L or M, pick larger among elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    } 
	else {
      array[k] = R[j];
      j++;
    }
    k++;
  }
  // When we run out of elements in either L or M, pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int array[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(array, l, m);
    mergeSort(array, m + 1, r);

    // Merge the sorted subarrays
    merge(array, l, m, r);
  }
}

int main(){
	int seed, size;
	cin >> seed >> size;
	int data[size];
	cout << "Arrar not sorted: "; 
	generateArray(seed, size, data);
	clock_t sortStart = clock();
	mergeSort(data, 0, size - 1);
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
