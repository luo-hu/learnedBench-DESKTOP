#include <tpie/tpie.h>
#include <tpie/stream.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    try {
        // 设置并清理临时目录
        std::string temp_dir = "/home/lh/Code/learnedbench/temp/tpie_test";
        fs::create_directories(temp_dir);
        for (const auto &entry : fs::directory_iterator(temp_dir)) {
            fs::remove_all(entry.path());
        }
        
        setenv("TPIE_TEMP", temp_dir.c_str(), 1);
        setenv("TPIE_MAX_MEM", "1073741824", 1);
        
        // 初始化 TPIE
        tpie::tpie_init();
        
        // 创建并写入一个简单的 TPIE 流
        {
            tpie::file_stream<int> stream;
            stream.open("test.tpie");
            stream.write(42);
            stream.close();
        }
        
        // 读取 TPIE 流
        {
            tpie::file_stream<int> stream;
            stream.open("test.tpie");
            int value = stream.read();
            std::cout << "Read from TPIE stream: " << value << std::endl;
            stream.close();
        }
        
        tpie::tpie_finish();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        tpie::tpie_finish();
        return 1;
    }
}