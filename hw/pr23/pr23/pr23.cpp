#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

void printMemoryLeaks()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
}

class Point {
public:
    int x;
    int y;

    Point(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }

    Point(const Point& other) {
        this->x = other.x;
        this->y = other.y;
    }

    Point& operator=(const Point& other) {
        if (this == &other) return *this;

        this->x = other.x;
        this->y = other.y;
    }
};

class Shape {
private:
    virtual int minX() = 0;
    virtual int minY() = 0;
    virtual int maxX() = 0;
    virtual int maxY() = 0;
public:
    virtual ~Shape() {}
    virtual void print() = 0;
};

class Line : public Shape {
private:
    Point start;
    Point end;

    int minX() {
        if (start.x > end.x) {
            return end.x;
        }
        return start.x;
    }
    int maxX() {
        if (start.x < end.x) {
            return end.x;
        }
        return start.x;
    }
    int minY() {
        if (start.y > end.y) {
            return end.y;
        }
        return start.y;
    }
    int maxY() {
        if (start.y < end.y) {
            return end.y;
        }
        return start.y;
    }
public:
    Line(Point start, Point end) {
        this->start = start;
        this->end = end;
    }

    void print() {
        cout << "Line. Coordinates:" << endl << "Start: x = " << start.x << ", y = " << start.y << endl;
        cout << "End: x = " << end.x << ", y = " << end.y << endl;
        cout << "Center coordinates:" << " x = " << (start.x + end.x) / 2.0 << ", y = " << (start.y + end.y) / 2.0 << endl;
        cout << "Min coordinates:" << " x = " << minX() << ", y = " << minY() << endl;
        cout << "Max coordinates:" << " x = " << maxX() << ", y = " << maxY() << endl;
    }
};

class PolyLine : public Shape {
private:
    vector<Point> points;

    double centroidX() {
        double sum = 0.0;
        for (int i = 0; i < points.size(); i++) {
            sum += points[i].x;
        }
        return sum / points.size();
    }

    double centroidY() {
        double sum = 0.0;
        for (int i = 0; i < points.size(); i++) {
            sum += points[i].y;
        }
        return sum / points.size();
    }

    int minX() {
        int ans;
        ans = points[0].x;
        for (int i = 1; i < points.size(); i++) {
            if (ans > points[i].x) ans = points[i].x;
        }

        return ans;
    }

    int maxX() {
        int ans;
        ans = points[0].x;
        for (int i = 1; i < points.size(); i++) {
            if (ans < points[i].x) ans = points[i].x;
        }

        return ans;
    }

    int minY() {
        int ans;
        ans = points[0].y;
        for (int i = 1; i < points.size(); i++) {
            if (ans > points[i].y) ans = points[i].y;
        }

        return ans;
    }

    int maxY() {
        int ans;
        ans = points[0].y;
        for (int i = 1; i < points.size(); i++) {
            if (ans < points[i].y) ans = points[i].y;
        }

        return ans;
    }

public:
    PolyLine(vector<Point> points_) {
        for (int i = 0; i < points_.size(); i++) {
            points.push_back(Point(points_[i]));
        }
    }

    void print() {
        cout << "PolyLine. All points:" << endl;
        for (int i = 0; i < points.size(); i++) {
            cout << "Point #" << i + 1 << ": x = " << points[i].x << ", y = " << points[i].y << endl;
        }
        cout << "Center coordinates:" << " x = " << centroidX() << ", y = " << centroidY() << endl;
        cout << "Min coordinates:" << " x = " << minX() << ", y = " << minY() << endl;
        cout << "Max coordinates:" << " x = " << maxX() << ", y = " << maxY() << endl;
    }
};

int main() {
    ifstream file("file.hpgl");
    vector<Shape*> shapes;

    bool penIsDown = false;
    vector <Point> points;
    string line;

    while (file.is_open() && file.good()) {
        string tmp;
        file >> tmp;
        line += tmp;
    }

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == 'P') {
            // already drawing
            if (line[i + 1] == 'A' && penIsDown) {
                int x, y;
                string tmp;
                for (int j = i + 2; line[j] != ';'; j++) {
                    if (line[j] != ',')
                        tmp += line[j];
                    else {
                        x = stoi(tmp);
                        tmp = "";
                    }
                }
                y = stoi(tmp);
                points.push_back(Point(x, y));
            }
            // moved position before starting to draw
            else if (line[i + 1] == 'A' && !penIsDown) {
                points.clear();
                int x, y;
                string tmp;
                for (int j = i + 2; line[j] != ';'; j++) {
                    if (line[j] != ',')
                        tmp += line[j];
                    else {
                        x = stoi(tmp);
                        tmp = "";
                    }
                }
                y = stoi(tmp);
                points.push_back(Point(x, y));
            }

            // start drawing shape
            else if (line[i + 1] == 'D') {
                penIsDown = true;
            }

            // finish drawing shape
            else if (line[i + 1] == 'U') {
                penIsDown = false;
                if (points.size() > 2) {
                    shapes.push_back(new PolyLine(points));
                }
                else if(points.size() == 2) {
                    shapes.push_back(new Line(points[0], points[1]));
                }
                points.clear();
            }
        }
    }

    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->print();
        cout << endl;
        cout << endl;
    }

    for (int i = 0; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();

    printMemoryLeaks();
    return 0;
}