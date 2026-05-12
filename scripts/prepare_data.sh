#!/bin/bash
#这是shell脚本语言

DATA_PATH="../data/"
BENCH_BIN="../build/bin/datagen"

if [ -e "$DATA_PATH" ]; then
    echo "$DATA_PATH 已经存在"
else
    echo "$DATA_PATH 不存在,已创建成功"
    mkdir -p "$DATA_PATH"
fi

REAL_DATA_PATH="${DATA_PATH}real/"
SYN_DATA_PATH="${DATA_PATH}synthetic/"
# 在合成数据目录下创建Default子目录
DEFAULT_PATH="${SYN_DATA_PATH}Default/"
if [ -e "$REAL_DATA_PATH" ]; then
    echo "$REAL_DATA_PATH 已经存在"
else
    echo "$REAL_DATA_PATH 不存在,已创建成功"
    mkdir -p "$REAL_DATA_PATH"
fi

if [ -e "$SYN_DATA_PATH" ]; then
    echo "$SYN_DATA_PATH 已经存在"
else
    echo "$SYN_DATA_PATH 不存在，已创建成功"
    mkdir -p "$SYN_DATA_PATH"
fi

DEFAULT_PATH="${SYN_DATA_PATH}Default/"
if [ -e "$DEFAULT_PATH" ]; then
    echo "$DEFAULT_PATH 已经存在"
else
    echo "$DEFAULT_PATH 不存在，已创建成功"
    mkdir -p "$DEFAULT_PATH"
fi


# real data 
echo "Download real datasets..."
#wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=11SaFlD7VifETSgSfsQzKNUrE4SW9Cz47' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=11SaFlD7VifETSgSfsQzKNUrE4SW9Cz47" -O real_data.zip && rm -rf /tmp/cookies.txt
#wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=11SaFlD7VifETSgSfsQzKNUrE4SW9Cz47' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=11SaFlD7VifETSgSfsQzKNUrE4SW9Cz47" -O real_data.zip && rm -rf /tmp/cookies.txt

# if [ -f dreal_data.zip ]; then
    # echo "start unzip real_data.zip"
    # unzip -d $REAL_DATA_PATH real_data.zip
    # rm real_data.zip
# else
#     echo "Download failed."
#     echo "Please manualy download the dataset from https://drive.google.com/file/d/11SaFlD7VifETSgSfsQzKNUrE4SW9Cz47/view"
#     echo "Then unzip it to ${REAL_DATA_PATH}."
# fi
# 明确指定 real_data.zip 的路径（基于 $REAL_DATA_PATH 变量）
ZIP_FILE="${REAL_DATA_PATH}/real_data.zip"

echo "start unzip $ZIP_FILE"
if [ -f "$ZIP_FILE" ]; then
    unzip -d "$REAL_DATA_PATH" "$ZIP_FILE"  # 解压到目标目录
    rm "$ZIP_FILE"  # 删除源 zip 文件
else
    echo "real_data.zip 不存在于 $REAL_DATA_PATH 目录"
fi


# synthetic data
MILLION=1000000
DEFAULT_N=20
DEFAULT_D=2
DEFAULT_S=1

# varying dataset size N
echo "Generate data by varying different N..."
for dist in "uniform" "gaussian" "lognormal"
do
    for n in 1 10 50 100
    do
        fname="${dist}_${n}m_${DEFAULT_D}_${DEFAULT_S}"
        real_n=$[$n * $MILLION] 
        $BENCH_BIN -t gen_data -f $fname --dist $dist -n $real_n -d $DEFAULT_D -s $DEFAULT_S
        mv $fname "${SYN_DATA_PATH}"
    done
done
    
# varying dimension d
echo "Generate data by varying different Dim..."
for dist in "uniform" "gaussian" "lognormal"
do
    for d in 2 4 6 8 10
    do
        fname="${dist}_${DEFAULT_N}m_${d}_${DEFAULT_S}"
        real_n=$[$DEFAULT_N * $MILLION]
        $BENCH_BIN -t gen_data -f $fname --dist $dist -n $real_n -d $d -s $DEFAULT_S
        mv $fname "${SYN_DATA_PATH}"
    done
done

# default setting
echo "Generate default data..."
for dist in "uniform" "gaussian" "lognormal"
do
    fname="${dist}_${DEFAULT_N}m_${DEFAULT_D}_${DEFAULT_S}"
    real_n=$[$DEFAULT_N * $MILLION]
    $BENCH_BIN -t gen_data -f $fname --dist $dist -n $real_n -d $DEFAULT_D -s $DEFAULT_S
    mv $fname "${SYN_DATA_PATH}Default"
done
