# 字节校园打卡记录

[toc]

## 8.19

### [3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/) ✨

- 双指针构成一个滑动窗口
- 哈希表记录每个元素的出现位置

```go
// go
func max(a int, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}

func lengthOfLongestSubstring(s string) int {
    mp := make(map[byte]int)
    l, r, ans := 0, 0, 0
    for r < len(s) {
        val, ok := mp[s[r]]
        if !ok {
            mp[s[r]] = r
        } else {
            // mp[s[r]] 表示上一个 s[r] 出现的位置，如果 mp[s[r]] > l，要把 l 移到 mp[s[r]] 之后
            if val >= l {
                l = val + 1
            }
            mp[s[r]] = r
        }
        ans = max(ans, r-l+1)
        r++
    }
    return ans
}
```

### [25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)✨

- 维护四个指针 ```pre, head, tail, next```
- 找到待反转链表的头尾
- 做一次普通反转链表，返回新的头尾
- 串联

```cpp
// cpp
#define PLL pair< ListNode *, ListNode * >
class Solution {
public:
    PLL getNewHeadTail(ListNode *head, ListNode *tail)
    {
        ListNode *pre = tail->next, *cur = head, *ed = tail->next;
        while (cur != ed) {
            ListNode *temp = cur->next;
            cur->next = pre;
            pre = cur, cur = temp;
        }
        return {tail, head};
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *dummy = new ListNode(0, head), *pre = dummy;
        while (head) {
            ListNode *tail = pre;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) return dummy->next;
            }
            ListNode *nxt = tail->next;
            PLL temp = getNewHeadTail(head, tail);
            head = temp.first, tail = temp.second;
            pre->next = head, tail->next = nxt;
            pre = tail, head = nxt;
        }
        return dummy->next;
    }
};
```

### [20. 有效的括号](https://leetcode-cn.com/problems/valid-parentheses/)

- 栈

```cpp
// cpp
class Solution {
public:
    bool isValid(string s) {
        stack<int> sta;
        for (auto &i: s) {
            if (i == '(' || i == '[' || i == '{') sta.push(i);
            else {
                if (sta.empty()) return 0;
                if (i == ')' && sta.top() != '(') return 0;
                if (i == ']' && sta.top() != '[') return 0;
                if (i == '}' && sta.top() != '{') return 0;
                sta.pop();
            }
        }
        return sta.empty();
    }
};
```

## 8.20

### [1. 两数之和](https://leetcode-cn.com/problems/two-sum/)

- 哈希
- 或者排序后双指针 ```meet in the middle```

```go
// go
func twoSum(nums []int, target int) []int {
    mp := make(map[int]int)
    for i, v := range nums {
        mp[v] = i
    }
    ans := []int{}
    for i, v := range nums {
        if pos, ok := mp[target-v]; ok && pos > i {
            ans = []int{i, pos}
            break
        }
    }
    return ans
}
```

### [15. 三数之和](https://leetcode-cn.com/problems/3sum/) ✨

- 排序
- 枚举第一个数字，接下来两个指针 ```meet in the middle```
- 用一些去重剪枝技巧

```go
// go
func threeSum(nums []int) [][]int {
    n := len(nums)
    sort.Ints(nums)
    ans := [][]int{}
    for i := 0; i < n; i++ {
        if nums[i] > 0 { // 剪枝
            break
        }
        if i > 0 && nums[i] == nums[i - 1] { // 去重,可能的解已经存在了
            continue;
        }
        k := n - 1
        for j := i + 1; j < n; j++ {
            if j > i + 1 && nums[j] == nums[j - 1] { // 去重,同上
                continue
            }
            for k > j && nums[i] + nums[j] + nums[k] > 0 {
                k--
            }
            if k == j {
                break
            }
            if nums[i] + nums[j] + nums[k] == 0 {
                ans = append(ans, []int{nums[i], nums[j], nums[k]})
            }
        }
    }
    return ans
}
```

### [54. 螺旋矩阵](https://leetcode-cn.com/problems/spiral-matrix/)

- ```dfs```

```go
// go
func spiralOrder(matrix [][]int) []int {
    m, n := len(matrix), len(matrix[0])
    ans := make([]int, m * n)
    vis := make([][]bool, m)
    for i := 0; i < len(matrix); i++ {
        vis[i] = make([]bool, n)
    }
    dfs(matrix, vis, ans, m, n, 0, 0, 0, 0)
    return ans
}
func check(m, n, x, y int, vis[][]bool) bool {
    return x >= 0 && x < m && y >= 0 && y < n && vis[x][y] == false
}
func dfs(matrix [][]int, vis [][]bool, ans []int, m, n, x, y, dir, cnt int) {
    if vis[x][y] {
        return
    }
    ans[cnt], cnt, vis[x][y] = matrix[x][y], cnt + 1, true
    DX := []int{0, 1, 0, -1}
    DY := []int{1, 0, -1, 0}
    var tx, ty int
    if check(m, n, x + DX[dir], y + DY[dir], vis) { // 继续顺着这个方向
        tx, ty = x + DX[dir], y + DY[dir]
    } else if check(m, n, x + DX[(dir + 1) % 4], y + DY[(dir + 1) % 4], vis) {  // 换下一个方向
        tx, ty, dir = x + DX[(dir + 1) % 4], y + DY[(dir + 1) % 4], (dir + 1) % 4
    }
    dfs(matrix, vis, ans, m, n, tx, ty, dir, cnt)
}
```

## 8.21

### [33. 搜索旋转排序数组](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

- 无聊的八股文，没兴趣写二分

```cpp
// cpp
class Solution {
public:
    int search(vector<int>& nums, int t) {
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] == t) return i;
        return -1;
    }
};
```

### [21. 合并两个有序链表](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

- 归并排序的子步骤

```go
// go
func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
    head := &ListNode {
        Val: 0,
        Next: nil,
    }
    pre := head
    for l1 != nil || l2 != nil {
        if l1 == nil || l1 != nil && l2 != nil && l1.Val > l2.Val {
            head.Next = l2
            l2 = l2.Next
        } else {
            head.Next = l1
            l1 = l1.Next
        }
        head = head.Next
    }
    return pre.Next
}
```

### [31. 下一个排列](https://leetcode-cn.com/problems/next-permutation/) ✨

- 逆序遍历，找到第一个 ```nums[i] < nums[i + 1]``` 的位置 ```p1```
- 在 ```[p1 + 1, n)``` 里面找到第一个比 ```nums[p1]``` 大的位置 ```p2```
- 逆转 ```[p1 + 1, n)```

```cpp
// cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(),  nums.end());
    }
};

// cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int pos = -1;
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {pos = i; break;}
        }
        if (pos != -1) {
            int p = n - 1;
            while (p > pos && nums[p] <= nums[pos]) p--;
            swap(nums[pos], nums[p]);
        }
        reverse(nums.begin() + pos + 1, nums.end());
    }
};
```

