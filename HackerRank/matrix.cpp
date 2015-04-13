#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <limits.h>

struct Node
{
    int id;
    bool has_machine;
    Node* parent;
    std::map<Node*, int> edges;

    Node() :
        has_machine(false),
        id(-1),
        parent(nullptr)
    {}
};

struct Matrix
{
public:
    void read_input()
    {
        std::cin >> N >> K;

        for (int i = 0; i < N - 1; ++i)
        {
            int city1, city2, time;
            std::cin >> city1 >> city2 >> time;

            if (nodes[city1] == nullptr)
                nodes[city1] = new Node();

            if (nodes[city2] == nullptr)
                nodes[city2] = new Node();

            nodes[city1]->edges[ nodes[city2]] = time;
            nodes[city2]->edges[ nodes[city1]] = time;
            nodes[city1]->id = city1;
            nodes[city2]->id = city2;
        }

        for (int i = 0; i < K; ++i)
        {
            int machine_location;
            std::cin >> machine_location;
            nodes[machine_location]->has_machine = true;
            machine_locations.push_back(machine_location);
        }
    }

    void goto_parent(Node* leaf)
    {
        while (leaf != nullptr && leaf->parent != nullptr)
        {
            printf("%d ------> %d with weight %d\n", leaf->id, leaf->parent->id, leaf->parent->edges[leaf]);
            leaf = leaf->parent;
        }
    }

    void dfs(Node *root_node, Node *curr_node, Node *prev_node, Node *node_to_be_deleted_1, Node* node_to_be_deleted_2, int mintime, int& total_time, std::vector<Node*>& visited, std::map<Node*, Node*>& deleted_pair)
    {
        if (std::find(visited.begin(), visited.end(), curr_node) != visited.end())
            return;

        if (prev_node != nullptr)
            curr_node->parent = prev_node;

        if (curr_node->has_machine && root_node != curr_node)
        {
            // goto_parent(curr_node);
            // printf("-------------------------------------\n");

            // We need to terminate this here and see if we can destroy a road between these 2
            if (curr_node->edges[prev_node] < mintime)
            {
                // Destroy this edge
                deleted_pair[curr_node] = prev_node;
                total_time += curr_node->edges[prev_node];
                // printf("Edge deleted: %d ----- %d\n", curr_node->id, prev_node->id);
            }
            else
            {
                if (deleted_pair.find(node_to_be_deleted_1) == deleted_pair.end())
                {
                    if (deleted_pair[node_to_be_deleted_1] != node_to_be_deleted_2)
                    {
                        // A previous node has to be deleted.
                        deleted_pair[node_to_be_deleted_1] = node_to_be_deleted_2;
                        total_time += node_to_be_deleted_1->edges[node_to_be_deleted_2];
                        // printf("Edge deleted: %d ----- %d\n", node_to_be_deleted_1->id, node_to_be_deleted_2->id);
                    }
                }

                // std::cout << "Total time: " << total_time << std::endl;
            }
            // printf("-------------------------------------\n");
        }
        else
        {
            if (prev_node != nullptr && curr_node->edges[prev_node] < mintime)
            {
                node_to_be_deleted_1 = prev_node;
                node_to_be_deleted_2 = curr_node;
                mintime = curr_node->edges[prev_node];
            }

            visited.push_back(curr_node);

            // we continue further
            for (auto node_time_pair : curr_node->edges)
            {
                dfs(root_node, node_time_pair.first, curr_node, node_to_be_deleted_1, node_to_be_deleted_2, mintime, total_time, visited, deleted_pair);
            }
        }
    }

    void solve()
    {
        int total_time = 0;
        int num_cuts = 0;
        // std::reverse(machine_locations.begin(), machine_locations.end());
        for (int i = 0; i < machine_locations.size(); ++i)
        {
            std::vector<Node*> visited;
            std::map<Node*, Node*> deleted_pair;

            // printf("Starting with root node: %d\n", nodes[machine_locations[i]]->id);
            dfs(nodes[machine_locations[i]], nodes[machine_locations[i]], nullptr, nullptr, nullptr, INT_MAX, total_time, visited, deleted_pair);

            num_cuts += deleted_pair.size();

            for (auto node1_node2_pair : deleted_pair)
            {
                // printf("Deleting edge: %d -----> %d with weight %d\n", node1_node2_pair.first->id, node1_node2_pair.second->id, node1_node2_pair.first->edges[node1_node2_pair.second]);
                node1_node2_pair.first->edges.erase(node1_node2_pair.second);
                node1_node2_pair.second->edges.erase(node1_node2_pair.first);
            }
        }

        std::cout << total_time << std::endl;
    }

private:
    std::map<int, Node*> nodes;
    std::vector<int> machine_locations;
    int N;
    int K;
};

int main(void)
{
    Matrix matrix;
    matrix.read_input();
    matrix.solve();
}