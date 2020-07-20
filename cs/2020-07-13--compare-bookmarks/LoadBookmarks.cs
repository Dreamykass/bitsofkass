using System;
using System.Collections.Generic;
using System.IO;

namespace compare_bookmarks
{
    class LoadBookmarks
    {
        public static List<KeyValuePair<String, String>> Load()
        {
            var bookmarks = new List<KeyValuePair<String, String>>();

            if (!File.Exists("compare-bookmarks.csproj"))
                throw new Exception("compare_bookmarks.csproj does not exist here "
                + "- current directory: " + Directory.GetCurrentDirectory());
            else
            {
                Directory.CreateDirectory("bookmark-input");
                Directory.CreateDirectory("bookmark-output");
            }

            var files = Directory.GetFiles("bookmark-input");
            Console.WriteLine("Loaded this many files: " + files.Length);
            if (files.Length == 0)
                throw new Exception("Loaded zero files from bookmark-input");


            foreach (var file in files)
                bookmarks.Add(new KeyValuePair<string, string>
                (
                    file.Remove(0, new String("bookmark-input/").Length),
                    File.ReadAllText(file))
                );

            Console.WriteLine("Loaded this many bookmarks files/strings: " + bookmarks.Count);
            foreach (var bookmark in bookmarks)
                Console.WriteLine("{0,20}, length: {1}", bookmark.Key, bookmark.Value.Length);

            return bookmarks;
        }
    }
}
