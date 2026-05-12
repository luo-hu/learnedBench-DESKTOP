# cmake_minimum_required(VERSION 3.16)

# project(learnedbench)

# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Release)
# endif()


# set(CMAKE_CXX_FLAGS "-mbmi2 -O3 -DNDEBUG")
# # set(CMAKE_CXX_FLAGS "-mbmi2 -Wall -Wextra")
# # set(CMAKE_CXX_FLAGS_DEBUG "-g")
# # set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# option(PROFILE "whether starting heap profile" OFF)
# option(RSMI "whether building RSMI" OFF)


# #set(BOOST_ROOT "/home/qiyu/boost_1_79_0")
# #set(Boost_INCLUDE_DIR "/home/qiyu/boost_1_79_0")
# #set(Boost_LIBRARY_DIR "/home/qiyu/boost_1_79_0/stage/lib")

# set(BOOST_ROOT "/usr/local/boost-1.79")
# set(Boost_INCLUDE_DIR "/usr/local/boost-1.79/include")
# set(Boost_LIBRARY_DIR "/usr/local/boost-1.79/lib")

# SET(EXECUTABLE_OUTPUT_PATH "/home/lh/Code/learnedbench/build/bin")

# #SET(EXECUTABLE_OUTPUT_PATH "/home/qiyu/learnedbench/build/bin")


# # check dependencies
# #set(TPIE_INCLUDE_DIR "/usr/local/lib/include")
# #set(TPIE_LIBRARIES "/usr/local/lib")
# #include_directories(${TPIE_INCLUDE_DIRS})
# find_package(TPIE REQUIRED)

# find_package(Boost 1.79.0 REQUIRED COMPONENTS program_options system filesystem)
# find_package(GEOS REQUIRED)

# if(PROFILE)
#   find_package(benchmark REQUIRED)
#   add_definitions(-DHEAP_PROFILE)
# endif()

# if(RSMI)
#   # the RSMI benchmark needs to be compiled using cxx14
#   # the dependency libtorch can be downloaded from 
#   set(CMAKE_CXX_STANDARD 14)
#   set(CMAKE_CXX_STANDARD_REQUIRED ON)

#   #set(TORCH_PATH "/home/qiyu/libtorch")
#   set(TORCH_PATH "/usr/local/libtorch")
#   list(APPEND CMAKE_PREFIX_PATH TORCH_PATH)
#   find_package(Torch REQUIRED PATHS ${TORCH_PATH} CONFIG)

#   # RSMI library path
#   set(RSMI_PATH "/home/lh/Code/learnedbench/indexes/rsmi")

#   include_directories(${Boost_INCLUDE_DIR} ${TPIE_INCLUDE_DIRS} ${RSMI_PATH})

#   #if(PROFILE)
#     #add_executable(bench_rsmi_hp bench/bench_rsmi.cpp)
#     #target_link_libraries(bench_rsmi_hp ${TPIE_LIBRARIES} ${TORCH_LIBRARIES} Boost::system Boost::filesystem pthread "${RSMI_PATH}/build/librsmi.a" -ltcmalloc)
#   #else()
#     #add_executable(bench_rsmi bench/bench_rsmi.cpp)
#     #target_link_libraries(bench_rsmi ${TPIE_LIBRARIES} ${TORCH_LIBRARIES} Boost::system Boost::filesystem pthread "${RSMI_PATH}/build/librsmi.a")
#   #endif()
#   #重写if(PROFILE)
#   if(PROFILE)
#     add_executable(bench_rsmi_hp bench/bench_rsmi.cpp)
#     target_link_libraries(bench_rsmi_hp 
#         ${TPIE_LIBRARIES} 
#         ${TORCH_LIBRARIES} 
#         Boost::system 
#         Boost::filesystem 
#         pthread 
#         "${RSMI_PATH}/build/librsmi.a" 
#         -ltcmalloc
#         snappy  # 添加 Snappy 库
#     )
#   else()
#     add_executable(bench_rsmi bench/bench_rsmi.cpp)
#     target_link_libraries(bench_rsmi 
#         ${TPIE_LIBRARIES} 
#         ${TORCH_LIBRARIES} 
#         Boost::system 
#         Boost::filesystem 
#         pthread 
#         "${RSMI_PATH}/build/librsmi.a"
#         snappy  # 添加 Snappy 库
#     )
#   endif()