## 8.22

### [42. 接雨水](https://leetcode-cn.com/problems/trapping-rain-water/) ✨

- 对于每个位置 ```i```，找到他左边和右边最高的位置 ```p1, p2```，则这个位置的贡献为 ```min(h[p1], h[p2]) - h[i]```
- 累加贡献

```go
// go
func trap(h []int) int {
    lmax := make([]int, len(h))
    rmax := make([]int, len(h))
    for i := 0; i < len(h); i++ {
        if i == 0 {
            lmax[i] = h[i];
        } else {
            lmax[i] = max(lmax[i - 1], h[i])
        }
    }
    for i := len(h) - 1; i >= 0; i-- {
        if i == len(h) - 1 {
            rmax[i] = h[i]
        } else {
            rmax[i] = max(rmax[i + 1], h[i])
        }
    }
    ans := 0
    for i := 1; i < len(h) - 1; i++ {
        ans += min(lmax[i], rmax[i]) - h[i]
    }
    return ans
}

func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
func min(a, b int) int {
    if a < b {
        return a
    } else {
        return b
    }
}
```

### [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

- 动态规划的思想

```go
// go
func maxSubArray(nums []int) int {
    sum, ans := 0, -100001
    for _, v := range(nums) {
        sum = max(sum + v, v)
        ans = max(ans, sum)
    }
    return ans
}

func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
```

### [88. 合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/)

- 没兴趣写 ```in place```

```go
// go
func merge(nums1 []int, m int, nums2 []int, n int)  {
    temp := make([]int, m + n)
    i, j, k := 0, 0, 0
    for i < m || j < n {
        if (i == m || i < m && j < n && nums1[i] > nums2[j]) {
            temp[k] = nums2[j]
            k++
            j++
        } else {
            temp[k] = nums1[i]
            k++
            i++
        }
    }
    for i, v := range(temp) {
        nums1[i] = v
    }
}
```

- ```in place``` 的补上了
- 从后往前归并，大的数据会被填在后面，前面的数据直接覆盖即可

```cpp
// cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int a = m - 1, b = n - 1, c = m + n - 1;
        while (c >= 0) {
            if (a >= 0 && b >= 0) {
                if (nums1[a] > nums2[b]) nums1[c--] = nums1[a--];
                else nums1[c--] = nums2[b--];  
            }
            else {
                if (a >= 0) nums1[c--] = nums1[a--];
                else if (b >= 0) nums1[c--] = nums2[b--];
            }
        }
    }
};
```

## 8.23

### [102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/) ✨

- 把一层放入队列来 ```bfs```

```cpp
// cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> level;
            for (int i = 1; i <= sz; ++i) {
                TreeNode *temp = q.front(); q.pop();
                level.push_back(temp->val);
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
            ans.push_back(level);
        }
        return ans;
    }
};
```

### [103. 二叉树的锯齿形层序遍历](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)

- 用双端队列来维护节点
- 从右往左遍历先放右儿子，从左往右遍历先放左儿子

```cpp
// cpp
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;
        deque<TreeNode *> q;
        q.push_back(root);
        int cnt = 0;
        while (!q.empty()) {
            int sz = q.size();
            vector<int> level;
            if (cnt == 0) {
                for (int i = 1; i <= sz; ++i) { // 从左往右遍历，先放左儿子
                    TreeNode *temp = q.front(); q.pop_front();
                    level.push_back(temp->val);
                    if (temp->left) q.push_back(temp->left);
                    if (temp->right) q.push_back(temp->right);
                }
            }
            else {
                for (int i = 1; i <= sz; ++i) { // 从右往左遍历，先放右儿子
                    TreeNode *temp = q.back(); q.pop_back();
                    level.push_back(temp->val);
                    if (temp->right) q.push_front(temp->right);
                    if (temp->left) q.push_front(temp->left);
                }
            }
            cnt = (cnt + 1) % 2;
            ans.push_back(level);
        }
        return ans;
    }
};
```

### [105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) ✨

- 前序结构为 ```[root] [left] [right]```
- 中序结构为 ```[left] [root] [right]```
- 在中序中找到根的位置 ```pos1```，就可以快速定位前序中左子树的右边界 ```pos2```
- 可以用哈希预处理中序里面根的位置

```cpp
// cpp
class Solution {
public:
    unordered_map<int, int> mp;
    void preSolve(vector<int> &inorder) {
        for (int i = 0; i < inorder.size(); ++i) {
            mp[inorder[i]] = i;
        }
    }
    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int pl, int pr, int il, int ir) {
        if (pl >= pr) return nullptr;
        TreeNode *root = new TreeNode(preorder[pl]);
        int pos1 = mp[root->val]; // 利用哈希表 O(1) 计算根在中序遍历中的位置 pos1
        int pos2 = pl + (pos1 - il); // 根据 pos1 计算出左子树的边界位置 pos2
        root->left = dfs(preorder, inorder, pl + 1, pos2 + 1, il, pos1);
        root->right = dfs(preorder, inorder, pos2 + 1, pr, pos1 + 1, ir);
        return root;
    }
    TreeNode* buildTree(vector<int>& p, vector<int>& i) {
        preSolve(i);
        return dfs(p, i, 0, p.size(), 0, i.size());
    }
};
/*
[root] [left] [right]
[left] [root] [right]
*/
```

## 8.24

### [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

- 对于每一个位置，维护之前的最小值即可

```go
// go
func maxProfit(p []int) int {
    mini := 10001
    ans := 0
    for _, v := range(p) {
        mini = min(mini, v)
        ans = max(ans, v - mini)
    }
    return ans
}
func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
func min(a, b int) int {
    if a < b {
        return a
    } else {
        return b
    }
}
```

### [141. 环形链表](https://leetcode-cn.com/problems/linked-list-cycle/)

- 快慢指针追

```go
// go
func hasCycle(head *ListNode) bool {
    if head == nil {
        return false
    }
    a, b := head, head.Next
    for a != nil && b != nil && a != b {
        a = a.Next
        b = b.Next
        if b != nil {
            b = b.Next
        } else {
            break
        }
    }
    return a == b
}
```

### [146. LRU 缓存机制](https://leetcode-cn.com/problems/lru-cache/) ✨

考虑需要的数据结构

- 需要左右删除，因此维护一个双向链表 ```node*```
- 需要快速定位节点位置，因此维护一个哈希表 ```unordered_map<int, node*>```
- 设置一个 ```dummy head, dummy tail```，避免删除特判情况
- 每次要根据节点的键来更新，因此双向链表里需要维护 ```key, val```

考虑需要的方法

- 每次 ```put```，需要添加到头，容量大了要删除尾巴
- 每次 ```get```，需要删除一个节点并添加到头
- 所以需要完善三个方法

