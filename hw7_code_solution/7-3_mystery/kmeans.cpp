#include "kmeans.hpp"


inline double Point::sDistance(Point& other) const{
    return ((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
}

std::istream& operator>>(std::istream& is, Point& pt){
    is>>pt.x>>pt.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, Point& pt){
    os<<pt.x<<' '<<pt.y;
    return os;
}

Kmeans::Kmeans(const std::vector<Point>& points, const std::vector<Point>& initialCenters){
    m_points=points;
    m_centers=initialCenters;
    m_numPoints=points.size();
    m_numCenters=initialCenters.size();
}


std::vector<index_t> Kmeans::Run(int maxIterations){
    // DO NOT MODIFY THESE CODE
    std::vector<index_t> assignment(m_numPoints, 0); // the return vector
    int currIteration = 0;
    std::cout << "Running kmeans with num points = " << m_numPoints 
            << ", num centers = " << m_numCenters 
            << ", max iterations = " << maxIterations << "...\n";

    // YOUR CODE HERE
    int flag=1;
//    double mn=1e9;
//    long be=clock(),p1=0,p2=0;
    std::vector<std::thread> tr;
    while(currIteration < maxIterations && flag){
        currIteration++;
        flag=0;
        tr.clear();
        for(int j=0;j<THREAD;j++){
            tr.emplace_back(std::thread(assigncenterNG,std::ref(assignment),j,this->m_numPoints,this->m_numCenters,std::ref(this->m_points),std::ref(this->m_centers)));
        }
        for(int j=0;j<THREAD;j++) {
            tr[j].join();
        }
//        p1+=clock()-be;
//        be=clock();
        std::vector<double> sx(m_numCenters,0),sy(m_numCenters,0);
        std::vector<int> sn(m_numCenters,0);
        for(int i=0;i<m_numPoints;i++){
            sx[assignment[i]]+=m_points[i].x;
            sy[assignment[i]]+=m_points[i].y;
            sn[assignment[i]]++;
        }
//        puts("iter");
        for(int j=0;j<m_numCenters;j++){
            if(sn[j]){
                double tx=sx[j]/(double)sn[j],ty=sy[j]/(double)sn[j];
                flag=flag|(std::abs(tx+ty-m_centers[j].x-m_centers[j].y)>eps);
                m_centers[j].x=tx;
                m_centers[j].y=ty;
            }
        }
//        p2+=clock()-be;
//        be=clock();
    }
//    std::cerr<<p1<<' '<<p2;
    // YOUR CODE ENDS HERE
    std::cout << "Finished in " << currIteration << " iterations." << std::endl;
    return assignment;
}

void assigncenterNG(std::vector<index_t>& assignment,int xi,int m_numPoints,int m_numCenters,std::vector<Point>& m_points,std::vector<Point>& m_centers){
    for(int i=xi;i<m_numPoints;i+=THREAD){
        double mn=1e18;
        for(int j=0;j<m_numCenters;j++) {
            double tmp = m_points[i].sDistance(m_centers[j]);
            if (tmp < mn) {
                assignment[i] = j;
                mn = tmp;
            }
        }
    }
}