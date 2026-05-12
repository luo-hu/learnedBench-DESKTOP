#!/bin/bash
# 快速测试脚本 - 测试 3 个索引在 1 个数据集上的性能    新建用来测试的，因为run_exp.sh耗时太长，所以先用quick_test.sh代替

# 设置 GEOS 库路径
export LD_LIBRARY_PATH=/usr/local/geos/lib:$LD_LIBRARY_PATH

BENCH="./../build/bin/bench2d_default"
DATA_PATH="./../data/synthetic/Default/"
RESULT_PATH="./../results/quick_test/"

mkdir -p ${RESULT_PATH}

echo "======================================"
echo "  快速测试 - Learned Index Benchmark"
echo "======================================"
echo ""

# 只测试 uniform 数据集，测试 2 个常用索引
data="uniform_20m_2_1"
N=20000000  # 数据点数量：2000万
for index in "rtree" "zm"
do
    echo "▶ Testing ${index} on ${data} (${N} points)..."
    ${BENCH} ${index} "${DATA_PATH}${data}" ${N} all > "${RESULT_PATH}${index}_${data}"

    if [ $? -eq 0 ]; then
        echo "  ✓ Completed"
    else
        echo "  ✗ Failed"
    fi
    echo ""
done

echo "======================================"
echo "测试完成！"
echo "结果保存在: ${RESULT_PATH}"
echo ""
echo "查看结果:"
echo "  cat ${RESULT_PATH}rtree_${data}"
echo "======================================"
