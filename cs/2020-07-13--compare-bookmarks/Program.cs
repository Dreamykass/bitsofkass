using System;
using System.IO;

namespace compare_bookmarks
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("---");
            try
            {
                var bookmarks = LoadBookmarks.Load();
                var links = MatchLinks.Match(bookmarks);
                Compare.Comp(links);
            }
            catch (Exception e)
            {
                Console.WriteLine("---");
                Console.WriteLine("Exception!");
                Console.WriteLine("Message: " + e.Message);
            }
            Console.WriteLine("---");
        }
    }
}
