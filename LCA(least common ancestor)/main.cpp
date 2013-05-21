#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <cmath>

using namespace std;
ifstream in;
fstream out;

bool isBlack (vector <string> color) {
    for (int i=0; i<color.size(); ++i) {
        if (color[i]!="black")
            return false;
    }
    return true;
}
class graph {
private:
    deque < deque <int> > vertex;
public:
    graph (deque < deque <int> > v) {
        vertex=v;
    }
    graph () {
        in.open("input.txt");
        int k;
        in >> k;
        vertex.resize(k+1);
        for (int i=0; i<k; ++i) {
            deque <int> links;
            int a,b;
            in >> a >> b;
            vertex[b].push_back(a);
        }
        //in.close();
    }
    void print () const {
        system ("touch graph.txt");
        out.open("graph.txt");
        out << "digraph G {" << endl;
        this->BFS(true);
        out << "}";
        out.close();
        system("dot graph.txt -o graph.png -T png");
        system ("rm graph.txt");
        system("gwenview graph.png");
    }
    void BFS (bool print=0) const {
        vector <string> color(vertex.size(), "white");
        vector <int> parent (vertex.size(), -1);
        list <int> Q;
        Q.push_front(0);
        while (!Q.empty()) {
            int current = Q.front();
            for (int i=0; i<vertex[current].size(); ++i) {
                if (print)
                    out << current << " -> " << vertex[current][i] << endl;
                //else
                    //cout << current << " -> " <<  vertex[current][i] << endl;
                
                if (color[vertex[current][i]]=="white") {
                    color[vertex[current][i]]="gray";
                    parent[vertex[current][i]]=current;
                    Q.push_back(vertex[current][i]);
                }
            }
            Q.pop_front();
            color[current]="black";
        }
    }
    void DFS_Visit (vector <double> &depth, vector <double> &visit, 
    vector <string> &color, vector <int> &parent,
    int current, int &time, bool print) const {
        color[current]="gray";
        time++;
        for (int i=0; i<vertex[current].size(); ++i) {
            if (print)
                out << current << " -> " <<  vertex[current][i] << endl;
            //else
            //    cout << current << " -> " <<  vertex[current][i] << endl;
            if (color[vertex[current][i]]=="white") {
                parent[vertex[current][i]]=current;
                visit.push_back(vertex[current][i]);
                depth.push_back(time);
                this->DFS_Visit(depth, visit, color, parent, vertex[current][i], time, print);
            }
        }
        color[current]="black";
        visit.push_back(parent[current]);
        time--;
        depth.push_back(time-1);
        return;
    }
    void DFS (vector <double> &depth, vector <double> &visit, bool print=0) const {
        vector <string> color(vertex.size(), "white");
        vector <int> parent(vertex.size(), -1), inTime(vertex.size()), outTime(vertex.size());
        int time=0;
        for (int i=0; i<vertex.size(); ++i) {
            visit.push_back(i);
            depth.push_back(time);
            if (color[i]=="white") {
                this->DFS_Visit(depth, visit, color, parent, i, time, print);
                visit.push_back(i);
                depth.push_back(time);
            }
        }
        for (int i=0; i<vertex.size()+1; ++i) {
            visit.pop_back();
            depth.pop_back();
        }
    }
};
double min (double a, double b) {
    if (a<b) return a;
    else return b;
}
class SegmentTree {
    int sizeArray,n;
    vector <pair <int,int> > request;
    vector <double> array,tree;
public:
    /*SegmentTree (){ //from file
        in.open("input.txt");
        in >> sizeArray;
        for (int i=0; i<sizeArray; ++i) {
            double tmp;
            in >> tmp;
            array.push_back(tmp);
        }
        int tmp;
        in >> tmp;
        for (int i=0; i<tmp; ++i) {
            pair <int, int> tmp2;
            in >> tmp2.first >> tmp2.second;
            tmp2.second-=1;
            request.push_back(tmp2);
        }
        //делаем sizeTree степенью двойки
        //ceil - round up value
        
        n=pow(2.0,ceil(log(sizeArray)/log(2)));
        //cout<< "size " << n << endl;
        tree.resize(2*n-1);
        //инициализируем листья
        for (int i=n-1; i<tree.size(); ++i) {
            if (i-n+1<sizeArray)
                tree[i]=array[i-n+1];
            else tree[i]=99999999;
        }
        //инициализируем остальные вершины
        for (int i=n-2; i>=0; --i) {
            //cout << tree[2*i+1] << ' ' << tree[2*i+2] << endl;
            if (i!=0)
                tree[i]=min(tree[2*i+1], tree[2*i+2]);
            else 
                tree[i]=min(tree[1], tree[2]);
        }
        in.close();
        type=false;
    }*/
    SegmentTree (vector <double> newArray){
        array=newArray;
        sizeArray=array.size();
        int tmp;
        in >> tmp;
        for (int i=0; i<tmp; ++i) {
            pair <int, int> tmp2;
            in >> tmp2.first >> tmp2.second;
            //tmp2.second-=1;
            request.push_back(tmp2);
        }
        //делаем sizeTree степенью двойки
        //ceil - round up value
        
        n=pow(2.0,ceil(log(sizeArray)/log(2)));
        //cout<< "size " << n << endl;
        tree.resize(2*n-1);
        //инициализируем листья
        for (int i=n-1; i<tree.size(); ++i) {
            if (i-n+1<sizeArray)
                tree[i]=array[i-n+1];
            else tree[i]=99999999;
        }
        //инициализируем остальные вершины
        for (int i=n-2; i>=0; --i) {
            //cout << tree[2*i+1] << ' ' << tree[2*i+2] << endl;
            if (i!=0)
                tree[i]=min(tree[2*i+1], tree[2*i+2]);
            else 
                tree[i]=min(tree[1], tree[2]);
        }
        in.close();
    }
    void printTree () const {
        for (int i=0; i<tree.size(); ++i)
            cout << tree[i] << ' ';
        cout << endl;
    }
    void printArray () const {
        for (int i=0; i<array.size(); ++i)
            cout << array[i] << ' ';
        cout << endl;
    }
    double RMQ (int a, int b) {
        double result=99999999;
        a+=n-1;
        b+=n-1;
        //cout << tree[a] << ' ' << tree[b] << endl;
        while (a<=b) {
            if (a%2==0) { // если левое поддерево "отпадает"
                result=min(result,tree[a]);
                a=(a)/2;
            }
            else { 
                result=min(result,tree[a]);
                a=(a-1)/2;
            }
            if (b%2==1) {//если правое дерево "отпадает"
                result=min(result,tree[b]);
                b=(b-3)/2;
            }
            else {
                result=min(result,tree[b]);
                b=(b-2)/2;                
            }        
        }
        return result;
    }
    void RMQ_AllRequests () {
        for (int i=0; i<request.size(); ++i) {
            cout << this->RMQ(request[i].first, request[i].second) << endl;
        }
    }
    vector <pair <int,int> > getRequests() {
        return request;
    }
};
int main () {
    graph G;
    vector <double> depth, visit;
    
    G.DFS(depth, visit);
    cout << "depth: " << endl;
    for (int i=0; i<depth.size(); ++i) {
        cout << depth[i] << ' ';
    }
    cout << endl << "visit: " << endl;
    for (int i=0; i<visit.size(); ++i) {
        cout << visit[i] << ' ';
    }
    cout << endl;
    SegmentTree tree(depth);
    vector <pair<int, int> > requests=tree.getRequests();
    for (int i=0; i<requests.size(); ++i) {
        int ind1=0, ind2=depth.size()-1;
        while(visit[ind1]!=requests[i].first)
            ind1++;
        while(visit[ind2]!=requests[i].second)
            ind2--;
        double rmqAnswer = tree.RMQ(ind1, ind2);
        for (int j=ind1; j<=ind2; j++) {
            if (depth[j]==rmqAnswer) {
                cout << visit[j] << endl;
                break;
            }
        }
    }
    G.print();
    return 0;
}