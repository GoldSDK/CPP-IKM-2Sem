#include <iostream>
#include <limits>
using namespace std;

class Node {
    public:
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* _head;
    Node* _tail;
    int _size;

public:
    LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

    void PushBack(int val) {
        Node* newNode = new Node(val);
        if (!_head) {
            _head = _tail = newNode;
        } 
        else {
            _tail->next = newNode;
            _tail = newNode;
        }
        _size++;
    }

    void Erase(Node* start, Node* end) {
        if (!start || !_head) return;
        Node* prev = nullptr;
        Node* current = _head;
        while (current && current != start) {
            prev = current;
            current = current->next;
        }

        Node* temp;
        int count = 0;
        while (current && current != end) {
            temp = current;
            current = current->next;
            delete temp;
            count++;
        }

        if (prev) {
            prev->next = current;
        } 
        else {
            _head = current;
        }

        if (!current) {
            _tail = prev; 
        }

        _size -= count;
    }

    int DestroySeq() {
        if (!_head) return 0;

        int destroyed = 0;
        bool found = true;

        while (found) {
            found = false;
            Node* current = _head;
            Node* rangeStart = nullptr;
            int count = 1;

            while (current) {
                if (current->next && current->value == current->next->value) {
                    if (!rangeStart) rangeStart = current;
                    count++;
                } 
                else {
                    if (count >= 3) {
                        Node* rangeEnd = current->next;
                        Erase(rangeStart, rangeEnd);
                        destroyed += count;
                        found = true;
                        break;
                }
                rangeStart = nullptr;
                count = 1;
            }
            current = current->next;
        }
    }
    return destroyed;
}

    void Print() {
        Node* current = _head;
        while (current) {
        cout << current->value << " ";
        current = current->next;
        }
       cout << endl;
    }

    ~LinkedList() {
        Node* current = _head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    cout << "=========================" << endl;
    cout << "Добро пожаловать в Шарики! " << endl;
    cout << "=========================" << endl;
    cout << "Тут конечно нет никаких шариков, но есть цифры. Введи количество шариков, которые будут задействованы." << endl;
    
    int n;
    while (true) {
        cout << " >> ";
        cin >> n;
        
        if (cin.fail() || n <= 0 || n > 100000) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "НЕПРАВИЛЬНО! Введи положительное целое число меньшее 10^5!" << endl;
        } 
        else {
            break;
        }
    }

    LinkedList list;

    cout << "Замечательно. Теперь введи сами 'шарики', это цифры в диапазоне от 0 до 9." << endl;
    cout << " >> ";
    for (int i = 0; i < n; i++) {
        int num;
        while (true) {
            cin >> num;
            if (cin.fail() || num < 0 || num > 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "НЕПРАВИЛЬНО! Введи цифру от 0 до 9!" << endl;
                cout << " >> ";
            }
            else {
                break;
            }
        }
        list.PushBack(num);
    }

    int totalDestroyed = list.DestroySeq();
    cout << "Уничтожено шариков: " << totalDestroyed << endl;
    cout << "Оставшиеся шарики: ";
    list.Print();
    return 0;
}