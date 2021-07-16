#ifndef NOISE_JSON_OBJECT_H
#define NOISE_JSON_OBJECT_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace {
    QJsonObject offsetMinMaxArguments() {
        QJsonObject json;
        json["offsetMin"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Offset Min" },
                                       { "value", 40 },
                                       { "min", 0 },
                                       { "max", 150 } };
        json["offsetMax"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Offset Max" },
                                       { "value", 40 },
                                       { "min", 0 },
                                       { "max", 150 } };
        return json;
    }
    QJsonObject msigmapMinpMaxArguments() {
        QJsonObject json;
        json["m"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "m" },
                                       { "value", 0 },
                                       { "min", 0 },
                                       { "max", 255 } };
        json["sigma"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "sigma" },
                                       { "value", 255 },
                                       { "min", 0 },
                                       { "max", 255 } };
        json["powerMin"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Power Min" },
                                       { "value", 0.2 },
                                       { "min", 0 },
                                       { "max", 1 } };
        json["powerMax"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Power Max" },
                                       { "value", 0.2 },
                                       { "min", 0 },
                                       { "max", 1 } };
        return json;
    }
}
#endif // NOISE_JSON_OBJECT_H
