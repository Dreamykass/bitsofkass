using System;
using System.Collections.Generic;
using System.IO;

namespace dir_nice_clone
{
	class ReverseDirDeleting
	{
		public static void ReverseDirDelete(string dirSource, string dirTarget, List<string> logs)
		{
			Terminal.Fore.Line("");
			Terminal.Yellow.Line("Reverse deleting redundant directories in the target tree...");

			long count = 0;

			if (!Directory.Exists(dirSource))
				throw new Exception("Source directory doesn't exist!");
			if (!Directory.Exists(dirTarget))
				throw new Exception("Target directory doesn't exist!");

			ProcessDirectory(dirTarget, dirSource, dirTarget, ref count);
			Terminal.Green.Line("\n\nNicely deleted redundant directories.");
			Terminal.Green.Line("Directory deletions: " + count);
			logs.Add(string.Format("{0,30}{1}", "Directory deletions: ", count));
		}

		private static void ProcessDirectory(string currentDir, string dirSource, string dirTarget, ref long count)
		{
			// Handle this directory.
			HandleDirectory(currentDir, dirSource, dirTarget, ref count);

			// Recurse into subdirectories.
			if (Directory.Exists(currentDir))
			{
				string[] subdirectoryEntries = Directory.GetDirectories(currentDir);
				foreach (string subdirectory in subdirectoryEntries)
					ProcessDirectory(subdirectory, dirSource, dirTarget, ref count);
			}
		}

		private static void HandleDirectory(string path, string dirSource, string dirTarget, ref long count)
		{
			string localPath = path.Remove(0, dirTarget.Length);
			string pathInTarget = dirTarget + localPath;
			string pathInSource = dirSource + localPath;

			if (Directory.Exists(pathInSource))
			{
				Terminal.Yellow.Write("[] No action: ");
				Terminal.Fore.Line(pathInTarget);
			}
			else
			{
				Terminal.Red.Write("[] Directory deleted at: ");
				Terminal.Fore.Line(pathInTarget);
				Directory.Delete(pathInTarget, true);
				count++;
			}

		}
	}
}
