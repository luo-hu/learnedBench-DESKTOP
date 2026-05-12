#pragma once

#include <array>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/io/io.hpp>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <tpie/file_stream.h>
#include <assert.h>
#include <tpie/tpie.h>
#include <utility>
#include <vector>
#include "common.hpp"
#include "type.hpp"


namespace bench { namespace utils { 

// generate n d-dimensional uniform points in range [0, r]
inline void gen_uniform(const std::string& fname, const int n, const int d, const double r) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0.0, r);

    tpie::file_stream<double> out;
    out.open(fname);
    for (int i=0; i<n*d; ++i) {
        out.write(dis(gen));
    }
    
    out.close();
}

inline void gen_uniform_geo(const std::string& fname, const int n, const int d, const double r) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0.0, r);

    tpie::file_stream<double> out;
    out.open(fname);
    for (int i=0; i<n*d; ++i) {
        out.write(dis(gen));
    }
    for (int i=0; i<n*d; ++i) {
        out.write(dis(gen));
    }
    
    out.close();
}

inline void gen_OSMTIGER() {
    tpie::file_stream<double> out;
    std::string fname = "/home/lh/Code/learnedbench/data/real/AREAWATER_tpie";
    out.open(fname);
    std::cout<<"lh\n";
    std::ifstream csv_data("/home/lh/Code/limbo-release-2.1/exp/test/AREAWATER.csv", std::ios::in);
    std::string line;
    if (!csv_data.is_open()) {
        std::cout << "Error: failed to open file\n";
        std::exit(1);
    }
    std::istringstream sin;  // 将整行字符串读入到字符串流中
    std::vector<std::string> words;
    std::string word;
    std::string lonlat;
    std::vector<std::vector<double>> boxes;
    int ccc = 0;
    int ccc1 = 0;
    // 读取标题行
    // std::getline(csv_data, line);
    // 读取数据
    double Minx = 200;
    double Maxx = -200;
    double Miny = 90;
    double Maxy = -90;
    while (std::getline(csv_data, line)) {
        sin.clear();
        sin.str(line);
        words.clear();
        std::vector<double> cx;
        std::vector<double> cy;
        double minx = 200;
        double maxx = -200;
        double miny = 90;
        double maxy = -90;
        int pointsNum = 0;
        bool isnan = false;
        bool isRecEnd = false;
#if true //polygon
        while (std::getline(
            sin, word, ',')) {  // 将字符串流sin中的字符读到word中，以字符'逗号'为分隔符
            size_t fInd = word.find("((");
            if(fInd==std::string::npos){
                size_t fInd2 = word.find("(");
                if(fInd2!=std::string::npos){
                    break;
                }
                size_t fInd1 = word.find(")");
                if(fInd1==std::string::npos){
                    lonlat = word.substr(0,word.length());//tiger
                    // lonlat = word.substr(1,word.length()-1);//osm
                }
                else{
                    lonlat = word.substr(0,fInd1);
                    isRecEnd = true;
                }
            }
            else{
                lonlat = word.substr(fInd+2,word.length()-fInd-2);
            }

            std::string xy;
            std::istringstream lonlatin;
            lonlatin.str(lonlat);
            std::vector<double> coord;
            int count = 0;
            while (std::getline(
                lonlatin, xy, ' ')) {
                if(xy==""){
                    continue;
                }
                double value = std::atof(xy.c_str());
                if(count==0){
                    cx.push_back(value);
                    if(value<-126 || value>-60)
                    // if(value<-180 || value>180)
                    {
                        isnan=true;
                        // std::cout<<"x: "<<value<<std::endl;
                    }
                    if(value<minx) minx = value;
                    if(value>maxx) maxx = value;
                    pointsNum++;
                }
                else {
                    cy.push_back(value);
                    if(value<24||value>90)
                    // if(value<-90||value>90)
                    {
                        isnan=true;
                        // std::cout<<"y: "<<value<<std::endl;
                    }
                    if(value<miny) miny = value;
                    if(value>maxy) maxy = value;
                }
                count++;
            }
            if(isnan || isRecEnd) break;
        }
#else //linestring
        while (std::getline(
            sin, word, ',')) {  // 将字符串流sin中的字符读到word中，以字符'逗号'为分隔符
            size_t fInd = word.find("(");
            if(fInd==std::string::npos){
                size_t fInd1 = word.find(")");
                if(fInd1==std::string::npos){
                    lonlat = word.substr(0,word.length());//tiger
                    // lonlat = word.substr(1,word.length()-1);//osm
                    int a=0;
                }
                else{
                    lonlat = word.substr(0,fInd1);
                    isRecEnd = true;
                }
            }
            else{
                lonlat = word.substr(fInd+1,word.length()-fInd-1);
            }

            std::string xy;
            std::istringstream lonlatin;
            lonlatin.str(lonlat);
            std::vector<double> coord;
            int count = 0;
            while (std::getline(
                lonlatin, xy, ' ')) {
                if(xy==""){
                    continue;
                }
                double value = std::atof(xy.c_str());
                if(count==0){
                    cx.push_back(value);
                    if(value<-126 || value>-60)
                    // if(value<-180 || value>180)
                    {
                        isnan=true;
                    }
                    if(value<minx) minx = value;
                    if(value>maxx) maxx = value;
                    pointsNum++;
                }
                else {
                    cy.push_back(value);
                    if(value<24||value>90)
                    // if(value<-90||value>90)
                    {
                        isnan=true;
                    }
                    if(value<miny) miny = value;
                    if(value>maxy) maxy = value;
                }
                count++;
            }
            if(isnan || isRecEnd) break;
        }
#endif
        ccc1++;
        if(isnan) std::cout<<"isnan "<<ccc1<<std::endl;
        if(pointsNum==0 || isnan) continue;

        out.write(minx);
        out.write(maxx);
        out.write(miny);
        out.write(maxy);
        out.write(pointsNum);
        for (int i = 0; i < pointsNum; ++i) {
            out.write(cx[i]);
            out.write(cy[i]);
        }

        if(miny<Miny) Miny = miny;
        if(maxy>Maxy) Maxy = maxy;
        if(minx<Minx) Minx = minx;
        if(maxx>Maxx) Maxx = maxx;

        ccc++;
        if(ccc%200000==0) std::cout<<ccc<<std::endl;
    }
    std::cout<<"recnum: "<<ccc<<" "<<ccc1<<std::endl;
    std::cout<<Minx<<","<<Maxx<<","<<Miny<<","<<Maxy<<std::endl;

    out.write(ccc);
    out.write(Minx);
    out.write(Maxx);
    out.write(Miny);
    out.write(Maxy);

    csv_data.close();
    
    out.close();
}

