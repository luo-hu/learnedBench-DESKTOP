#!/bin/bash
# 设置 GEOS 和 LibTorch 库路径
export LD_LIBRARY_PATH=/usr/local/geos/lib:/usr/local/libtorch/lib:$LD_LIBRARY_PATH
DATA_PATH="../data/"
BENCH_RSMI="../build/bin/bench_rsmi"


# REAL_DATA_PATH="${DATA_PATH}real/"  目前没有真实数据，所以先注释掉
SYN_DATA_PATH="${DATA_PATH}synthetic/"
DEFAULT_SYN_DATA_PATH="${DATA_PATH}synthetic/Default/"

RESULT_PATH="../results/default/"

mkdir ${RESULT_PATH}

# for data in "uniform_20m_2_1" "gaussian_20m_2_1" "lognormal_20m_2_1"
for data in "uniform_20m_2_1" 

do
    for index in "rsmi" 
    do
        echo "Benchmark ${index} dataset ${data}"
        #20000000
        ${BENCH_RSMI} ${index} "${DEFAULT_SYN_DATA_PATH}$data" 20000000 all > "${RESULT_PATH}${index}_${data}"
    done
done

# fs和osm-china数据集目前没有真实数据，所以先注释掉
#data="fs"
#for index in "rsmi" 
#do
#    echo "Benchmark ${index} dataset ${data}"
#    #3680126
#    ${BENCH_RSMI} ${index} "${REAL_DATA_PATH}$data" 3680126 all > "${RESULT_PATH}${index}_${data}"
#done

#data="osm-china"
#for index in "rsmi" 
#do
#    echo "Benchmark ${index} dataset ${data}"
#    #62734869
#    ${BENCH_RSMI} ${index} "${REAL_DATA_PATH}$data" 62734869 all > "${RESULT_PATH}${index}_${data}"
#done
