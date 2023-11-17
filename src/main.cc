// 系统头文件
#include <memory>
#include <iostream>
#include <fstream>

// 自定义头文件
#include "txsim_module_service.h"
#include "CameraFun.h"

int main(int argc, char** argv) {
  std::string name="CameraIO";
  // 自动打开roscore
  std::cerr<<"enter main function\n";
  //system("roscore&");
  // ros 初始化
  ros::init(argc,argv,"camera_node");
  std::cerr<<"enter main function\n";
  auto nh = ros::NodeHandle();
  std::cerr<<"enter main function\n";
  
  // 重定位cout的输出至home目录下info.txt文件
  // 默认log地址为~/.config/tadsim/log/user_log
  // std::ofstream of("info.txt");
  // std::streambuf* cout_buf = std::cout.rdbuf(of.rdbuf());
  
  // CameraFun这个class的实例化，用的是shared_ptr
  std::shared_ptr<tx_sim::SimModule> module = std::make_shared<CameraFun>(nh);
  std::cerr<<"enter main function\n";
  tx_sim::SimModuleService service;
  std::cerr<<"server\n";

  // SimModuleService类的Server（），Wait（）函数调用
  service.Serve(name, module);
  service.Wait();
  std::cerr<<"wait\n";
  exit(0);
  return 0;
}