inline void gen_zipfian_geo(const std::string& fname, const int n, const int d, const double r) {
    int alpha = 1;
    double extentLevel = 100000;
    std::vector<double> v;
    v.reserve(extentLevel);
    for (int i = 1; i <= extentLevel; ++i) {
      v.push_back(1.0 / pow(i, alpha));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    //zipfian extent
    std::discrete_distribution<> dis(v.begin(), v.end());

    //uniform center
    std::uniform_real_distribution<> dis2(0.0, r);

    //gaussian center
    std::normal_distribution<> disx(0.0, r);
    std::normal_distribution<> disy(0.0, r);
    
    tpie::file_stream<double> out;
    out.open(fname);
    std::ofstream outFile;
    outFile.open("test.csv", std::ios::out | std::ios::trunc);
    double xc = 0;
    double yc = 0;
    double xs = 0;
    double ys = 0;
    //center
    for (int i=0; i<n; ++i) {
        if(i%(n/100)==0){
            xc = dis2(gen);
            yc = dis2(gen);
            while(true){
                xs = dis2(gen);
                if(xs>0.02 && xs<0.1) break;
            }
            while(true){
                ys = dis2(gen)/10;
                if(ys>0.02 && ys<0.1) break;
            }
            std::normal_distribution<double> tmpdisx(xc, xs);
            std::normal_distribution<double> tmpdisy(yc, ys);
            disx.param(tmpdisx.param());
            disy.param(tmpdisy.param());
        }
        // for(intj=0;j<d;++j){
        //     out.write(dis3(gen));
        // }
        double x=0;
        double y=0;
        while(true){
            x = disx(gen);
            if(x>=0 && x<=1) break;
        }
        while(true){
            y = disy(gen);
            if(y>=0 && y<=1) break;
        }
        out.write(x);
        out.write(y);
        outFile << std::to_string(x) << ','
            << std::to_string(y) << std::endl;
    }
    //extent
    for(int i = 0; i < n*d; ++i) {
        out.write(dis(gen)/extentLevel);
    }
    for(int i = 0; i < n; ++i) {
        outFile << std::to_string(dis(gen)/extentLevel) << ','
            << std::to_string(dis(gen)/extentLevel) << std::endl;
    }
    out.close();
    outFile.close();
}

// generate n d-dimensional points from a Gaussian distribution N(0, s^2)
inline void gen_gaussian(const std::string& fname, const int n, const int d, const double s) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::normal_distribution<> dis(0.0, s);

    tpie::file_stream<double> out;
    out.open(fname);
    for (int i=0; i<n*d; ++i) {
        out.write(dis(gen));
    }
    out.close();
}