```cpp
void addHead(node *)
void del(node *)
void delTail(node *)
```

代码

```cpp
// cpp
struct node
{
    node *left, *right;
    int key, val;
    node(){}
    node(int _key, int _val): key(_key), val(_val), left(nullptr), right(nullptr) {}
};
class LRUCache {
private:
    unordered_map< int, node * > mp;
    node *head, *tail;
    int sz, cap;

public:
    LRUCache(int capacity): cap(capacity), sz(0) {
        head = new node(-1, 0);
        tail = new node(-2, 0);
        head->right = tail;
        tail->left = head;
    }
    void del(node *cur) {
        mp[cur->key] = nullptr;
        node *a = cur->left;
        node *b = cur->right;
        a->right = b;
        b->left = a;
        sz--;
    }
    void delTail() {
        node *a = tail->left;
        del(a);
    }
    void addHead(node *cur) {
        node *a = head->right;
        head->right = cur, cur->left = head;
        cur->right = a, a->left = cur;
        mp[cur->key] = cur;
        sz++;
    }
    int get(int key)
    {
        node *cur = mp[key];
        if (cur) {
            int ans = cur->val;
            del(cur);
            addHead(cur);
            return ans;
        }
        else return -1;
    }
    void put(int key, int value)
    {
        node *temp = mp[key];
        if (temp) {
            temp->val = value;
            del(temp);
            addHead(temp);
        }
        else {
            node *cur = new node(key, value);
            addHead(cur);
            if (sz > cap) delTail();
            mp[key] = cur;
        }
        //debug(head);
    }
    void debug(node *head) {
        cout << "fuck" << ' ' << sz << ' ' << cap << endl;
        while (head) {
            cout << head->key << ' ' << head->val << endl;
            head = head->right;
        }
    }
};
```

## 8.25

### [160. 相交链表](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

- 两个指针走，走到尽头换一个头开始遍历
- 相遇或者走到头时两个指针走的路程一定一样

```go
// go
func getIntersectionNode(headA, headB *ListNode) *ListNode {
    A, B := headA, headB
    for A != B {
        if A == nil {
            A = headB
        } else {
            A = A.Next
        }
        if B == nil {
            B = headA
        } else {
            B = B.Next
        }
    }
    return A
}
```

### [199. 二叉树的右视图](https://leetcode-cn.com/problems/binary-tree-right-side-view/)

- 层序遍历，把一行放入队列，用队列的大小来指导循环次数
- 把每一行的最后一个数放入列表，最终返回这个列表

```cpp
// cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans; 
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 1; i <= sz; ++i) {
                TreeNode* temp = q.front(); q.pop();
                if (i == sz) ans.push_back(temp->val);
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
        }
        return ans;
    }
};
```

### [200. 岛屿数量](https://leetcode-cn.com/problems/number-of-islands/)

- 求联通块个数，可以 ```bfs```，也可以并查集

```cpp
// cpp
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};
class Solution {
public:
    bool check(int x, int y, vector<vector<char>>& grid, vector<vector<int>>& vis) {
        int m = grid.size();
        int n = grid[0].size();
        return x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != '0';
    }
    void bfs(int x, int y, vector<vector<char>>& grid, vector<vector<int>>& vis) {
        queue<pair<int, int>> q;
        q.push(pair<int, int>{x, y});
        vis[x][y] = 1;
        while (!q.empty()) {
            pair<int, int> temp = q.front(); q.pop();
            //cout << temp.first << ' ' << temp.second << endl;
            for (int i = 0; i < 4; ++i) {
                int tx = temp.first + DX[i];
                int ty = temp.second + DY[i];
                if (check(tx, ty, grid, vis)) {
                    q.push(pair<int, int>{tx, ty});
                    vis[tx][ty] = 1;
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<int>> vis(grid.size(), vector<int>(grid[0].size()));
        int ans = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (!vis[i][j] && grid[i][j] != '0') {
                    bfs(i, j, grid, vis);
                    ans++;
                }
            }
        }
        return ans;
    }
};
```

## 8.26

### [反转链表](https://leetcode-cn.com/problems/reverse-linked-list/submissions/)

- 经典

```cpp
// cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = nullptr;
        while (head) {
            ListNode *temp = head->next;
            head->next = pre;
            pre = head;
            head = temp;
        }
        return pre;
    }
};
```

## 8.27

### [300. 最长递增子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

- $O(n\log n)$ 做法
- 定义 $dp[i]$ 表示长度为 $i + 1$ 的 $LIS$ 最后一位的最小元素

```cpp
// cpp
#define inf 0x3f3f3f3f
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n);
        fill(dp.begin(), dp.end(), inf);
        for (int i = 0; i < n; ++i) {
            *lower_bound(dp.begin(), dp.end(), nums[i]) = nums[i];
        }
        //for (int i = 0; i < n; ++i) cout << i << ' ' << dp[i] << endl;
        return lower_bound(dp.begin(), dp.end(), inf) - dp.begin();
    }
};
```

- $O(n^2)$ 做法

```go
// go
func lengthOfLIS(nums []int) int {
    dp := make([]int, len(nums))
    dp[0] = 1;
    ans := 1
    for i := 1; i < len(nums); i++ {
        dp[i] = 1
        for j := 0; j < i; j++ {
            if nums[j] < nums[i] {
                dp[i] = max(dp[i], dp[j] + 1)
            }
        }
        ans = max(ans, dp[i])
    }
    return ans
}

func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
```

### [415. 字符串相加](https://leetcode-cn.com/problems/add-strings/)

- 模拟

