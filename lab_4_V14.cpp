#include <iostream>
#include <initializer_list>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class DequeBasedOnUnidirectionalCyclicLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    unsigned size;

public:
    DequeBasedOnUnidirectionalCyclicLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    explicit DequeBasedOnUnidirectionalCyclicLinkedList(const T& element) : head(nullptr), tail(nullptr), size(0) {
        PushBack(element);
    }

    DequeBasedOnUnidirectionalCyclicLinkedList(const DequeBasedOnUnidirectionalCyclicLinkedList<T>& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node<T>* curr = other.head;
        while (curr != nullptr) {
            PushBack(curr->data);
            curr = curr->next;
        }
    }

    DequeBasedOnUnidirectionalCyclicLinkedList(DequeBasedOnUnidirectionalCyclicLinkedList<T>&& other) noexcept {
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    DequeBasedOnUnidirectionalCyclicLinkedList(initializer_list<T> ilist) : head(nullptr), tail(nullptr), size(0) {
        for (const T& value : ilist) {
            PushBack(value);
        }
    }

    ~DequeBasedOnUnidirectionalCyclicLinkedList() {
        while (!IsEmpty()) {
            T element;
            PopFront(element);
        }
    }

    unsigned GetSize() const {
        return size;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }

        Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    DequeBasedOnUnidirectionalCyclicLinkedList& operator=(const DequeBasedOnUnidirectionalCyclicLinkedList<T>& other) {
        if (this != &other) {
            while (!IsEmpty()) {
                T element;
                PopFront(element);
            }

            Node<T>* curr = other.head;
            while (curr != nullptr) {
                PushBack(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    DequeBasedOnUnidirectionalCyclicLinkedList& operator=(DequeBasedOnUnidirectionalCyclicLinkedList<T>&& other) noexcept {
        if (this != &other) {
            while (!IsEmpty()) {
                T element;
                PopFront(element);
            }

            head = other.head;
            tail = other.tail;
            size = other.size;

            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    DequeBasedOnUnidirectionalCyclicLinkedList& operator=(initializer_list<T> ilist) {
        while (!IsEmpty()) {
            T element;
            PopFront(element);
        }

        for (const T& value : ilist) {
            PushBack(value);
        }

        return *this;
    }

    bool PushFront(const T& element) {
        Node<T>* newNode = new Node<T>(element);

        if (IsEmpty()) {
            head = newNode;
            tail = newNode;
            tail->next = head; // Make it cyclic
        }
        else {
            newNode->next = head;
            head = newNode;
            tail->next = head; // Update cyclic link
        }

        size++;
        return true;
    }

    bool PopFront(T& element) {
        if (IsEmpty()) {
            return false;
        }

        element = head->data;

        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node<T>* temp = head;
            head = head->next;
            tail->next = head; // Update cyclic link
            delete temp;
        }

        size--;
        return true;
    }

    bool PushBack(const T& element) {
        Node<T>* newNode = new Node<T>(element);

        if (IsEmpty()) {
            head = newNode;
            tail = newNode;
            tail->next = head; // Make it cyclic
        }
        else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // Update cyclic link
        }

        size++;
        return true;
    }

    bool PopBack(T& element) {
        if (IsEmpty()) {
            return false;
        }

        element = tail->data;

        if (size == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node<T>* curr = head;
            while (curr->next != tail) {
                curr = curr->next;
            }
            delete curr->next;
            curr->next = head; // Update cyclic link
        }

        size--;
        return true;
    }

    bool PeekFront() const {
        if (IsEmpty()) {
            return false;
        }

        return head->data;
    }

    bool PeekBack() const {
        if (IsEmpty()) {
            return false;
        }

        return tail->data;
    }

    bool IsEmpty() const {
        return size == 0;
    }
};

int main() {
    DequeBasedOnUnidirectionalCyclicLinkedList<int> deque;// Создаём дэк
    //накинем несколько елементов для видимости
    //спереди
    deque.PushFront(1);
    deque.PushFront(2);
    deque.PushFront(3);
    deque.PushFront(4);
    //сзади
    deque.PushBack(2);
    deque.PushBack(3);
    deque.PushBack(4);

    cout << "Size: " << deque.GetSize() << endl;
    cout << "Front elem: " << deque.PeekFront() << endl;
    cout << "Back elem: " << deque.PeekBack() << endl;

    cout << "\nDeque print: ";
    for (unsigned i = 0; i < deque.GetSize(); i++) {
        cout << deque[i] << " ";
    }
    cout << endl;

    //поудаляем спереди и сзади
    int removedElement;
    if (deque.PopFront(removedElement)) {
        cout << "\nRemoved from Front: " << removedElement << endl;
    }

    if (deque.PopBack(removedElement)) {
        cout << "Removed from Back: " << removedElement << endl;
    }

    //результат
    cout << "\nSize: " << deque.GetSize() << endl;
    cout << "Deque: ";
    for (unsigned i = 0; i < deque.GetSize(); i++) {
        cout << deque[i] << " ";
    }
    cout << endl;

    return 0;
}