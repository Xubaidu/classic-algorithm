# 造题自动机

## 简单脚手架

用一个类维护一个简单的脚手架，维护 5 个方法

```cpp
class GenProb {
private:
    const int idx;
    const int MAXN;
public:
    GenProb(int _idx, int _MAXN);
    const int Solve(const int n, const int k, const vector<int>& a);
    const InputData* Gen() const;
    void WriteInFile(const InputData* input) const;
    void WriteOutFile(const int ans) const;
    void Automata();
};
```

每次修改对应的方法，执行代码即可生成输入输出数据
