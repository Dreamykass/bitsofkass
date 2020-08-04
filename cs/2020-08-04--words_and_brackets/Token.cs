using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace WordsAndBrackets
{
    class Token
    {
        public enum Type
        {
            Word,
            TokenList,
        }

        public Type type;

        public String wordString;

        public List<Token> tokenList = new List<Token>();
        public Char bracketType;
    }
}
