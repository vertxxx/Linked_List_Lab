#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

struct Node
{
    int data;
    Node* tail;
    Node* head;
};

Node* createList(int size)
{
    Node* curr = nullptr, * next = nullptr;

    if (size == 0)
    {
        cout << "The list is empty\n";
        return curr;
    }
    else
    {
        for (int i = 1; i <= size; i++) {
            curr = new Node;
            curr->tail = next;
            if (next)
                next->head = curr;

            next = curr;
        }
        curr->head = nullptr;

        return curr;
    }
}

int sizeList(Node* beg)
{
    int size = 0;
    while (beg != nullptr)
    {
        size++;
        beg = beg->tail;
    }
    return size;
}

void printList(Node* head)
{
    int size = sizeList(head);
    for (int i = 0; i < size; i++) {
        cout << head->data << ' ';
        head = head->tail;
    }
}

void printArray(int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
}

void pushBack(Node*& beg, int data, int size)
{
    if (beg == nullptr) 
    {
        beg = new Node;
        beg->data = data;
        beg->tail = nullptr;
        beg->head = nullptr;
    }
    else
    {
        Node* temp = beg;
        while (temp->tail != nullptr) {
            temp = temp->tail;
        }
        Node* newNode = new Node;
        newNode->data = data;
        newNode->tail = nullptr;
        newNode->head = temp;
        temp->tail = newNode;
    }
}

void pushFront(Node*& beg,int data)
{
    Node* temp = new Node;
    temp->data = data;
    beg->head = temp;
    temp->tail = beg;
    temp->head = nullptr;
    beg = temp;
}

void insert(Node*& beg, int data, int index)
{
    int size = sizeList(beg);
    if (index >= size || index < 0) {
        cout << "Index is out of range\n";
        return;
    }

    auto insertStart = steady_clock::now();

    if (beg == nullptr)
    {
        beg = new Node;
        beg->data = data;
        beg->tail = nullptr;
        beg->head = nullptr;
    }

    else if (beg->tail == nullptr || index == size - 1)
    {
        Node* temp = beg;
        while (temp->tail != nullptr) {
            temp = temp->tail;
        }
        Node* newNode = new Node;
        newNode->data = data;
        newNode->tail = nullptr;
        newNode->head = temp;
        temp->tail = newNode;
    }

    else if (index == 0)
    {
        Node* temp = new Node;
        temp->data = data;
        beg->head = temp;
        temp->tail = beg;
        temp->head = nullptr;
        beg = temp;
    }

    else
    {
        Node* curr = beg;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->tail;
        }

        Node* temp = new Node;
        temp->head = curr;       
        temp->tail = curr->tail;
        temp->tail->head = temp;
        temp->data = data;
        curr->tail = temp;
    }
    auto insertEnd = steady_clock::now();
    auto insertTime = duration_cast<nanoseconds>(insertEnd - insertStart).count();
    cout << "\n[Duration of insert for List is " << insertTime << " ns]\n\n";
}


void removeAt(Node*& beg, int index, int size)
{
    if (index >= size) {
        cout << "\nIndex is out of range!\nThe list didn't changed:\n";
        return;
    }
    else if (index == 0)
    {
        Node* temp = beg;
        beg = temp->tail;
        delete temp;
        beg->head = nullptr;
        return;
    }

    Node* previous = beg;
    for (int i = 0; i < index - 1; i++) {
        previous = previous->tail;
    }

    Node* toDelete = previous->tail;

    if (toDelete->tail == nullptr)
    {
        previous->tail = toDelete->tail;
    }
    else
    {
        previous->tail = toDelete->tail;

        previous->tail->head = previous;
    }

    delete toDelete;
}

void removeValue(Node*& beg, int value)
{
    auto start = steady_clock::now();

    Node* item = beg;
    if (item == nullptr) {
        cout << "The list is empty";
        return;
    }

    while (item != nullptr)
    {
        if (item->data == value) {
            if (item->head == nullptr)
            {
                Node* toDelete = item;
                item = item->tail;
                delete toDelete;
                if (item)
                {
                    item->head == nullptr;
                    beg = item;
                }
            }
            else
            {
                Node* toDelete = item;
                item = item->head;
                item->tail = toDelete->tail;
                delete toDelete;
                if (item->tail != nullptr) {
                    item->tail->head == item;
                }
            }
        }

        else {
            item = item->tail;
        }
    }

    auto end = steady_clock::now();

    auto result = duration_cast<nanoseconds> (end - start);
    cout << "\n[Duration of removeValue for List is " << result.count() << " ns]\n";
}

