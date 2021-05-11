#include <bits/stdc++.h>
using namespace std;
#define ll long long

typedef complex<long long> P;
#define x real()
#define y imag()

int get_cross_product(P a, P b)
{
    return a.x * b.y - b.x * a.y;
}

//determine weather p3 is on the left, right, or toughing line p1p2
string point_location(P p1, P p2, P p3)
{
    //shift points so that p1 is at (0, 0)
    p2 += P{-p1.x, -p1.y};
    p3 += P{-p1.x, -p1.y};
    //calculate cross product
    int cross_product = get_cross_product(p2, p3);
    if (cross_product > 0) {
        //p2 is on right and p3 is on left
        return "LEFT ";
    }
    if (cross_product < 0) {
        //p2 is on left and p3 is on right
        return "RIGHT";
    }
    if (cross_product == 0) {
        //p3 and p2 are collinear
        return "TOUCH";
    }
}

//determine weather LINE SEGMENTS p1p2 and p3p4 intersect or not
string line_segment_intersection(P p1, P p2, P p3, P p4)
{
    //determine weather p3 is on the left or right of p1p2
    int cp1 = get_cross_product(P{p2.x - p1.x, p2.y - p1.y}, P{p3.x - p1.x, p3.y - p1.y});
    //determine weather p4 is on the left or right of p1p2
    int cp2 = get_cross_product(P{p2.x - p1.x, p2.y - p1.y}, P{p4.x - p1.x, p4.y - p1.y});
    //determine weather line segment p3p4 is disjoint from p1p2
    if ((cp1 < 0 && cp2 < 0) || (cp1 > 0 && cp2 > 0)) return "NO";

    //determine weather p1 is on the left or right of p3p4
    cp1 = get_cross_product(P{p3.x - p4.x, p3.y - p4.y}, P{p2.x - p4.x, p2.y - p4.y});
    //determine weather p2 is on the left or right of p3p4
    cp2 = get_cross_product(P{p3.x - p4.x, p3.y - p4.y}, P{p1.x - p4.x, p1.y - p4.y});
    //determine weather line segment p1p2 is disjoint from p3p4
    if ((cp1 < 0 && cp2 < 0) || (cp1 > 0 && cp2 > 0)) return "NO";
    //if both line segments are not disjoint from each other, they must intersect
    return "YES";

}

long double slope(P p1, P p2)
{
    if (p1.x == p2.x) return 0;
    return (p2.y - p1.y) / (p2.x - p1.x);
}

//return shortest distance from p3 to line p1p2
long double distance_from_line(P p1, P p2, P p3)
{//shortest distance has to be when p3 to intersection point is perpendicular
    //line stores {m=slope, c=constant} y = mx + b
    pair<long double, long double> line = {slope(p1, p2), p1.y - slope(p1, p2)*p1.x};
    pair<long double, long double> intersection;
    intersection.first = (p3.x + line.first * p3.y - line.second * line.first) / (line.first * line.first + 1);
    intersection.second = line.first * intersection.first + line.second;
    return abs(p3 - P{intersection.first, intersection.second});
}


//given a vector of points which are adjacent to each other and the last point is adjacent to the first
//these points form the vertices of a polygon
//determine weather point p lies inside or outside the polygon
string point_inside_polygon(vector<P> points, P p)
{
    //create a horizontal ray from point p to the right
    //if the number of times it intersects with an edge is odd, then it is inside polygon
    //else it is outside polygon

    //polygon must have 3 or more vertices
    if (points.size() < 3) return "INVALID POLYGON";
    //the horizontal ray from p is actually a line segment of length infinity
    P ray = {INT_MAX, p.y};
    int count = 0, cur_ind = 0;
    do {
        //next and adjacent vertex, should be mod points.size() because last point is adj to first point
        int next_ind = (cur_ind + 1) % points.size();
        P cur_point = points[cur_ind], next_point = points[next_ind];
        //check if ray and the side connecting the 2 vertices forming the line segment intersect
        if (line_segment_intersection(cur_point, next_point, p, ray) == "YES") {
            count++;
        }
        cur_ind = next_ind;
    } while (cur_ind != 0);
    if (count % 2 == 1) return "INSIDE";
    else return "OUTSIDE";
}

