// #pragma once
// #include <geos_c.h> // 替换所有C++头文件为C接口[1,3](@ref)

// #ifdef HEAP_PROFILE
// #include <gperftools/heap-profiler.h>
// #endif

// #include <chrono>
// #include <vector>
// #include <iostream>

// #include "../base_index.hpp"
// #include "../../utils/type.hpp"

// namespace bench { namespace index {

// // GEOS初始化单例[1,3](@ref)
// struct GEOSContext {
//     GEOSContextHandle_t handle;
    
//     GEOSContext() {
//         handle = GEOS_init_r(); // 线程安全初始化
//     }
    
//     ~GEOSContext() {
//         GEOS_finish_r(handle);
//     }
// };

// // 包装GEOS几何对象[1,6](@ref)
// struct GEOSGeometryWrapper {
//     GEOSGeometry* geom;
//     GEOSContextHandle_t ctx;
    
//     GEOSGeometryWrapper(GEOSContextHandle_t c, GEOSGeometry* g) 
//         : ctx(c), geom(g) {}
    
//     ~GEOSGeometryWrapper() {
//         if (geom) GEOSGeom_destroy_r(ctx, geom);
//     }
    
//     // 禁止拷贝
//     GEOSGeometryWrapper(const GEOSGeometryWrapper&) = delete;
//     GEOSGeometryWrapper& operator=(const GEOSGeometryWrapper&) = delete;
    
//     // 允许移动
//     GEOSGeometryWrapper(GEOSGeometryWrapper&& other) noexcept 
//         : ctx(other.ctx), geom(other.geom) {
//         other.geom = nullptr;
//     }
// };

// template<size_t Dim>
// class QDTree : public BaseIndex {
//     using Point = point_t<Dim>;
//     using Points = std::vector<Point>;
//     using Box = box_t<Dim>;
    
//     // 线程局部存储避免多线程冲突[1](@ref)
//     static thread_local GEOSContext geosContext;
//     GEOSContextHandle_t ctx;
    
//     // 存储几何对象
//     std::vector<GEOSGeometryWrapper> geosPoints;
//     GEOSSTRtree* tree; // 四叉树索引[1,3](@ref)

// public:
//     QDTree(Points& points) : ctx(geosContext.handle) {
//         std::cout << "Construct QDTree Dim=" << Dim << std::endl;
        
//         auto start = std::chrono::steady_clock::now();
        
//     #ifdef HEAP_PROFILE
//         HeapProfilerStart("qdtree");
//     #endif

//         // 创建四叉树索引[1](@ref)
//         tree = GEOSSTRtree_create_r(ctx, 10);
        
//         // 转换点数据为GEOS几何对象
//         for (size_t i=0; i<points.size(); ++i) {
//             const auto& p = points[i];
//             // 创建GEOS点对象[1,6](@ref)
//             GEOSCoordSequence* seq = GEOSCoordSeq_create_r(ctx, 1, 2);
//             GEOSCoordSeq_setX_r(ctx, seq, 0, std::get<0>(p));
//             GEOSCoordSeq_setY_r(ctx, seq, 0, std::get<1>(p));
            
//             GEOSGeometry* pt = GEOSGeom_createPoint_r(ctx, seq);
//             geosPoints.emplace_back(ctx, pt);
            
//             // 插入到四叉树[1](@ref)
//             GEOSSTRtree_insert_r(ctx, tree, pt, GEOSGeom_getExtent_r(ctx, pt));
//         }

//     #ifdef HEAP_PROFILE
//         HeapProfilerDump("final");
//         HeapProfilerStop();
//     #endif

//         auto end = std::chrono::steady_clock::now();
//         build_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//         std::cout << "Build Time: " << get_build_time() << " [ms]" << std::endl;
//     }

//     ~QDTree() {
//         GEOSSTRtree_destroy_r(ctx, tree);
//     }

//     Points range_query(Box& box) {
//         // 创建查询范围[6](@ref)
//         GEOSGeometry* queryEnv = createEnvelope(box);
//         Points results;
        
//         auto start = std::chrono::steady_clock::now();
        
//         // 定义查询回调[1](@ref)
//         auto callback = [](void* item, void* userdata) {
//             auto ctx = static_cast<GEOSContextHandle_t>(userdata);
//             auto geom = static_cast<GEOSGeometry*>(item);
//             auto results = static_cast<Points*>(userdata);
            
//             Point pt;
//             pt[0] = GEOSGeomGetX_r(ctx, geom);
//             pt[1] = GEOSGeomGetY_r(ctx, geom);
//             results->push_back(pt);
            
//             return 1;
//         };
        
//         // 执行范围查询[1,3](@ref)
//         GEOSSTRtree_query_r(ctx, tree, queryEnv, &callback, &results);
        
//         auto end = std::chrono::steady_clock::now();
//         range_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//         range_count++;
        
//         GEOSGeom_destroy_r(ctx, queryEnv);
//         return results;
//     }

//     inline size_t count() const {
//         return geosPoints.size();
//     }

// private:
//     // 创建查询范围[6](@ref)
//     GEOSGeometry* createEnvelope(const Box& box) {
//         GEOSCoordSequence* seq = GEOSCoordSeq_create_r(ctx, 5, 2);
        
