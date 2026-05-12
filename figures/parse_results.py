#!/usr/bin/env python3
"""
解析 results/default/ 目录下的实验结果
生成 notebook 可以使用的 Python 代码
"""

import os
import re
import glob

RESULT_PATH = "../results/default/"

def parse_result_file(filepath):
    """解析单个结果文件"""
    with open(filepath, 'r') as f:
        content = f.read()

    # 提取 range query 结果
    range_pattern = r'Sel=\[[\d., ]+\]\s+Avg\. Time:\s+([\d.]+)\s+\[us\]'
    range_times = [float(x) for x in re.findall(range_pattern, content)]

    # 提取 kNN query 结果
    knn_pattern = r'k=(\d+)\s+Avg\. Time:\s+([\d.]+)\s+\[us\]'
    knn_matches = re.findall(knn_pattern, content)
    knn_times = {int(k): float(t) for k, t in knn_matches}

    return {
        'range': range_times,
        'knn': knn_times
    }

def get_index_from_filename(filename):
    """从文件名提取索引类型和数据集名"""
    # 文件名格式: rtree_uniform_20m_2_1
    parts = os.path.basename(filename).replace('.txt', '').split('_')
    index = parts[0]
    dataset = '_'.join(parts[1:])  # 处理带下划线的数据集名
    return index, dataset

def main():
    # 查找所有结果文件
    result_files = glob.glob(os.path.join(RESULT_PATH, '*_20m_2_1*'))

    # 按数据集分组
    datasets = {
        'uniform': {},
        'gaussian': {},
        'lognormal': {}
    }

    for filepath in result_files:
        index, dataset = get_index_from_filename(filepath)

        # 确定数据集类型
        dataset_type = None
        for dtype in ['uniform', 'gaussian', 'lognormal']:
            if dtype in dataset:
                dataset_type = dtype
                break

        if not dataset_type:
            continue

        # 解析结果
        results = parse_result_file(filepath)
        datasets[dataset_type][index] = results

    # 生成 Python 代码
    print("=" * 60)
    print("# 复制以下代码到 notebook 中使用")
    print("=" * 60)
    print()

    for dtype in ['uniform', 'gaussian', 'lognormal']:
        print(f"# {dtype} dataset")
        print(f"range_{dtype} = {{")

        # 获取第一个索引的 range 查询数量
        first_index = list(datasets[dtype].keys())[0]
        n_range = len(datasets[dtype][first_index]['range'])

        # 输出 range query 数据
        for i, index in enumerate(sorted(datasets[dtype].keys())):
            range_times = datasets[dtype][index]['range']
            # 只取 5 个代表性的选择度
            selected_times = range_times[:5] if len(range_times) >= 5 else range_times
            print(f'    "{index}": {selected_times}' +
                  (',' if i < len(datasets[dtype]) - 1 else ''))
        print("}")

        print()

        # 输出 kNN query 数据
        print(f"knn_{dtype} = {{")

        # 获取 k 值
        k_values = [1, 10, 100, 1000, 10000]

        for i, index in enumerate(sorted(datasets[dtype].keys())):
            knn_times = datasets[dtype][index]['knn']
            selected_times = [knn_times.get(k, 0) for k in k_values]
            print(f'    "{index}": {selected_times}' +
                  (',' if i < len(datasets[dtype]) - 1 else ''))
        print("}")
        print()

if __name__ == "__main__":
    main()
