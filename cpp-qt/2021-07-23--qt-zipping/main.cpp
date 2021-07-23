#include <QCoreApplication>

//#include "miniz.h"
#include "zip.h"
#include <cstddef>
#include <fstream>
#include <vector>

std::vector<uint8_t> readFile(const char *filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<uint8_t> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());

    return vec;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    struct zip_t *zip = zip_open("W:/foo.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    {
        zip_entry_open(zip, "foo-1.txt");
        {
            const char *buf = "Some data here...\0";
            zip_entry_write(zip, buf, strlen(buf));
        }
        zip_entry_close(zip);

        zip_entry_open(zip, "foo-2.txt");
        {
            // merge 3 files into one entry and compress them on-the-fly.
            zip_entry_fwrite(zip, "foo-2.1.txt");
            zip_entry_fwrite(zip, "foo-2.2.txt");
            zip_entry_fwrite(zip, "foo-2.3.txt");
        }
        zip_entry_close(zip);

        zip_entry_open(zip, "a.jpeg");
        {
            auto jpeg = readFile("W:/a.jpeg");
            zip_entry_write(zip, jpeg.data(), jpeg.size());
        }
        zip_entry_close(zip);

        zip_entry_open(zip, "foo.zip");
        {
            auto jpeg = readFile("W:/foo.zip");
            zip_entry_write(zip, jpeg.data(), jpeg.size());
        }
        zip_entry_close(zip);
    }
    zip_close(zip);
}
