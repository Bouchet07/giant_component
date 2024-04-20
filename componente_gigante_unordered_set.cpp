#include <unordered_map>
#include <unordered_set>
#include <vector>
//#include <array>
#include <cstdint>
#include <iostream>
#include <stack>

using node = uint16_t;

int findFalseIndex(const std::vector<bool>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (!vec[i]) {
            return i;
        }
    }
    return -1; // Return -1 if no false element found
}

class Net {
    private:
    std::unordered_map<node, std::unordered_set<node>> Nodes;

    public:
    Net() {}
    Net(std::unordered_map<node, std::unordered_set<node>>& neighbors) : Nodes(neighbors) {}
    Net(const std::vector<std::unordered_set<node>>& neighbors) {
        for (size_t i = 0; i < neighbors.size(); i++) {
            Nodes[i] = neighbors[i];
        }
    }

    // Adds a new node at i with no neighbors
    void add(const node i) {
        Nodes[i] = std::unordered_set<node>();
    }
    // Adds a new node at i with the given neighbors
    void add(const node i, const std::unordered_set<node>& neighbors) {
        Nodes[i] = neighbors;
    }
    // Adds a new node at available index with no neighbors
    node add() {
        for (node i = 0; i < Nodes.size(); i++) {
            if (Nodes.find(i) == Nodes.end()) {
                Nodes[i] = std::unordered_set<node>();
                return i;
            }
        }
    }
    // Adds a new node at available index with the given neighbors
    node add(const std::unordered_set<node>& neighbors) {
        for (node i = 0; i < Nodes.size(); i++) {
            if (Nodes.find(i) == Nodes.end()) {
                Nodes[i] = neighbors;
                return i;
            }
        }
    }
    // Removes the node i
    void remove(const node i) {
        Nodes.erase(i);
    }
    // clears the net
    void clear() {
        Nodes.clear();
    }

    // links node i with node j
    void link(const node i, const node j) {
        Nodes[i].insert(j);
        Nodes[j].insert(i);
    }
    // links node i with all nodes in the set neighbors
    void link(const node i, const std::unordered_set<node>& neighbors) {
        for (const node& j : neighbors) {
            Nodes[i].insert(j);
            Nodes[j].insert(i);
        }
    }
    // unlinks node i with node j
    void unlink(const node i, const node j) {
        Nodes[i].erase(j);
    }
    // unlinks node i with all nodes in the set neighbors
    void unlink(const node i, const std::unordered_set<node>& neighbors) {
        for (const node& j : neighbors) {
            Nodes[i].erase(j);
            Nodes[j].erase(i);
        }
    }

    std::unordered_map<node, std::unordered_set<node>> getNodes() const {
        return Nodes;
    }

    Net get_giant_component() {
        if (Nodes.empty()) {
            return Net();
        }

        std::vector<bool> visited(Nodes.size(), false);
        std::vector<bool> best(Nodes.size(), false);
        //std::vector<bool> recorded(Nodes.size(), false);
        size_t best_count = 0, count = 0, giant_count = 0;

        std::stack<node> dfs_stack;

        for (size_t start = 0; start < Nodes.size(); ++start) {
            if (visited[start]) continue;
            std::vector<bool> recorded(Nodes.size(), false);
            giant_count = 0;
            dfs_stack.push(start);

            while (!dfs_stack.empty()) {
                node current = dfs_stack.top();
                dfs_stack.pop();

                if (!visited[current]) {
                    visited[current] = true;
                    recorded[current] = true;
                    ++giant_count;

                    for (const node& neighbor : Nodes[current]) {
                        if (!visited[neighbor]) {
                            dfs_stack.push(neighbor);
                        }
                    }
                }
            }

            if (giant_count > best_count) {
                best = std::move(recorded);
                best_count = giant_count;
            }
            if (best_count >= (Nodes.size()-count)) break;
        }

        std::unordered_map<node, std::unordered_set<node>> giant_component;
        for (size_t i = 0; i < best.size(); ++i) {
            if (best[i]) {
                giant_component[i] = Nodes[i];
            }
        }

        return Net(giant_component);
    }


    size_t count_unseen(const node i, std::vector<bool>& seen, std::vector<bool>& recorded) {
        size_t count = 1;
        seen[i] = true;
        recorded[i] = true;
        for (const node& j : Nodes[i]) {
            if (!seen[j]) {
                count += count_unseen(j, seen, recorded);
            }
        }
        return count;
    }

    void print() {
        if (Nodes.empty()) {
            std::cout << "Empty net" << std::endl;
            return;
        }
        for (const auto& [i, neighbors] : Nodes) {
            std::cout << i << ": ";
            for (const node& j : neighbors) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main(){
    Net net;
    std::cout << net.getNodes().size() << std::endl;
    net.add(5);
    net.link(3,{5,2});
    net.print();
    std::cout << net.getNodes().size() << std::endl;
    std::cout << "Giant component:" << std::endl;
    Net giant_net = net.get_giant_component();
    giant_net.print();
    return 0;
}