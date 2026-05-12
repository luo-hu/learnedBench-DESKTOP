#!/bin/bash

# 设置 GEOS 库路径
export LD_LIBRARY_PATH=/usr/local/geos/lib:$LD_LIBRARY_PATH

DATA_PATH="../data/"
BENCH2D_DEFAULT="./../build/bin/bench2d_default"
BENCH2D_FS="./../build/bin/bench2d_fs"
BENCH2D_OSM="./../build/bin/bench2d_osm"

REAL_DATA_PATH="${DATA_PATH}real/"
SYN_DATA_PATH="${DATA_PATH}synthetic/"
DEFAULT_SYN_DATA_PATH="${DATA_PATH}synthetic/Default/"

RESULT_PATH="./../results/default/"

mkdir -p ${RESULT_PATH}

# 数据点数量
N=20000000  # 2000万点

#run experiments on default synthetic datasets
for data in "uniform_20m_2_1" "gaussian_20m_2_1" "lognormal_20m_2_1"
do
    for index in "rtree" "rstar" "zm" "mli" "lisa" "fs"
        # for index in "rtree" "rstar" "zm"  "fs"
    do
        echo "Benchmark ${index} dataset ${data}"
        ${BENCH2D_DEFAULT} ${index} "${DEFAULT_SYN_DATA_PATH}$data" ${N} all > "${RESULT_PATH}${index}_${data}"
    done

    for index in "kdtree" "ann"
    do
        echo "Benchmark ${index} dataset ${data}"
        ${BENCH2D_DEFAULT} ${index} "${DEFAULT_SYN_DATA_PATH}$data" ${N} knn > "${RESULT_PATH}${index}_${data}"
    done

    for index in "qdtree" "ug" "edg"  "ifi" "flood"
    do
        echo "Benchmark ${index} dataset ${data}"
        ${BENCH2D_DEFAULT} ${index} "${DEFAULT_SYN_DATA_PATH}$data" ${N} range > "${RESULT_PATH}${index}_${data}"
    done
done

# run experiments on FourSquare
# data="fs"
# for index in "rtree" "rstar" "zm" "mli" "lisa"
# do
#     echo "Benchmark ${index} dataset ${data}"
#     #3680126
#     ${BENCH2D_FS} ${index} "${REAL_DATA_PATH}$data" 3680126 all > "${RESULT_PATH}${index}_${data}"
# done

# for index in "kdtree" "ann" 
# do
#     echo "Benchmark ${index} dataset ${data}"
#     ${BENCH2D_FS} ${index} "${REAL_DATA_PATH}$data" 368 knn > "${RESULT_PATH}${index}_${data}"
# done

# for index in "qdtree" "ug" "edg" "fs" "ifi" "flood"
# do
#     echo "Benchmark ${index} dataset ${data}"
#     ${BENCH2D_FS} ${index} "${REAL_DATA_PATH}$data" 368 range > "${RESULT_PATH}${index}_${data}"
# done

# run experiments on OSM
# data="osm-china"
# for index in "rtree" "rstar" "zm" "mli" "lisa"
# do
#     echo "Benchmark ${index} dataset ${data}"
#     #62734869
#     ${BENCH2D_OSM} ${index} "${REAL_DATA_PATH}$data" 627 all > "${RESULT_PATH}${index}_${data}"
# done

# for index in "kdtree" "ann" 
# do
#     echo "Benchmark ${index} dataset ${data}"
#     ${BENCH2D_OSM} ${index} "${REAL_DATA_PATH}$data" 627 knn > "${RESULT_PATH}${index}_${data}"
# done

# for index in "qdtree" "ug" "edg" "fs" "ifi" "flood"
# do
#     echo "Benchmark ${index} dataset ${data}"
#     ${BENCH2D_OSM} ${index} "${REAL_DATA_PATH}$data" 627 range > "${RESULT_PATH}${index}_${data}"
# done