//         // 创建矩形边界
//         GEOSCoordSeq_setX_r(ctx, seq, 0, box.min_corner()[0]);
//         GEOSCoordSeq_setY_r(ctx, seq, 0, box.min_corner()[1]);
        
//         GEOSCoordSeq_setX_r(ctx, seq, 1, box.max_corner()[0]);
//         GEOSCoordSeq_setY_r(ctx, seq, 1, box.min_corner()[1]);
        
//         GEOSCoordSeq_setX_r(ctx, seq, 2, box.max_corner()[0]);
//         GEOSCoordSeq_setY_r(ctx, seq, 2, box.max_corner()[1]);
        
//         GEOSCoordSeq_setX_r(ctx, seq, 3, box.min_corner()[0]);
//         GEOSCoordSeq_setY_r(ctx, seq, 3, box.max_corner()[1]);
        
//         // 闭合矩形
//         GEOSCoordSeq_setX_r(ctx, seq, 4, box.min_corner()[0]);
//         GEOSCoordSeq_setY_r(ctx, seq, 4, box.min_corner()[1]);
        
//         return GEOSGeom_createLinearRing_r(ctx, seq);
//     }
// };

// // 初始化线程局部存储
// template<size_t Dim>
// thread_local GEOSContext QDTree<Dim>::geosContext;

// }}

#pragma once
#include <geos/geom/Envelope.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Point.h>
#include <geos/index/quadtree/Quadtree.h>
// TemplateSTRtree.h 仅在 GEOS 3.9+ 中可用，当前代码未使用，因此注释掉
// #include <geos/index/strtree/TemplateSTRtree.h>

#ifdef HEAP_PROFILE
#include <gperftools/heap-profiler.h>
#endif

#include <chrono>

#include "../base_index.hpp"
#include "../../utils/type.hpp"


namespace bench { namespace index {
    
struct GEOSGeometry {
    std::vector<geos::geom::Geometry *> geometry;
    geos::geom::GeometryFactory::Ptr factory;

    GEOSGeometry() {
        factory = geos::geom::GeometryFactory::create();
    }

    ~GEOSGeometry() {
        for (geos::geom::Geometry * g : geometry) {
            factory->destroyGeometry(g);
        }
        geometry.clear();
    }
};


template<size_t Dim>
void points_to_geos(vec_of_point_t<Dim>& points, GEOSGeometry& geos_points) {
    geos_points.geometry.reserve(points.size());

    for (auto& p : points) {
        // GEOS 3.8 兼容：createPoint() 返回原始指针
        geos::geom::Geometry * temp = geos_points.factory->createPoint(geos::geom::Coordinate(std::get<0>(p), std::get<1>(p)));
        // GEOS 3.9+ 版本：createPoint() 返回 unique_ptr，需要 .release()
        // geos::geom::Geometry * temp = geos_points.factory->createPoint(geos::geom::Coordinate(std::get<0>(p), std::get<1>(p))).release();
        geos_points.geometry.push_back(temp);
    }
}


template<size_t Dim=2>
class QDTree : public BaseIndex {

using QDTree_t = geos::index::quadtree::Quadtree;
using Point = point_t<Dim>;
using Points = std::vector<Point>;
using Box = box_t<Dim>;

public:
QDTree(Points& points) { 
    std::cout << "Construct QDTree " << "Dim=" << Dim << std::endl;

    points_to_geos(points, geos_points);

    auto start = std::chrono::steady_clock::now();

#ifdef HEAP_PROFILE
HeapProfilerStart("qdtree");
#endif

    _qdtree = new QDTree_t();

    for (size_t i=0; i<points.size(); ++i) {
        _qdtree->insert(geos_points.geometry[i]->getEnvelopeInternal(), reinterpret_cast<void *>(geos_points.geometry[i]));
    }

#ifdef HEAP_PROFILE
HeapProfilerDump("final");
HeapProfilerStop();
#endif

    auto end = std::chrono::steady_clock::now();
    build_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Build Time: " << get_build_time() << " [ms]" << std::endl;
}


~QDTree() {
    delete _qdtree;
}


Points range_query(Box& box) {
    // prepare the query geometry
    geos::geom::GeometryFactory::Ptr gf = geos::geom::GeometryFactory::create();

    geos::geom::Envelope geos_box(box.min_corner()[0], box.max_corner()[0], box.min_corner()[1], box.max_corner()[1]);
    auto query_geometry = gf->toGeometry(&geos_box);

    // query the geometry envolope
    auto start = std::chrono::steady_clock::now();

    std::vector<void*> results;
    _qdtree->query(query_geometry->getEnvelopeInternal(), results);

    auto end = std::chrono::steady_clock::now();
    range_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    range_count ++;

    // collect results
    // the geos libaray returns geometries **may** intersect the query rectangle
    Points point_results;
    for (size_t i=0; i<results.size(); ++i) {
        auto pg = static_cast<geos::geom::Geometry *>(results[i]);
        if (query_geometry->contains(pg)) {
            Point temp;
            temp[0] = pg->getCoordinate()->x;
            temp[1] = pg->getCoordinate()->y;
            point_results.emplace_back(temp);
        }
        
    }

    return point_results;
}


inline size_t count() {
    return _qdtree->size();
}


private:
QDTree_t* _qdtree;
GEOSGeometry geos_points;
};


}
}