# else()
#   # the other benchmarks are compiled using cxx17 (required by PGM-Index)
#   set(CMAKE_CXX_STANDARD 17)
#   set(CMAKE_CXX_STANDARD_REQUIRED ON)

#   # ANN library path
#   set(ANN_PATH "/home//learnedbench/indexes/ann_1.1.2")

#   include_directories(${Boost_INCLUDE_DIR} ${TPIE_INCLUDE_DIRS} ${RSMI_PATH} ${ANN_PATH})

#   #add_executable(datagen utils/datagen.cpp)
#   #target_link_libraries(datagen ${TPIE_LIBRARIES} Boost::program_options pthread)

# # 在创建目标之前查找所有依赖包
# find_package(Snappy REQUIRED)

# # 创建目标
# add_executable(datagen utils/datagen.cpp)


# # 链接所有必要的库
# target_link_libraries(datagen PRIVATE
#     tpie
#     snappy    # 直接使用库名称
#     lz4       # LZ4 压缩
#     zstd      # Zstandard 压缩
#     z         # zlib 压缩
#     Boost::program_options
#     pthread
# )
#   if(PROFILE)
#     add_executable(bench2d_hp bench/bench.cpp)
#     # 将绝对路径改为相对路径
#     #target_link_libraries(bench2d_hp ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a" -ltcmalloc)
#     target_link_libraries(bench2d_hp ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a" -ltcmalloc)

#   else()
#     # add_executable(bench2d_default bench/bench.cpp)
#     # target_link_libraries(bench2d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_default PUBLIC PARTITION_NUM=100)
    
#     # add_executable(bench2d_fs bench/bench.cpp)
#     # target_link_libraries(bench2d_fs ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_fs PUBLIC PARTITION_NUM=60)

#     # add_executable(bench2d_osm bench/bench.cpp)
#     # target_link_libraries(bench2d_osm ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_osm PUBLIC PARTITION_NUM=250)
    
#     #由于这些目标被注释，make 编译时不会生成 bench2d_fs、bench2d_osm 等可执行文件,下面

#     # 恢复 bench2d_fs 目标
#     add_executable(bench2d_fs bench/bench.cpp)
#     target_link_libraries(bench2d_fs PRIVATE
#         ${TPIE_LIBRARIES}
#         Boost::program_options
#         GEOS::geos
#         pthread
#         "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a"
#         snappy  # 确保包含必要的依赖库
#         lz4
#         zstd
#         z
#     )
#     target_compile_definitions(bench2d_fs PUBLIC PARTITION_NUM=60)

#     # 恢复 bench2d_osm 目标
#     add_executable(bench2d_osm bench/bench.cpp)
#     target_link_libraries(bench2d_osm PRIVATE
#         ${TPIE_LIBRARIES}
#         Boost::program_options
#         GEOS::geos
#         pthread
#         "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a"
#         snappy  # 包含必要的依赖库
#         lz4
#         zstd
#         z
#     )
#     target_compile_definitions(bench2d_osm PUBLIC PARTITION_NUM=250)

#     # add_executable(bench3d_toronto bench/bench.cpp)
#     # target_link_libraries(bench3d_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench3d_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20)

#     # add_executable(bench4d_default bench/bench.cpp)
#     # target_link_libraries(bench4d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench4d_default PUBLIC BENCH_DIM=4 PARTITION_NUM=10)

#     # add_executable(bench6d_default bench/bench.cpp)
#     # target_link_libraries(bench6d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench6d_default PUBLIC BENCH_DIM=6 PARTITION_NUM=5)

#     # add_executable(bench8d_default bench/bench.cpp)
#     # target_link_libraries(bench8d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench8d_default PUBLIC BENCH_DIM=8 PARTITION_NUM=4)

#     # add_executable(bench10d_default bench/bench.cpp)
#     # target_link_libraries(bench10d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench10d_default PUBLIC BENCH_DIM=10 PARTITION_NUM=3)