```cpp
// cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int result = x + y + add;
            ans += '0' + result % 10;
            add = result / 10;
            i -= 1;
            j -= 1;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

### [23. 合并 K 个升序链表](https://leetcode-cn.com/problems/merge-k-sorted-lists/) ✨

- 用优先队列来维护
- 动态开内存

```cpp
// cpp
struct node {
    ListNode *head;
    int val;
    node() {}
    node(ListNode* _head, int _val):
        head(_head), val(_val) {}
};
bool operator < (const node &a, const node &b) {
    return a.val > b.val;
}
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<node> pq;
        for (auto &i: lists) if (i) pq.push(node(i, i->val));
        ListNode *pre = new ListNode();
        ListNode *head = pre;
        while (!pq.empty()) {
            node temp = pq.top(); pq.pop();
            //cout << temp.val << pq.size() << ' ' << endl;
            head->next = new ListNode(temp.val);
            if (temp.head->next) pq.push(node(temp.head->next, temp.head->next->val));
            head = head->next;
        }
        return pre->next;
    }
};
```

## 8.28

### [2. 两数相加](https://leetcode-cn.com/problems/add-two-numbers)

- 模拟

```go
// go
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    up := 0
    head := &ListNode {
        Val: 0,
        Next: nil,
    }
    pre := head
    for l1 != nil || l2 != nil || up > 0 {
        temp := 0
        if l1 != nil {
            temp += l1.Val
            l1 = l1.Next
        }
        if l2 != nil {
            temp += l2.Val
            l2 = l2.Next
        }
        temp += up
        head.Next = &ListNode {
            Val: temp % 10,
            Next: nil,
        }
        up = temp / 10
        head = head.Next
    }
    return pre.Next
}
```

### [5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)✨

- 区间 $dp$
- 定义 $dp[i][j]$ 表示区间 $[i,\ j]$ 是否为回文串
- 第一层枚举区间长度，第二层枚举区间左端点
- $dp[i - 1][j + 1]$ 由 $dp[i][j]$ 转移过来
- 时间复杂度和空间复杂度 $O(n^2)$

```go
// go
func longestPalindrome(s string) string {
    n := len(s)
    dp := make([][]bool, n)
    for i := 0; i < n; i++ {
        dp[i] = make([]bool, n)
    }
    pos, ans := 0, 1
    for i := 0; i < n; i++ {
        dp[i][i] = true
        if i+1 < n && s[i+1] == s[i] && ans < 2 {
            dp[i][i+1] = true
            pos = i
            ans = 2
        }
    }
    for L := 0; L < n; L++ {
        for i := 0; i < n; i++ {
            if i-1 >= 0 && i+L+1 < n && s[i-1] == s[i+L+1] && dp[i][i+L] && L+3 > ans {
                dp[i-1][i+L+1] = true
                pos = i - 1
                ans = L + 3
            }
        }
    }
    return s[pos : pos+ans]
}
```

### [39. 组合总和](https://leetcode-cn.com/problems/combination-sum/) ✨

说几个 ```dfs``` 的细节

- 可重复选，所以选完当前这个，```idx``` 保持不变
- 可不选当前，所以 ```idx + 1``` 后进入下一层

```go
// go
func combinationSum(c []int, target int) (ans [][]int) {
    temp := []int{}
    var dfs func(idx, sum int)
    dfs = func(idx, sum int) {
        if idx == len(c) {
            return
        }
        if sum == 0 {
            ans = append(ans, append([]int{}, temp...))
            return
        }
        dfs(idx + 1, sum) // 直接跳过
        if sum - c[idx] >= 0 { // 选择当前
            temp = append(temp, c[idx])
            dfs(idx, sum - c[idx]) // 可重复选择
            temp = temp[:len(temp) - 1]
        }
    }
    dfs(0, target)
    return ans
}
```

## 8.29

### [41. 缺失的第一个正数](https://leetcode-cn.com/problems/first-missing-positive/)

- 哈希，复杂度为 $O(n)$

```go
// go
func firstMissingPositive(nums []int) int {
    mp := make(map[int]int)
    ans := 0
    for i := 0; i < len(nums); i++ {
        mp[nums[i]] = 1
    }
    for i := 1; mp[i] != 0; i++ {
        ans = i    
    }
    return ans + 1
}
```

### [46. 全排列](https://leetcode-cn.com/problems/permutations/)

- 排序后调用 ```next_permutation```

```cpp
// cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        bool flag = false;
        do {
            ans.push_back(nums);
            flag = next_permutation(nums.begin(), nums.end());
        } while(flag);
        return ans;
    }
};
```

### [56. 合并区间](https://leetcode-cn.com/problems/merge-intervals/)

- 按照左端点、右端点升序排序
- 按顺序逐个合并

```go
// go
type interval [][]int
func (I interval) Len() int {
    return len(I)
}
func (I interval) Less(i, j int) bool {
    if I[i][0] == I[j][0] {
        return I[i][1] < I[j][1]
    }
    return I[i][0] < I[j][0]
}
func (I interval) Swap(i, j int) {
    I[i], I[j] = I[j], I[i]
}
func merge(intervals [][]int) [][]int {
    sort.Sort(interval(intervals))
    ans := make([][]int, 0)
    l, r := intervals[0][0], intervals[0][1]
    for i := 1; i < len(intervals); i++ {
        if intervals[i][0] <= r {
            r = max(r, intervals[i][1])
        } else {
            ans = append(ans, []int{l, r})
            l, r = intervals[i][0], intervals[i][1]
        }
    }
    ans = append(ans, []int{l, r})
    return ans
}
func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
```

## 8.30

### [69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/)

- 二分答案，遇到可行解则保留答案，时间复杂度 $O(\log x)$

```go
// go
func mySqrt(x int) int {
    l, r := 0, x
    ans := 0
    for l <= r { // 二分答案
        mid := (l + r) / 2
        if mid * mid <= x { // 遇到了可行解
            ans = mid
            l = mid + 1
        } else {
            r = mid - 1;
        }
    }
    return ans
}
```

### [70. 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)

- 斐波那契，可以优化空间到 $O(1)$

```go
// go
func climbStairs(n int) int {
    dp := make([]int, n + 1)
    dp[0], dp[1] = 1, 1
    for i := 2; i <= n; i++ {
        dp[i] = dp[i - 1] + dp[i - 2]
    }
    return dp[n]
}
```

###

## 8.31

### [92. 反转链表 II](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

- 参考「k 个一组反转链表」
- 四个指针维护，子问题为反转链表

```cpp
// cpp
class Solution {
public:
    pair<ListNode*, ListNode*> solve(ListNode *L, ListNode *R) {
        ListNode *pre = new ListNode(0, L), *ed = R->next;
        ListNode *head = L, *tail = pre;
        while (head != ed) {
            ListNode *temp = head->next;
            head->next = pre;
            pre = head;
            head = temp;
        }
        return {pre, tail->next};
    }
    ListNode* reverseBetween(ListNode* head, int l, int r) {
        ListNode *dummy = new ListNode(0, head);
        ListNode *pre = dummy, *tail = dummy;
        ListNode *L = head, *R = head;
        int cnt = 0;
        while (head) {
            cnt++;
            if (cnt < l) {
                pre = head;
                L = head->next;
            }
            else if (cnt == r) {
                R = head;
                tail = head->next;
            }
            head = head->next;
        }
        pair<ListNode*, ListNode*> temp = solve(L, R);
        pre->next = temp.first;
        temp.second->next = tail;
        return dummy->next;
    }
};
```

### [94. 二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

- 中序遍历

```cpp
// cpp
class Solution {
public:
    vector<int> dfs_sec;
    void ldr(TreeNode *root) {
        if (!root) return;
        if (root->left) ldr(root->left);
        dfs_sec.push_back(root->val);
        if (root->right) ldr(root->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        ldr(root);
        return dfs_sec;
    }
};
```

### [98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/submissions/)

- 中序遍历得到中序数组，判断数组是否有序即可
  
```cpp
// cpp
class Solution {
public:
    vector<int> dfs_sec;
    void ldr(TreeNode *root) {
        if (!root) return;
        if (root->left) ldr(root->left);
        dfs_sec.push_back(root->val);
        if (root->right) ldr(root->right);
    }
    bool isValidBST(TreeNode* root) {
        ldr(root);
        for (int i = 1; i < dfs_sec.size(); ++i) {
            if (dfs_sec[i] <= dfs_sec[i - 1]) return false;
        }
        return true;
    }
};
```

## 9.1

### [101. 对称二叉树](https://leetcode-cn.com/problems/symmetric-tree/) ✨

- 左子树与右子树镜像对称，且左子树与右子树均为对称二叉树
- 维护两个指针 $p,\ q$，彼此向相反方向各移动一个单位，然后递归求解

```go
// go
func check(a, b *TreeNode) bool {
    if a == nil && b == nil  {
        return true
    }
    if a == nil || b == nil {
        return false
    }
    return check(a.Left, b.Right) && check(a.Right, b.Left) && a.Val == b.Val
}
func isSymmetric(root *TreeNode) bool {
    return check(root, root)    
}
```

### [112. 路径总和](https://leetcode-cn.com/problems/path-sum/)

- ```dfs```

```go
// go
func dfs(root *TreeNode, t, sum int) bool {
    if root == nil {
        return false
    }
    sum += root.Val
    if root.Left == nil && root.Right == nil && sum == t {
        return true
    }
    flag := dfs(root.Left, t, sum) || dfs(root.Right, t, sum)
    return flag
}
func hasPathSum(root *TreeNode, t int) bool {
    return dfs(root, t, 0)
}
```

### [113. 路径总和 II](https://leetcode-cn.com/problems/path-sum-ii/)

说几点 ```go``` 的语法

- ```defer``` 保证函数执行完之后一定会执行，不管这个函数是异常退出还是正常结束
- ```func```  是可以作为变量被传递的，定义在该函数之外的变量自然相对于其成为全局变量，可以被使用
- ```ans = append([]int{}, temp...)``` 是为了把一个 ```temp``` 的 ```copy``` 添加进 ```ans```，否则 ```temp``` 的改变会导致 ```ans``` 里的元素也改变

```go
// go
func pathSum(root *TreeNode, t int) (ans [][]int) {
    temp := []int{}
    var dfs func(root *TreeNode, sum int)
    dfs = func(root *TreeNode, sum int) {
        if root == nil {
            return
        }
        sum -= root.Val
        temp = append(temp, root.Val)
        defer func() { temp = temp[:len(temp)-1] }()
        if root.Left == nil && root.Right == nil && sum == 0 {
            ans = append(ans, append([]int{}, temp...))
        }
        dfs(root.Left, sum)
        dfs(root.Right, sum)
    }
    dfs(root, t)
    return ans
}
```

## 9.2

### [124. 二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

用树形 ```dp``` 的思想，考虑以节点 ```root``` 为根最大的路径和，有三种状态可以向上转移

- 左子树带上 ```root```
- 右子树带上 ```root```
- 只有 ```root```

维护答案的时候，还要计算左右子树带上 ```root``` 的情况，虽然这种状态无法向上转移

```go
// go
func maxPathSum(root *TreeNode) int {
    ans := -1001
    var dfs func(root *TreeNode) int
    dfs = func(root *TreeNode) int {
        if root == nil {
            return 0
        }
        Left := dfs(root.Left)
        Right := dfs(root.Right)
        temp := max(root.Val, max(Left, Right) + root.Val)
        ans = max(ans, max(temp, root.Val + Left + Right))
        return temp
    }
    ans = max(ans, dfs(root))
    return ans
}

func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
```

### [129. 求根节点到叶节点数字之和](https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/)

- ```dfs```

```go
// go
var ans int
func sumNumbers(root *TreeNode) int {
    pre := 0
    ans = 0
    dfs(root, pre)
    return ans
}

func dfs(root *TreeNode, val int) {
    if root == nil {
        return
    }
    val = val * 10 + root.Val
    if root.Left != nil {
        dfs(root.Left, val)
    }
    if root.Right != nil {
        dfs(root.Right, val)
    } 
    if root.Left == nil && root.Right == nil {
        ans += val
    }
    val = (val - root.Val) / 10
}
```

### [142. 环形链表 II](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

快指针步长为 $2$，慢指针为 $1$，设环之前的链长 $a$，快慢指针相遇处距离环口 $b$，剩下的环长 $c$

当快慢指针相遇时，设快指针走了 $x$ 圈，慢指针走了 $y$ 圈，考虑速度比，有 $a + x(b + c) + b = 2\cdot [a + y(b + c) + b]$

即 $a + b\equiv 0\mod (b + c)$，从而 $a\equiv c\mod (b + c)$

因此再设置一个指针从头走，一定可以与慢指针在环口相遇

```go
// go
func detectCycle(head *ListNode) *ListNode {
    a, b := head, head
    for b != nil {
        a = a.Next
        if b.Next == nil {
            return nil
        }
        b = b.Next.Next
        if a == b {
            c := head
            for a != c {
                a, c = a.Next, c.Next
            }
            return c
        }
    }
    return nil
}
```

## 9.3

### [143. 重排链表](https://leetcode-cn.com/problems/reorder-list/) ✨

- 用快慢指针找到链表中点
- 快指针步长为 $2$，慢指针步长为 $1$，这样可以确保快指针到达终点的时候慢指针到达了中点
- 反转后面一段链表
- 合并两个链表

```go
// go
func reorderList(head *ListNode)  {
    mid := getMid(head)
    b := mid.Next
    mid.Next = nil
    a := revert(b)
    merge(head, a)
}

// 快慢指针获取链表中点
func getMid(head *ListNode) *ListNode {
    a, b := head, head
    for b != nil {
        if b.Next == nil {
            break
        }
        b = b.Next.Next
        a = a.Next
    }
    return a
}

// 反转链表
func revert(head *ListNode) *ListNode {
    var pre *ListNode
    for head != nil {
        temp := head.Next
        head.Next = pre
        pre = head
        head = temp
    }
    return pre
}

// 合并链表
func merge(a, b *ListNode) {
    for a != nil && b != nil {
        c := a.Next
        d := b.Next
        a.Next, b.Next = b, c
        a, b = c, d
    }
}
```

### [155. 最小栈](https://leetcode-cn.com/problems/min-stack/)

- 借用辅助栈，辅助栈栈顶维护主栈中的最小值
- 这样便可以 $O(1)$ 调用主栈中的最小值

```cpp
// cpp
class MinStack {
public:
    stack<int> sta1, sta2;
    MinStack() {
    }
    
