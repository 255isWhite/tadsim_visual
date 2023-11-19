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
  std::cerr<<"Enter main function\n";
  system("roscore&");
  // ros 初始化
  ros::init(argc,argv,"camera_node");
  auto nh = ros::NodeHandle();
  
  // CameraFun这个class的实例化，用的是shared_ptr
  std::shared_ptr<tx_sim::SimModule> module = std::make_shared<CameraFun>(nh);
  tx_sim::SimModuleService service;
  std::cerr<<"Server service\n";

  // SimModuleService类的Server（），Wait（）函数调用
  service.Serve(name, module);
  service.Wait();
  std::cerr<<"wait\n";
  exit(0);
  return 0;
}
