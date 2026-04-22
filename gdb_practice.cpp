#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

// ==========================================
// Stage 1: child 類別的指標未初始化 
// 對應講義: p.2, p.5-6 的 demo.cpp
// ==========================================
class child {
public:
    int value;
    string id;
    child* dad;

    child(int a, string b) { value = a; id = b; dad = nullptr; } // 故意讓 dad 為 null
    void printinfo() { 
        cout << dad->value << " "; 
        cout << dad->id << endl;
    }
};

void stage1() {
    cout << "\n[Stage 1] 測試 child 類別..." << endl;
    child* y = new child(60, "root");
    child* x = new child(50, "child");
    
    x->printinfo(); 
    
    cout << "[Stage 1] 通過！指標問題已修復。" << endl;
    delete x; delete y;
}

// ==========================================
// Stage 2: person 建構子的記憶體區段錯誤
// 對應講義: p.12 的 bug.cpp
// ==========================================
class person {
public:
    char* name_;
    int age_;
    
    person(char* n, int a) {
        int length = strlen(n); 
        name_ = new char[length + 1];
        strcpy(name_, n);
        age_ = a;
    }
    ~person() { delete[] name_; }
};

void stage2() {
    cout << "\n[Stage 2] 測試 person 類別..." << endl;
    char* bad_ptr = nullptr;
    person p(bad_ptr, 20); 
    
    cout << "[Stage 2] 通過！字串記憶體處理正確。" << endl;
}

// ==========================================
// Stage 3: summation 陣列越界與無號數無窮迴圈
// 對應講義: p.13-25 的 bug.cpp
// ==========================================
#define size 6

int summation(int array[]) {
    int result = 0;

    for (unsigned int i = size; i >= 0; --i) {
        result += array[i];
    }
    return result;
}

void stage3() {
    cout << "\n[Stage 3] 測試 summation 陣列計算..." << endl;
    int array[size];
    for (unsigned int i = 0; i < size; ++i) {
        array[i] = rand() % 10 + 1;
    }
    
    int val = summation(array);
    cout << "陣列總和: " << val << endl;
    
    cout << "[Stage 3] 通過！陣列越界與迴圈問題已修復。" << endl;
}

// ==========================================
// 主程式 Main
// ==========================================
int main() {
    srand(time(NULL));
    cout << "=== OOP GDB 實戰演練開始 ===" << endl;
    cout << "只要程式發生 Segmentation fault，請用 GDB 找出在哪一行並修復它！" << endl;

    stage1();
    stage2();
    stage3();

    cout << "\n🎉 恭喜你！所有 Bug 都解完了！" << endl;
    return 0;
}
