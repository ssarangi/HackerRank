#include <tuple>
#include <vector>
#include <iostream>
#include <queue>

struct Edge;

struct Node
{
    int id;
    int subid;
    std::vector<Edge*> edges;
};

struct Edge
{
    Node *start;
    Node *end;
    int weight;
};

struct Graph
{
    std::vector<Node*> nodes;

    int start_node;
    int end_node;

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

    std::vector<Graph*> graphs;
};

void TestCase::create_graph()
{
    for (int i = 0; i < edges.size(); ++i)
    {
        Graph *g = new Graph();
        
        int start_node_id = edges[i].first;
        int end_node_id = edges[i].second;

        g->start_node = start_node_id;
        g->end_node = end_node_id;

        for (int j = start_node_id; j < end_node_id; ++j)
        {
            Node *pNode = new Node();
            pNode->id = j;
            g->nodes.push_back(pNode);
        }

        for (int j = start_node_id; j < end_node_id; ++j)
        {
            int units_req = fuel_price[j].first;
            int cost_per_unit = fuel_price[j].second;

            Node *start_node = new Node();
            start_node->id = start_node_id;

            for (int k = units_req; k <= C; ++k)
            {
                Node *end_node = g->nodes[j + 1];
                Edge *edge = new Edge();
                edge->start = start_node;
                edge->end = end_node;
                edge->weight = k * cost_per_unit;
                start_node->edges.push_back(edge);
            }
        }

        graphs.push_back(g);
    }
}

void TestCase::execute()
{
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