namespace stlcontainer 
{

template <typename T> class ForwardList;
template <typename T> class ForwardListIterator;

template<typename NodeType>
class ForwardListNode
{
// Friend declarations
friend class ForwardListIterator<NodeType>;
friend class ForwardList<NodeType>;

// Type definitions
public:
    using value_type = NodeType;
    using reference = value_type&;
    using const_reference = const reference;

private:
    value_type _value;
    stlcontainer::ForwardListNode<NodeType>* _next;

    // Constructor and destructor
    ForwardListNode(const_reference value = value_type{}, stlcontainer::ForwardListNode<NodeType>* next = nullptr): _value(value), _next(next) {};
    ~ForwardListNode() = default;
};

} // namespace stlcontainer