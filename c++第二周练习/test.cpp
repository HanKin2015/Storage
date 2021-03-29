template<class T>
class list {
public
:
    struct Node {      // list cell
        T data;
        Node *next, *prev;
        Node(T s = 0, Node* n = NULL,
             Node* p = NULL) : data(s), next(n), prev(p) {
        };  // suggest u to use the constructor
    };
    class iterator {
    public
    :
        friend class list;  // suggest u to use friend class
        explicit iterator(Node* p = 0) {
            current = p;
        }
        iterator(const iterator& other) {
            current = other.current;
        }
        iterator& operator++() {
            current = current->next;
            return *this;
        }
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        Node* operator->() {
            return current;
        }
        T& operator*() {
            return current->data;
        }
        bool operator==(const iterator & rhs) const
        { return current == rhs.current; }
        bool operator!=(const iterator & rhs) const
        { return !( *this == rhs ); }
        // u can use iterator as Node* sometimes
        operator Node * () {return current;}  // conversion;
    private
    :
        Node* current;  // current listelem or 0;
    };
private
:
    Node *head, *tail;  // head and tail
    int _size;
    void init() {
        _size = 0;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
public
:
    list() {
        init();
    }
    ~list() {
        clear();
        delete head;
        delete tail;
    }
    list(size_t n_elements, const T& c) {
        init();
        for (int i = 0; i != n_elements; i++) {
            push_back(c);
        }
    }
    list(const list& x) {
        init();
        for (iterator iter = x.begin(); iter != x.end(); iter++) {
            push_back(*iter);
        }
    }
    list(iterator b, iterator e) {
        init();
        for (iterator iter = b; iter != e; iter++) {
            push_back(*iter);
        }
    }
    iterator begin() const {
        return iterator(head->next);
    }
    iterator end() const {
        return iterator(tail);
    }
    size_t size() const {
        return _size;
    }
    void push_front(const T& c) {
        insert(begin(), c);
    }
    void push_back(const T& c) {
        insert(end(), c);
    }
    void pop_front() {
        erase(begin());
    }
    void pop_back() {
        erase(--end());
    }
    iterator insert(iterator position, const T& val) {
        Node* p = position.current;
        _size++;
        return iterator(p->prev = p->prev->next = new Node(val, p, p->prev));
    }
    iterator erase(iterator position) {
        Node* p = position.current;
        iterator retVal(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        _size--;
        return retVal;
    }
    bool empty() const {
        return _size == 0;
    }
    T& front() {
        return *begin();
    }
    T& back() {
        return *(--end());
    }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    friend ostream& operator << (ostream& out, const list& x) {
        if (x.empty()) {
            out << "[ ]";
            return out;
        }
        out << "[ ";
        for (iterator iter =
             x.begin(); iter != (x.end())->prev; iter++) {
            out << *iter << " ";
        }
        out << (x.end())->prev->data;
        out << " ]";
        return out;
    }
};