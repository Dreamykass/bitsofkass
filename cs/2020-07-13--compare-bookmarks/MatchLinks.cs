using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Linq;

namespace compare_bookmarks
{
    class MatchLinks
    {
        public static List<KeyValuePair<String, List<String>>> Match(List<KeyValuePair<String, String>> bookmarks)
        {
            Console.WriteLine("Matching links from strings...");

            var links = new List<KeyValuePair<String, List<String>>>();
            // Regex regex = new Regex(@"/^([^:]+):\\/\\/([-\\w._]+)(\\/[-\\w._]\\?(.+)?)?$/ig");
            Regex regex = new Regex(@"\b(?:https?://|www\.)\S+\b");

            foreach (var bookmark in bookmarks)
            {
                var matches = regex.Matches(bookmark.Value);

                links.Add(new KeyValuePair<string, List<string>>
                (
                    bookmark.Key,
                    new List<String>(matches.OfType<Match>().Select(m => m.Value).ToArray())
                ));

                Console.WriteLine("{0, 20}, found this many links: {1}", bookmark.Key, matches.Count);
            }

            return links;
        }
    }
}
