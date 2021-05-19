/* 
This is a Binary Search Tree with a INITIALIZE, PRINT, DELETE, SEARCH, and QUIT options. INITIALIZE allows for a console and file input with numbers 
seperated w/ 1 space each. 
Author: Pujan Patel
Recieved help from GeeksForGeeks
*/

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
//binary tree node
struct node {
    node * left = NULL;
    node * right = NULL;
    int value;
};
//initailize varaibles
node * initialize(node * head, int arrayValue);
void print(node * head, int space);
node * search(node * head, int serachValue, bool & in);
node * deleteNode(node * head, int deleteValue);
node * minValueNode(node * head);
//main
int main () {
    node * head = new node;
    int space = 0;
    char * input = new char[999];
    int * array = new int[999];
    bool running = true;
    while (running) {//if runnning, ask for function and run it
        cout << "INITIALIZE, PRINT, DELETE, SEARCH, QUIT" << endl;
        cin >> input;
        if (strcmp("INITIALIZE", input) == 0) {
            cout << "CONSOLE, FILE" << endl;
            cin >> input;
            if(strcmp("CONSOLE", input) == 0) {
                int arrayIndex = 0;
                cout << "Input #s seperated with space, EX: 1 2 3 4 5" << endl;
                char * numInput = new char[999];
                cin.ignore(999,'\n');
                cin.getline(numInput, 999);
                char * token = strtok(numInput, " ");
                while(token != NULL) {
                    array[arrayIndex] = atoi(token);
                    token = strtok(NULL, " ");
                    arrayIndex++;
                }
                for(int i = 0; i < arrayIndex + 1; i++) {
                    if(array[i] != 0) {
                        initialize(head, array[i]);
                    }
                    array[i] = 0;
                }
            }
            if(strcmp("FILE", input) == 0) {
                int arrayIndex = 0;
                cout << "Name of File" << endl;
                cin >> input;
                int num = 0;
                ifstream numFile (input);
                while(numFile >> num) {
                    initialize(head, num);
                }
            }
        }
        else if(strcmp("DELETE", input) == 0) {
            cout << "Value you wish to delete" << endl;
            int deleteValue; 
            cin >> deleteValue;
            deleteNode(head, deleteValue);
        }
         else if(strcmp("PRINT", input) == 0) {
            print(head, space);
        }
        else if(strcmp("SEARCH", input) == 0) {
            cout << "Value you wish to search" << endl;
            int searchValue;
            cin >> searchValue;
            bool in = false;
            search(head, searchValue, in);
            if(in) {
                cout << "The Tree contains that value" << endl;
            }
            else {
                cout << "The Tree does not contain that value" << endl;
            }
        }
        else if(strcmp("QUIT", input) == 0) {
            running = false;
        }
    } 

    return 0;
}
node * initialize(node * head, int arrayValue) {//send in head node and value, add it to place it belongs
    if(head -> value == 0) {
        head -> value = arrayValue;
        return head;
    }
    node * temp = new node;
    temp -> value = arrayValue;
    if(arrayValue > head -> value && head -> right != NULL) {
        head -> right = initialize(head -> right, arrayValue);
    }
    else if(arrayValue <= head -> value && head -> left != NULL){
        head -> left = initialize(head -> left, arrayValue);
    }
    else if(arrayValue > head -> value) {
        head -> right = temp;
    }
    else if(arrayValue <= head -> value) {
        head -> left = temp;
    }
    return head;
}
void print(node * head, int space) {//print tree visually
    if(head == NULL) {
        return;
    }
    space += 10;
    print(head -> right, space);
    cout << " " << endl;
    for (int i = 10; i < space; i++) {
        cout << " ";
    }
    cout << head -> value << endl;
    print(head -> left, space);

}
node * search(node * head, int searchValue, bool & in) {//check if value is in tree, reply
    if(head == NULL) {
        return head;
    }
    if(searchValue > head -> value) {
        head -> right = search(head -> right, searchValue, in);
    }
    else if(searchValue < head -> value) {
        head -> left  = search(head -> left, searchValue, in);
    }
    else if(searchValue == head -> value) {
        in = true;
        return head;
    }
    return head;
}
node * deleteNode(node * head, int deleteValue) {//delete node in tree and shift accordingly
    if(head == NULL) {
        return head;
    }
    if(deleteValue > head -> value) {
        head -> right = deleteNode(head -> right, deleteValue);
    }
    else if(deleteValue < head -> value) {
        head -> left  = deleteNode(head -> left, deleteValue);
    }
    else {
        if(head -> left == NULL) {
            node * temp = head -> right;
            delete head;
            return temp;
        }
        else if(head -> right == NULL) {
            node * temp = head -> left;
            delete head;
            return temp;
        }
        node * temp = minValueNode(head -> right);
        head -> value = temp -> value;
        head -> right = deleteNode(head -> right, temp -> value);
    }
    return head;
}
node * minValueNode(node * head) {//helper function, find minimum value in tree
    node * current = head;
    while(current != NULL && current -> left != NULL) {
        current = current -> left;
    }
    return current;
}