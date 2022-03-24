#ifndef BASEDATA_H
#define BASEDATA_H

#include <QString>

//基本数据头文件
struct WindData//风力数据
{
    int CompassDegrees;//指南针度数
    QString Direction;//风向
    float Speed;//风速
};

struct BaseData//基本数据
{
    QString COG;//COG
    QString SOG;//SOG
    float HeadingAngle;//艏向角
    QString Latitude;//纬度
    QString longitude;//经度

    //风力数据
    WindData windData;
    //水深
    double waterDepth;

};

#endif // BASEDATA_H
