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
        system("cls");//����ˢ��
        cout << "========������Ϣ����ϵͳ========" << endl;
        cout << "1.������������ͼ" << endl;
        cout << "2.��ѯ������Ϣ" << endl;
        cout << "3.���ξ��㵼��" << endl;
        cout << "4.�������·��" << endl;
        cout << "5.�����·�滮" << endl;
        cout << "0.�˳�" << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                createGraph();
                cout << "��������ͼ�ɹ���" << endl;
                cout << "������Ŀ��" << graph->getVexNum() << endl;
                cout << "========����========" << endl;
                map<int, ScenicSpot *> spots = graph->getSpots();
                for (int i = 0; i < spots.size(); ++i) {
                    cout << i << "--" << spots.at(i)->name << endl;
                }
                cout << "==========��==========" << endl;
                vector<Path *> paths = graph->getPaths();
                for (int i = 0; i < paths.size(); ++i) {
                    Path *p = paths.at(i);
                    cout << "(" << p->point1 << "," << p->point2 << ") " << p->length << endl;
                }
            }
                break;
            case 2: {
                if (graph==NULL) {
                    cout<<"��ľ���ͼ��û������~"<<endl;
                    break;
                }
                cout << "========����========" << endl;
                map<int, ScenicSpot *> spots = graph->getSpots();
                for (int i = 0; i < spots.size(); ++i) {
                    cout << i << "--" << spots.at(i)->name << endl;
                }
                cout << "��������Ҫ��ѯ�ľ����ţ�";
                int num;
                cin >> num;
                cout << spots.at(num)->id << endl;
                cout << spots.at(num)->name << endl;
                cout << spots.at(num)->introduce << endl;
                cout << "=============�ܱ߾���============" << endl;
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
        cout << "�����������..." << endl;
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