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

        Iterator(Node *head)
        {
            current = head;
            rightMost = nullptr;
            value = next();
        }
        bool hasNext() { return current != nullptr; }
        
        pointer next() {
            if (!hasNext()) {
                return nullptr;
            }
        
            if (current->left == nullptr) 
            {
                pointer temp = current;
                current = current->right;
                return temp;
            }
        
            rightMost = current->left;
        
            while (rightMost->right != nullptr
                && rightMost->right != current) 
            {
                rightMost = rightMost->right;
            }
        
            if (rightMost->right == nullptr) {
                rightMost->right = current;
                current = current->left;
            } else {
                rightMost->right = nullptr;
                pointer temp = current;
                current = current->right;
                return temp;
            }
        
            return next();
        }
        reference operator*() const { return *value; }
        pointer operator->() { return value; }

        Iterator& operator++()
        { 
            value = next(); 
            return *this; 
        }  


        friend bool operator== (const Iterator& a, const Iterator& b) { return a.value == b.value; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.value != b.value; };  


        private:
            pointer current, rightMost, value;
    };
    Iterator begin() 
    {
        Iterator iter(&root);
        iter.next();
        return iter;
    }
    Iterator end() 
    {
        Iterator iter(nullptr);
        return iter; 
    } 
    SearchingTree(const K &key,const V &value)
    {
        root.key = key;
        root.value = value;
    }
    Node *head()
    {
        return &root;
    }
    void insert(const K &key, const V &value)
    {
        Node *current = &root;
        while (current->key != key)
        {
            if (current->key < key)
            {
                if (current->right == nullptr)
                {
                    current->right = new Node;
                    current->right->key = key;
                    current->right->value = value;
                    return;
                }
                else
                {
                    current = current->right;
                }
            }
            else
            {
                if (current->left == nullptr)
                {
                    current->left = new Node;
                    current->left->key = key;
                    current->left->value = value;
                    return;
                }
                else
                {
                    current = current->left;
                }
            }
        }
        return;
    }
    void erase(const K &key)
        {
        Node *current = &root;
        while ((current->left == nullptr || current->left != nullptr && current->left->key != key )&& (current->right == nullptr || current->right != nullptr && current->right->key !=key))
        {
            if (current->key < key)
            {
                if (current->right == nullptr)
                {
                    return;
                }
                else
                {
                    current = current->right;
                }
            }
            else
            {
                if (current->left == nullptr)
                {
                    return;
                }
                else
                {
                    current = current->left;
                }
            }
        }
        Node **del_node;
        if (current->left != nullptr && current->left->key == key)
        {
            del_node = &current->left;
        }
        else
        {
            del_node = &current->right;
        }
        Node *tmp = *del_node, *min;
        Node **path_to_min = &((*del_node)->right);
        if (*path_to_min == nullptr)
        {
            *del_node = tmp->left;
        }
        else
        {
            while ((*path_to_min)->left !=nullptr)
            {
                path_to_min = &((*path_to_min)->left);
            }
            min = *path_to_min;
            *path_to_min = min->right;
            min->right = (*del_node)->right;
            min->left = (*del_node)->left;
            *del_node = min;
        }
        delete tmp;
        return;
    }
    Iterator find(const K &key)
    {
        Iterator i(&root);
        while (i->key != key && i.hasNext())
        {
            ++i;
        }
        return i;
    }
private:
    Node root;

};