#     # add_executable(bench2d_1m_default bench/bench.cpp)
#     # target_link_libraries(bench2d_1m_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_1m_default PUBLIC PARTITION_NUM=23)

#     # add_executable(bench2d_10m_default bench/bench.cpp)
#     # target_link_libraries(bench2d_10m_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_10m_default PUBLIC PARTITION_NUM=70)

#     # add_executable(bench2d_50m_default bench/bench.cpp)
#     # target_link_libraries(bench2d_50m_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_50m_default PUBLIC PARTITION_NUM=158)

#     # add_executable(bench2d_100m_default bench/bench.cpp)
#     # target_link_libraries(bench2d_100m_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_100m_default PUBLIC PARTITION_NUM=223)

#     # add_executable(bench2d_e4_default bench/bench.cpp)
#     # target_link_libraries(bench2d_e4_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e4_default PUBLIC PARTITION_NUM=100 INDEX_ERROR_THRESHOLD=4)

#     # add_executable(bench2d_e16_default bench/bench.cpp)
#     # target_link_libraries(bench2d_e16_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e16_default PUBLIC PARTITION_NUM=100 INDEX_ERROR_THRESHOLD=16)

#     # add_executable(bench2d_e64_default bench/bench.cpp)
#     # target_link_libraries(bench2d_e64_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e64_default PUBLIC PARTITION_NUM=100 INDEX_ERROR_THRESHOLD=64)

#     # add_executable(bench2d_e256_default bench/bench.cpp)
#     # target_link_libraries(bench2d_e256_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e256_default PUBLIC PARTITION_NUM=100 INDEX_ERROR_THRESHOLD=256)

#     # add_executable(bench2d_e1024_default bench/bench.cpp)
#     # target_link_libraries(bench2d_e1024_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e1024_default PUBLIC PARTITION_NUM=100 INDEX_ERROR_THRESHOLD=1024)

#     # add_executable(bench2d_e4_fs bench/bench.cpp)
#     # target_link_libraries(bench2d_e4_fs ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e4_fs PUBLIC PARTITION_NUM=60 INDEX_ERROR_THRESHOLD=4)

#     # add_executable(bench2d_e16_fs bench/bench.cpp)
#     # target_link_libraries(bench2d_e16_fs ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e16_fs PUBLIC PARTITION_NUM=60 INDEX_ERROR_THRESHOLD=16)

#     # add_executable(bench2d_e64_fs bench/bench.cpp)
#     # target_link_libraries(bench2d_e64_fs ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e64_fs PUBLIC PARTITION_NUM=60 INDEX_ERROR_THRESHOLD=64)

#     # add_executable(bench2d_e256_fs bench/bench.cpp)
#     # target_link_libraries(bench2d_e256_fs ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e256_fs PUBLIC PARTITION_NUM=60 INDEX_ERROR_THRESHOLD=256)

#     # add_executable(bench2d_e1024_fs bench/bench.cpp)
#     # target_link_libraries(bench2d_e1024_fs ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench2d_e1024_fs PUBLIC PARTITION_NUM=60 INDEX_ERROR_THRESHOLD=1024)

#     # add_executable(bench3d_e4_toronto bench/bench.cpp)
#     # target_link_libraries(bench3d_e4_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench3d_e4_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20 INDEX_ERROR_THRESHOLD=4)

#     # add_executable(bench3d_e16_toronto bench/bench.cpp)
#     # target_link_libraries(bench3d_e16_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench3d_e16_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20 INDEX_ERROR_THRESHOLD=16)

#     # add_executable(bench3d_e64_toronto bench/bench.cpp)
#     # target_link_libraries(bench3d_e64_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench3d_e64_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20 INDEX_ERROR_THRESHOLD=64)

#     # add_executable(bench3d_e256_toronto bench/bench.cpp)
#     # target_link_libraries(bench3d_e256_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench3d_e256_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20 INDEX_ERROR_THRESHOLD=256)

#     # add_executable(bench3d_e1024_toronto bench/bench.cpp)
#     # target_link_libraries(bench3d_e1024_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     # target_compile_definitions(bench3d_e1024_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20 INDEX_ERROR_THRESHOLD=1024)