void getAt(Node*& beg, int index, int size)
{
    if (index >= size) {
        cout << "This index is out of range";
        return;
    }

    Node* item = beg;

    for (int i = 0; i <= index; i++)
    {
        if (i == index)
        {
            cout << item->data;
        }
        item = item->tail;
    }
}

void getValue(Node*& beg, int value)
{
    Node* item = beg;
    int valueCounter = 0, index = 0;
    if (item == nullptr) {
        cout << "The list is empty";
        return;
    }

    while (item != nullptr)
    {
        if (item->data == value)
        {
            cout << item->data << " at index " << index << "\n";
            valueCounter++;
        }
        item = item->tail;
        index++;
    }

    cout << "\nThe amount of numbers " << value << " = " << valueCounter;
}

Node* listItem(Node*& beg, int index)
{
    int size = sizeList(beg);
    for (int i = 0; i < size; i++) {
        if (index == i)
        {
            return beg;
        }
        beg = beg->tail;
    }
    return nullptr;
}

void swapItems(Node*& beg, int firstIndex, int secondIndex)
{
    Node* firstItem = nullptr;
    Node* secondItem = nullptr;
    Node* curr = beg;
       
    int size = sizeList(beg);

    if (beg == nullptr) {
        cout << "The list is empty";
        return;
    }

    if (firstIndex >= size || secondIndex >= size || firstIndex < 0 || secondIndex < 0) {
        cout << "Index is out of range";
        return;
    }

    for (int i = 0; i < firstIndex; i++) {
        curr = curr->tail;
    }
    firstItem = curr;
    curr = beg;

    for (int i = 0; i < secondIndex; i++) {
        curr = curr->tail;
    }
    secondItem = curr;

    int tempData = secondItem->data;
    secondItem->data = firstItem->data;
    firstItem->data = tempData;
}

void insertItemArray(int*& arr, int data, int index, int& size)
{
    int* newArr = new int[size + 1];
    for (int i = 0; i < index; i++) 
        newArr[i] = arr[i];
    newArr[index] = data;

    for (int i = index + 1; i < size + 1; i++) 
        newArr[i] = arr[i - 1];
    size++;

    delete[] arr;
    arr = newArr;
}

void removeItemArray(int*& arr, int& size, int index)
{
    int* newArr = new int[size - 1];
    for (int i = 0; i < index; ++i) 
        newArr[i] = arr[i];

    for (int i = index; i < size - 1; ++i) 
        newArr[i] = arr[i + 1];
    size--;

    delete[] arr;
    arr = newArr;
}

void clear(Node*& beg)
{
    Node* next;
    while (beg) {
        next = beg->tail;
        delete beg;
        beg = next;
    }
}

