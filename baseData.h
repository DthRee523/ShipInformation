#ifndef BASEDATA_H
#define BASEDATA_H

#include <string>

using namespace std;

//基本数据头文件
struct WindData//风力数据
{
    int CompassDegrees;//指南针度数
    string Direction;//风向
    float Speed;//风速
};

struct BaseData//基本数据
{
    string COG;//COG
    string SOG;//SOG
    float HeadingAngle;//艏向角
    string Latitude;//纬度
    string longitude;//经度

    //风力数据
    WindData windData;
    //水深
    double waterDepth;

};

#endif // BASEDATA_H