    void push(int val) {
        sta1.push(val);
        sta2.push(min(getMin(), val));
    }
    
    void pop() {
        if (!sta1.empty()) {
            sta1.pop();
            sta2.pop();
        }
    }
    
    int top() {
        return sta1.top();
    }
    
    int getMin() {
        if (!sta2.empty()) return sta2.top();
        else return 2147483647;
    }
};
```

### [232. 用栈实现队列](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

- 维护两个栈 $A,\ B$，其中 $A$ 维护输入序列，$B$ 维护输出序列
- 每当需要 ```pop, peek``` 的时候，将 $A$ 的元素全部 ```push``` 到 $B$ 中去
- 每个元素只入栈出栈各 $2$ 次，因此均摊复杂度为 $O(1)$

```cpp
// cpp
class MyQueue {
public:
    stack<int> sta1, sta2;
    MyQueue() {

    }
    void mv() {
        if (sta2.empty()) {
            while (!sta1.empty()) {
                sta2.push(sta1.top());
                sta1.pop();
            }
        }
    }
    void push(int x) {
        sta1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        mv();
        int ans = sta2.top(); sta2.pop();
        return ans;
    }
    
    /** Get the front element. */
    int peek() {
        mv();
        return sta2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return sta1.empty() && sta2.empty();
    }
};

```

## 9.4

### [剑指 Offer 22. 链表中倒数第k个节点](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)

```go
// go
func getKthFromEnd(head *ListNode, k int) *ListNode {
    n := 0
    temp := head
    for temp != nil {
        n++
        temp = temp.Next
    }
    temp = head
    x := n - k + 1
    n = 0
    var ans *ListNode
    for temp != nil {
        n++
        if n == x {
            ans = temp
            break
        }
        temp = temp.Next
    }
    return ans
}
```

## 9.7

### [51. N 皇后](https://leetcode-cn.com/problems/n-queens/)

- 回溯

```go
// go
func solveNQueens(n int) [][]string {
    ans := [][]string{}
    col := make(map[int]int)
    mp1 := make(map[int]int)
    mp2 := make(map[int]int)
    var dfs func(step, n int, temp []string)
    dfs = func(step, n int, temp []string) {
        if step == n {
            ans = append(ans, append([]string{}, temp...))
            return
        }
        row := make([]byte, n)
        for i := 0; i < n; i++ {
            row[i] = '.'
        }
        for i := 0; i < n; i++ {
            if (col[i] == 0 && mp1[i + step] == 0 && mp2[i - step] == 0) {
                col[i], mp1[i + step], mp2[i - step] = 1, 1, 1
                row[i] = 'Q'
                temp = append(temp, string(row))
                dfs(step + 1, n, temp)
                col[i], mp1[i + step], mp2[i - step] = 0, 0, 0
                row[i] = '.'
                temp = temp[:len(temp) - 1]
            }
        }
    }
    dfs(0, n, []string{})
    return ans
}
```

### [62. 不同路径](https://leetcode-cn.com/problems/unique-paths/)

- ```dp```

```go
// go
func uniquePaths(m int, n int) int {
    dp := make([][]int, m)
    for i := 0; i < m; i++ {
        dp[i] = make([]int, n)
    }
    dp[0][0] = 1
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            if i - 1 >= 0 {
                dp[i][j] += dp[i - 1][j]
            }
            if j - 1 >= 0 {
                dp[i][j] += dp[i][j - 1]
            }
        }
    }
    return dp[m - 1][n - 1]
}
```

### [剑指 Offer 09. 用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

- 参考上面一样的题目

```cpp
// cpp
class CQueue {
public:
    stack<int> s1, s2;
    CQueue() {
    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {
        if (s2.empty()) {
            while (!s1.empty()) s2.push(s1.top()), s1.pop();
        }
        if (s2.empty()) return -1;
        else {
            int x = s2.top(); s2.pop();
            return x;
        }
    }
};
```

## 9.8

### [64. 最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)

- 二维动态规划

```go
// go
func minPathSum(grid [][]int) int {
    m := len(grid)
    n := len(grid[0])
    dp := make([][]int, m)
    for i := 0; i < m; i++ {
        dp[i] = make([]int, n)
    }
    dp[0][0] = grid[0][0]
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            if i - 1 >= 0 {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j])
            }
            if j - 1 >= 0 {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j])
            }
        }
    }
    return dp[m - 1][n - 1]
}

