#include <iostream>
#include <limits>
using namespace std;

// узел связного списка
class Node {
public:
    int value;
    Node* next; 

    // конструктор узла
    Node(int val) : value(val), next(nullptr) {}
};

// односвязный список
class LinkedList {
private:
    Node* _head;
    Node* _tail;
    int _size; // количество элементов в списке

public:
    LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

    // добавление элемента в конец
    void PushBack(int val) {
        Node* newNode = new Node(val);
        if (!_head) {
            _head = _tail = newNode; // новый узел становится и головой и хвостом
        } 
        else {
            _tail->next = newNode; // добавляем узел в конец
            _tail = newNode; // обновляем указатель на хвост
        }
        _size++; // увеличиваем счетчик элементов
    }

    // удаление цепочки узлов от start до end (без end)
    void Erase(Node* start, Node* end) {
        if (!start || !_head) return;
        
        // поиск узла перед start
        Node* prev = nullptr;
        Node* current = _head;
        while (current && current != start) {
            prev = current;
            current = current->next;
        }

        // удаление узлов
        Node* temp;
        int count = 0;
        while (current && current != end) {
            temp = current;
            current = current->next;
            delete temp;
            count++; // считаем удаленные узлы
        }

        // обновление связей
        if (prev) {
            prev->next = current; 
        } 
        else {
            _head = current;
        }

        // обновление хвоста
        if (!current) {
            _tail = prev;
        }

        _size -= count;
    }

    // поиск и удаление цепочки из 3+ шариков
    int DestroySeq() {
        if (!_head) return 0;

        int destroyed = 0; // счетчик уничтоженных шариков
        bool found = true; // флаг для продолжения поиска

        while (found) {
            found = false;
            Node* current = _head;
            Node* rangeStart = nullptr;  // начало последовательности
            int count = 1;               // длина

            // поиск последовательностей
            while (current) {
                if (current->next && current->value == current->next->value) {
                    if (!rangeStart) rangeStart = current;  // запоминаем начало
                    count++;
                } 
                else {
                    if (count >= 3) { // нашли последовательность
                        Node* rangeEnd = current->next;
                        Erase(rangeStart, rangeEnd); // удаляем
                        destroyed += count;
                        found = true; // продолжаем поиск
                        break;
                    }
                    rangeStart = nullptr; // сброс для новой последовательности
                    count = 1;
                }
                current = current->next;
            }
        }
        return destroyed;
    }

    // вывод списка
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
    cout << "Добро пожаловать в SHARIQI! " << endl;
    cout << "=========================" << endl;
    cout << "Тут конечно нет никаких шариков, но есть цифры. Введи количество шариков, которые будут задействованы." << endl;
    
    // ввод количества шариков с проверкой
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

    LinkedList list;  // создаем список

    // ввод последовательности шариков
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
        list.PushBack(num);  // добавляем шарик в список
    }

    // вывод результатов
    int totalDestroyed = list.DestroySeq();
    cout << "Уничтожено шариков: " << totalDestroyed << endl;
    cout << "Оставшиеся шарики: ";
    list.Print();
    
    return 0;
}