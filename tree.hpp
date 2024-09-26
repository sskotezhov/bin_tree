#include <iostream>
#include <iterator> 
#include <cstddef> 
template<class K, class V>  
class SearchingTree {  
public:
    struct Node
    {
        K key;
        V value;
        Node *right = nullptr;
        Node *left = nullptr;
    };
    class Iterator
    {
        public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Node;
        using pointer           = Node*;
        using reference         = Node&;

        Iterator(Node *head);
        bool hasNext();
        
        pointer next();
        reference operator*() const { return *value; }
        pointer operator->() { return value; }

        Iterator& operator++();

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.value == b.value; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.value != b.value; };  


        private:
            pointer current, rightMost, value;
    };
    Iterator begin();
    Iterator end();
    SearchingTree(const K &key,const V &value);
    Node *head() { return &root; }
    void insert(const K &key, const V &value);
    void erase(const K &key);
    Iterator find(const K &key);
private:
    Node root;

};