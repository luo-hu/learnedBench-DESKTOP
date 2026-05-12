#!/bin/bash

echo "=== 快速基准测试 ==="

# 创建结果目录
mkdir -p results/quick

# 测试小数据集 - 只测试几个核心索引
echo "测试 R-tree..."
timeout 30s ./build/bin/bench2d_default rtree data/synthetic/Default/uniform_20m_2_1 10 range > results/quick/rtree_quick.txt 2>&1

echo "测试 ZM-Index..."
timeout 30s ./build/bin/bench2d_default zm data/synthetic/Default/uniform_20m_2_1 10 range > results/quick/zm_quick.txt 2>&1

echo "测试 KD-tree..."
timeout 30s ./build/bin/bench2d_default kdtree data/synthetic/Default/uniform_20m_2_1 10 knn > results/quick/kdtree_quick.txt 2>&1

echo "✅ 快速测试完成！"
echo "结果文件："
ls -lh results/quick/