#     add_executable(bench2d_default bench/bench.cpp)
#     #target_link_libraries(bench2d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     #target_link_libraries(bench2d_default ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a")
#     #这个错误表明在链接 bench2d_default 时，TPIE 库需要 Snappy 库，但链接器找不到 Snappy 的符号。虽然之前已经为 datagen 目标添加了 Snappy 链接，但 bench2d_default 目标可能没有正确链接 Snappy。
#     target_link_libraries(bench2d_default PRIVATE
#     ${TPIE_LIBRARIES}
#     Boost::program_options
#     GEOS::geos
#     pthread
#     "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a"
#     tcmalloc
#     snappy  # 添加这一行
# )
#     target_compile_definitions(bench2d_default PUBLIC PARTITION_NUM=100)

#     add_executable(bench3d_toronto bench/bench.cpp)
#     #target_link_libraries(bench3d_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${ANN_PATH}/lib/libANN.a")
#     #target_link_libraries(bench3d_toronto ${TPIE_LIBRARIES} Boost::program_options GEOS::geos pthread "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a")
#     #这个错误表明在构建 bench3d_toronto 目标时出现了与之前相同的问题：TPIE 库需要 Snappy 库，但链接器找不到 Snappy 的符号。虽然您已经修复了 datagen 和 bench2d_default 的链接问题，但 bench3d_toronto 目标仍然缺少 Snappy 依赖。

# target_link_libraries(bench3d_toronto PRIVATE
#     ${TPIE_LIBRARIES}
#     Boost::program_options
#     GEOS::geos
#     pthread
#     "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2/lib/libANN.a"
#     tcmalloc
#     snappy
#     lz4
#     zstd
#     z
# )
#     target_compile_definitions(bench3d_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20)

    
#   endif()
# endif()

cmake_minimum_required(VERSION 3.16)
project(learnedbench)

# ========== 基础配置（修正：统一C++标准+路径） ==========
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# 修正：添加C++标准到编译FLAGS，与后续CMAKE_CXX_STANDARD联动
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mbmi2 -O3 -DNDEBUG -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# 修正：输出路径改为相对路径（基于build目录），提升可移植性
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# ========== 选项定义 ==========
option(PROFILE "whether starting heap profile" OFF)
option(RSMI "whether building RSMI" OFF)

# ========== 依赖查找（修正：移到最前，确保全局可用） ==========
# 1. Boost 配置（核心修正：添加NO_SYSTEM_PATHS，使用静态库）
set(BOOST_ROOT "/usr/local/boost-1.79")
set(Boost_NO_SYSTEM_PATHS ON)  # 强制使用指定的Boost 1.79，不混旧版本
set(Boost_USE_STATIC_LIBS ON)  # 使用静态库，避免动态库链接问题
set(Boost_INCLUDE_DIR "${BOOST_ROOT}/include")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib")
find_package(Boost 1.79 REQUIRED COMPONENTS program_options system filesystem)

# 2. 基础依赖（修正：全局查找，所有目标可用）
find_package(TPIE REQUIRED)
find_package(GEOS REQUIRED)
# find_package(Snappy REQUIRED)  # 移到全局，所有目标可引用Snappy::Snappy
# 1. 手动查找 Snappy
find_path(SNAPPY_INCLUDE_DIR NAMES snappy.h PATHS /usr/include /usr/local/include)
find_library(SNAPPY_LIBRARY NAMES snappy libsnappy PATHS /usr/lib/x86_64-linux-gnu /usr/local/lib)
if(NOT SNAPPY_INCLUDE_DIR OR NOT SNAPPY_LIBRARY)
  message(FATAL_ERROR "Snappy library not found! Install libsnappy-dev first.")
endif()

# 手动查找LZ4（替代find_package(LZ4 REQUIRED)）
find_path(LZ4_INCLUDE_DIR NAMES lz4.h PATHS /usr/include /usr/local/include)
find_library(LZ4_LIBRARY NAMES lz4 liblz4 PATHS /usr/lib/x86_64-linux-gnu /usr/local/lib)
if(NOT LZ4_INCLUDE_DIR OR NOT LZ4_LIBRARY)
  message(FATAL_ERROR "LZ4 library not found! Install liblz4-dev first.")
