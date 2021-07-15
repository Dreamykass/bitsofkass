#ifndef OPTICAL_JSON_OBJECT_H
#define OPTICAL_JSON_OBJECT_H

#include "distortion.h"
#include "opencv2/opencv.hpp"

namespace {
    QJsonObject positionXYkXY() {
        QJsonObject json;
        json["positionXMin"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Position X Min %" },
                                       { "value", 50 },
                                       { "min", 0 },
                                       { "max", 100 } };
        json["positionXMax"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Position X Max %" },
                                       { "value", 50 },
                                       { "min", 0 },
                                       { "max", 100 } };
        json["positionYMin"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Position Y Min %" },
                                       { "value", 50 },
                                       { "min", 0 },
                                       { "max", 100 } };
        json["positionYMax"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Position Y Max %" },
                                       { "value", 50 },
                                       { "min", 0 },
                                       { "max", 100 } };
        json["kXMin"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Force in X Min" },
                                       { "value", 10 },
                                       { "min", 1 },
                                       { "max", 1000 } };
        json["kXMax"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Force in X Max" },
                                       { "value", 10 },
                                       { "min", 1 },
                                       { "max", 1000 } };
        json["kYMin"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Force in Y Min" },
                                       { "value", 10 },
                                       { "min", 1 },
                                       { "max", 1000 } };
        json["kYMaxs"] = QJsonObject{ { "type", "double spin box" },
                                       { "name", "Force in Y Max" },
                                       { "value", 10 },
                                       { "min", 1 },
                                       { "max", 1000 } };
        return json;
    }
}
#endif // OPTICAL_JSON_OBJECT_H
