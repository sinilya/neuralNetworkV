#include "picturedata.h"

pictureData::pictureData(int dataSize)
{
    data.insert(0, dataSize, 0);
}

void pictureData::insertElem(double value, int pos){
    data[pos] = value;
}

std::vector<double> pictureData::getData(){
    return data.toStdVector();
}
