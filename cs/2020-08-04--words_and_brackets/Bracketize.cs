using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace WordsAndBrackets
{
    class Bracketize
    {
        static List<Tuple<Char, Char>> brackets = new List<Tuple<Char, Char>>();

        public static void Init()
        {
            brackets.Add(new Tuple<Char, Char>('(', ')'));
        }

        public static List<Token> Now(List<String> words, int beg, int end, Stack<Char> bracketStack)
        {
            List<Token> rootTokenList = new List<Token>();

            for (int it = beg; it < end; it++)
            {
                var word = words[it];
                var firstChar = word.ElementAt(0);

                Console.WriteLine("----stack: {0}", string.Join("", bracketStack.ToArray()));

                if (word.Length == 1 && brackets.Any(b => b.Item1.Equals(firstChar) || b.Item2.Equals(firstChar)))
                {
                    Console.WriteLine("bracket at {0}: {1}", it + 1, word);

                    if (brackets.Any(b => b.Item1.Equals(firstChar)))
                    {
                        bracketStack.Push(firstChar);
                        it++;

                        Token token = new Token();
                        token.type = Token.Type.TokenList;
                        token.bracketType = firstChar;
                        token.tokenList = Now(words, it++, end, bracketStack);
                        rootTokenList.Add(token);
                    }
                    else if (brackets.Any(b => b.Item2.Equals(firstChar)))
                    {
                        bracketStack.Pop();
                        return rootTokenList;
                    }
                }
                else
                {
                    Console.WriteLine("word at    {0}: {1}", it + 1, word);

                    Token token = new Token();
                    token.type = Token.Type.Word;
                    token.wordString = word;
                    rootTokenList.Add(token);
                }
            }

            return rootTokenList;
        }

        public static List<Token> Now2(List<String> words, int beg, int end, Stack<Char> bracketStack)
        {
            List<Token> rootTokenList = new List<Token>();

            for (int it = beg; it < end; it++)
            {
                var word = words[it];
                var firstChar = word.ElementAt(0);

                Console.WriteLine("----stack: {0}", string.Join("", bracketStack.ToArray()));

                if (word.Length == 1 && brackets.Any(b => b.Item1.Equals(firstChar) || b.Item2.Equals(firstChar)))
                {
                    Console.WriteLine("bracket at {0}: {1}", it + 1, word);

                    if (brackets.Any(b => b.Item1.Equals(firstChar)))
                    {
                        bracketStack.Push(firstChar);
                        it++;

                        Token token = new Token();
                        token.type = Token.Type.TokenList;
                        token.bracketType = firstChar;
                        token.tokenList = Now(words, it++, end, bracketStack);
                        rootTokenList.Add(token);
                    }
                    else if (brackets.Any(b => b.Item2.Equals(firstChar)))
                    {
                        bracketStack.Pop();
                        return rootTokenList;
                    }
                }
                else
                {
                    Console.WriteLine("word at    {0}: {1}", it + 1, word);

                    Token token = new Token();
                    token.type = Token.Type.Word;
                    token.wordString = word;
                    rootTokenList.Add(token);
                }
            }

            return rootTokenList;
        }
    }
}
