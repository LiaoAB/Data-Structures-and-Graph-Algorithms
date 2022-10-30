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

//selection sort function
void selectionSort(int array[], int size) {
  for (int move = 0; move < size - 1; move++) {
    int minIndex = move;
    for (int i = move + 1; i < size; i++) {

      // Select the minimum element in each loop.
      if (array[i] < array[minIndex])
        minIndex = i;
    }

    // put min at the correct position
    swap(&array[minIndex], &array[move]);
  }
}

int main(){
	int seed, size;
	cin >> seed >> size;
	int data[size];
	cout << "Arrar not sorted: "; 
	generateArray(seed, size, data);
	clock_t sortStart = clock();
	selectionSort(data, size);
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
