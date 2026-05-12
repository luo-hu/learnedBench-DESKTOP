/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-12 11:31:43
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-10-12 15:17:50
 * @FilePath: /learnedbench/utils/datagen.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// #include <boost/program_options.hpp>
// #include <ios>
// #include <iostream>
// #include <string>
// #include <tpie/tpie.h>
// #include "type.hpp"
// #include "datautils.hpp"

// namespace po = boost::program_options;

// int main(int argc, char const *argv[]) {
//     po::options_description desc("Allowed options");
//     desc.add_options()
//         ("help", "produce help message")
//         ("task,t", po::value<std::string>(), "tasks: gen_data, process_csv")
//         ("infname", po::value<std::string>(), "input data file name")
//         ("fname,f", po::value<std::string>(), "file name of generated data")
//         ("dist", po::value<std::string>(), "distribution used to generate data")
//         ("num,n", po::value<int>(), "number of points to be generated")
//         ("dim,d", po::value<int>(), "dimension of points to be generated")
//         ("scale,s", po::value<double>(), "distribution scale factor")
//     ;

//     po::variables_map vm;
//     po::store(po::parse_command_line(argc, argv, desc), vm);
//     po::notify(vm);

//     if (vm.count("help")) {
//         std::cout << desc << std::endl;
//         return 0;
//     }

//     tpie::tpie_init();
//     if (vm.count("task")) {
//         std::string task = vm["task"].as<std::string>();
//         if (task.compare("process_csv") == 0) {
//             if (vm.count("infname") && vm.count("fname")) {
//                 std::string infname = vm["infname"].as<std::string>();
//                 std::string outfname = vm["fname"].as<std::string>();
//                 bench::utils::csv_to_bin(infname, outfname);
//             } else {
//                 std::cout << "Please provide infname and fname." << std::endl;
//                 tpie::tpie_finish();
//                 return 1;
//             }
//         } else if (task.compare("gen_osmtiger") == 0) {
//             bench::utils::gen_OSMTIGER();
//         } else if (task.compare("gen_data") == 0) {
//             if (vm.count("fname") && vm.count("dist") && vm.count("num") && vm.count("dim") && vm.count("scale")) {
//                 std::string fname = vm["fname"].as<std::string>();
//                 std::string dist = vm["dist"].as<std::string>();
//                 int n = vm["num"].as<int>();
//                 int d = vm["dim"].as<int>();
//                 double s = vm["scale"].as<double>();

//                 if (dist.compare("uniform") == 0) {
//                     // generate uniform data
//                     std::cout << "Generate " << n << " * " << d << "D Uniform" << "(0, " << s << ") data to file: " << fname << std::endl;
//                     bench::utils::gen_uniform(fname, n, d, s);
//                 } else if (dist.compare("uniform_geo") == 0) {
//                     // generate gaussian data
//                     std::cout << "Generate " << n << " * " << d << "D Uniform Geo" << "(0, " << s << "^2) data to file: " << fname << std::endl;
//                     bench::utils::gen_uniform_geo(fname, n, d, s);
//                 } else if (dist.compare("zipfian_geo") == 0) {
//                     // generate gaussian data
//                     std::cout << "Generate " << n << " * " << d << "D Zipfian Geo" << "(0, " << s << "^2) data to file: " << fname << std::endl;
//                     bench::utils::gen_zipfian_geo(fname, n, d, s);
//                 } else if (dist.compare("gaussian") == 0) {
//                     // generate gaussian data
//                     std::cout << "Generate " << n << " * " << d << "D Gaussian" << "(0, " << s << "^2) data to file: " << fname << std::endl;
//                     bench::utils::gen_gaussian(fname, n, d, s);
//                 } else if (dist.compare("lognormal") == 0) {
//                     // generate lognormal data
//                     std::cout << "Generate " << n << " * " << d << "D Lognormal" << "(0, " << s << ") data to file: " << fname << std::endl;
//                     bench::utils::gen_lognormal(fname, n, d, s);
//                 } else {
//                     std::cout << "Arg --dist is in [uniform, gaussian, lognormal]." << std::endl;
//                     tpie::tpie_finish();
//                     return 1;
//                 }
//             } else {
//                 std::cout << "Please provide fname, dist, num, dim, and scale." << std::endl;
//                 tpie::tpie_finish();
//                 return 1;
//             }
//         } else {
//             std::cout << "Arg --task is in [gen_data, process_csv]." << std::endl;
//             tpie::tpie_finish();
//             return 1;
//         }
//     } else {
//         std::cout << "Specify a task." << std::endl;
//         std::cout << desc << std::endl;
//         tpie::tpie_finish();
//         return 1;
//     }

