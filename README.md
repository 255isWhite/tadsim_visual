# <div align="center">tadsim_visual</div>

<div align="center">
    <!-- an image which can properly describe this repository -->
    <!-- images are stored under .github/images -->
    <img src=".github/images/cover.png" width="850">
    <p>
    腾讯TAD SIM自动驾驶仿真软件视觉仿真示例.
    </p>


简体中文 | [English](.github/README_en.md)

</div>

## <div align="center">前期基础</div>
<!-- setting details to open will display all below  -->
<details open>
<summary>环境依赖</summary>

<!-- names of dependencies and websites if had -->
- [OpenCV 3.4.16](https://opencv.org/releases/)
- [Ubuntu 20.04.06 LTS](https://ubuntu.com/download/alternative-downloads)
- [ROS Noetic](https://wiki.ros.org/noetic/Installation/Ubuntu)
- tadsim 2.87.1624

    <!-- some details about environment if needed -->  

</details>

<details open>
<summary>快速上手</summary>

1. 在本地主机上安装好上述环境依赖;
   
2. 进入本地ROS工作空间下的/src文件夹，克隆visual示例并编译
    ```bash
    git clone git@github.com:255isWhite/tadsim_visual.git
    ## or 
    git clone https://github.com/255isWhite/tadsim_visual.git
    ```
    ```
    catkin_make -DCATKIN_WHITELIST_PKGS=tadsim_visual
    ```

3. 配置TAD Sim
    ```bash
    ## 在终端打开tadsim
    tadsim
    ```
    自定义模块
    - 模块名称：CameraIO
    - 可执行文件路径：功能包编译后生成的可执行文件，例如/home/robot/catkin_ws/devel/lib/tadsim_visual/camera_node
    - 依赖路径：["/lib/x86_64-linux-gnu","/opt/tadsim/resources/app/service/simdeps","/opt/ros/noetic/lib/"]
    - 初始化参数：Height=1208（**手动换行**）Width=1920

    模组配置
    - 确保包含Display和CameraIO模块

    主车配置
    - 确保主车搭载摄像头，分辨率为1920*1208，建议摄像头位置(x,y,z)为(150,0,180)

4. 接口运行

    TAD Sim内选定场景点击运行，在下方终端内选择CameraIO选项卡，可以查看相关程序输出。
    ```bash
    rviz -d catkin_ws/src/tadsim_visual/config/image.rviz 
    ```
    此时在Rviz窗口内可以接收到话题为/tadsim_img的图像数据了，若未能成功，请检查上述步骤。



</details>

<details open>
<summary>已知Bug</summary>
  
- TAD Sim必须在终端内输入tadsim启动，否则会和ROS相关环境变量发生冲突


</details>

<!-- <details off>
<summary>Anything you wanna add here</summary>
Some descriptions for this.

</details>

## <div align="center">Anything you wanna add here</div>
<details open>
<summary>Anything</summary>

<p>To be done</p>

</details>

<details open>
<summary>Anything</summary>
<p>To be done</p>
</details>

<details open>
<summary>Anything</summary>
<p>To be done</p>
</details> -->

## <div align="center">Contact</div>
Welcome all questions in issues tag or if u wanna contact me at nocap.wzh@gmail.com