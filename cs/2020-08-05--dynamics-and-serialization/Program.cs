using System;
using System.Collections.Generic;
using System.IO;
using System.Dynamic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace _2020_08_05__dynamics_and_serialization
{
    class Foo
    {
        public dynamic member { get; set; }

        public Foo()
        {

        }
        public Foo(String type)
        {
            if (type == "str")
            {
                var memberStr = "";
                Random rand = new Random();
                var chars = "qwerroyipsmcz29xmcvbnngjfaplomnwegjbimcxnbejrko".ToCharArray();
                for (int i = 0; i < 10; i++)
                    memberStr += chars[rand.Next(0, chars.Length)].ToString();
                member = memberStr;
            }
            else if (type == "int")
            {
                var memberInt = (Int32?)(32);
                Random rand = new Random();
                memberInt = rand.Next(1000, 4000);
                member = memberInt;
            }
            else
            {
                var memberList = new List<Int32>();
                member = memberList;
                Random rand = new Random();
                memberList.Add(rand.Next(0, 10));
                memberList.Add(rand.Next(0, 10));
                memberList.Add(rand.Next(0, 10));
                memberList.Add(rand.Next(0, 10));
            }
        }

        public void PrintWithIs()
        {
            if (member is String)
            {
                Console.WriteLine("member is String: {0}", member);
            }
            else if (member is Int32)
            {
                Console.WriteLine("member is Int32: {0}", member);
            }
            else if (member is List<Int32>)
            {
                var memberList = member as List<Int32>;
                String elements = "";
                memberList.ForEach(x => elements += x + ", ");
                Console.WriteLine("member is List<Int32>: {0}", elements);
            }
            else
            {
                Console.WriteLine("else...");
            }
        }

        public void PrintWithCast()
        {
            var memberStr = member as String;
            var memberInt = member as Int32?;
            var memberList = member as List<Int32>;

            if (memberStr != null)
            {
                Console.WriteLine("member is String: {0}", memberStr);
            }
            else if (memberInt != null)
            {
                Console.WriteLine("member is Int32: {0}", memberInt);
            }
            else if (memberList != null)
            {
                String elements = "";
                memberList.ForEach(x => elements += x + ", ");
                Console.WriteLine("member is List<Int32>: {0}", elements);
            }
            else
            {
                Console.WriteLine("else...");
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello.");

            List<Foo> foos = new List<Foo>();

            foos.Add(new Foo("str"));
            foos.Add(new Foo("int"));
            foos.Add(new Foo("list"));

            Console.WriteLine("---------------- print with is");
            foreach (var foo in foos)
                foo.PrintWithIs();

            Console.WriteLine("---------------- print with cast");
            foreach (var foo in foos)
                foo.PrintWithCast();

            Console.WriteLine("---------------- reverse and serialize");
            foos.Reverse();
            var jsonString = JsonSerializer.Serialize(foos);
            File.WriteAllText("ser.json", jsonString);

            Console.WriteLine("---------------- deserialize and print with is");
            var rawString = File.ReadAllText("ser.json");
            var newFoos = JsonSerializer.Deserialize<List<Foo>>(rawString);
            foreach (var foo in newFoos)
                foo.PrintWithIs();
            {

            }
        }
    }
}
