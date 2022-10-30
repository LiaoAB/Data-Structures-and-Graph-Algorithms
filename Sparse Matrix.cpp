#include<bits/stdc++.h>
using namespace std;

//Declare node for linked list, 
//each node contains value, row_number, column_number, and address of the next node.
//Also define friend class LinkedList, and two ways to create a node:
//with no specified value and with specified value
class Node{
private:
    int value;
    int row_number;
    int column_number;
    Node *next;

public:
    Node(): next(NULL){};
    Node(int a): value(a), next(NULL){};
    friend class LinkedList;
};

//Declare LinkedList, set the first node as start.
//Also define functions that are needed:
//addNode() to add new node into list,
//printMatrix() to print out the LinkedList matrix,
//matrixAdd() to add matrix,
//matrixMultiply() to multiple matrix,
//searchElement() to search the value for particular position in matrix.
class LinkedList{
    private:
        Node *start;

    public:
        LinkedList(): start(NULL){};
        void addNode(int newrow_number, int newcolumn_number, int newvalue);
        void printMatrix(int m, int n);
        LinkedList matrixAdd(LinkedList list1, LinkedList list2);
        LinkedList matrixMultiply(LinkedList list1, LinkedList list2, int m, int n, int l);
        int searchElement(LinkedList list1, int row_index, int column_index);
    };

int main(){
    int m, n, l, position, value;
    int code;
    LinkedList list1, list2, list3;

    cout << "Press 1 to do addition, press 2 do multiplication:" << endl;
    cin >> code;

    if (code == 1){
        cout << "Enter the number of row and column:" << endl;
        cin >> m >> n;
        cout << "Enter matrix A:" << endl;

        for (int i = 0; i < m; i++){
            while (cin >> position && position != 0 && position <= n){
                cin >> value;
                position = position - 1;
                list1.addNode(i, position, value);
            }
            if (position > n){
                cout << "It's not a valid position." << endl;
                return 0;
            }
        }

        cout << "Enter matrix B:" << endl;

        for (int j = 0; j < m; j++){
            while (cin >> position && position != 0){
                if (position > n){
                    cout << "It's not a valid position." << endl;
                    return 0;
                };
                cin >> value;
                position = position - 1;
                list2.addNode(j, position, value);
            }
        }

        list3 = list3.matrixAdd(list1, list2);

        cout << endl << "Matrix A:" << endl;
        list1.printMatrix(m, n);
        cout << endl << "Matrix B:" << endl;
        list2.printMatrix(m, n);
        cout << endl << "Matrix A+B:" << endl;
        list3.printMatrix(m, n);
        cout << endl;
    }
    else if (code == 2){
        cout << "Enter the number of row and column for A:" << endl;
        cin >> m >> n;
        cout << endl << "Enter the column number for B:" << endl;
        cin >> l;
        cout << endl << "Enter matrix A:" << endl;

        for (int i = 0; i < m; i++){
            while (cin >> position && position != 0 && position <= n){
                cin >> value;
                position = position - 1;
                list1.addNode(i, position, value);
            }
            if (position > n){
                cout << "It's not a valid position." << endl;
                return 0;
            }
        }

        cout << "Enter matrix B:" << endl;

        for (int j = 0; j < n; j++){
            while (cin >> position && position != 0){
                if (position > l){
                    cout << "It's not a valid position." << endl;
                    return 0;
                }
                cin >> value;
                position = position - 1;
                list2.addNode(j, position, value);
            }
        }

        list3 = list3.matrixMultiply(list1, list2, m, n, l);

        cout << "The matrix A:" << endl;
        list1.printMatrix(m, n);
        cout << endl << "The matrix B:" << endl;
        list2.printMatrix(n, l);
        cout << endl << "The matrix AB:" << endl;
        list3.printMatrix(m, l);
        cout << endl;
    }
    
    return 0;
}

//Define the addNode() function to add new node.
void LinkedList::addNode(int newrow_number, int newcolumn_number, int newvalue){

    //Define node newNode to store the node we want to add,
    //node temp to temporarily store the incoming data,
    //node temp2 to temporarily store the incoming data,
    //if node temp has already been used by other incoming data.
    Node *newNode = new Node(newvalue);
    Node *temp = new Node();
    Node *temp2 = new Node();

    //If there is nothing inside the list,
    //set the new node as the first node.
    if(start == NULL){
        temp->value = newvalue;
        temp->row_number = newrow_number;
        temp->column_number = newcolumn_number;
        temp->next = NULL;
        start = temp;
    } 

    //If the list is not empty,
    //reach the end of the list first,
    //then add the new node.
    else{
        temp = start;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp2->value = newvalue;
        temp2->row_number = newrow_number;
        temp2->column_number = newcolumn_number;
        temp2->next = NULL;
        temp->next = temp2;
    }
}