func min(a, b int) int {
    if a < b {
        return a
    } else {
        return b
    }
}
```

### [72. 编辑距离](https://leetcode-cn.com/problems/edit-distance/) ✨

- 字符串下标从 $1$ 开始
- 定义 $dp[i][j]$ 表示 $w_1,\ w_2$ 前 $i,\ j$ 个位置，即 ```w1[1:i], w2[1:i]``` 的距离，从而进行转移

```cpp
#define inf 0x3f3f3f3f
class Solution {
public:
    int minDistance(string w1, string w2) {
        if (w1 == "" && w2 == "") return 0;
        else if (w1 == "") return w2.length();
        else if (w2 == "") return w1.length();
        int m = w1.length(), n = w2.length();
        int dp[m + 1][n + 1];
        memset(dp, inf, sizeof(dp));
        for (int i = 0; i <= m; ++i) dp[i][0] = i;
        for (int j = 0; j <= n; ++j) dp[0][j] = j;
        dp[1][1] = (w1[0] != w2[0]);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = min(dp[i - 1][j - 1] + (w1[i - 1] != w2[j - 1]), min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
            }
        }
        return dp[m][n];
    }
};
```

### [78. 子集](https://leetcode-cn.com/problems/subsets/)

- 二进制枚举

```cpp
// cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int N = 1 << n;
        vector<vector<int>> ans;
        for (int i = 0; i < N; ++i) {
            vector<int> temp;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) temp.push_back(nums[j]);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};
