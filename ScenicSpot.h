//
// Created by tlh on 2016/5/4.
//

#ifndef GRAPHANDSCENERY_SCENICSPOT_H
#define GRAPHANDSCENERY_SCENICSPOT_H
#include <string>
using namespace std;
class ScenicSpot {
public:
    int id;
    string name;
    string introduce;
    ScenicSpot(int id, const string &name, const string &introduce) : id(id), name(name), introduce(introduce) { }
};
#endif //GRAPHANDSCENERY_SCENICSPOT_H