//given a vector points such that points next to each other are adjacent
//also the first and last points are adjacent
//find the area of the polygon by implementing the shoelace theorem
int polygon_area(vector<P> points)
{
    if (points.size() < 3) return 0;
    int cur_ind = 0;
    long double area = 0;
    do {//traversing polygon's adjacent points
        int next_ind = (cur_ind + 1) % (points.size());
        P cur_point = points[cur_ind], next_point = points[next_ind];
        //for every adjacent (x1, y1), (x2, y2), add to the area x1y2 - x2y1
        long double add = cur_point.x * next_point.y - next_point.x * cur_point.y;
        area += add;
        cur_ind = next_ind;
    } while (cur_ind != 0);
    //the shoelace theorem actually returns twice the area of polygon
    return area/2;
}

//calculate the number of lattice points including the end points of a line segment
int lattice_points_line_segment(P p1, P p2)
{
    //number of lattice points in segment excluding p1, p2 will be gcd(p1, p1) - 1
    //because of slope and (x1, y1) and (x1 + dx, y1 + dy) will be lattice point
    int ans = 2;//including p1 and p2
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    ans += abs(__gcd(dx, dy)) - 1;
    return ans;
}

//given a vector of adjacent points, first and last are adjacent
//forming a polygon find the number of lattice points on the boundary
//of polygon
int lattice_points_boundary(vector<P> points)
{
    if (points.size() < 3) return 0;
    //there will be at least be the number of vertices of polygon number of lattice points on boundary
    int ans = points.size();
    int cur_ind = 0;
    do {
        int next_ind = (cur_ind + 1) % points.size();
        P cur_point = points[cur_ind], next_point = points[next_ind];
        //calculate number of lattice points inside the line segment connecting the 2 vertices
        int dx = cur_point.x - next_point.x;
        int dy = cur_point.y - next_point.y;
        ans += abs(__gcd(dx, dy)) - 1;
    } while (cur_ind != 0);
    return ans;
}

//given vertices of a polygon, find the number of lattice point sin its interior
//by implementing Pick's Theorem Area = Interior + Boundary/2 - 1
int lattice_points_interior(vector<P> points) {
    //rearranging pick's formula: Interior = Area - Boundary/2 + 1
    int area = polygon_area(points);
    int boundary = lattice_points_boundary(points);
    return area - (boundary / 2) + 1;
}

long double euclidean_distance(P p1, P p2)
{
    return sqrt(pow(p1.y - p2.y, 2) + pow(p1.x - p2.x, 2));
}

long double manhattan_distance(P p1, P p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

//comparison operator for 2 points
bool comp(P p1, P p2)
{
    if (p1.x > p2.x) return false;
    if (p1.x < p2.x) return true;
    if (p1.x == p2.x) {
        if (p1.y >= p2.y) return false;
        else return true;
    }
}

//given a set of points in a plane, return the vertices of the convex hull
//surrounding the given set of points by implementing Andrew's Algorithm
vector<P> convex_hull(vector<P> points)
{
    //sort points based on x corrdinates
    sort(points.begin(), points.end(), comp);
    //ans will store upper and lower hull as they will be calculated seperately
    vector<P> ans;
    for (int rep = 0; rep < 2; rep++) {//2 reps for upper and lower hulls
        vector<P> hull;
        for (int i = 0; i < points.size(); i++) {//iterate through points
            while (hull.size() >= 2) {//if there is a line segment cureently
                P c = points[i], b = points[i - 1], a = points[i - 2];
                //if c is to the right of or collinear to line ab, then it is convex
                //check cross product in respect to a with line ab and point c
                int cp = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
                if (cp <= 0) {//c is on the right or touching line ab
                    //hull.push_back(c);
                    break;
                }
                else hull.pop_back();//otherwise back track and delete last point
            }
            hull.push_back(points[i]);//if there is no line segment formed push the point back
        }
        hull.pop_back();//remove rightmost point
        reverse(points.begin(), points.end());
        for (P p : hull) ans.push_back(p);
    }
    return ans;
}

int run()
{
    vector<P> points = { {2, 1}, {2, 5}, {3, 3}, {4, 3}, {4, 4}, {6, 3} };
    for (P p : convex_hull(points)) {
        cout << p << endl;
    }
}
