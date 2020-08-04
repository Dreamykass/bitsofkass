using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace WordsAndBrackets
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello.");

            var input = "workspace/round.txt";
            var lines = new List<String>(File.ReadAllLines(input));

            // trim lines
            {
                var trimmedLines = new List<String>();
                lines.ForEach(line => trimmedLines.Add(line.Trim()));
                lines = trimmedLines;
                lines.RemoveAll(line => line == "");
                lines.RemoveAll(line => line.Length < 1);
                File.WriteAllLines("output/trimmed.txt", lines);
            }

            // lines to words
            List<String> words = lines;

            // bracketize
            Bracketize.Init();
            var tokenList = Bracketize.Now(words, 0, words.Count, new Stack<Char>());

            Console.WriteLine("Bye.");
        }
    }
}
