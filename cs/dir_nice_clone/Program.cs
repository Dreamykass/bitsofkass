using System;
using System.Collections.Generic;

namespace dir_nice_clone
{
    class Program
    {
        static void Main(string[] args)
        {
            string dirSource = "";
            string dirTarget = "";
            List<string> logs = new List<string>();

            try
            {
                Terminal.Yellow.Line("Received this many args: " + args.Length);

                if (args.Length == 0)
                {
                    Terminal.Yellow.Line("Usage: ");
                    Terminal.Yellow.Line("  .app.exe <source-directory> <target-directory>");
                    Terminal.Yellow.Line("Goodbye.");
                    Terminal.Reset();
                    return;
                }

                if (args.Length != 2)
                    throw new Exception("Invalid number of arguments!");

                dirSource = args[0];
                dirTarget = args[1];

                Terminal.Yellow.Write("Source directory: ");
                Terminal.Fore.Line(dirSource);
                Terminal.Yellow.Write("Target directory: ");
                Terminal.Fore.Line(dirTarget);

                // ############################################################

                RecreatingTree.RecreateTree(dirSource, dirTarget, logs);

                ReverseDirDeleting.ReverseDirDelete(dirSource, dirTarget, logs);

                ReverseFilDeleting.ReverseFilDelete(dirSource, dirTarget, logs);

                var count = TraverseCounting.TraverseCount(dirSource, dirTarget, logs);

                TraversingProper.TraverseProper(dirSource, dirTarget, count, logs);

                // ############################################################

                Terminal.Green.Line("");
                Terminal.Green.Line("Terminated successfully!");

                Terminal.Yellow.Write("  Source directory: ");
                Terminal.Fore.Line(dirSource);
                Terminal.Yellow.Write("  Target directory: ");
                Terminal.Fore.Line(dirTarget);

                Terminal.Green.Line("Logs and messages:");
                foreach (var log in logs)
                    Terminal.Fore.Line("  " + log);
                Terminal.Green.Line("Goodbye.");
                Terminal.Green.Line("");
            }
            catch (Exception e)
            {
                Terminal.Red.Line("");
                Terminal.Red.Line("Exception!");
                Terminal.Red.Line("Message: " + e.Message);

                Terminal.Yellow.Write("  Source directory: ");
                Terminal.Fore.Line(dirSource);
                Terminal.Yellow.Write("  Target directory: ");
                Terminal.Fore.Line(dirTarget);

                Terminal.Red.Line("Logs and messages:");
                foreach (var log in logs)
                    Terminal.Fore.Line("  " + log);
                Terminal.Red.Line("Goodbye.");
                Terminal.Red.Line("");
            }

            Terminal.Reset();
        }
    }
}
