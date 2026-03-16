#include <iostream>
#include <vector>


using namespace std;

class ST {
    public:
    vector<int> st;
    int n; 

    ST(vector<int>& array) {
        n = array.size();
        st.resize(4*n);
        build(array, 0, n - 1, 1);
    }

    void build(vector<int>& array, int left, int right, int node) {
        if(left == right) {
            st[node] = array[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(array, left, mid, 2*node);
        build(array, mid + 1, right, 2*node + 1);
        st[node] = st[2*node] + st[2*node + 1];

    }

    void update(int node, int left, int right, int index, int val) {
        if(left == right) {
            st[node] = val;
            return;
        }

        int mid = left + (right - left) / 2;


        if(index <= mid) update(2*node, left, mid, index, val);
        else update(2*node +1, mid + 1, right, index, val);
        st[node] = st[2*node] + st[2*node+1];        
    }

    int query(int node, int start, int end, int q_left, int q_right) {
        if(q_right < start || q_left > end) return 0;
        if(q_left <= start && q_right >= end) return st[node];
        int mid = start + (end - start) / 2;
        return query(2*node, start, mid, q_left, q_right) +
            query(2*node + 1, mid + 1, end, q_left, q_right);
    }
    void update(int index, int val) {update(1, 0, n - 1, index, val);}
    int query(int left, int right) {return query(1, 0, n - 1, left, right);}

};
int main() {
    std::vector<int> data = {2, 2, 5, 7, 9, 11};
    ST st(data);

    std::cout << "Sum [1, 3]: " << st.query(1, 3) << std::endl; // 3+5+7 = 15
    st.update(2, 10); // Change 5 to 10
    std::cout << "New Sum [1, 3]: " << st.query(1, 3) << std::endl; // 3+10+7 = 20
}
