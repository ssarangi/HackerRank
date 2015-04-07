#include <tuple>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>

struct Edge;

struct Node
{
    int id;
    int weight;
    int cost;
    int fuel_left;
    int fuel_filled;
    std::vector<Node*> nodes;
};


struct Graph
{
    std::vector<Node*> nodes;

    int start_node;
    int end_node;

    std::unordered_map<unsigned int, std::vector<Node*>> nodes_at_id;
    void dijkstra();
};

void Graph::dijkstra()
{
    int *distances = new int[end_node - start_node];

    for (int i = 0; i < end_node - start_node; ++i)
        distances[i] = INT_MAX;

    std::queue<Node*> queue;
    queue.push(nodes[start_node]);

    while (!queue.empty())
    {

    }
}

struct TestCase
{
    std::vector<std::pair<int, int>> fuel_price;
    std::vector<std::pair<int, int>> edges;
    int C;
    int N;

    void execute();
    void create_graph();
    Node* create_node(Node *parent, int node_id, int units_filled, int units_req, int cost_per_unit, int current_cost, int end_node);
    void create_connections();

    std::vector<Graph*> graphs;
};

//Node* TestCase::create_node(Node *parent, int node_id, int units_filled, int unit_req, int cost_per_unit, int current_cost, int end_node)
//{
//    if (node_id > end_node)
//        return nullptr;
//
//    Node *new_node = new Node();
//    new_node->id = node_id;
//    new_node->cost = units_filled * cost_per_unit;
//    new_node->fuel_left = units_filled - unit_req;
//
//    printf("Creating Node: %d -- Units Filled: %d -- Units Req: %d -- Units Left: %d -- Cost: %d\n", node_id, units_filled, unit_req, new_node->fuel_left, new_node->cost);
//
//    if (parent != nullptr)
//        parent->nodes.push_back(new_node);
//    
//    int next_units_req = fuel_price[node_id].first;
//    int next_cost_per_unit = fuel_price[node_id].second;
//
//    for (int units_can_be_filled = C; units_can_be_filled >= next_units_req; --units_can_be_filled)
//    {
//        create_node(new_node, node_id + 1, units_can_be_filled, next_units_req, next_cost_per_unit, new_node->cost, end_node);
//    }
//
//    return new_node;
//}

void TestCase::create_graph()
{
    for (int i = 0; i < edges.size(); ++i)
    {
        Graph *g = new Graph();
        
        int start_node_id = edges[i].first;
        int end_node_id = edges[i].second;
    
        // Node *root = create_node(nullptr, start_node_id, 0, 0, 0, 0, end_node_id);
        // Gas filled up at each node

        for (int i = start_node_id; i < end_node_id; ++i)
        {
            g->nodes_at_id[i].clear();

            for (int fuel_units_filled = 0; fuel_units_filled <= C; ++fuel_units_filled)
            {
                Node *n = new Node();
                n->id = i;
                n->fuel_filled = fuel_units_filled;
                g->nodes_at_id[i].push_back(n);
            }
        }

        graphs.push_back(g);
    }
}

void TestCase::create_connections()
{
    for (int i = 0; i < edges.size(); ++i)
    {
        Graph *g = graphs[i];

        int start_node_id = edges[i].first;
        int end_node_id = edges[i].second;


        for (int node_id = start_node_id; node_id < end_node_id; ++node_id)
        {
            // Connect the nodes.

        }
    }
}

void TestCase::execute()
{
    create_graph();

    for (int i = 0; i < graphs.size(); ++i)
    {
        // Execute this.
        graphs[i]->dijkstra();
    }
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

    std::cout << "Num Test cases: " << test_cases << std::endl;
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