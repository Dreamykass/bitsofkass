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
            var tokenList = Bracketize.Now2(words);

            // tokens to file
            {
                List<String> indentedWords = new List<String>();
                String indentation = "";

                Action<List<Token>> printer = null;
                printer = (List<Token> tokenL) =>
                {
                    foreach (var token in tokenL)
                    {
                        if (token.type == Token.Type.Word)
                        {
                            indentedWords.Add(indentation + token.wordString);
                        }
                        else if (token.type == Token.Type.TokenList)
                        {
                            indentation += "    ";
                            printer(token.tokenList);
                            indentation = indentation.Remove(indentation.Length - 4);
                        }
                    }
                };

                printer(tokenList);

                File.WriteAllLines("output/finished.txt", indentedWords);
            }

            Console.WriteLine("Bye.");
        }
    }
}
