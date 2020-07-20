using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace dir_nice_clone
{
	class TraversingProper
	{
		private class Counts
		{
			public long countTotal = 0;
			public long countCurrent = 0;

			public long noaction = 0;
			public long copied = 0;
			public long overwritten = 0;
		}

		public static void TraverseProper(string dirSource, string dirTarget, long countTotal, List<string> logs)
		{
			Terminal.Fore.Line("");
			Terminal.Yellow.Line("Traversing proper...");

			Counts count = new Counts();
			count.countCurrent = 0;
			count.countTotal = countTotal;

			if (!Directory.Exists(dirSource))
				throw new Exception("Source directory doesn't exist!");
			if (!Directory.Exists(dirTarget))
				throw new Exception("Target directory doesn't exist!");

			ProcessDirectory(dirSource, dirSource, dirTarget, ref count);
			Terminal.Green.Line("\n\nDone traversing!");
			Terminal.Green.Line("File copies:       " + count.copied);
			Terminal.Green.Line("File overwrites:   " + count.overwritten);
			Terminal.Green.Line("File no actions:    " + count.noaction);
			logs.Add(string.Format("{0,30}{1}", "File copies: ", count.copied));
			logs.Add(string.Format("{0,30}{1}", "File overwrites: ", count.overwritten));
			logs.Add(string.Format("{0,30}{1}", "File no actions: ", count.noaction));
		}

		private static void ProcessDirectory(string currentDir, string dirSource, string dirTarget, ref Counts count)
		{
			// Print current directory.
			HandleDirectory(currentDir, dirSource, dirTarget, ref count);

			// Process the files in this directory.
			string[] fileEntries = Directory.GetFiles(currentDir);
			foreach (string fileName in fileEntries)
			{
				HandleFile(fileName, dirSource, dirTarget, ref count);
				count.countCurrent += 1;
			}

			// Recurse into subdirectories.
			string[] subdirectoryEntries = Directory.GetDirectories(currentDir);
			foreach (string subdirectory in subdirectoryEntries)
				ProcessDirectory(subdirectory, dirSource, dirTarget, ref count);
		}

		private static void HandleDirectory(string path, string dirSource, string dirTarget, ref Counts count)
		{
			string localPath = path.Remove(0, dirSource.Length);
			string oldPath = path;

			Terminal.Yellow.Write(string.Format("[{0,8}/{1} ] ", "dir", count.countTotal));
			Terminal.Yellow.Write("Directory at: ");
			Terminal.Yellow.Line(oldPath);
		}

		private static void HandleFile(string path, string dirSource, string dirTarget, ref Counts count)
		{
			string localPath = path.Remove(0, dirSource.Length);
			string oldPath = path;
			string newPath = dirTarget + localPath;

			if (!File.Exists(newPath))
			{
				Terminal.Green.Write(string.Format("[{0,8}/{1} ] ", count.countCurrent, count.countTotal));
				Terminal.Green.Write("Copying: ");
				Terminal.Fore.Line(localPath);
				File.Copy(oldPath, newPath);
				count.copied++;
			}
			else
			{
				var oldLength = new FileInfo(oldPath).Length;
				var newLength = new FileInfo(newPath).Length;

				if (oldLength.Equals(newLength))
				{
					Terminal.Yellow.Write(string.Format("[{0,8}/{1} ] ", count.countCurrent, count.countTotal));
					Terminal.Yellow.Write("No action: ");
					Terminal.Fore.Line(localPath);
					count.noaction++;
				}
				else
				{
					Terminal.Magenta.Write(string.Format("[{0,8}/{1} ] ", count.countCurrent, count.countTotal));
					Terminal.Magenta.Write("Overwriting: ");
					Terminal.Fore.Line(localPath);
					File.Copy(oldPath, newPath, true);
					count.overwritten++;
				}
			}

		}
	}
}
