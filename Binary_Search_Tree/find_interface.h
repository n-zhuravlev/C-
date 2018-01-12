template<typename NodePtr, typename Key, typename Enable = void>
class FindInterface;


// FindInterface specialization in which Key template parameter has operator < and operator ==
template<typename NodePtr, typename Key>
class FindInterface<NodePtr, Key, typename std::enable_if<has_lt_eq<Key>::value>::type> {
protected:

	NodePtr head;

public:

	explicit const NodePtr find(const Key &key) const;
};