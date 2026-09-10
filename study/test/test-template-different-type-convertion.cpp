#include <iostream>

// 假设有一个模板类
template <typename T>
class MyTemplateClass {
public:
    // 构造函数，用于从不同类型的对象创建当前类型的对象
    MyTemplateClass(T value1){
        value = value1;
    }
    template <typename U>
    MyTemplateClass(const MyTemplateClass<U>& other) {
        // 这里可以实现具体的类型转换逻辑
        // 例如，如果 T 和 U 可以相互转换，可以在这里进行相应的转换
        value = static_cast<T>(other.GetValue());
    }

    // 获取当前对象的值
    T GetValue() const {
        return value;
    }

private:
    T value;
};

// 辅助函数，用于演示类型转换
template <typename T>
void DisplayValue(const MyTemplateClass<T>& obj) {
    std::cout << "Value: " << obj.GetValue() << std::endl;
}

int main() {
    // 创建一个 MyTemplateClass<int> 对象
    MyTemplateClass<int> intObj(42);

    // 将其转换为 MyTemplateClass<double>
    MyTemplateClass<char> doubleObj = intObj;

    // 显示转换后的值
    DisplayValue(intObj);
    DisplayValue(doubleObj);

    return 0;
}