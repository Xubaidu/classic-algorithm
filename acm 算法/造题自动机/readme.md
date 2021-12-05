# 造题自动机

## 简单脚手架

造一个简单的脚手架，维护 5 个方法

- ```Solve``` 接收输入数据，返回输出数据
- ```Gen``` 创造输入数据
- ```WriteInFile``` 负责将输入写入 ```.in``` 文件
- ```WriteOutFile``` 负责将输出写入 ```.out``` 文件
- ```Automata``` 负责业务逻辑调用，自动化执行

输入数据封装在 ```InputData``` 里面

```cpp
struct InputData {
    const int n, k;
    const vector<int> a;
    InputData(const int _n, const int _k, const vector<int>& _a):
        n(_n), k(_k), a(_a) {}
};

class GenProb {
private:
    const int idx;
    const int MAXN;
public:
    GenProb(int _idx, int _MAXN);
    int Solve(const int n, const int k, const vector<int>& a) const;
    shared_ptr<InputData> Gen() const;
    void WriteInFile(const shared_ptr<InputData>& input) const;
    void WriteOutFile(const int ans) const;
    void Automata() const;
};
```

每次修改对应的方法，执行 ```Automata``` 方法即可生成输入输出数据

## 一些细节

- 用智能指针代替 ```raw pointer```，帮助管理内存

- 成员函数声明为 ```const```，防止修改成员变量