endif()

# 手动查找ZSTD（替代find_package(ZSTD REQUIRED)）
find_path(ZSTD_INCLUDE_DIR NAMES zstd.h PATHS /usr/include /usr/local/include)
find_library(ZSTD_LIBRARY NAMES zstd libzstd PATHS /usr/lib/x86_64-linux-gnu /usr/local/lib)
if(NOT ZSTD_INCLUDE_DIR OR NOT ZSTD_LIBRARY)
  message(FATAL_ERROR "ZSTD library not found! Install libzstd-dev first.")
endif()

find_package(ZLIB REQUIRED)    # 显式查找ZLib（TPIE依赖）

# 3. Profile模式依赖
if(PROFILE)
  find_package(benchmark REQUIRED)
  add_definitions(-DHEAP_PROFILE)
  # 查找tcmalloc（修正：显式查找，避免直接写-ltcmalloc）
  find_library(TCMALLOC_LIB tcmalloc PATHS /usr/lib /usr/local/lib)
  if(NOT TCMALLOC_LIB)
    message(FATAL_ERROR "tcmalloc library not found!")
  endif()
endif()

# ========== RSMI模式编译（修正：变量作用域+链接规范） ==========
if(RSMI)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器扩展，提升兼容性

  # 修正：Torch路径变量加${}
  set(TORCH_PATH "/usr/local/libtorch")
  list(APPEND CMAKE_PREFIX_PATH ${TORCH_PATH})
  find_package(Torch REQUIRED PATHS ${TORCH_PATH} CONFIG)

  # RSMI路径定义（全局可见）
  set(RSMI_PATH "/home/lh/Code/learnedbench/indexes/rsmi")

  # 构建bench_rsmi（修正：目标级include，避免全局污染）
  if(PROFILE)
    add_executable(bench_rsmi_hp bench/bench_rsmi.cpp)
    target_link_libraries(bench_rsmi PRIVATE
      ${TPIE_LIBRARIES}
      ${TORCH_LIBRARIES}
      pthread
      "${RSMI_PATH}/build/librsmi.a"
      ${SNAPPY_LIBRARY}
      ${LZ4_LIBRARY}
      ${ZSTD_LIBRARY}
      ZLIB::ZLIB
      Boost::program_options
      Boost::filesystem  # 先写依赖方
      Boost::system      # 后写被依赖方（解决 undefined reference）
      # 兜底：显式指定 system 库绝对路径，确保链接器找到
      /usr/local/boost-1.79/lib/libboost_system.so.1.79.0
    )
    target_link_libraries(bench_rsmi_hp PRIVATE
      ${TPIE_LIBRARIES}
      ${TORCH_LIBRARIES}
      ${TCMALLOC_LIB}
      pthread
      "${RSMI_PATH}/build/librsmi.a"
      ${SNAPPY_LIBRARY}
      ${LZ4_LIBRARY}
      ${ZSTD_LIBRARY}
      ZLIB::ZLIB
      Boost::program_options
      Boost::filesystem
      Boost::system
      /usr/local/boost-1.79/lib/libboost_system.so.1.79.0
    )
  else()
    add_executable(bench_rsmi bench/bench_rsmi.cpp)
    target_include_directories(bench_rsmi PRIVATE
      ${Boost_INCLUDE_DIR}
      ${TPIE_INCLUDE_DIRS}
      ${RSMI_PATH}
      ${TORCH_INCLUDE_DIRS}
    )
    target_link_libraries(bench_rsmi PRIVATE
      ${TPIE_LIBRARIES}
      ${TORCH_LIBRARIES}
      pthread
      "${RSMI_PATH}/build/librsmi.a"
      ${SNAPPY_LIBRARY}
      ${LZ4_LIBRARY}
      ${ZSTD_LIBRARY}
      ZLIB::ZLIB
      -Wl,--no-as-needed  # 强制链接所有 Boost 依赖
      Boost::program_options
      Boost::filesystem
      Boost::system
    )
  endif()

