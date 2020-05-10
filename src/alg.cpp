#include <cassert>

struct SYM {
    char ch;
    int  prior;
};

template<typename T>
class TPQueue {
private:
    T* arr;
    int size;
    int begin;
    int end;
    int count;
    int next(int end);
    int prev(int end);
public:
    TPQueue(int = 100);
    ~TPQueue();
    void push(const T&);
    T pop();
    T get() const;
    bool isEmpty() const;
    bool isFull() const;
};

template<typename T>
int TPQueue<T>::prev(int lp) {
    if (--lp < 0)
        lp += size + 1;
    return lp;
}
template<typename T>
int TPQueue<T>::next(int lp) {
    if (++lp > size)
        lp -= size + 1;
    return lp;
}

template<typename T>
TPQueue<T>::TPQueue(int sizeQueue): size(sizeQueue), begin(0), end(0), count(0) {
    arr = new T[size + 1];
}

template<typename T>
TPQueue<T>::~TPQueue() {
    delete[] arr;
}

template<typename T>
void TPQueue<T>::push(const T& item) {
    assert(count < size);
    if (isEmpty()) {
        arr[end] = item;
    }
    else {
        int tmp = prev(end); 
        if (arr[tmp].prior >= item.prior) {
            arr[end] = item;
        }
        else {
            do {
                arr[next(tmp)] = arr[tmp];
                tmp = prev(tmp);
            } 
            while (arr[tmp].prior < item.prior && next(tmp) != begin);
            arr[next(tmp)] = item;
        }
    }
    end = next(end);
    count++;
}

template<typename T>
T TPQueue<T>::pop() {
    assert(count > 0);
    T item = arr[begin];
    begin = next(begin);
    count--;
    return item;
}

template<typename T>
T TPQueue<T>::get() const {
    assert(count > 0);
    return arr[begin];
}

template<typename T>
bool TPQueue<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
bool TPQueue<T>::isFull() const {
    return count == size;
}

