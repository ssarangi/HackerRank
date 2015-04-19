using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HackerRank_CSharp
{
    class JimLanParty
    {
        class Node
        {
            public int game;
            public List<Node> connections = new List<Node>();
            public int ID;
        }

        class Graph
        {
            public int[] group_size_for_game;
            public Dictionary<int, Node> nodes = new Dictionary<int, Node>();

            public Graph()
            {
            }
        }

        Graph g = new Graph();

        bool DFS(Node node, ref DFSState dfs_state)
        {
            if (!dfs_state.node_visited.ContainsKey(node.ID))
            {
                if (dfs_state.games_visited.ContainsKey(node.game))
                    ++dfs_state.games_visited[node.game];
                else
                    dfs_state.games_visited[node.game] = 1;

                if (dfs_state.games_visited[node.game] == g.group_size_for_game[node.game] &&
                    g.group_size_for_game[node.game] > 1)
                    dfs_state.games_connected.Add(node.game);
            }

            dfs_state.node_visited[node.ID] = true;

            bool res = false;
            bool visited_atleast_one = false;
            foreach (Node n in node.connections)
            {
                bool visited = false;
                dfs_state.node_visited.TryGetValue(n.ID, out visited);

                if (!visited)
                {
                    res |= DFS(n, ref dfs_state);
                    visited_atleast_one = true;
                }
            }

            if (!visited_atleast_one)
                dfs_state.terminating_nodes[node.ID] = true;

            return res;
        }

        class DFSState
        {
            public Dictionary<int, bool> node_visited = new Dictionary<int, bool>();
            public Dictionary<int, int> games_visited = new Dictionary<int, int>();
            public List<int> games_connected = new List<int>();
            public Dictionary<int, bool> terminating_nodes = new Dictionary<int, bool>();
        }

        void ReadInput()
        {
            string[] inputs = Console.ReadLine().Split(' ');
            int N = Convert.ToInt32(inputs[0]);
            int M = Convert.ToInt32(inputs[1]);
            int Q = Convert.ToInt32(inputs[2]);

            for (int i = 1; i <= N; ++i)
            {
                Node node = new Node();
                node.ID = i;
                g.nodes[i] = node;
            }

            g.group_size_for_game = new int[M + 1];

            string[] games = Console.ReadLine().Split(' ');

            for (int i = 1; i <= games.Length; ++i )
            {
                g.nodes[i].game = Convert.ToInt32(games[i-1]);
                g.group_size_for_game[g.nodes[i].game]++;
            }

            Dictionary<int, int> connections_which_enabled_group = new Dictionary<int, int>();
            List<DFSState> dfs_states = new List<DFSState>();

            for (int i = 0; i < Q; ++i)
            {
                string[] connections = Console.ReadLine().Split(' ');
                int start = Convert.ToInt32(connections[0]);
                int end = Convert.ToInt32(connections[1]);
                g.nodes[start].connections.Add(g.nodes[end]);
                g.nodes[end].connections.Add(g.nodes[start]);

                DFSState dfs_state_to_use = null;

                foreach (DFSState dfs_state in dfs_states)
                {
                    if (dfs_state.node_visited.ContainsKey(start) || dfs_state.node_visited.ContainsKey(end))
                        dfs_state_to_use = dfs_state;
                }
                
                if (dfs_state_to_use == null)
                {
                    dfs_state_to_use = new DFSState();
                    dfs_states.Add(dfs_state_to_use);
                }

                DFS(g.nodes[start], ref dfs_state_to_use);
                foreach (int game in dfs_state_to_use.games_connected)
                    if (!connections_which_enabled_group.ContainsKey(game))
                        connections_which_enabled_group[game] = i;
            }

            for (int i = 1; i <= M; ++i)
            {
                int connection = -1;
                if (connections_which_enabled_group.ContainsKey(i))
                    connection = connections_which_enabled_group[i] + 1;
                else if (g.group_size_for_game[i] == 1)
                    connection = 0;

                Console.WriteLine(connection);
            }
        }

        static void Main(string[] args)
        {
            JimLanParty jimLanPartyProblem = new JimLanParty();
            jimLanPartyProblem.ReadInput();
        }
    }
}