// generate n d-dimensional points from a lognormal distribution mean=0 sigma=s
inline void gen_lognormal(const std::string& fname, const int n, const int d, const double s) {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::lognormal_distribution<> dis(0.0, s);

    tpie::file_stream<double> out;
    out.open(fname);

    for (int i=0; i<n*d; ++i) {
        out.write(dis(gen));
    }

    out.close();
}


struct dist_info_t {
    std::string dist_name;
    int n;
    int d;
};


// read data
inline void read_data(vec_of_double_vec_t& vv, const std::string& fname, const int n, const int d) {
    vv.resize(n);

    // tpie::tpie_init();
    tpie::file_stream<double> in;
    in.open(fname);

    for (int i=0; i<n; ++i) {
        vv[i].resize(d);
        for (int j=0; j<d; ++j) {
            vv[i][j] = in.read();
        }
    }

    in.close();
    // tpie::tpie_finish();
}


template<size_t dim>
inline void read_points(vec_of_point_t<dim>& out_points, const std::string& fname, const size_t N) {
    out_points.reserve(N);

    tpie::tpie_init();
    tpie::file_stream<double> in;
    in.open(fname);

    point_t<dim> p;
    for (size_t i=0; i<N; ++i) {
        for (size_t j=0; j<dim; ++j) {
            p[j] = in.read();
        }
        out_points.emplace_back(p);
    }

    in.close();
    tpie::tpie_finish();
}

template<size_t dim>
inline void read_geopoints(vec_of_point_t<dim>& out_points, const std::string& fname, const size_t N) {
    out_points.reserve(N*2);

    tpie::tpie_init();
    tpie::file_stream<double> in;
    in.open(fname);
   point_t<dim> p;
    for (size_t i=0; i<N; ++i) {
        for (size_t j=0; j<dim; ++j) {
            p[j] = in.read();
        }
        out_points.emplace_back(p);
    }

    for (size_t i=0; i<N; ++i) {
        for (size_t j=0; j<dim; ++j) {
            p[j] = in.read();
        }
        out_points.emplace_back(p);
    }

    in.close();
    tpie::tpie_finish();
}

template<size_t dim>
inline void read_geoboxes(vec_of_box_t<dim>& out_boxes, vec_of_point_t<dim>& out_points, const std::string& fname, const size_t N) {
    out_boxes.reserve(N);

    tpie::tpie_init();
    tpie::file_stream<double> in;
    in.open(fname);
    point_t<dim> p;
    vec_of_point_t<dim> centerPoints;
    for (size_t i=0; i<N; ++i) {
        for (size_t j=0; j<dim; ++j) {
            p[j] = in.read();
        }
        centerPoints.emplace_back(p);
    }
    double width;
    double height;
    for (size_t i=0; i<N; ++i) {
        // for (size_t j=0; j<dim; ++j) {
            
        // }
        width = in.read();
        height = in.read();
        point_t<dim> mincor = {centerPoints[i][0]-width/2,centerPoints[i][1]-height/2};
        point_t<dim> maxcor = {centerPoints[i][0]+width/2,centerPoints[i][1]+height/2};
        box_t<dim> onebox = box_t<dim>(mincor,maxcor);
        out_boxes.emplace_back(onebox);
    }
    out_points = centerPoints;
    in.close();
    tpie::tpie_finish();
}

