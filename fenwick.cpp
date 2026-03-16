#include <iostream>
#include <vector>

using namespace std;


class BIT {
public:
    vector<int> tree;

    BIT(int n) {
        tree.resize(n);
    }

    void update(int i, int val) {
        for(; i < tree.size(); i += i & -i)
            tree[i] += val;
    }

    int query(int i) {
        int sum = 0;
        for(; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int queryRange(int left, int right) {
        return query(right) - query(left - 1);
    }
};

int main() {
    std::vector<int> data = {1, 3, 5, 7, 9, 11};
    BIT ft(data.size());

    // Build the tree
    for (int i = 0; i < data.size(); i++) {
        ft.update(i + 1, data[i]);
    }

    std::cout << "Sum of first 3 elements: " << ft.query(3) << std::endl; // 1+3+5 = 9
    std::cout << "Sum of range [2, 5]: " << ft.queryRange(2, 5) << std::endl; // 3+5+7+9 = 24

    // Real-time update: Change element at index 3 (value 5) by adding 2
    ft.update(3, 2); 
    std::cout << "New sum of first 3 elements: " << ft.query(3) << std::endl; // 9 + 2 = 11

    return 0;
}
