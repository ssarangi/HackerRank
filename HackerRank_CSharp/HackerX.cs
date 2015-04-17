using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HackerRank_CSharp
{
    struct Node
    {

    }

    class HackerX
    {
        void ReadInput()
        {
            int N = Convert.ToInt32(Console.ReadLine());

            for (int i = 0; i < N; ++i)
            {
                string line = Console.ReadLine();

                int ti = Convert.ToInt32(line.Split(' ')[0]);
                int fi = Convert.ToInt32(line.Split(' ')[1]);
            }
        }

        void Solve()
        {

        }

        //static void Main(string[] args)
        //{
        //    HackerX hackerX = new HackerX();
        //    hackerX.ReadInput();
        //    hackerX.Solve();
        //}
    }
}