//Define the printMatrix() function to print the matrix.
void LinkedList::printMatrix(int m, int n){

    //Search the list from the beginning to the end,
    //take out the values ​and store them in the matrix ​one by one. 
    Node *current = start;
    int **matrix;
    matrix = new int *[m];
    for (int i = 0; i < m; i++){
        matrix[i] = new int[m];
        for (int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }
    while (current != NULL){
        int row, col;
        row = current->row_number;
        col = current->column_number;

        matrix[row][col] = current->value;
        current = current->next;
    }

    //Print out the matrix that has gotten from the list.
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//Define the matrixAdd() function to add two matrices.
LinkedList LinkedList::matrixAdd(LinkedList list1, LinkedList list2){

    //Define list3 to store the result after addition,
    //set the start of list1 and list2. 
    LinkedList list3;
    Node *node1 = list1.start;
    Node *node2 = list2.start;

    //If both matrix has value. 
    while (node1 != NULL && node2 != NULL){

        //If both elements' row numbers are the same.
        if (node1->row_number == node2->row_number){
            //If both elements' column numbers are also the same,
            //add their value together and put it into list3, 
            //and then point node1 and node2 to the next.
            if (node1->column_number == node2->column_number){
                int sum = node1->value + node2->value;
                list3.addNode(node1->row_number, node1->column_number, sum);
                node1 = node1->next;
                node2 = node2->next;
            } 

            //If the row number is the same but the column number is different, 
            //compare the size of the column number.
            else{
                
                //If the number of node1 column is smaller, save the data of node1 into list3,
                //and then point node1 to the next.
                if (node1->column_number < node2->column_number){
                    list3.addNode(node1->row_number, node1->column_number, node1->value);
                    node1 = node1->next;
                }

                //If the number of node2 column is smaller, save the data of node2 into list3,
                //and then point node2 to the next.
                else{
                    list3.addNode(node2->row_number, node2->column_number, node2->value);
                    node2 = node2->next;
                }
            }
        } 

        //If both elements' row numbers are not the same.
        else{

            //If the number of node1 row is smaller, save the data of node1 into list3,
            //and then point node1 to the next.
            if (node1->row_number < node2->row_number){
                list3.addNode(node1->row_number, node1->column_number, node1->value);
                node1 = node1->next;
            } 

            //If the number of node2 row is smaller, save the data of node2 into list3,
            //and then point node2 to the next.
            else{
                list3.addNode(node2->row_number, node2->column_number, node2->value);
                node2 = node2->next;
            }
        }
    }

    //If one of the matrices has been inspected and there is nothing left, 
    //that position's value is the element inspected by the other matrix, 
    //put it directly into list3.
    while (node1 != NULL){
        list3.addNode(node1->row_number, node1->column_number, node1->value);
        node1 = node1->next;
    }
    while (node2 != NULL){
        list3.addNode(node2->row_number, node2->column_number, node2->value);
        node2 = node2->next;
    }

    return list3;
}

//Define the searchElement() function to search the value for particular position in matrix.
int LinkedList::searchElement(LinkedList list1, int row_index, int column_index){

    //Set the start of list1.
    Node *start = list1.start;

    //Search for node that row number = given row index,
    //column number = given column index,
    //and return the node.
    while (start != NULL){
        if (start->row_number == row_index && start->column_number == column_index){
            return start->value;
        }
        start = start->next;
    }
    return 0;
}

//Define the matrixMultiply() function to multiply two matrices.
LinkedList LinkedList::matrixMultiply(LinkedList list1, LinkedList list2, int m, int n, int l){
    
    //Define list3 to store the result after addition,
    //value1 and value2 to store the value of same position elements from list1 and list2 to do mutiply,
    //result to store the answer of value1 * value2.
    LinkedList list3;
    int value1, value2, result;

    //For each row of list1.
    for (int i = 0; i < m; i++){
        //For each column of list2.
        for (int j = 0; j < l; j++){
            result = 0;

            //For each column of list1,
            //take out the values ​​at the corresponding row and column positions, 
            //and multiply them to get the result.
            for (int k = 0; k < n; k++){
                value1 = searchElement(list1, i, k);
                value2 = searchElement(list2, k, j);
                result += value1 * value2;
            }

            //If result is not zero,
            //put it into list3 to be the value of that position.
            if (result != 0){
                list3.addNode(i, j, result);
            }
        }
    }

    return list3;
}