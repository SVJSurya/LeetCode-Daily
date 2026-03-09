class LRUCache {

private:
    struct Node{
        int key, value;
        Node *prev, *next;
        Node(int k, int v) :key(k), value(v), prev(nullptr), next(nullptr) {} 
    };

    int capacity;
    unordered_map<int, Node*> mp;
    Node *head, *tail;
    
    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insert(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (mp.find(key) == mp.end())
            return -1;

        Node* node = mp[key];
        remove(node);
        insert(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            node->value = value;
            remove(node);
            insert(node);
        } else {
            if (mp.size() == capacity) {
                Node* lru = tail->prev;
                mp.erase(lru->key);
                remove(lru);
                delete lru;
            }
            Node* node = new Node(key, value);
            mp[key] = node;
            insert(node);
        }
    }
};
auto init = atexit([]() { ofstream("display_runtime.txt") << "0";});
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */