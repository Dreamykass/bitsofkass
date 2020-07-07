using System;
using System.Collections.Generic;
using System.Text;

namespace dir_nice_clone
{
	class Terminal
	{
		public static void Reset()
		{
			Console.ResetColor();
		}

		public class Red
		{
			public static void Write(string str)
			{
				Console.ForegroundColor = ConsoleColor.Red;
				Console.Write(str);
			}

			public static void Line(string str)
			{
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine(str);
			}
		}

		public class Yellow
		{
			public static void Write(string str)
			{
				Console.ForegroundColor = ConsoleColor.Yellow;
				Console.Write(str);
			}

			public static void Line(string str)
			{
				Console.ForegroundColor = ConsoleColor.Yellow;
				Console.WriteLine(str);
			}
		}

		public class Fore
		{
			public static void Write(string str)
			{
				Console.ResetColor();
				Console.Write(str);
			}

			public static void Line(string str)
			{
				Console.ResetColor();
				Console.WriteLine(str);
			}
		}

		public class Green
		{
			public static void Write(string str)
			{
				Console.ForegroundColor = ConsoleColor.Green;
				Console.Write(str);
			}

			public static void Line(string str)
			{
				Console.ForegroundColor = ConsoleColor.Green;
				Console.WriteLine(str);
			}
		}

		public class Magenta
		{
			public static void Write(string str)
			{
				Console.ForegroundColor = ConsoleColor.Magenta;
				Console.Write(str);
			}

			public static void Line(string str)
			{
				Console.ForegroundColor = ConsoleColor.Magenta;
				Console.WriteLine(str);
			}
		}
	}
}
