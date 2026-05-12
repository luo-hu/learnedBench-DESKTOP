#!/bin/bash

# 快速测试脚本 - 测试几个核心索引
DATA_PATH="data/synthetic/Default/"
RESULT_PATH="results/test/"

# 创建目录
mkdir -p ${RESULT_PATH}

echo "=== 学习索引基准测试快速验证 ==="

# 测试数据集
datasets=("uniform_20m_2_1" "gaussian_20m_2_1")

# 核心索引
for data in "${datasets[@]}"; do
    echo "Testing with dataset: $data"

    echo "  R-tree..."
    ./build/bin/bench2d_default rtree ${DATA_PATH}$data 20 range > ${RESULT_PATH}rtree_$data 2>&1

    echo "  R*-tree..."
    ./build/bin/bench2d_default rstar ${DATA_PATH}$data 20 range > ${RESULT_PATH}rstar_$data 2>&1

    echo "  KD-tree..."
    ./build/bin/bench2d_default kdtree ${DATA_PATH}$data 20 knn > ${RESULT_PATH}kdtree_$data 2>&1

    echo "  ANN..."
    ./build/bin/bench2d_default ann ${DATA_PATH}$data 20 knn > ${RESULT_PATH}ann_$data 2>&1

    echo "  ZM-Index..."
    ./build/bin/bench2d_default zm ${DATA_PATH}$data 20 all > ${RESULT_PATH}zm_$data 2>&1

    echo "  ✅ $data 测试完成"
    echo ""
done

echo "=== 所有测试完成！结果保存在 ${RESULT_PATH} ==="

# 显示结果摘要
echo "结果文件:"
ls -lh ${RESULT_PATH}*