```

```go
// go
func subsets(nums []int) [][]int {
    n := len(nums)
    N := 1 << n
    ans := [][]int{}
    for i := 0; i < N; i++ {
        temp := []int{}
        for j := 0; j < n; j++ {
            if ((i >> j) & 1) == 1 {
                temp = append(temp, nums[j])
            }
        }
        ans = append(ans, temp)
    }
    return ans
}
```

## 9.9

### [79. 单词搜索](https://leetcode-cn.com/problems/word-search/)

- ```dfs```

```go
// go
func exist(board [][]byte, word string) bool {
    DX := []int{1, 0, -1, 0}
    DY := []int{0, -1, 0, 1}
    m, n := len(board), len(board[0])
    vis := make([][]bool, m)
    for i := 0; i < m; i++ {
        vis[i] = make([]bool, n)
    }
    var dfs func(x, y, step int) bool
    dfs = func(x, y, step int) bool {
        if word[step] != board[x][y] {
            return false
        }
        if step == len(word) - 1 {
            return true
        }
        for i := 0; i < 4; i++ {
            tx, ty := x + DX[i], y + DY[i]
            if tx >= 0 && tx < m && ty >= 0 && ty < n && !vis[tx][ty] {
                vis[tx][ty] = true
                if dfs(tx, ty, step + 1) {
                    return true
                }
                vis[tx][ty] = false
            }
        }
        return false
    }
    for i := 0; i < m; i++ {
        for j := 0; j < n; j++ {
            vis[i][j] = true
            if dfs(i, j, 0) {
                return true
            }
            vis[i][j] = false
        }
    }
    return false
}
```

### [83. 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

- 设置一个 ```dummy```
- 维护两个指针，分别指向前一个元素和当前元素
- 若当前元素和前一个元素相同，则删掉当前元素

```go
// go
func deleteDuplicates(head *ListNode) *ListNode {
    pre := &ListNode {
        Val: -101,
        Next: head,
    }
    prev := pre
    for head != nil {
        if head.Val == prev.Val {
            prev.Next = head.Next
        } else {
            prev = prev.Next
        }
        head = head.Next
    }
    return pre.Next
}
```

### [82. 删除排序链表中的重复元素 II](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)

- 设置两个 ```dummy```
- 维护三个指针

```go
// go
func deleteDuplicates(head *ListNode) *ListNode {
    b := &ListNode {
        Val: -101,
        Next: head,
    }
    a := &ListNode {
        Val: -102,
        Next: b,
    }
    p1, p2 := a, b
    for head != nil {
        if head.Val == p2.Val {
            for head != nil && head.Val == p2.Val {
                p2.Next = head.Next
                head = head.Next
            }
            p1.Next = head
            p2 = head
            if head == nil {
                break
            }
            head = head.Next
        } else {
            p1 = p1.Next
            p2 = p2.Next
            head = head.Next
        }
    }
    return b.Next
}
```

## 9.10

### [104. 二叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

- ```dfs```

```go
// go
func maxDepth(root *TreeNode) int {
    var dfs func(root *TreeNode) int
    dfs = func(root *TreeNode) int {
        if root == nil {
            return 0
        }
        return 1 + max(dfs(root.Left), dfs(root.Right))
    }
    return dfs(root)
}
func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
```

### [110. 平衡二叉树](https://leetcode-cn.com/problems/balanced-binary-tree/)

- 记录一下左右子树的高度差即可
- 如果要判断是不是 ```BBST```，需要记录 ```dfs``` 序，然后判断是否有序

```go
// go
func isBalanced(root *TreeNode) bool {
    var dfs func(root *TreeNode) (int, bool)
    dfs = func(root *TreeNode) (int, bool) {
        if root == nil {
            return 0, true
        }
        h1, f1 := dfs(root.Left)
        h2, f2 := dfs(root.Right)
        if f1 && f2 && abs(h1 - h2) <= 1 {
            return max(h1, h2) + 1, true
        }
        return max(h1, h2) + 1, false
    }
    _, f := dfs(root)
    return f
}

func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}

func abs(a int) int {
    if a < 0 {
        return -a
    } else {
        return a
    }
}
```

## 9.11

### [114. 二叉树展开为链表](https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/) ✨

- 考虑递归
- 将左子树展开成链表，挂在根的右节点上
- 再把右子树展开成链表，挂在左子树的末尾的右节点上

```go
// go
func flatten(root *TreeNode)  {
    var dfs func(root *TreeNode)
    dfs = func(root *TreeNode) {
        if root == nil {
            return
        }
        dfs(root.Left)
        dfs(root.Right)
        temp := root.Right
        root.Left, root.Right = nil, root.Left
        cur := root
        for cur.Right != nil {
            cur = cur.Right
        }
        cur.Right = temp
    }
    dfs(root)
}
```

### [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

- 线性 ```dp```，每一天的状态只和前一天有关

```cpp
// cpp
class Solution {
public:
    int maxProfit(vector<int>& p) {
        int n = p.size();
        int dp[n + 1][2];
        dp[0][0] = 0, dp[0][1] = -p[0];
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i - 1][1] + p[i], dp[i - 1][0]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p[i]);
        }
        return dp[n - 1][0];
    }
};

```

### [139. 单词拆分](https://leetcode-cn.com/problems/word-break/)

- 定义 $dp[i]$ 表示前 $i$ 个字符组成的字符串能否由字典拼凑而成
- 枚举 $j$，判断 $j..i$ 是否在字典里即可

```go
// go
func wordBreak(s string, wordDict []string) bool {
    dp := make([]bool, len(s) + 1)
    mp := make(map[string]bool)
    for _, v := range(wordDict) {
        mp[v] = true
    }
    dp[0] = true
    for i := 1; i <= len(s); i++ {
        for j := 0; j < i; j++ {
            if dp[j] && mp[s[j:i]] {
                dp[i] = true
            }
        }
    }
    return dp[len(s)]
}
```

## 9.12

### [144. 二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)

- 前序遍历

```go
// go
func preorderTraversal(root *TreeNode) []int {
    ans := []int{}
    var dfs func(root *TreeNode)
    dfs = func(root *TreeNode) {
        if root == nil {
            return
        }
        ans = append(ans, root.Val)
        dfs(root.Left)
        dfs(root.Right)
    }
    dfs(root)
    return ans
}
```

### [148. 排序链表](https://leetcode-cn.com/problems/sort-list/)

- 用 ```multiset``` 维护

```go
// go
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        multiset<int> st;
        while (head) st.insert(head->val), head = head->next;
        ListNode *pre = new ListNode(0);
        ListNode *cur = pre;
        for (auto &i: st) cur->next = new ListNode(i), cur = cur->next;
        return pre->next;
    }
};
```

## 9.14

### [198. 打家劫舍](https://leetcode-cn.com/problems/house-robber/)

- 动态规划，当前状态与前一天和大前天的状态有关

```go
// go
func rob(nums []int) int {
    dp := make([]int, len(nums))
    dp[0] = nums[0]
    for i := 1; i < len(nums); i++ {
        if i == 1 {
            dp[i] = max(dp[i - 1], nums[i]);
        } else {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
    }
    return dp[len(nums) - 1];
}

func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}
```

### [209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/) ✨

- 滑动窗口 $O(n)$ 算法

```cpp
// cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& a) {
        int l = 0, r = 0, n = a.size(), ans = INT_MAX, sum = 0;
        while (r < n) {
            sum += a[r];
            while (l <= r && sum >= target) {
                ans = min(ans, r - l + 1);
                sum -= a[l++];
            }
            r++;
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
```

- 维护前缀和，在前缀和上二分
- 对于当前位置 $i$，找到第一个大于等于 ```s[i - 1] + target``` 的位置，维护答案

```cpp
// cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& a) {
        int n = a.size(), ans = INT_MAX, sum = 0;
        int s[n + 1];
        for (int i = 1; i <= n; ++i)
            s[i] = s[i - 1] + a[i - 1];
        for (int i = 1; i <= n; ++i) {
            int temp = s[i - 1] + target;
            int r = lower_bound(s + i, s + 1 + n, temp) - s;
            if (r <= n) ans = min(ans, r - i + 1);
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
```

### [221. 最大正方形](https://leetcode-cn.com/problems/maximal-square/) ✨

- 定义 ```dp[i][j]``` 表示以 ```(i, j)``` 为右下角的全 ```1``` 正方形的最大边长
- 考虑由 ```dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]``` 转移而来
- 画图有助于理解

```cpp
// cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& a) {
        int m = a.size(), n = a[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j] == '0') dp[i][j] = 0;
                else {
                    if (i >= 1 && j >= 1) {
                        dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    }
                    else dp[i][j] = 1;
                }
                ans = max(ans, dp[i][j]);
            }
        }
        return ans * ans;
    }
};
```

## 9.15

### [226. 翻转二叉树](https://leetcode-cn.com/problems/invert-binary-tree/)

- 优雅的递归
- 这道题据传被谷歌拿去考 ```homebrew``` 的作者，结果后者没写出来

```go
// go
func invertTree(root *TreeNode) *TreeNode {
    if root == nil {
        return nil
    }
    root.Left, root.Right = root.Right, root.Left
    invertTree(root.Left)
    invertTree(root.Right)
    return root
}
```

### [230. 二叉搜索树中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/)

- 获取 ```dfs``` 序之后返回下标为 ```k - 1``` 的值

```go
// go
func kthSmallest(root *TreeNode, k int) int {
    dfs_sec := []int{}
    var dfs func(root *TreeNode)
    dfs = func(root *TreeNode) {
        if root == nil {
            return
        }
        dfs(root.Left)
        dfs_sec = append(dfs_sec, root.Val)
        dfs(root.Right)
    }
    dfs(root)
    return dfs_sec[k - 1]
}
```

## 9.16

### [234. 回文链表](https://leetcode-cn.com/problems/palindrome-linked-list/)

- 先找到 ```mid```，然后反转后一半链表
- 比较两段链表的值是否一致

```go
// go
func isPalindrome(head *ListNode) bool {
    mid := findMid(head)
    newHead := reverse(mid)
    for newHead != nil {
        if head.Val != newHead.Val {
            return false
        }
        head = head.Next
        newHead = newHead.Next
    }
    return true
}

