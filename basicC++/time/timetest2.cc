#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>

using namespace std;

int main() {
   // DEMO:通过获取两个时刻的时间，然后计算时间长度

    using namespace std::chrono;

    // Step one: 定义一个clock
    typedef system_clock sys_clk_t;

    // Step two: 分别获取两个时刻的时间
    typedef system_clock::time_point time_point_t;
    // 第1个时间
    time_point_t time01 = sys_clk_t::now();
    // 延时5秒
    std::this_thread::sleep_for(std::chrono::duration<int>(5));
    // 第2个时间
    time_point_t time02 = sys_clk_t::now();

    // Step three: 计算时间差
    cout << "dt_time(system_clock period) = " << (time02 - time01).count() << endl;

    typedef duration<int, std::ratio<1, 1000>> mili_sec_t;
    cout << "\ndt_time(user define period) = " << 
    (time_point_cast<mili_sec_t>(time02) - time_point_cast<mili_sec_t>(time01)).count() << endl;
    
    return 0;
}