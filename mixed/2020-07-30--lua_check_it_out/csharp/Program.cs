using System;
using System.IO;
using NLua;
using System.Collections.Generic;

namespace csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            Lua state = new Lua();

            var script = File.ReadAllText("../script.lua");

            state.DoString(script);

            var list_from_global = state["GlobalTable"] as LuaTable;
            var list_from_function = state["TableFromFunction"] as LuaTable;

            Console.WriteLine("list_from_global");
            foreach (var item in list_from_global.Values)
            {
                Console.WriteLine("---{0}", item);
            }

            Console.WriteLine("list_from_function");
            foreach (var item in list_from_function.Values)
            {
                Console.WriteLine("---{0}", item);
            }

        }
    }
}
