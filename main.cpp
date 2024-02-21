#include <iostream>
#include <thread>
#include <chrono>
#include "instruments/scissors.h"

int main()
{
    std::cout << "start" << std::endl;

    Scissors s("/dev/ttyUSB0");
    if (!s.initialize()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    // 整体旋转
    for (int i = 0; i < 80; ++i) {
        s.control({0, 100, 0, 0});
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    // 整体旋转(负方向)
    for (int i = 0; i < 80; ++i) {
        s.control({0, -100, 0, 0});
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    // 摆动
    for (int i = 0; i < 50; ++i) {
        s.control({0, 0, 100, 0});
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    
    // 摆动(负方向)
    for (int i = 0; i < 60; ++i) {
        s.control({0, 0, -100, 0});
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    // 剪打开（需要同时控制两个关节）
    for (int i = 0; i < 50; ++i) {
        s.control({100, 0, 0, 100});
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    // 剪关闭（需要同时控制两个关节）
    for (int i = 0; i < 70; ++i) {
        s.control({-100, 0, 0, -100});
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    s.uninitialize();

    return 0;
}