//
// Created by tlh on 2016/5/4.
//

#include <cstring>
#include <iostream>
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
        bVisited[i] = false;
    }
    memset(bVisited, false, sizeof(bVisited));
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
            bVisited[i] = false;
        }
    }
}

void CGraph::findShortestRoute(int start, int end) {
    Route route(m_VexNum);
    int *dis = new int[m_VexNum];
    int *way = new int[m_VexNum];
    int *book = new int[m_VexNum];
    for (int i = 0; i < m_VexNum; i++) {
        dis[i] = m_AdjMatrix[start][i];
        book[i] = 0;
        way[i] = start;
    }
    book[start] = 1;
    //Dijkstra算法的核心代码
    for (int i = 0; i < m_VexNum; i++) {
        //找出离源点最近的点
        int min = INF_LEN;
        int min_point = start;
        for (int j = 0; j < m_VexNum; j++) {
            if (book[j] == 0 && dis[j] < min) {
                min = dis[j];
                min_point = j;
            }
        }
        //start到end的最短路径已经找到
        if (min_point == end) {
            break;
        }
        book[min_point] = 1;
        //遍历min_point的邻接节点，更新dis数组和way数组
        for (int v = 0; v < m_VexNum; v++) {
            if (m_AdjMatrix[min_point][v] < INF_LEN) {
                if (dis[v] > dis[min_point] + m_AdjMatrix[min_point][v]) {
                    dis[v] = dis[min_point] + m_AdjMatrix[min_point][v];
                    way[v] = min_point;
                }
            }
        }
    }
    //简易栈
    int result[100];
    int index = 0;
    int temp = end;
    result[index++] = temp;
    while (temp != start) {
        temp = way[temp];
        result[index++] = temp;
    }
    for (int k = index - 1; k > 0; --k) {
        cout << spots[result[k]]->name << "->";
    }
    cout << spots[result[0]]->name << endl;
    cout << "Shortest distance is:" << dis[end] << endl;
}

void CGraph::designPath() {
    int len = 0;
    Path *paths = findMinTreeWithPrim(len);
    for (int i = 0; i < m_VexNum - 1; ++i) {
        cout << spots[paths[i].point1]->name << "--" << spots[paths[i].point2]->name << "  " << paths[i].length << endl;
    }
    cout << "total length:" << len << endl;
}

Path *CGraph::findMinTreeWithPrim(int &len) {
    Path *paths = new Path[m_VexNum - 1];
    int *distanceToTree = new int[m_VexNum];
    Path *edgeToTree = new Path[m_VexNum];
    int *book = new int[m_VexNum];//记录顶点是否被添加到树中
    //初始化
    for (int i = 0; i < m_VexNum; ++i) {
        distanceToTree[i] = m_AdjMatrix[0][i];
        edgeToTree[i].point1 = i;
        edgeToTree[i].point2 = 0;
        edgeToTree[i].length = distanceToTree[i];
        book[i] = 0;
    }
    book[0] = 1;
    int count = 1;
    //prim算法核心代码
    while (count != m_VexNum) {
        int min = INF_LEN;
        int vexToTree = 0;
        //从1开始可以了，因为0号顶点一开始就已经添加树中
        for (int i = 1; i < m_VexNum; ++i) {
            if (book[i] == 0 && min > distanceToTree[i]) {
                min = distanceToTree[i];
                vexToTree = i;
            }
        }
        len += min;
        book[vexToTree] = 1;
        paths[count - 1].point1 = edgeToTree[vexToTree].point1;
        paths[count - 1].point2 = edgeToTree[vexToTree].point2;
        paths[count - 1].length = edgeToTree[vexToTree].length;
        //遍历所有vexToTree的邻接节点，更新数组distanceToTree
        for (int i = 0; i < m_VexNum; ++i) {
            if (book[i] == 0 && m_AdjMatrix[vexToTree][i] < distanceToTree[i]) {
                distanceToTree[i] = m_AdjMatrix[vexToTree][i];
                edgeToTree[i].point2 = vexToTree;
                edgeToTree[i].length = m_AdjMatrix[vexToTree][i];
            }
        }
        count++;
    }
    return paths;
}













