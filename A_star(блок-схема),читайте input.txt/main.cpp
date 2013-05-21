#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <string>
#include <set>
#include <deque>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
ifstream in;
ofstream out;
struct point  {
    string s;
    int x,y;
    int g,h,f;//g - длина пути из старта, h - оценка до конца, f=g+h
    //int xparent, yparent;
    int num_parent;
    point& operator=(point p) {
        x=p.x;
        y=p.y;
        g=p.g;
        h=p.h;
        f=p.f;
        s=p.s;
        num_parent=p.num_parent;
        return *this;
    }
    bool operator==(point p) {
        if (
        this->x==p.x &&
        this->y==p.y &&
        this->g==p.g &&
        this->h==p.h &&
        this->f==p.f &&
        this->s==p.s &&
        this->num_parent==p.num_parent
        ) return true;
        else return false;
    }

};
int way (point a, point b, point parent) {
    int c;
    if ((a.x==b.x && a.x==parent.x) || (a.y==b.y && a.y==parent.y))
        c=1;
    else c=10;
    return a.g+c;
}
class field {
    vector <point> map;
    int countOfLinks,size,num_start,num_end;
    point start;
    point end;
    vector <point> StartVector,EndVector;
public:
    field() {
    in.open("input.txt");
    in >> size >> countOfLinks;
    StartVector.resize(countOfLinks);
    EndVector.resize(countOfLinks);
    for (int j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            char *x = new char;
            in >> x;
            point p;
            if (x[0]=='0') p.s="way";
            else if (x[0]=='#') p.s="wall";
            else if (x[0]=='1') {
                 p.s="start";
                 num_start=j*size+i;
                }
            else if (x[0]=='2') {
                    p.s="end";
                    num_end=j*size+i;
                }
            else if (atoi(x)>=3) {
                point temp;
                temp.x=i;
                temp.y=j;
                //cout << atoi(x) << endl;
                if (atoi(x)%2==1) {
                    StartVector[(atoi(x)-1)/2-1]=temp;
                }
                else {
                    EndVector[atoi(x)/2-2]=temp;
                    //cout << temp.x << temp.y << endl;
                }
                p.s="way";
            }
            p.x=i;
            p.y=j;
            map.push_back(p);
        }
    }
    in.close();
    map[num_start].num_parent=num_start;
    start=map[num_start];
    end=map[num_end];
    }
    void changeStartEnd (int x) {
        //старые старт и финиш становятся старыми
        map[start.x+size*start.y].s="oldStart";
        map[end.x+size*end.y].s="oldEnd";
        start=StartVector[x];
        end=EndVector[x];
        num_start=start.x+size*start.y;
        num_end=end.x+size*end.y;
        map[num_start].num_parent=num_start;
        //новые старт и финиш
        map[start.x+size*start.y].s="start";
        map[end.x+size*end.y].s="end";
        //Старые пути - теперь стены
        for (int i=0; i<map.size(); ++i) {
            if (map[i].s=="trueWay")
                map[i].s="oldWay";
        }
    }
    void newHeuristic () {
        //определим с какой стороны от квадрата финиш
        string temp;
        if (map.at(end.x+size*end.y+1).s=="wall" && map.at(end.x+size*end.y+2).s=="wall")
            temp="left";
        else if (map.at(end.x+size*end.y-1).s=="wall" && map.at(end.x+size*end.y-2).s=="wall")
            temp="right";
        else if (map.at(end.x+size*(end.y+1)).s=="wall" && map.at(end.x+size*(end.y+2)).s=="wall")
            temp="up";
        else if (map.at(end.x+size*(end.y-1)).s=="wall" && map.at(end.x+size*(end.y-2)).s=="wall")
            temp="down";
        //cout << temp << endl;
        for (int i=0; i<map.size(); i++) {
            int h;
            //h - Эвристика (выгоднее ходить по прямым линиям)
            if (temp=="left")
                if (map[i].y==end.y) 
                    h=fabs(end.x-map[i].x-1);     
                else 
                    h=10*fabs(end.x-map[i].x-1)+fabs(end.y-map[i].y);
            else
            if (temp=="right")
                if (map[i].y==end.y) 
                    h=fabs(end.x-map[i].x+1);     
                else 
                    h=10*fabs(end.x-map[i].x+1)+fabs(end.y-map[i].y);
            else
            if (temp=="up")
                if (map[i].x==end.x) 
                    h=fabs(end.y-map[i].y-1);     
                else 
                    h=10*fabs(end.y-map[i].y-1)+fabs(end.x-map[i].x);
            else
                if (map[i].x==end.x) 
                    h=fabs(end.y-map[i].y+1);     
                else 
                    h=10*fabs(end.y-map[i].y+1)+fabs(end.x-map[i].x);

            map[i].h=h;
            if (map[i].s=="start") {
                    start.g=0;
                    start.f=0;
                    map[i].g=0;
                    map[i].f=0;
            }
                else {
                    map[i].g=10000;
                    map[i].f=10000;
                }
        }
    }
    void printHeuristic () {
        cout << "Эвристика" << endl;
    for (vector <point>::iterator it=map.begin(); it!=map.end(); ) {
        for (int i=0; i<size; i++) {
            //cout << it->x << ' ' << it->y <<'|';
            cout << setw(3) <<it->h;
            ++it;
        }
        cout << endl;
    }
    }
    void printF () {
              cout << "F" << endl;
    for (vector <point>::iterator it=map.begin(); it!=map.end(); ) {
        for (int i=0; i<size; i++) {
            //cout << it->x << ' ' << it->y <<'|';
            cout << setw(6) <<it->f;
            ++it;
        }
        cout << endl;
    } 
    }
    void printG () {
              cout << "G" << endl;
    for (vector <point>::iterator it=map.begin(); it!=map.end(); ) {
        for (int i=0; i<size; i++) {
            //cout << it->x << ' ' << it->y <<'|';
            cout << setw(10) <<it->g;
            ++it;
        }
        cout << endl;
    } 
    }
    void A_star () {
    list <point> open;
    vector <point> closed;
    open.push_back(start);
    while (!open.empty()) {      
        point current=open.front();
        int num_parent=(current.x)+size*(current.y);       
        open.erase(open.begin());
        if (current.x==end.x && current.y==end.y) {
            //если нашли финиш
            vector <point> reverse_way;
            point a,b;
            a.x=end.x;
            a.y=end.y;
            a.num_parent=current.num_parent;
            reverse_way.push_back(a);
            while ((a.x!=start.x) || (a.y!=start.y)) {
                b.x=map[a.num_parent].x;
                b.y=map[a.num_parent].y;
                b.num_parent=map[a.num_parent].num_parent;
                reverse_way.push_back(b);
                a.x=b.x;
                a.y=b.y;
                a.num_parent=b.num_parent;
            }
            for (int i=0; i<reverse_way.size(); ++i) {
                if (map[reverse_way[i].x+size*reverse_way[i].y].s!="start" && 
                        map[reverse_way[i].x+size*reverse_way[i].y].s!="end")
                map[reverse_way[i].x+size*reverse_way[i].y].s="trueWay";
            }
            cout << "Success" << endl;
            return;
        }
        closed.push_back(current);
        for (int i=-1; i<=1; i++)
            for (int j=-1; j<=1; j++) {
                //отбираем только существующие соседние точки, не стену
                if ( (i==0 && j==0) ||  current.x-i<0 || current.x-i>=size || abs(i+j)==2 || abs(i+j)==0
                    || current.y-j<0 || current.y-j>=size || map[(current.x-i)+size*(current.y-j)].s=="wall" ||
                        map[(current.x-i)+size*(current.y-j)].s=="oldWay" || map[(current.x-i)+size*(current.y-j)].s=="oldEnd" ||
                        map[(current.x-i)+size*(current.y-j)].s=="olsStart");
                    else {
                        int c=(current.x-i)+size*(current.y-j);
                        bool q=false;
                        //если точка в закрытом списке, то игнорируем ее
                        for (vector <point>::iterator it=closed.begin(); it!=closed.end(); ++it)
                            if (*it==map[c]) {
                                q=true;
                                break;
                            }
                        if (q) continue;
                        //temp= цена пути из current в map[c]
                        //cout << current.s+' ' << current.g << endl;
                        int temp=way(current, map[c],map[map[num_parent].num_parent]);
                        bool b=false;
                        list <point>::iterator in_open;
                        for (list <point>::iterator it=open.begin(); it!=open.end(); ++it)
                            if (*it==map[c]) {
                                b=true;
                                in_open=it;
                                break;
                            }
                        //если точки нет в открытом списке
                        if (!b) {
                            map[c].num_parent=num_parent;
                            map[c].g=current.g+temp;
                            //cout << current.g <<' '<< temp;
                            map[c].f=map[c].h+map[c].g;
                            //сразу сортируем open
                            if (open.size()!=0) {
                                if (open.size()==1)
                                    if (open.begin()->f<map[c].f)
                                        open.push_back(map[c]);
                                    else open.push_front(map[c]);
                                else {
                                    list <point>::iterator q=open.begin();
                                    if (open.begin()->f >= map[c].f)
                                        open.push_front(map[c]);
                                    else if ((open.rbegin())->f <= map[c].f)
                                            open.push_back(map[c]);
                                            else
                                                for (list <point>::iterator it=(++open.begin()); it!=open.end(); ++it)
                                                    if (q->f <= map[c].f && it->f >= map[c].f)
                                                        open.insert(q,map[c]);
                                                    else ++q;
                                }
                            }
                            else
                            open.push_back(map[c]);
                        }
                        else
                            if (current.g+temp<map[c].g) {
                                map[c].num_parent=num_parent;
                                map[c].g=current.g+temp;
                                //cout << current.g <<' '<< temp;
                                map[c].f=map[c].h+map[c].g;
                                (*in_open)=map[c];
                            }
                        /*for (list <point>::iterator it=open.begin(); it!=open.end(); ++it) {
                            cout << "open, после: " << it->x << ' ' << it->y << endl;
                        }
                        cout << endl;*/
                    }
                }

        }
        cout << "unattainable" << endl;
        return;

}
    void printAnswer () {
        //вывод пути на экран
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++)
            if (map[j+i*size].s=="trueWay" || map[j+i*size].s=="oldWay")
                cout << 'w' << ' ';
            else if (map[j+i*size].s=="wall")
                cout << '#' << ' ';
            else if (map[j+i*size].s=="start" || map[j+i*size].s=="oldStart")
                cout << "S ";
            else if (map[j+i*size].s=="end" || map[j+i*size].s=="oldEnd")
                cout << "E ";
            else cout << "- ";
        cout << endl;
    }
    }
    void outToFile () {
        out.open("output.txt");
    //вывод пути в файл
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++)
            if (map[j+i*size].s=="trueWay" || map[j+i*size].s=="oldWay")
                out << 'w' << ' ';
            else if (map[j+i*size].s=="wall")
                out << '#' << ' ';
            else if (map[j+i*size].s=="start" || map[j+i*size].s=="oldStart")
                out << "S ";
            else if (map[j+i*size].s=="end" || map[j+i*size].s=="oldEnd")
                out << "E ";
            else out << "- ";
        out << endl;
    }
    out.close();
    }
    int getCountOfLinks () {
        return countOfLinks;
    }
};

int main() {
    field F;
    F.newHeuristic();
    F.A_star();
    for (int i=0; i<F.getCountOfLinks()-1; ++i) {
        F.changeStartEnd(i);
        F.newHeuristic();
        F.A_star();
    }
    F.printAnswer();
    return 0;
}