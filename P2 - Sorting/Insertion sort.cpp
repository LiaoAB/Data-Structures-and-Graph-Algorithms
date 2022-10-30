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

//check sorted result function
int checkSorted(int array[], int size){
	for(int i = 0; i < size - 1; i++){
		if(array[i + 1] < array[i]){
			return 0;
		}
	}
	return 1;
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

//insertion sort function
void insertionSort(int array[], int size){
	for(int move; move < size; move++){
		int now = array[move];
		int n = move - 1;
		
		//keep compare now value with the left until find a value that is smaller than now
		while(now < array[n] && n >= 0){
			array[n + 1] = array[n];
			--n; 
		}
		array[n + 1] = now;
	}
}

int main(){
	int seed, size;
	cin >> seed >> size;
	int data[size];
	cout << "Arrar not sorted: "; 
	generateArray(seed, size, data);
	clock_t sortStart = clock();
	insertionSort(data, size);
	cout << "Sorted array: ";
	printArray(data, size);
	clock_t sortEnd = clock();
	long double passTime = 1000.0 * (sortEnd - sortStart) / CLOCKS_PER_SEC;
	if(checkSorted(data,size) == 1){
		cout << "sorted" << endl;
	}
	else{
		cout << "unsorted" << endl;
	}
	cout << "Time used: " << passTime / 1000.0 << "sec" <<endl;
}
