using System;
using System.Collections.Generic;
using System.Linq;

namespace _2021_01_25__random_sort
{
    class Program
    {

        static List<T> ShuffleSort<T>(List<T> list)
        {
            var rand = new Random();

            var sorted = new List<T>();
            foreach (var t in list)
                sorted.Add(t);
            sorted.Sort();

            while (!list.SequenceEqual(sorted))
            {
                list = list.OrderBy(_ => rand.Next()).ToList();
            }

            return list;
        }

        static void Main(string[] args)
        {
            var rand = new Random();

            var list = new List<int>();
            list.AddRange(Enumerable.Range(0, 10));
            list = list.OrderBy(a => rand.Next()).ToList();

            foreach (var i in list)
                Console.Write("{0}, ", i);

            list = ShuffleSort(list);

            Console.WriteLine();
            Console.WriteLine();

            foreach (var i in list)
                Console.Write("{0}, ", i);
        }
    }
}
