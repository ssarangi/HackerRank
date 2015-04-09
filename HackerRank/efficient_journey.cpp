#include <tuple>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

struct Edge;

struct Node
{
    int id;
    int cost;
    int fuel_left;
    std::vector<Node*> nodes;
};


struct Graph
{
    std::vector<Node*> nodes;

    int start_node;
    int end_node;
    int num_nodes;
    int min_cost;

    Node* root;
    Node* dummy_end_node;

    void dijkstra();
};

void Graph::dijkstra()
{
    //std::queue<Node*> queue;
    //queue.push(root);

    //int *distances = new int[num_nodes + 1];

    //for (int i = 0; i < num_nodes; ++i)
    //{
    //    distances[i] = INT_MAX;
    //}

    //while (!queue.empty())
    //{
    //    Node *node = queue.front();
    //    queue.pop();

    //    // Look at all the paths from this node
    //    int child_nodes = node->nodes.size();
    //    int min_cost = INT_MAX;
    //    Node* next_node = nullptr;
    //    for (int i = 0; i < child_nodes; ++i)
    //    {
    //        // Find the minimum cost path
    //        if (node->nodes[i]->cost <= distances[node->nodes[i]->cost])
    //        {
    //            min_cost = node->nodes[i]->cost;
    //            next_node = node->nodes[i];
    //            distances[node->nodes[i]->id] = min_cost;
    //        }
    //    }
    //}
}

struct TestCase
{
    std::vector<std::pair<int, int>> fuel_price;
    std::vector<std::pair<int, int>> edges;
    int C;
    int N;

    void execute();
    void create_graph();
    Node* create_node(Graph* g, Node *parent, int node_id, int units_filled, int units_req, int current_cost, int end_node);

    std::vector<Graph*> graphs;
};

Node* TestCase::create_node(Graph *g, Node *parent, int node_id, int units_filled, int unit_req, int current_cost, int end_node)
{
    Node *new_node = new Node();
    new_node->id = g->num_nodes;
    new_node->cost = current_cost;
    new_node->fuel_left = units_filled - unit_req;
    ++g->num_nodes;

    if (parent != nullptr)
        parent->nodes.push_back(new_node);
 
    if (node_id >= end_node)
    {
        new_node->nodes.push_back(g->dummy_end_node);
        if (g->min_cost > current_cost)
            g->min_cost = current_cost;

        // printf("Creating Node: %d -- Units Filled: %d -- Units Req: %d -- Units Left: %d -- Cost: %d\n", node_id, units_filled, unit_req, new_node->fuel_left, new_node->cost);
        return nullptr;
    }

    int next_units_req = fuel_price[node_id].first;
    int next_cost_per_unit = fuel_price[node_id].second;

    for (int units_can_be_filled = C; units_can_be_filled >= next_units_req; --units_can_be_filled)
    {
        int units_actually_filled = units_can_be_filled - new_node->fuel_left;
        int cost = new_node->cost + units_actually_filled * next_cost_per_unit;

        create_node(g, new_node, node_id + 1, units_can_be_filled, next_units_req, cost, end_node);
    }

    return new_node;
}

void TestCase::create_graph()
{
    for (int i = 0; i < edges.size(); ++i)
    {
        Graph *g = new Graph();
        g->num_nodes = 0;
        g->min_cost = INT_MAX;

        int start_node_id = edges[i].first;
        int end_node_id = edges[i].second;
    
        Node *root = create_node(g, nullptr, start_node_id, 0, 0, 0, end_node_id);
        Node *dummy_end_node = new Node();
        dummy_end_node->cost = 0;

        g->root = root;
        g->dummy_end_node = dummy_end_node;
        graphs.push_back(g);
        std::cout << g->min_cost << std::endl;
    }
}

void TestCase::execute()
{
    create_graph();
}

class EfficientJourney
{
public:
    EfficientJourney()
    {}

    void read_input();
    void execute();

private:
    std::vector<TestCase> m_testcases;
};

void EfficientJourney::read_input()
{
    // Read number of test cases
    int test_cases = 0;
    std::cin >> test_cases;

    for (int i = 0; i < test_cases; ++i)
    {
        TestCase test_case;
        int N = 0, K = 0, C = 0;

        std::cin >> N >> K >> C;

        test_case.C = C;
        test_case.N = N;

        test_case.fuel_price.push_back(std::make_pair(0, 0));
        for (int i = 0; i < N - 1; ++i)
        {
            int f, p;
            std::cin >> f >> p;
            test_case.fuel_price.push_back(std::make_pair(f, p));
        }

        std::vector<std::tuple<int, int>> start_end;
        for (int i = 0; i < K; ++i)
        {
            int a, b;
            std::cin >> a >> b;
            test_case.edges.push_back(std::make_pair(a, b));
        }

        m_testcases.push_back(test_case);
    }
}

void EfficientJourney::execute()
{
    for (int i = 0; i < m_testcases.size(); ++i)
    {
        m_testcases[i].execute();
    }
}

int main(void)
{
    EfficientJourney efficient_journey;
    efficient_journey.read_input();
    efficient_journey.execute();
}