void menu(Node*& list, int*& arr)
{
    srand(time(NULL));
    int size = 0, insertIndex, insertData, addValue, deleteIndex, deleteValue, indexToGet, valueToGet, firstSwapIndex, secondSwapIndex;
    int mainMenu;
    cout << "Main menu:\n"
        << "[0] Exit\n"
        << "[1] Input list\n"
        << "[2] (Insert / Delete / Swap / Get) List\n"
        << "[3] Exit [IDZ - Destructor]\n";
    cin >> mainMenu;

    switch (mainMenu)
    {
    case 1:
        system("cls");
        char pick;
        cout << "Choose input method:\n[a] User enters size\n[b] User enters every element\n";
        cin >> pick;
        if (pick == 'a')
        {
            cout << "Size list: ";
            cin >> size;
            auto arrStart = steady_clock::now();
            arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 100;
 
            }
            auto arrEnd = steady_clock::now();
            auto arrTimeCreating = duration_cast<nanoseconds>(arrEnd - arrStart).count();
            
            

            auto listStart = steady_clock::now();
            list = createList(size);
            Node* temp = list;
            for (int i = 0; i < size; i++) {
                temp->data = arr[i];
                temp = temp->tail;
            }
            auto listEnd = steady_clock::now();
            auto listCreateTime = duration_cast<nanoseconds>(listEnd - listStart).count();
            cout << "\nList:  ";
            printList(list);
            cout << "\nArray: ";
            printArray(arr, size);

            cout << "\n\n[Duration of createList is " << listCreateTime << " ns]";
            cout << "\n[Duration of createArray is " << arrTimeCreating << " ns]\n\n";
        }
        else if (pick == 'b')
        {
            string inputData;
            cout << "Input elements: \n";
            cin.ignore();
            getline(cin, inputData);
            string String;
            int size = 1;
            for (int i = 0; i < inputData.size(); i++) {
                if (inputData[i] == ' ') {
                    size++;
                }
            }

            auto listStart = steady_clock::now();
            list = createList(size);
            Node* temp = list;
            for (int i = 0; i < inputData.size(); i++) {
                if (inputData[i] != ' ') {
                    String.push_back(inputData[i]);
                }
                else
                {
                    temp->data = stoi(String);
                    temp = temp->tail;
                    String = "";
                }
            }

            if (!String.empty())
                temp->data = stoi(String);

            auto listEnd = steady_clock::now();
            auto listCreateTime = duration_cast<nanoseconds>(listEnd - listStart).count();
            cout << "\nList:  ";
            printList(list);

            auto arrStart = steady_clock::now();
            arr = new int[size];
            String = "";
            int locIndex = 0;
            for (int i = 0; i < inputData.size(); i++) {
                if (inputData[i] != ' ') {
                    String.push_back(inputData[i]);
                }
                else
                {
                    arr[locIndex] = stoi(String);
                    locIndex++;
                    String = "";
                }
            }

            if (!String.empty())
                arr[locIndex] = stoi(String);

            auto arrEnd = steady_clock::now();
            auto arrCreateTime = duration_cast<nanoseconds>(arrEnd - arrStart).count();
            cout << "\nArray: ";
            printArray(arr, size);

            cout << "\n[Duration of createList is " << listCreateTime << " ns]";
            cout << "\n[Duration of createArr is " << arrCreateTime << " ns]\n\n";
        }

        system("Pause");
        system("cls");
        menu(list, arr);
        break;
    case 2:
        int operationPicker;
        cout << "Choose operation: \n[1] Insert\n[2] Delete\n[3] Swap\n[4] Get\n";
        cin >> operationPicker;
        size = sizeList(list);
        if (operationPicker == 1)
        {
            cout << "\nEnter the index to insert: ";
            cin >> insertIndex;
            cout << "\nEnter the value to insert: ";
            cin >> insertData;
            insert(list, insertData, insertIndex);

            auto arrayStart = chrono::steady_clock::now();
            insertItemArray(arr, insertData, insertIndex, size);
            auto arrayEnd = chrono::steady_clock::now();
            auto arrayInsertTime = duration_cast<nanoseconds>(arrayEnd - arrayStart).count();
            cout << "[Duration of insert for Array is " << arrayInsertTime << " ns]\n";
            cout << "\nList:  ";
            printList(list);
            cout << "\nArray: ";
            printArray(arr, size);
            
        }
        if (operationPicker == 2)
        {
            int methodToRemove;
            if (list == nullptr) {
                cout << "The List is empty, you can't delete any element from it!\n";
                return;
            }
            cout << "Choose method to delete element:\n[1] By index\n[2] By value\n";
            cin >> methodToRemove;
            size = sizeList(list);
            if (methodToRemove == 1)
            {
                cout << "\nEnter the index to delete: ";
                cin >> deleteIndex;
                cout << "Previous list:\n";
                printList(list);
                auto removeStart = steady_clock::now();
                removeAt(list, deleteIndex, size);
                auto removeEnd = steady_clock::now();
                auto indexRemoveTime = duration_cast<nanoseconds>(removeEnd - removeStart).count();
                cout << "\n\nNew list:\n";
                printList(list);
                

                auto arrayStart = chrono::steady_clock::now();
                removeItemArray(arr, size, deleteIndex);
                auto arrayEnd = steady_clock::now();
                auto arrayDeleteTime = duration_cast<nanoseconds>(arrayEnd - arrayStart).count();
                cout << "\n\nNew array:\n";
                printArray(arr, size);
                cout << "\n\n[Duration of removeAt for List is " << indexRemoveTime << " ns]";
                cout << "\n[Duration of removeAt for Array is " << arrayDeleteTime << " ns]\n\n";
            }
            else if (methodToRemove == 2)
            {
                cout << "\nEnter the value to delete: ";
                cin >> deleteValue;
                cout << "Previous list:\n";
                printList(list);
                cout << "\n";
                removeValue(list, deleteValue);
                cout << "\nNew list:\n";
                printList(list);

                
                auto arrayBegin = chrono::steady_clock::now();
                bool flag = false;
                for (int i = 0; i < size; ++i) {
                    if (deleteValue == arr[i]) {
                        flag = true;
                        removeItemArray(arr, size, i);
                        break;
                    }
                }
                if (!flag) {
                    cout << "\nArray item not found" << "\n";
                }
                auto arrayEnd = chrono::steady_clock::now();
                auto arrayDeleteTime = chrono::duration_cast<std::chrono::nanoseconds>(arrayEnd - arrayBegin).count();
                cout << "\nNew array:\n";
                printArray(arr, size);
                cout << "\n[Duration of removeValue for Array is " << arrayDeleteTime << " ns]\n\n";
            
            }
        }
        if (operationPicker == 3)
        {
            cout << "\nEnter 2 swap index: ";
            cin >> firstSwapIndex >> secondSwapIndex;
            cout << "Previous list:\n";
            printList(list);

            auto swapStart = steady_clock::now();
            swapItems(list, firstSwapIndex, secondSwapIndex);
            auto swapEnd = steady_clock::now();
            auto swapTime = duration_cast<nanoseconds>(swapEnd - swapStart).count();
            cout << "\n\nNew list:\n";
            printList(list);

            auto arrayStart = chrono::steady_clock::now();
            swap(arr[firstSwapIndex], arr[secondSwapIndex]);
            auto arrayEnd = chrono::steady_clock::now();
            auto arraySwapTime = duration_cast<nanoseconds>(arrayEnd - arrayStart).count();
            cout << "\n\nNew array:\n";
            printArray(arr, size);

            cout << "\n\n[Duration of swapItems for List is " << swapTime << " ns]";
            cout << "\n[Duration of swapItems for Array is " << arraySwapTime << " ns]\n\n";
        }
        if (operationPicker == 4)
        {
            int methodToGet;
            cout << "Choose method to get element:\n[1] By index\n[2] By value\n";
            cin >> methodToGet;
            if (methodToGet == 1)
            {
                size = sizeList(list);
                cout << "\nEnter index to get: ";
                cin >> indexToGet;
                cout << "List:\n";
                printList(list);
                cout << "\n\nElement by index " << indexToGet << " = ";
                auto listStart = steady_clock::now();
                getAt(list, indexToGet, size);
                auto listEnd = steady_clock::now();
                auto listGetAtTime = duration_cast<nanoseconds> (listEnd - listStart);

                auto arrayStart = steady_clock::now();
                for (int i = 0; i < size; ++i) {
                    if (indexToGet == i) {
                        cout << "\nElement (in Array) = " << arr[i] << "\n";
                        break;
                    }
                }
                auto arrayEnd = steady_clock::now();
                auto arrayGetAtTime = duration_cast<nanoseconds>(arrayEnd - arrayStart);
                cout << "\n[Duration of getAt for List is " << listGetAtTime.count() << " ns]\n";
                cout << "\n[Duration of getAt for Array is " << arrayGetAtTime.count() << " ns]\n";
            }
            else if (methodToGet == 2)
            {
                cout << "\nEnter the value to get: ";
                cin >> valueToGet;
                cout << "List:\t";
                printList(list);
                cout << "\n\n";
                auto listStart = steady_clock::now();
                getValue(list, valueToGet);
                auto listEnd = steady_clock::now();
                auto listGetValueTime = duration_cast<nanoseconds> (listEnd - listStart);

                auto arrayStart = steady_clock::now();
                bool flag = false;
                for (int i = 0; i < size; ++i) {
                    if (valueToGet == arr[i]) {
                        cout << "\nIndex: " << i << "\n";
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    cout << "\nArray index not found" << "\n";
                }
                auto arrayEnd = steady_clock::now();
                auto arrayGetValueTime = duration_cast<nanoseconds>(arrayEnd - arrayStart);
                cout << "\n[Duration of getValue for List is " << listGetValueTime.count() << " ns]\n";
                cout << "\n[Duration of getValue for Array is " << arrayGetValueTime.count() << " ns]\n";

            }
            else
            {
                cout << "Input error\n";
            }
     
        }

        cout << "\n\n";
        system("Pause");
        system("cls");
        menu(list, arr);
        break;

    case 3:
        if (list == nullptr) {
            cout << "The list is empty. Input list!\n";
            system("Pause");
            system("cls");
            menu(list, arr);
        }
        auto listStart = steady_clock::now();
        clear(list);
        auto listEnd = steady_clock::now();
        auto listClearTime = duration_cast<nanoseconds>(listEnd - listStart).count();

        auto arrayStart = steady_clock::now();
        delete[] arr;
        auto arrayEnd = steady_clock::now();
        auto arrayClearTime = duration_cast<nanoseconds>(arrayEnd - arrayStart).count();
        cout << "\n[Duration of clear for List is " << listClearTime << " ns]\n";
        cout << "\n[Duration of delete for Array is " << arrayClearTime << " ns]\n\n";

        system("Pause");
        system("cls");

        cout << "Want to continue or exit?\n[1] Continue\n[2] Exit\n";
        int exitChoice;
        cin >> exitChoice;
        if (exitChoice == 1)
        {
            system("Pause");
            system("cls");
            menu(list, arr);
        }
        else if (exitChoice == 2)
        {
            system("cls");
        }
        break;

    
    defult:
        cout << "Error! Try again\n";
        system("Pause");
        system("cls");
        menu(list, arr);
        break;
    }

}

int main()
{
    Node* list = nullptr;
    int size = 0;
    int* arr = new int[size];
    menu(list, arr);

}

