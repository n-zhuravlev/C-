#include "tree.h"
#include "metaclasses.h"


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::BinarySearchTree(const BinarySearchTree &tree)
{
    if (!tree.head) {
        head = nullptr;
        return;
    }

    enum {
        RIGHT_SUB_TREE,
        LEFT_SUB_TREE,
        PARENT
    } from = PARENT;

    const NodePtrType ptr = tree.head;
    head = new NodeType(*ptr);

    while (ptr->parent || from) {

        switch (from) {

            case RIGHT_SUB_TREE:

                from = (ptr == ptr->parent->left) ? LEFT_SUB_TREE : RIGHT_SUB_TREE;
                ptr = ptr->parent;
                head = head->parent;
                break;

            case LEFT_SUB_TREE:

                if (ptr->right) {
                    from = PARENT;
                    ptr = ptr->right;
                    head = head->right = new NodeType(*ptr, head);
                }
                else from = RIGHT_SUB_TREE;
                break;

            case PARENT:

                if (ptr->left) {
                    from = PARENT;
                    ptr = ptr->left;
                    head = head->left = new NodeType(*ptr, head);
                }
                else from = LEFT_SUB_TREE;
                break;
        }
    }
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::~BinarySearchTree()
{
    if (head) {

        while (true) {

            if (head->left)
                head = head->left;

            else if (head->right)
                head = head->right;

            else if (head->parent) {

                head = head->parent;

                if (head->left) {
                    delete head->left;
                    head->left = nullptr;
                }
                else {
                    delete head->right;
                    head->right = nullptr;
                }
            }
            else break;
        }

        delete head;
    }
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::TreeType &BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::operator=(const TreeType &tree)
{
    if (this != &tree) {

        // delete current tree nodes (see destructor) if needed
        if (head) {

            while (true) {

                if (head->left)
                    head = head->left;

                else if (head->right)
                    head = head->right;

                else if (head->parent) {

                    head = head->parent;

                    if (head->left) {
                        delete head->left;
                        head->left = nullptr;
                    }
                    else {
                        delete head->right;
                        head->right = nullptr;
                    }
                }
                else break;
            }

            delete head;
            head = nullptr;
        }

        // copy new nodes if needed
        if (tree.head) {

            enum {
                RIGHT_SUB_TREE,
                LEFT_SUB_TREE,
                PARENT
            } from = PARENT;

            const NodePtrType ptr = tree.head;
            head = new NodeType(*ptr);

            while (ptr->parent || from) {

                switch (from) {

                    case RIGHT_SUB_TREE:

                        from = (ptr == ptr->parent->left) ? LEFT_SUB_TREE : RIGHT_SUB_TREE;
                        ptr = ptr->parent;
                        head = head->parent;
                        break;

                    case LEFT_SUB_TREE:

                        if (ptr->right) {
                            from = PARENT;
                            ptr = ptr->right;
                            head = head->right = new NodeType(*ptr, head);
                        }
                        else from = RIGHT_SUB_TREE;
                        break;

                    case PARENT:

                        if (ptr->left) {
                            from = PARENT;
                            ptr = ptr->left;
                            head = head->left = new NodeType(*ptr, head);
                        }
                        else from = LEFT_SUB_TREE;
                        break;
                }
            }
        }
    }

    return *this;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
inline const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::head_key() const
{
    return head;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::min_key() const
{
    if (!head)
        return nullptr;

    const NodePtrType ptr = head;

    while (ptr->left)
        ptr = ptr->left;

    return ptr;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::max_key() const
{
    if (!head)
        return nullptr;

    const NodePtrType ptr = head;

    while (ptr->right)
        ptr = ptr->right;

    return ptr;
}


// KeyType has overloaded operator< and operator!=
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_lt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type &key) const
{
    const NodePtrType ptr = head;

    while (ptr && (key != ptr->key))
        ptr = (key < ptr->key) ? ptr->left : ptr->right;

    return ptr;
}


// KeyType has overloaded operator< and operator==
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_lt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type &key) const
{
    const NodePtrType ptr = head;

    while (ptr && (!(key == ptr->key)))
        ptr = (key < ptr->key) ? ptr->left : ptr->right;

    return ptr;
}


// KeyType has overloaded operator> and operator!=
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_gt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type &key) const
{
    const NodePtrType ptr = head;

    while (ptr && (key != ptr->key))
        ptr = (key > ptr->key) ? ptr->right : ptr->left;

    return ptr;
}


// KeyType has overloaded operator> and operator==
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_gt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type &key) const
{
    const NodePtrType ptr = head;

    while (ptr && (!(key == ptr->key)))
        ptr = (key > ptr->key) ? ptr->right : ptr->left;

    return ptr;
}


// KeyType has overloaded operator< and operator!=
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_lt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type *key) const
{
    const NodePtrType ptr = head;

    while (ptr && (*key != ptr->key))
        ptr = (*key < ptr->key) ? ptr->left : ptr->right;

    return ptr;
}


// KeyType has overloaded operator< and operator==
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_lt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type *key) const
{
    const NodePtrType ptr = head;

    while (ptr && (!(*key == ptr->key)))
        ptr = (*key < ptr->key) ? ptr->left : ptr->right;

    return ptr;
}


// KeyType has overloaded operator> and operator!=
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_gt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type *key) const
{
    const NodePtrType ptr = head;

    while (ptr && (*key != ptr->key))
        ptr = (*key > ptr->key) ? ptr->right : ptr->left;

    return ptr;
}


// KeyType has overloaded operator> and operator==
template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const typename std::enable_if<(has_gt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type *key) const
{
    const NodePtrType ptr = head;

    while (ptr && (!(*key == ptr->key)))
        ptr = (*key > ptr->key) ? ptr->right : ptr->left;

    return ptr;
}
