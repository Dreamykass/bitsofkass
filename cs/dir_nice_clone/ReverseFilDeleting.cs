using System;
using System.Collections.Generic;
using System.IO;

namespace dir_nice_clone
{
	class ReverseFilDeleting
	{
		public static void ReverseFilDelete(string dirSource, string dirTarget, List<string> logs)
		{
			Terminal.Fore.Line("");
			Terminal.Yellow.Line("Reverse deleting redundant files in the target tree...");

			long count = 0;

			if (!Directory.Exists(dirSource))
				throw new Exception("Source directory doesn't exist!");
			if (!Directory.Exists(dirTarget))
				throw new Exception("Target directory doesn't exist!");

			ProcessDirectory(dirTarget, dirSource, dirTarget, ref count);
			Terminal.Green.Line("\n\nNicely deleted redundant files.");
			Terminal.Green.Line("File deletions: " + count);
			logs.Add(string.Format("{0,30}{1}", "File deletions: ", count));
		}

		private static void ProcessDirectory(string currentDir, string dirSource, string dirTarget, ref long count)
		{
			// Recurse into subdirectories.
			if (Directory.Exists(currentDir))
			{
				string[] subdirectoryEntries = Directory.GetDirectories(currentDir);
				foreach (string subdirectory in subdirectoryEntries)
					ProcessDirectory(subdirectory, dirSource, dirTarget, ref count);
			}

			// Process the files in this directory.
			string[] fileEntries = Directory.GetFiles(currentDir);
			foreach (string fileName in fileEntries)
			{
				HandleFile(fileName, dirSource, dirTarget, ref count);
			}
		}

		private static void HandleFile(string path, string dirSource, string dirTarget, ref long count)
		{
			string localPath = path.Remove(0, dirTarget.Length);
			string pathInTarget = dirTarget + localPath;
			string pathInSource = dirSource + localPath;

			if (File.Exists(pathInSource))
			{
				Terminal.Yellow.Write("[] No action: ");
				Terminal.Fore.Line(pathInTarget);
			}
			else
			{
				Terminal.Red.Write("[] File deleted at: ");
				Terminal.Fore.Line(pathInTarget);
				File.Delete(pathInTarget);
				count++;
			}

		}


	}
}
