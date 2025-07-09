/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* createcpy(Node* node, unordered_map<Node*, Node*>& mp) {
        Node* curr = new Node(node->val);
        mp[node] = curr;
        for(int i=0;i<node->neighbors.size();i++) {
            auto pt = node->neighbors[i];
            if(mp.find(pt) != mp.end()) {
                curr->neighbors.push_back(mp[pt]);
            }
            else {
                curr->neighbors.push_back(createcpy(pt, mp));
            }
        }
        return curr;
    }
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;
        unordered_map<Node*, Node*> mp;
        return createcpy(node, mp);
         
    }
};