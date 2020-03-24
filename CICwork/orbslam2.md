# orbslam2

## 环境安装

项目github地址：[https://github.com/raulmur/ORB_SLAM2](https://github.com/raulmur/ORB_SLAM2)

安装过程可以参考README.md文件

安装Pangolin [https://github.com/stevenlovegrove/Pangolin](https://github.com/stevenlovegrove/Pangolin)

cmake安装过程：

```bash
git clone https://github.com/stevenlovegrove/Pangolin
cd Pangolin
mkdir build
cmake ..
make
sudo make install
```

安装OpenCV

Required at leat 2.4.3. Tested with OpenCV 2.4.11 and OpenCV 3.2.

opencv 3.2下载地址：[https://github.com/opencv/opencv/archive/3.2.0.zip](https://github.com/opencv/opencv/archive/3.2.0.zip)

安装opencv的时候需要ippicv_linux_20151201.tgz文件，将其放在opencv-3.2.0/3rdparty/ippicv/downloads/ippicv_linux_20151201.tgz。

如果没有，安装脚本会自动下载，速度较慢

opencv 也使用cmake进行安装

安装Eigen3[http://eigen.tuxfamily.org](http://eigen.tuxfamily.org)

要求至少3.1.0版本

编译安装DBoW2 和 g2o （在ORB_slam项目的Thirdparty目录中）

ORB_SLAM项目本身也用cmake编译，在安装好所有的依赖环境后

```bash
mkdir build
cmake ..
make -j
```

在编译的过程中，可能会报错usleep函数未定义，添加头文件unistd.h即可

```cpp
#include <unistd.h>
```

## 运行测试

以Monocular单目slam为例，使用TUM数据集

下载数据集：[http://vision.in.tum.de/data/datasets/rgbd-dataset/download](http://vision.in.tum.de/data/datasets/rgbd-dataset/download)

将文件夹解压放在合适的位置，执行

```bash
./Examples/Monocular/mono_tum Vocabulary/ORBvoc.txt Examples/Monocular/TUM3.yaml PATH_TO_SEQUENCE_FOLDER
```

## 相机标定

使用棋盘标定

[http://graphics.cs.msu.ru/en/node/909](http://graphics.cs.msu.ru/en/node/909)

## 视频制作

对同一场景，从不同方向拍摄两个视频，20-30s即可

使用ffmpeg将视频转换成图片

在orbslam2 example中，所有图片都是以时间戳命名的，所以目前采用的方法是使用ffmpeg处理后，使用一段c++代码给图片打上时间戳，并产生对于的rgb.txt文件

```bash
#视频转图片命令：
ffmpeg -i input.mp4 output_%08d.png
```

建立文件夹存放图片，目录结构：注意将所有.png文件放入rgb子文件夹中

```bash
data1
├── rgb
│   └── ffmpeg1.rar
├── test
└── Timestamp.cc
```

执行c++程序后，会将所有图片名转换为时间戳，并生成rgb.txt文件，可用于执行orbslam算法

```bash
#输出参数N为图片个数，拍摄的数据集使用了480张图片
./test N
```

## 执行orb_slam2

目前执行的是Monocular版本

TUM.yaml根据TUM3.yaml进行修改，只需要修改fx,fy,cx,cy即可

```bash
Camera.fx: 832.369
Camera.fy: 831.622
Camera.cx: 671.344
Camera.cy: 622.046
```

```bash
./Examples/Monocular/mono_tum Vocabulary/ORBvoc.txt Examples/Monocular/TUM_phone.yaml ../data1/
```

生成的KeyFrameTrajectory.txt文件记录关键帧，此时相机坐标，相机四元式


