using System;
using System.Collections.Generic;
using System.IO;

namespace dir_nice_clone
{
	class RecreatingTree
	{
		public static void RecreateTree(string dirSource, string dirTarget, List<string> logs)
		{
			Terminal.Fore.Line("");
			Terminal.Yellow.Line("Recreating the tree...");

			long count = 0;

			if (!Directory.Exists(dirSource))
			{
				throw new Exception("Source directory doesn't exist!");
			}
			if (!Directory.Exists(dirTarget))
			{
				Terminal.Red.Line("Target directory doesn't exist. Creating it.");
				Directory.CreateDirectory(dirTarget);
			}

			ProcessDirectory(dirSource, dirSource, dirTarget, ref count);
			Terminal.Green.Line("\n\nNicely recreated the tree.");
			Terminal.Green.Line("Directory creations: " + count);
			logs.Add(string.Format("{0,30}{1}", "Directory creations: ", count));
		}

		private static void ProcessDirectory(string currentDir, string dirSource, string dirTarget, ref long count)
		{
			// Handle this directory.
			HandleDirectory(currentDir, dirSource, dirTarget, ref count);

			// Recurse into subdirectories.
			string[] subdirectoryEntries = Directory.GetDirectories(currentDir);
			foreach (string subdirectory in subdirectoryEntries)
				ProcessDirectory(subdirectory, dirSource, dirTarget, ref count);
		}

		private static void HandleDirectory(string path, string dirSource, string dirTarget, ref long count)
		{
			string localPath = path.Remove(0, dirSource.Length);
			string newPath = dirTarget + localPath;

			if (Directory.Exists(newPath))
			{
				Terminal.Yellow.Write("[] No action: ");
				Terminal.Fore.Line(newPath);
				Directory.CreateDirectory(newPath);
			}
			else
			{
				Terminal.Green.Write("[] Directory created at: ");
				Terminal.Fore.Line(newPath);
				Directory.CreateDirectory(newPath);
				count++;
			}

		}

	}
}
