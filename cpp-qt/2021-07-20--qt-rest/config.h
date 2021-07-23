#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

struct Config
{
    QString url;
    QString pathDatasetCreate;
    QString authorization;
};

Config loadConfig();

#endif // CONFIG_H
