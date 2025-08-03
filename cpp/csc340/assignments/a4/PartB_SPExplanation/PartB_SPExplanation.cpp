/****************************************************************
 *
 * File: [Assignment-03_PB_CCNumberValidation.cpp]
 * By: [Ramanuja Mohanty]
 * Date: [07/02/25]
 *
 * Description: [Demonstrations for Part B topics.]
 *
 * ****************************************************************/

// Smart Pointers - Assignment Part B (10 Extra Credit Points)
// Each section includes an explanation followed by a code experiment.

#include <iostream>
#include <memory>

// -----------------------------
// 1. Deleting the Same Memory Twice
// -----------------------------
void double_delete_example() {
    std::cout << "\n[1] Double Delete Example\n";
    int* ptr1 = new int(42);
    int* ptr2 = ptr1;

    delete ptr1;  // OK

    std::cout << "Avoided double delete.\n";
}

// -----------------------------
// 2. Smart Pointers with Automatic Scope-based Deletion
// -----------------------------
void smart_pointer_scope_example() {
    std::cout << "\n[2] Smart Pointer Scope Example\n";
    std::unique_ptr<int> smart_int = std::make_unique<int>(99);
    std::cout << "Smart pointer holds value: " << *smart_int << "\n";
    // Automatically deleted when function exits
}

// -----------------------------
// 3. Smart Pointers as Class Data Members
// -----------------------------
class Sample {
private:
    std::unique_ptr<int> data;
public:
    Sample(int value) : data(std::make_unique<int>(value)) {
        std::cout << "Sample created with value " << *data << "\n";
    }
    ~Sample() {
        std::cout << "Sample destroyed.\n";
    }
};

void class_member_smart_pointer_example() {
    std::cout << "\n[3] Class Member Smart Pointer Example\n";
    Sample obj(123);
    // Automatic destruction of obj and its internal data
}

// -----------------------------
// 4. Converting unique_ptr to shared_ptr
// -----------------------------
void unique_to_shared_example() {
    std::cout << "\n[4] unique_ptr to shared_ptr Example\n";
    std::unique_ptr<int> uptr = std::make_unique<int>(42);
    std::shared_ptr<int> sptr = std::move(uptr);  // Transfer ownership

    if (!uptr)
        std::cout << "unique_ptr is now null after move\n";

    std::cout << "shared_ptr holds: " << *sptr << "\n";
}

// -----------------------------
// 5. Using weak_ptr to Avoid Circular Reference
// -----------------------------
class B;  // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> a_ptr;  // weak_ptr prevents circular reference
    ~B() { std::cout << "B destroyed\n"; }
};

void weak_ptr_example() {
    std::cout << "\n[5] weak_ptr Circular Reference Example\n";
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;  // weak_ptr prevents memory leak

    std::cout << "End of weak_ptr example scope.\n";
}

int main() {
    double_delete_example();
    smart_pointer_scope_example();
    class_member_smart_pointer_example();
    unique_to_shared_example();
    weak_ptr_example();

    return 0;
}

