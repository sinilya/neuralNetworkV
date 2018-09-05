#ifndef PICTUREDATA_H
#define PICTUREDATA_H

#include <QVector>
#include <QDebug>
class pictureData
{
public:
    pictureData(int dataSize);
    void insertElem(double value, int pos);
    std::vector<double> getData();
private:
    QVector<double> data;
};

#endif // PICTUREDATA_H
