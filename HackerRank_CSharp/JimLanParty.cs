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
        }

        class Graph
        {
            public Node[] nodes = new Node[100000];
            public int[,] adj_matrix = new int[100000, 100000];
            public int[] group_size_for_game = new int[100000];

            public Graph()
            {
                for (int i = 0; i < 100000; ++i)
                {
                    nodes[i] = new Node();
                }
            }
        }

        Graph g = new Graph();

        void DFS()

        void Solve()
        {
            string[] inputs = Console.ReadLine().Split(' ');
            int N = Convert.ToInt32(inputs[0]);
            int M = Convert.ToInt32(inputs[1]);
            int Q = Convert.ToInt32(inputs[2]);

            string[] games = Console.ReadLine().Split(' ');

            for (int i = 0; i < games.Length; ++i )
            {
                g.nodes[i].game = Convert.ToInt32(games[i]);
                g.group_size_for_game[g.nodes[i].game]++;
            }

            for (int i = 0; i < Q; ++i)
            {
                string[] connections = Console.ReadLine().Split(' ');
                int start = Convert.ToInt32(connections[0]);
                int end = Convert.ToInt32(connections[1]);
                g.adj_matrix[start, end] = 1;
                g.adj_matrix[end, start] = 1;
            }
        }

        static void Main(string[] args)
        {
            JimLanParty jimLanPartyProblem = new JimLanParty();
            jimLanPartyProblem.Solve();
        }
    }
}
