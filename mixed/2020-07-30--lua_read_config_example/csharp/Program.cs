using System;
using System.IO;
using NLua;

namespace csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello from C#");

            Lua lua_state = new Lua();

            var script_str = File.ReadAllText("../script.lua");
            lua_state.DoString(script_str);

            var ErrorCodes = lua_state["ErrorCodes"] as LuaTable;
            Console.WriteLine("Error code 007: " + ErrorCodes[7]);
            Console.WriteLine("Error code -1: " + ErrorCodes[-1]);

            Console.WriteLine("Error codes and their strings:");
            foreach (var item in ErrorCodes)
            {
                Console.WriteLine("{0}", item);
            }


        }
    }
}
