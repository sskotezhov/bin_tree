#include "tree.hpp"
template<class K, class V>
typename SearchingTree<K, V>::Node* SearchingTree<K, V>::Iterator::next()
{
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

template<class K, class V>
bool SearchingTree<K, V>::Iterator::hasNext() { return current != nullptr; }
template<class K, class V>
SearchingTree<K, V>::Iterator::Iterator(typename SearchingTree<K, V>::Node* head)
{
    current = head;
    rightMost = nullptr;
    value = next();
}
template<class K, class V>
typename SearchingTree<K, V>::Iterator& SearchingTree<K, V>::Iterator::operator++()
{
    value = next(); 
    return *this; 
} 
template<class K, class V>
typename SearchingTree<K, V>::Iterator SearchingTree<K, V>::begin()
{
    Iterator iter(&root);
    iter.next();
    return iter;
}
template<class K, class V>
typename SearchingTree<K, V>::Iterator SearchingTree<K, V>::end()
{
    Iterator iter(nullptr);
    return iter;
}
template<class K, class V>
typename SearchingTree<K, V>::Iterator SearchingTree<K, V>::find(const K &key)
{
    Iterator i(&root);
    while (i->key != key && i.hasNext())
    {
        ++i;
    }
    return i;
}
template<class K, class V>
SearchingTree<K, V>::SearchingTree(const K &key,const V &value)
{
    root.key = key;
    root.value = value;
}
template<class K, class V>
void SearchingTree<K,V>::insert(const K &key, const V &value)
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
template<class K, class V>
void SearchingTree<K, V>::erase(const K &key)
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