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

vector<Route> CGraph::findVisitRoute(int startPoint) {
    vector<Route> routeList;
    int *route = new int[m_VexNum];
    memset(route, 0, sizeof(route));
    bool *bVisited = new bool[m_VexNum];
    for (int i = 0; i < m_VexNum; ++i) {
        bVisited[i]= false;
    }
    memset(bVisited,false, sizeof(bVisited));
    dfs(startPoint, bVisited, 0, route, routeList);
    return routeList;
}

void CGraph::dfs(int vex, bool *bVisited, int index, int *route, vector<Route> &routeList) {
    bVisited[vex] = true;
    route[index++] = vex;
    bool allVisited = true;
    for (int i = 0; i < m_VexNum; ++i) {
        if (!bVisited[i]) {
            allVisited = false;
            break;
        }
    }
    if (allVisited) {
        //保存路径
        Route r(m_VexNum);
        for (int i = 0; i < m_VexNum; ++i) {
            r.vexs[i] = route[i];
        }
        routeList.push_back(r);
    } else {
        for (int i = 0; i < m_VexNum; ++i) {
            if (m_AdjMatrix[vex][i] >= INF_LEN || vex == i || bVisited[i])
                continue;
            dfs(i, bVisited, index, route, routeList);
            bVisited[i]= false;
        }
    }
}







