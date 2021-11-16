#include <bits/stdc++.h>
using namespace std;

const int MAXN1 = 1e2;
const int MAXN2 = 1e3;
const int MAXN3 = 1e5;
const int N = 1e4;

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
    GenProb(int _idx, int _MAXN): idx(_idx), MAXN(_MAXN)
    {
        const string command1("mkdir -p ./data");
        const string command2("mkdir -p ./data");
        system(command1.c_str());
        system(command2.c_str());
    }
    int Solve(const int n, const int k, const vector<int>& a) const
    {
        vector<int> sum(n + 1);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + a[i];
        }
        int L = n - k, ans = 0;
        for (int i = 1; i + L - 1 <= n; ++i) {
            int j = i + L - 1;
            ans = max(ans, sum[i - 1] + sum[n] - sum[j]);
        }
        return ans;
    }
    shared_ptr<InputData> Gen() const
    {
        int n = rand() % MAXN + 1;
        int k = rand() % (n - 1) + 1;
        vector<int> vec(n + 1);
        for (int i = 1; i <= n; ++i) vec[i] = rand() % N + 1;
        auto input(make_shared<InputData>(n, k, vec));
        return input;
    }
    void WriteInFile(const shared_ptr<InputData>& input) const
    {
        const string inFileName("./data/" + to_string(idx) + ".in");
        ofstream ofs(inFileName.c_str());
        if (!ofs.is_open()) {
            cout << "error opening file in gen\n";
            return;
        }
        ofs << input->n << " " << input->k << "\n";
        for (int i = 1; i <= input->n; ++i) ofs << input->a[i] << " \n"[i == input->n];
        ofs.close();
    }
    void WriteOutFile(const int ans) const
    {
        const string inFileName("./data/" + to_string(idx) + ".out");
        ofstream ofs(inFileName.c_str());
        if (!ofs.is_open()) {
            cout << "error opening file in gen\n";
            return;
        }
        ofs << ans << "\n";
        ofs.close();
    }
    void Automata() const
    {
        auto input = Gen();
        int ans = Solve(input->n, input->k, input->a);
        WriteInFile(input);
        WriteOutFile(ans);
    }
};

int main()
{
    for (int i = 1; i <= 20; ++i) {
        if (i <= 6) {
            auto GP(make_unique<GenProb>(i, MAXN1));
            GP->Automata();
        }
        else if (i <= 12) {
            auto GP(make_unique<GenProb>(i, MAXN2));
            GP->Automata();
        }
        else {
            auto GP(make_unique<GenProb>(i, MAXN3));
            GP->Automata();
        }
    }
    return 0;
}