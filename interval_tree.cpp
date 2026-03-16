#include <iostream>
#include <utility>
#include <vector> 

using namespace std;

class Node {
public:
    pair<int, int> interval;
    int max_value;
    Node *left, *right;

    Node(pair<int, int> i, int m) : interval(i), max_value(m), left(nullptr), right(nullptr) {}
};

class IntervalTree {
private: 
    Node *root = nullptr;

    // insert
    /**
     * root == null -> create node as root; 
     */
    Node* insert(Node *root, pair<int, int> interval) {
        if(root == nullptr)
            return new Node(interval, interval.second);
        
        if(root->interval.first > interval.first) 
            root->left = insert(root->left, interval);
        else 
            root->right = insert(root->right, interval);
        
        root->max_value = max(root->max_value, interval.second);

        return root; // new node
    }

    // searchOverlaps
    pair<int, int> searchOverlap(Node* root, pair<int, int> interval) {
        if(root == nullptr)
            return pair<int, int>();
        
        if(root->interval.first <= interval.second && interval.first <= root->interval.second)
            return root->interval;
        
        if(root->left != nullptr && root->left->max_value >= interval.first)
            return searchOverlap(root->left, interval);
        
        return searchOverlap(root->right, interval);
    }

    void searchOverlap(Node* root, pair<int, int> interval, vector<pair<int, int>>& result) {
        if(root == nullptr)
            return ;
        
        if(root->interval.first <= interval.second && interval.first <= root->interval.second)
            result.push_back(root->interval);
        
        if(root->left != nullptr && root->left->max_value >= interval.first)
            searchOverlap(root->left, interval, result);
        if(root->right != nullptr && root->interval.first <= interval.second)
            searchOverlap(root->right, interval, result);
    }

    void inorder(Node* root) {
        if(root == nullptr)
            return;
        inorder(root->left);
        cout << root->interval.first << " " << root->interval.second << endl;
        inorder(root->right);
         
    }
public:
    void insert(pair<int, int> interval) {
        root = insert(root, interval);
    }
    
    pair<int, int> searchOverlap(pair<int, int> interval) {
        return searchOverlap(root, interval);
    }

    vector<pair<int, int>> searchOverlaps(pair<int, int> interval) {
        vector<pair<int, int>> result;
        searchOverlap(root, interval, result);
        return result;
    }
    void inorder() {
        inorder(root);
    }
    
};

int main() {

    IntervalTree i;
    i.insert({10, 20});
    // cout << "first";
    i.insert({20, 30});
    i.insert({25, 35});
    i.insert({27, 40});
    i.insert({5, 8});
    i.insert({6, 9});


    vector<pair<int, int>> results = i.searchOverlaps({24, 29});
    for(auto result: results)
        cout << result.first << " " << result.second << endl;

    cout << endl;
    i.inorder();
    return 0;
}