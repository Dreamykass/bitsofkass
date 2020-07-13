using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace compare_bookmarks
{
    class Compare
    {
        public static void Comp(List<KeyValuePair<String, List<String>>> links_kpv_list)
        {
            Console.WriteLine("Comparing lists...");

            foreach (var links_collection in links_kpv_list)
            {
                var missing_links = new List<string>();

                foreach (var other_collection in links_kpv_list)
                {
                    if (links_collection.Key == other_collection.Key)
                        continue;

                    var found_missing = new List<string>(other_collection.Value.Except(links_collection.Value).ToArray());
                    Console.WriteLine("{0,20} misses from {1, -20}: {2}",
                        links_collection.Key, other_collection.Key, found_missing.Count);

                    missing_links.InsertRange(0, found_missing);
                }

                File.WriteAllLines("bookmark-output/missing-from-" + links_collection.Key, missing_links.ToArray());
            }
        }
    }
}