//     tpie::tpie_finish();
//     return 0;
// }

#include <boost/program_options.hpp>
#include <ios>
#include <iostream>
#include <string>
#include <tpie/tpie.h>
#include "type.hpp"
#include "datautils.hpp"

namespace po = boost::program_options;

int main(int argc, char const *argv[]) {
    // 定义允许的命令行选项
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message") 
        ("task,t", po::value<std::string>(), "tasks: gen_data, process_csv, gen_osmtiger") //指定任务类型：生成数据 处理csv数据  生成osmtiger
        ("infname", po::value<std::string>(), "input data file name")        //输入数据的文件名
        ("fname,f", po::value<std::string>(), "file name of generated data") //生成数据的文件名
        ("dist", po::value<std::string>(), "distribution used to generate data: uniform, uniform_geo, zipfian_geo, gaussian, lognormal")  //数据分布的类型
        ("num,n", po::value<int>(), "number of points to be generated")    //生成点的数量
        ("dim,d", po::value<int>(), "dimension of points to be generated") //生成点的维度
        ("scale,s", po::value<double>(), "distribution scale factor")      //分布比例因子
    ;

    // 解析命令行参数
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // 显示帮助信息
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    // 初始化TPIE库
    tpie::tpie_init();
    int returnCode = 0;

    try {
        // 检查是否指定了任务
        if (!vm.count("task")) {
            throw std::invalid_argument("Specify a task.");
        }

        std::string task = vm["task"].as<std::string>();

        if (task == "process_csv") {
            // 处理CSV文件任务
            if (!vm.count("infname") || !vm.count("fname")) {
                throw std::invalid_argument("Please provide infname and fname.");
            }
            
            std::string infname = vm["infname"].as<std::string>();
            std::string outfname = vm["fname"].as<std::string>();
            bench::utils::csv_to_bin(infname, outfname);
            
        } else if (task == "gen_osmtiger") {
            // 生成OSMTIGER数据任务
            bench::utils::gen_OSMTIGER();
            
        } else if (task == "gen_data") {
            // 生成数据任务
            if (!vm.count("fname") || !vm.count("dist") || !vm.count("num") || 
                !vm.count("dim") || !vm.count("scale")) {
                throw std::invalid_argument("Please provide fname, dist, num, dim, and scale.");
            }
            
            std::string fname = vm["fname"].as<std::string>();
            std::string dist = vm["dist"].as<std::string>();
            int n = vm["num"].as<int>();
            int d = vm["dim"].as<int>();
            double s = vm["scale"].as<double>();

            // 验证分布类型
            if (dist == "uniform") {
                std::cout << "Generate " << n << " * " << d << "D Uniform" << "(0, " << s << ") data to file: " << fname << std::endl;
                bench::utils::gen_uniform(fname, n, d, s);
            } else if (dist == "uniform_geo") {
                std::cout << "Generate " << n << " * " << d << "D Uniform Geo" << "(0, " << s << "^2) data to file: " << fname << std::endl;
                bench::utils::gen_uniform_geo(fname, n, d, s);
            } else if (dist == "zipfian_geo") {
                std::cout << "Generate " << n << " * " << d << "D Zipfian Geo" << "(0, " << s << "^2) data to file: " << fname << std::endl;
                bench::utils::gen_zipfian_geo(fname, n, d, s);
            } else if (dist == "gaussian") {
                std::cout << "Generate " << n << " * " << d << "D Gaussian" << "(0, " << s << "^2) data to file: " << fname << std::endl;
                bench::utils::gen_gaussian(fname, n, d, s);
            } else if (dist == "lognormal") {
                std::cout << "Generate " << n << " * " << d << "D Lognormal" << "(0, " << s << ") data to file: " << fname << std::endl;
                bench::utils::gen_lognormal(fname, n, d, s);
            } else {
                throw std::invalid_argument("Arg --dist is invalid. Allowed values: uniform, uniform_geo, zipfian_geo, gaussian, lognormal");
            }
            
        } else {
            throw std::invalid_argument("Arg --task is invalid. Allowed values: gen_data, process_csv, gen_osmtiger");
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << desc << std::endl;
        returnCode = 1;
    } catch (...) {
        std::cerr << "Error: An unknown error occurred." << std::endl;
        returnCode = 1;
    }

    // 清理TPIE库资源
    tpie::tpie_finish();
    return returnCode;
}