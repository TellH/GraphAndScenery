//
// Created by tlh on 2016/5/4.
//

#ifndef GRAPHANDSCENERY_CGRAPH_H
#define GRAPHANDSCENERY_CGRAPH_H


#include <vector>
#include <map>
#include "ScenicSpot.h"
#include "Path.h"

class CGraph {
private:
    int** m_AdjMatrix;
    map<int, ScenicSpot *> spots;
    vector<Path *> paths;
    int m_VexNum;

public:
    static const int INF_LEN=99999999;
    CGraph(int num);

    int getVexNum() const {
        return m_VexNum;
    }

    int** getMatrix(){ return m_AdjMatrix;}

    const vector<Path *> &getPaths() const {
        return paths;
    }

    void setPaths(const vector<Path *> &paths) {
        CGraph::paths = paths;
    }

    const map<int, ScenicSpot *> &getSpots() const {
        return spots;
    }

    void setSpots(const map<int, ScenicSpot *> &spots) {
        CGraph::spots = spots;
    }

    void build();
};


#endif //GRAPHANDSCENERY_CGRAPH_H
