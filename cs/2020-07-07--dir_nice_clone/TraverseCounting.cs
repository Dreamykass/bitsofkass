using System;
using System.Collections.Generic;
using System.IO;

namespace dir_nice_clone
{
	class TraverseCounting
	{
		public static long TraverseCount(string dirSource, string dirTarget, List<string> logs)
		{
			Terminal.Fore.Line("");
			Terminal.Yellow.Line("Counting the files in source...");

			long count = 0;

			if (!Directory.Exists(dirSource))
				throw new Exception("Source directory doesn't exist!");
			if (!Directory.Exists(dirTarget))
				throw new Exception("Target directory doesn't exist!");

			ProcessDirectory(dirSource, dirSource, dirTarget, ref count);
			Terminal.Green.Line("Nicely counted the files in source.");
			Terminal.Green.Line("Found this many files: " + count);
			logs.Add(string.Format("{0,30}{1}", "Found this many files: ", count));

			return count;
		}

		private static void ProcessDirectory(string currentDir, string dirSource, string dirTarget, ref long count)
		{
			// Count the files in this directory.
			string[] fileEntries = Directory.GetFiles(currentDir);
			foreach (string fileName in fileEntries)
				count += 1;

			// Recurse into subdirectories.
			string[] subdirectoryEntries = Directory.GetDirectories(currentDir);
			foreach (string subdirectory in subdirectoryEntries)
				ProcessDirectory(subdirectory, dirSource, dirTarget, ref count);
		}

	}
}
