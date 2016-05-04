//
// Created by tlh on 2016/5/4.
//

#include <cstring>
#include "CGraph.h"

CGraph::CGraph(int num) {
    m_VexNum = num;
    m_AdjMatrix = new int *[num];
    for (int i = 0; i < num; ++i) {
        m_AdjMatrix[i] = new int[num];
    }
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < num; ++j) {
            if (i == j) {
                m_AdjMatrix[i][j] = 0;
                continue;
            }
            m_AdjMatrix[i][j] = INF_LEN;
        }
    }
}

void CGraph::build() {
    if (spots.empty() || paths.empty())
        return;
    for (int i = 0; i < paths.size(); ++i) {
        Path *p = paths.at(i);
        //检查是否越界
        if (p->point1 >= m_VexNum || p->point2 >= m_VexNum)
            continue;
        m_AdjMatrix[p->point1][p->point2] = p->length;
        m_AdjMatrix[p->point2][p->point1] = p->length;
    }
}