func findMid(head *ListNode) *ListNode {
    i, j := head, head
    for j != nil {
        if j.Next == nil {
            break
        }
        j = j.Next.Next
        i = i.Next
    }
    return i    
}

func reverse(head *ListNode) *ListNode{
    var pre *ListNode
    cur := head
    for cur != nil {
        temp := cur.Next
        cur.Next = pre
        pre, cur = cur, temp
    }
    return pre
}
```

### [239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/) ✨

- 为了寻找滑动窗口最大值，需要维护一个**单调递减**的队列，队列里面维护值的下标
- 出队有两种情况，比当前元素小，下标过期
- 可以理解为，实力不如当前选手的人得退役，年纪大了的人得退役
- 时间复杂度 $O(n)$

```cpp
// cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;
        for (int i = 0; i < nums.size(); ++i) {
            while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
            dq.push_back(i);
            while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
            if (i >= k - 1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};
```

### [240. 搜索二维矩阵 II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)

- 从左下角开始找
- 如果当前值小于目标值，向上寻找
- 如果当前值大于目标值，向右寻找
- 二维矩阵的有序性保证，如果存在，一定可以找到，时间复杂度 $O(n + m)$

```cpp
// cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = m - 1, y = 0, cnt = 0;
        while (cnt < m * n) {
            if (!(x >= 0 && x < m && y >= 0 && y < n)) break;
            ++cnt;
            int temp = matrix[x][y];
            if (temp == target) return 1;
            else if (temp < target) y++;
            else x--;
        }
        return 0;
    }
};
```

## 9.17

### [264. 丑数 II](https://leetcode-cn.com/problems/ugly-number-ii/) ✨

- 定义 $dp[i]$ 表示第 $i$ 个丑数（只包含质因子 ```2, 3, 5```）
- 定义三个指针 ```p2, p3, p5``` 进行三路归并排序
- 当前状态 ```dp[i]``` 由之前的状态 ```dp[p2] * 2, dp[p3] * 3, dp[p5] * 5``` 转移而来

```txt
1 * 2, 2 * 2, 3 * 2, 4 * 2, 5 * 2...

1 * 3, 2 * 3, 3 * 3, 4 * 3, 5 * 3...

1 * 5, 2 * 5, 3 * 5, 4 * 5, 5 * 5...

三路归并
```

```cpp
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n + 1);
        int p2 = 1, p3 = 1, p5 = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = min(min(dp[p2] * 2, dp[p3] * 3), dp[p5] * 5);
            if (dp[i] == dp[p2] * 2) p2++;
            if (dp[i] == dp[p3] * 3) p3++;
            if (dp[i] == dp[p5] * 5) p5++;
        }
        return dp[n];
    }
};
```

### [322. 零钱兑换](https://leetcode-cn.com/problems/coin-change/)

- 动态规划

```cpp
// cpp
#define inf 0x3f3f3f3f
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, inf);
        dp[0] = 0;
        for (int i = 0; i <= amount; ++i) {
            for (auto &j: coins) {
                if (i - j >= 0) dp[i] = min(dp[i], dp[i - j] + 1);
            }
        }
        return dp[amount] == inf ? -1 : dp[amount];
    }
};
```

### [394. 字符串解码](https://leetcode-cn.com/problems/decode-string/)

- 用栈模拟

```cpp
// cpp
class Solution {
public:
    pair<string, int> readSta(stack<char> &sta) {
        string temp, num;
        bool flag = false;
        while (!sta.empty()) {
            char x = sta.top();
            if (flag && !isdigit(x)) break;
            else {
                if (isalpha(x)) temp += x;
                else if (x == '[') {sta.pop(); continue;}
                else if (isdigit(x)) flag = true, num += x;
                sta.pop();
            }
        }
        reverse(temp.begin(), temp.end());
        reverse(num.begin(), num.end());
        int val = atoi(num.c_str());
        return pair<string, int>{temp, val};
    }
    void pushIntoSta(string s, int val, stack<char> &sta) {
        for (int i = 1; i <= val; ++i)
            for (auto &j: s) sta.push(j);
    }
    string sta2string(stack<char> &sta) {
        string ans;
        while (!sta.empty()) ans += sta.top(), sta.pop();
        reverse(ans.begin(), ans.end());
        return ans;
    }
    string decodeString(string s) {
        stack<char> sta;
        for (auto &i: s) {
            if (i == ']') {
                auto x = readSta(sta);
                pushIntoSta(x.first, x.second, sta);
            }
            else sta.push(i);
        }
        return sta2string(sta);
    }
};
```