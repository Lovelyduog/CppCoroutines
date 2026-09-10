#include <iostream>
#include <string>

class MyString {
private:
    const char* buffer = nullptr;

public:
    // 带参构造函数
    MyString()  {
      std::cout << " MyString() " << std::endl;  
    }
    MyString(MyString & other) {
        std::cout << " MyString(MyString & other)" << std::endl;
    }
};

// 外部传参buffer的函数
MyString createString() {
    MyString str;
    return str;
}

int main() {
    MyString str = createString();  

    return 0;
}