#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "ScenicSpot.h"
#include "Path.h"
#include "CGraph.h"

using namespace std;

bool bRunning = true;
map<int, ScenicSpot *> spots;
vector<Path *> paths;
CGraph *graph;
int choice;

void createGraph();

int main() {
    while (bRunning) {
        system("cls");//清屏刷新
        cout << "========景点信息管理系统========" << endl;
        cout << "1.创建景区景点图" << endl;
        cout << "2.查询景点信息" << endl;
        cout << "3.旅游景点导航" << endl;
        cout << "4.搜索最短路径" << endl;
        cout << "5.铺设电路规划" << endl;
        cout << "0.退出" << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                createGraph();
                cout << "创建景点图成功！" << endl;
                cout << "景点数目：" << graph->getVexNum() << endl;
                cout << "========顶点========" << endl;
                map<int, ScenicSpot *> spots = graph->getSpots();
                for (int i = 0; i < spots.size(); ++i) {
                    cout << i << "--" << spots.at(i)->name << endl;
                }
                cout << "==========边==========" << endl;
                vector<Path *> paths = graph->getPaths();
                for (int i = 0; i < paths.size(); ++i) {
                    Path *p = paths.at(i);
                    cout << "(" << p->point1 << "," << p->point2 << ") " << p->length << endl;
                }
            }
                break;
            case 2: {
                if (graph==NULL) {
                    cout<<"你的景点图还没创建呢~"<<endl;
                    break;
                }
                cout << "========顶点========" << endl;
                map<int, ScenicSpot *> spots = graph->getSpots();
                for (int i = 0; i < spots.size(); ++i) {
                    cout << i << "--" << spots.at(i)->name << endl;
                }
                cout << "请输入想要查询的景点编号：";
                int num;
                cin >> num;
                cout << spots.at(num)->id << endl;
                cout << spots.at(num)->name << endl;
                cout << spots.at(num)->introduce << endl;
                cout << "=============周边景区============" << endl;
                int **matrix = graph->getMatrix();
                for (int i = 0; i < graph->getVexNum(); ++i) {
                    if (matrix[num][i] == CGraph::INF_LEN || i == num)
                        continue;
                    cout << spots.at(num)->name<<"->"<<spots[i]->name<<" "<<matrix[num][i]<<"m"<<endl;
                }
            }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                bRunning = false;
                break;
        }
        cout << "按任意键继续..." << endl;
        getchar();
        getchar();
    }
    return 0;
}

void createGraph() {
    ifstream fin_Vex;
    fin_Vex.open("C:\\Users\\tlh\\ClionProjects\\GraphAndScenery\\Vex.txt", ios_base::in);
    FILE *fin_Edge = NULL;
    fin_Edge = fopen("C:\\Users\\tlh\\ClionProjects\\GraphAndScenery\\Edge.txt", "r");
    if (fin_Edge == NULL || !fin_Vex.is_open()) {
        cout << "file not found" << endl;
    }
    string num;
    getline(fin_Vex, num);
    int pointCount = atoi(num.c_str());
    int i = 0;
    while (fin_Vex.good() && i <= pointCount) {
        string id;
        getline(fin_Vex, id);
        string name;
        getline(fin_Vex, name);
        string introduce;
        getline(fin_Vex, introduce);
        ScenicSpot *spot = new ScenicSpot(atoi(id.c_str()), name, introduce);
        spots.insert(map<int, ScenicSpot *>::value_type(spot->id, spot));
        i++;
    }
    while (!feof(fin_Edge)) {
        int point1;
        int point2;
        int length = 0;
        fscanf(fin_Edge, "%d\t%d\t%d\n", &point1, &point2, &length);
        paths.push_back(new Path(point1, point2, length));
    }
    graph = new CGraph(pointCount);
    graph->setPaths(paths);
    graph->setSpots(spots);
    graph->build();
}