template<size_t dim>
inline void read_encboxes(vec_of_box_t<dim>& out_boxes, vec_of_point_t<dim>& out_points, const std::string& fname) {
    std::cout<<"run read_encboxes"<<std::endl;

    tpie::tpie_init();
    tpie::file_stream<double> in;
    in.open(fname);
    int N = in.size();
    N = N / 4;
    point_t<dim> p;
    vec_of_point_t<dim> centerPoints;
    double minx;
    double maxx;
    double miny;
    double maxy;
    for (size_t i=0; i<N; ++i) {
        minx = in.read();
        maxx = in.read();
        miny = in.read();
        maxy = in.read();
        point_t<dim> mincor = {minx,miny};
        point_t<dim> maxcor = {maxx,maxy};
        box_t<dim> onebox = box_t<dim>(mincor,maxcor);
        out_boxes.emplace_back(onebox);

        p[0] = (minx+maxx)/2;
        p[1] = (miny+maxy)/2;
        centerPoints.emplace_back(p);
    }
    out_points = centerPoints;
    in.close();
    tpie::tpie_finish();
}

template<size_t dim>
inline void read_encpoints(std::vector<vec_of_point_t<dim>>& out_points, const std::string& fname) {
    std::cout<<"run read_encpoints"<<std::endl;

    tpie::tpie_init();
    tpie::file_stream<double> in;
    in.open(fname);
    int N = in.size();
    N = N / 2;
    point_t<dim> p;
    vec_of_point_t<dim> centerPoints;
    for (size_t i=0; i<N; ++i) {
        for (size_t j=0; j<dim; ++j) {
            p[j] = in.read();
        }
        centerPoints.emplace_back(p);
    }
    double width;
    double height;
    for (size_t i=0; i<N; ++i) {
        // for (size_t j=0; j<dim; ++j) {
            
        // }
        width = in.read();
        height = in.read();
        point_t<dim> mincor = {centerPoints[i][0]-width/2,centerPoints[i][1]-height/2};
        point_t<dim> maxcor = {centerPoints[i][0]+width/2,centerPoints[i][1]+height/2};
        box_t<dim> onebox = box_t<dim>(mincor,maxcor);
        // out_boxes.emplace_back(onebox);
    }
    out_points = centerPoints;
    in.close();
    tpie::tpie_finish();
}

template<size_t dim>
inline void read_osmtiger(std::vector<std::pair<box_t<dim>,polygon_t<dim>>>& outpairs, const std::string& fname) {
    std::cout<<"run read_osmtiger"<<std::endl;

    tpie::tpie_init();
    tpie::file_stream<double> in;
    std::cout<<fname<<std::endl;
    in.open(fname);
    std::cout<<fname<<std::endl;
    int count = 0;
    while(true){
        float minx = in.read();
        if(minx>1000000){
            std::cout<<"!!! "<<minx<<std::endl;
            float Minx = in.read();
            float Maxx = in.read();
            float Miny = in.read();
            float Maxy = in.read();
            std::cout<<"!!! "<<minx<<","<<Minx<<","<<Maxx<<","<<Miny<<","<<Maxy<<","<<std::endl;
            break;
        }
        float maxx = in.read();
        float miny = in.read();
        float maxy = in.read();
        point_t<dim> mincor = {minx,miny};
        point_t<dim> maxcor = {maxx,maxy};
        box_t<dim> onebox = box_t<dim>(mincor,maxcor);

        polygon_t<dim> onepolygon;
        int pointsNum = in.read();
        for(int i=0;i<pointsNum;i++){
            float x = in.read();
            float y = in.read();

            // pointf_t<dim> p = pointf_t<dim>(x,y);
            point_t<dim> p;
            p[0] = x;
            p[1] = y;

            bg::append(onepolygon.outer(),p);
        }

        outpairs.push_back(std::make_pair(onebox,onepolygon));
        count++;
        // if(count%100000==0) std::cout<<"count: "<<count<<std::endl;
    }
    
    std::cout<<"read_osmtiger finished"<<std::endl;
    in.close();
    tpie::tpie_finish();
}


