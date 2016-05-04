//
// Created by tlh on 2016/5/4.
//

#ifndef GRAPHANDSCENERY_PATH_H
#define GRAPHANDSCENERY_PATH_H
#include <string>
using namespace std;
struct Path {
    int point1;
    int point2;
    int length;
    Path(int point1, int point2, int length) : point1(point1), point2(point2), length(length) { }
};
struct Route {
    int *vexs;
    Route(int vexCount) {
        vexs = new int[vexCount];
    }
};
#endif //GRAPHANDSCENERY_PATH_H
