#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
//#include <array>
#include <cstdint>
#include <iostream>
#include <stack>
#include <chrono>
#include <random>


using node = uint32_t;

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
        for (auto& [_, neighbors] : Nodes) {
            neighbors.erase(i);
        }
    }
    // clears the net
    void clear() {
        Nodes.clear();
    }

    // links node i with node j
    void link(const node i, const node j) {
        if (i == j) return;
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

    std::vector<node> index_to_node() {
        std::vector<node> index_to_node(Nodes.size());
        size_t j = 0;
        for (const auto& [i, _] : Nodes) {
            index_to_node[j]= i;
            ++j;
        }
        return index_to_node;
    }
    std::unordered_map<node, node> node_to_index(std::vector<node> index_to_node) {
        std::unordered_map<node, node> node_to_index;
        for (size_t i = 0; i < index_to_node.size(); ++i) {
            node_to_index[index_to_node[i]] = i;
        }
        return node_to_index;
    }

    Net get_giant_component() {
        if (Nodes.empty()) {
            return Net();
        }

        std::vector<bool> visited(Nodes.size(), false);
        std::vector<node> best, recorded;
        std::vector<node> index_to_node = this->index_to_node();
        std::unordered_map<node, node> node_to_index = this->node_to_index(index_to_node);

        size_t count = 0;

        node start, current, current_index;
        std::stack<node> dfs_stack;
        for (node i = 0; i < Nodes.size(); ++i) {
            start = index_to_node[i];
            if (visited[i]) continue;
            recorded.clear();
            dfs_stack.push(start);

            while (!dfs_stack.empty()) {
                current = dfs_stack.top();
                dfs_stack.pop();

                current_index = node_to_index[current];
                if (!visited[current_index]) {
                    visited[current_index] = true;
                    recorded.push_back(current);

                    for (const node& neighbor : Nodes[current]) {
                        if (!visited[node_to_index[neighbor]]) {
                            dfs_stack.push(neighbor);
                        }
                    }
                }
            }
            count += recorded.size();
            if (recorded.size() > best.size()) best = recorded;
            if (best.size() >= (Nodes.size()-count)) break;
        }

        std::unordered_map<node, std::unordered_set<node>> giant_component;
        for (const node& i : best) {
            giant_component[i] = Nodes[i];
        }

        return Net(giant_component);
    }

    Net ring(const node N) {
        std::unordered_map<node, std::unordered_set<node>> ring;
        for (node i = 0; i < N; i++) {
            ring[i] = {};
        }
        Net net(ring);
        for (node i = 0; i < N; i++) {
            net.link(i, (i+1)%N);
        }
        return net;
    }

    node max(){
        node max = 0;
        for (const auto& [i, _] : Nodes) {
            if (i > max) {
                max = i;
            }
        }
        return max;
    }

    Net join(const Net& net) {
        node sum = this->max() + 1;
        std::unordered_map<node, std::unordered_set<node>> joined = Nodes;
        std::unordered_set<node> neighbors_sum;
        for (const auto& [i, neighbors] : net.getNodes()) {
            neighbors_sum.clear();
            for (const node& j : neighbors) {
                neighbors_sum.insert(j+sum);
            }
            joined[i+sum] = neighbors_sum;
        }
        return Net(joined);
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