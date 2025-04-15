#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>
#include <typeinfo>

using namespace std;


//Ex6
// ������� ���������� ���������� ������ Array<T>
template <typename T>
class Array {
private:
    vector<T> data;

public:
    Array(size_t size, const T& value) : data(size, value) {}

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    size_t size() const {
        return data.size();
    }
};

// *** flatten ��� "��������" ����� (�� ������ ������) ***
template <typename T>
void flatten(const T& value, ostream& out) {
    out << value << " ";
}

// *** flatten ��� ������� (����������� �������������� ����������) ***
template <typename T>
void flatten(const Array<T>& arr, ostream& out) {
    for (size_t i = 0; i < arr.size(); ++i) {
        flatten(arr[i], out); // ����������� �����
    }
}


//Ex7---------------------------------------------------------------------------

// ��������� ��� ������������
struct ICloneable {
    virtual ~ICloneable() {}
    virtual ICloneable* clone() const = 0;
};

// ������, �������� �������� ������ ����
template <typename T>
struct ValueHolder : public ICloneable {
    T data_;

    ValueHolder(const T& value) : data_(value) {}

    ICloneable* clone() const override {
        return new ValueHolder<T>(data_);
    }
};

// ����� Any � ����� ������� ������ ������ ����
class Any {
private:
    ICloneable* ptr_;  // ��������� �� ������� ���������

public:
    // ����������� �� ��������� � ������ "������"
    Any() : ptr_(nullptr) {}

    // ��������� ����������� � ������ �������� ���� T
    template <typename T>
    Any(const T& value) : ptr_(new ValueHolder<T>(value)) {}

    // ���������� � ������������ ��������
    ~Any() {
        delete ptr_;
    }

    // ����������� �����������
    Any(const Any& other) {
        ptr_ = other.ptr_ ? other.ptr_->clone() : nullptr;
    }

    // �������� ����������� ������������
    Any& operator=(const Any& other) {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_ ? other.ptr_->clone() : nullptr;
        }
        return *this;
    }

    // ��������� �������� ������������ (��������, empty = 5;)
    template <typename T>
    Any& operator=(const T& value) {
        delete ptr_;
        ptr_ = new ValueHolder<T>(value);
        return *this;
    }

    // ����� cast<T> � ���������� ���������� ����
    template <typename T>
    T* cast() {
        ValueHolder<T>* p = dynamic_cast<ValueHolder<T>*>(ptr_);
        return p ? &p->data_ : nullptr;
    }

    // ������ const ��� ������������� � const Any
    template <typename T>
    const T* cast() const {
        const ValueHolder<T>* p = dynamic_cast<const ValueHolder<T>*>(ptr_);
        return p ? &p->data_ : nullptr;
    }
};

//Ex8----------------------------------------------------------------------------

// �������� ������ � �� ��������� ���� *������*
template <typename T, typename U>
struct SameType {
    static const bool value = false;
};

// ��������� ������������� � ���� *����������*
template <typename T>
struct SameType<T, T> {
    static const bool value = true;
};

struct Dummy {};
typedef int type;

int main() {

    setlocale(LC_ALL, "RUS");

    //Ex8


    cout << SameType<int, int>::value << endl;          // 1
    cout << SameType<int, type>::value << endl;         // 1
    cout << SameType<int, int&>::value << endl;         // 0
    cout << SameType<Dummy, Dummy>::value << endl;      // 1
    cout << SameType<int, const int>::value << endl;    // 0

    return 0;
   
    //Ex7

    Any empty; // ������ ������
    Any i(10); // ������ int

    int* iptr = i.cast<int>();
    if (iptr) cout << "i = " << *iptr << endl;

    char* cptr = i.cast<char>();
    if (!cptr) cout << "i �� ������ char\n";

    Any copy(i); // �����
    cout << "copy = " << *copy.cast<int>() << endl;

    empty = copy;
    cout << "empty = " << *empty.cast<int>() << endl;

    empty = 3.14;
    double* dptr = empty.cast<double>();
    cout << "������ empty ������ double: " << *dptr << endl;

    int* wrong = empty.cast<int>();
    cout << "������� �������� int �� double: "
        << (wrong ? "�����" : "�������") << endl;

    return 0;

    //Ex6
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;

    cout << "ints: ";
    flatten(ints, cout);  // ��������� �����: "10 20"
    cout << endl;

    Array< Array<int> > array_of_ints(2, ints);
    cout << "array_of_ints: ";
    flatten(array_of_ints, cout);  // ��������� �����: "10 20 10 20"
    cout << endl;

    Array<double> doubles(3, 1.5);
    doubles[1] = 2.5;
    doubles[2] = 3.5;
    cout << "doubles: ";
    flatten(doubles, cout);  // ��������� �����: "1.5 2.5 3.5"
    cout << endl;

    // ��������� ������ ������
    Array< Array< Array<int> > > deep(2, array_of_ints);
    cout << "deep nested: ";
    flatten(deep, cout);  // ��������� �����: "10 20 10 20 10 20 10 20"
    cout << endl;

    return 0;
}