// template<size_t dim>
// inline void read_geoboxes2(Boxes2d& out_boxes, const std::string& fname, const size_t N) {
//     out_boxes.reserve(N);

//     tpie::tpie_init();
//     tpie::file_stream<double> in;
//     in.open(fname);
//     point2d p;
//     std::vector<point2d> centerPoints;
//     for (size_t i=0; i<N; ++i) {
//         p = point2d(in.read(),in.read());
//         centerPoints.emplace_back(p);
//     }
//     double width;
//     double height;
//     for (size_t i=0; i<N; ++i) {
//         width = in.read();
//         height = in.read();
//         point2d mincor = {centerPoints[i].x()-width/2,centerPoints[i].y()-height/2};
//         point2d maxcor = {centerPoints[i].x()+width/2,centerPoints[i].y()+height/2};
//         box2d onebox = box2d(mincor,maxcor);
//         out_boxes.emplace_back(onebox);
//     }

//     in.close();
//     tpie::tpie_finish();
// }

template<typename T, typename Iter, std::size_t... Is>
constexpr auto to_array(Iter& iter, std::index_sequence<Is...>)
-> std::array<T, sizeof...(Is)> {
    return {{ ((void)Is, *iter++)... }};
}


template<std::size_t N, typename Iter,
         typename T = typename std::iterator_traits<Iter>::value_type>
constexpr auto to_array(Iter iter)
-> std::array<T, N> {
    return to_array<T>(iter, std::make_index_sequence<N>{});
}


// transform data to vector of points
template<size_t dim>
inline auto to_points(vec_of_double_vec_t& vv) {
    std::vector<std::array<double, dim>> points;
    auto n = vv.size();
    points.reserve(n);

    for (size_t i=0; i<n; ++i) {
        // use move instead of copy to save memory
        points.push_back(to_array<dim>(std::make_move_iterator(vv[i].begin())));
    }

    return points;
}


// parse csv data
inline void csv_to_bin(const std::string& in_fname, const std::string& out_fname) {
    // open tpie for output
    // tpie::tpie_init();
    tpie::file_stream<double> out;
    out.open(out_fname);
    
    // open input csv file
    std::ifstream infile(in_fname);
    std::string line;

    size_t count = 0;
    std::string strr = ".000";
    while (std::getline(infile, line)) {
        line.pop_back();
        // std::cout<<line<<std::endl;
        if(line.find(strr)!=std::string::npos){
            // std::cout<<line<<std::endl;
            continue;
        }
        std::istringstream is(line);
        std::string val_str;
        while (std::getline(is, val_str, ',')) {
            out.write(std::stod(val_str));
        }
        count++;

        if(count%1000000==0) 
            std::cout<<count<<std::endl;
    }
    std::cout<<count<<std::endl;

    infile.close();
    out.close();
    // tpie::tpie_finish();
}


// trasform csv format data to binary data
inline void csv_to_bin(const std::string& in_fname, const std::string& out_fname, const char delimiter, const int n, const int d) {
    std::cout<<"lh:csv_to_bin"<<std::endl;
    std::ifstream in_fs(in_fname);
    // tpie::tpie_init();
    tpie::file_stream<double> out;
    out.open(out_fname);

    std::string line;
    int count_n = 0;
    while (std::getline(in_fs, line)) {
        std::stringstream line_stream(line);
        std::string cell;
        int count_d = 0;
        while (std::getline(line_stream, cell, delimiter)) {
            out.write(std::stod(cell));
            count_d++;
        }

        // chech dimension
        assert(count_d == d);
        count_n++;
    }

    // check total size
    assert(count_n == n);

    in_fs.close();
    out.close();
    // tpie::tpie_finish();
}

}
}