# ========== 非RSMI模式编译（修正：变量/链接/作用域） ==========
else()
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)

  # ANN路径定义（全局可见）
  set(ANN_PATH "${CMAKE_SOURCE_DIR}/indexes/ann_1.1.2")
  # 修正：RSMI_PATH未定义问题，赋空值
  set(RSMI_PATH "" CACHE PATH "RSMI path (unused in non-RSMI mode)")

  # 构建datagen（修正：用官方命名空间目标）
  add_executable(datagen utils/datagen.cpp)
  target_include_directories(datagen PRIVATE
    ${Boost_INCLUDE_DIR}
    ${TPIE_INCLUDE_DIRS}
    ${ANN_PATH}
  )
  target_link_libraries(datagen PRIVATE
    ${TPIE_LIBRARIES}
    Boost::program_options
    pthread
    ${SNAPPY_LIBRARY}
    ${LZ4_LIBRARY}
    ${ZSTD_LIBRARY}
    ZLIB::ZLIB
  )

  # 构建bench2d_fs
  add_executable(bench2d_fs bench/bench.cpp)
  target_include_directories(bench2d_fs PRIVATE
    ${Boost_INCLUDE_DIR}
    ${TPIE_INCLUDE_DIRS}
    ${ANN_PATH}
  )
  target_link_libraries(bench2d_fs PRIVATE
    ${TPIE_LIBRARIES}
    Boost::program_options
    GEOS::geos
    pthread
    "${ANN_PATH}/lib/libANN.a"
    ${SNAPPY_LIBRARY}
    ${LZ4_LIBRARY}
    ${ZSTD_LIBRARY}
    ZLIB::ZLIB
  )
  target_compile_definitions(bench2d_fs PUBLIC PARTITION_NUM=60)

  # 构建bench2d_osm
  add_executable(bench2d_osm bench/bench.cpp)
  target_include_directories(bench2d_osm PRIVATE
    ${Boost_INCLUDE_DIR}
    ${TPIE_INCLUDE_DIRS}
    ${ANN_PATH}
  )
  target_link_libraries(bench2d_osm PRIVATE
    ${TPIE_LIBRARIES}
    Boost::program_options
    GEOS::geos
    pthread
    "${ANN_PATH}/lib/libANN.a"
    ${SNAPPY_LIBRARY}
    ${LZ4_LIBRARY}
    ${ZSTD_LIBRARY}
    ZLIB::ZLIB
  )
  target_compile_definitions(bench2d_osm PUBLIC PARTITION_NUM=250)

  # 构建bench2d_default
  add_executable(bench2d_default bench/bench.cpp)
  target_include_directories(bench2d_default PRIVATE
    ${Boost_INCLUDE_DIR}
    ${TPIE_INCLUDE_DIRS}
    ${ANN_PATH}
  )
  target_link_libraries(bench2d_default PRIVATE
    ${TPIE_LIBRARIES}
    Boost::program_options
    GEOS::geos
    pthread
    "${ANN_PATH}/lib/libANN.a"
    ${SNAPPY_LIBRARY}
    ${LZ4_LIBRARY}
    ${ZSTD_LIBRARY}
    ZLIB::ZLIB
  )
  if(PROFILE)
    target_link_libraries(bench2d_default PRIVATE ${TCMALLOC_LIB})
  endif()
  target_compile_definitions(bench2d_default PUBLIC PARTITION_NUM=100)

  # 构建bench3d_toronto
  add_executable(bench3d_toronto bench/bench.cpp)
  target_include_directories(bench3d_toronto PRIVATE
    ${Boost_INCLUDE_DIR}
    ${TPIE_INCLUDE_DIRS}
    ${ANN_PATH}
  )
  target_link_libraries(bench3d_toronto PRIVATE
    ${TPIE_LIBRARIES}
    Boost::program_options
    GEOS::geos
    pthread
    "${ANN_PATH}/lib/libANN.a"
    ${SNAPPY_LIBRARY}
    ${LZ4_LIBRARY}
    ${ZSTD_LIBRARY}
    ZLIB::ZLIB
  )
  if(PROFILE)
    target_link_libraries(bench3d_toronto PRIVATE ${TCMALLOC_LIB})
  endif()
  target_compile_definitions(bench3d_toronto PUBLIC BENCH_DIM=3 PARTITION_NUM=20)

endif()