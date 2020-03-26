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

<<<<<<< HEAD
## 寻找最匹配关键帧

在运行orb_slam后，生成的KeyFrameTrajectory.txt记录了关键帧，使用ransac算法对两个视频的关键帧进行循环匹配，找到相似度最高的两张图片

## 匹配MapPoint，关联坐标

将视频2中的图片放入视频1中，得到对应的描述子和世界坐标。在视频2中也进行相应的操作，将结果输出到文件。

## 读取MapPoint，进行匹配

使用ransac算法，将坐标进行关联

## 使用SVD算法，获得旋转矩阵R(3*3)和平移矩阵t(3*1)

=======
points.txt记录所有的MapPoint坐标

## 寻找最匹配关键帧

在运行orb_slam后，生成的KeyFrameTrajectory.txt记录了关键帧，使用ransac算法对两个视频的关键帧进行循环匹配，找到相似度最高的两张图片

程序：compare.cc，读取两个KeyFrameTrajectory.txt，对每个关键帧进行匹配，最后输出相似度最高的两个关键帧的时间戳

```bash
#编译命令：

g++ -std=c++11 -o compare compare.cc `pkg-config opencv --cflags` `pkg-config opencv --libs`

#执行：
./compare

#运行结果
1584792784.403922 1584792968.012194
```

## 输出关键帧的描述子和3D坐标

这里我们用video2中的关键帧替换掉video1中的关键帧，这样在video1和video2两个不同坐标系统下对同一副图片进行计算，方便后续的匹配

在ORB运行的时候，找到上述两个关键帧，将描述子和坐标输出到文件中，进行匹配

在GrabImageMonocular函数执行完tracking()后，通过时间戳找帧

```cpp
//if ((fabs(1584792784.403922 - mCurrentFrame.mTimeStamp) < 1e-3))     //video1
if ((fabs(1584792968.012194 - mCurrentFrame.mTimeStamp) < 1e-3)) //video2
```

因为ORBslam运行过程中使用了很多随机数，不一定每次运行都能初始化成功，如果不成功，直接重新运行即可

输出MapPoint个数和对应的坐标到文件

第一行为个数，之后一行描述子(32个unsigned char)，一行坐标(3个point)

```cpp
fout << count << endl;

for (int i = 0; i < mCurrentFrame.N; i++)
{
    if (mCurrentFrame.mvpMapPoints[i] != NULL && mCurrentFrame.mvpMapPoints[i]->isBad() == false)
    {
        for (int j = 0; j < mCurrentFrame.mDescriptors.cols; j++)
            fout << static_cast<unsigned int>(mCurrentFrame.mDescriptors.at<uchar>(i, j)) << " ";
        fout << endl;
        auto mt = mCurrentFrame.mvpMapPoints[i]->GetWorldPos();
        fout << fixed << setprecision(7) << mt.at<float>(0, 0) << " " << mt.at<float>(0, 1) << " " << mt.at<float>(0, 2) << endl;
    }
}
```

执行完后对文件进行改名，避免第二次执行的时候覆盖

## 读取MapPoint，进行匹配

读取上一步生成的MapPoints-1.txt和MapPoint-2.txt，使用ransac算法，将3d坐标进行关联

代码文件：Match.cc

```bash
#编译命令
g++ -std=c++11 -o Match Match.cc `pkg-config opencv --cflags` `pkg-config opencv --libs`

# 执行
./Match

#运行结果
Match Points: 201
```

显式了匹配的点个数，并生成MatchPoints.txt

第一行为匹配点的个数

第二行起每行6个float，前3个为videos1中的点，后3个为video2的点，一一对应

## 使用SVD算法，获得旋转矩阵R(3*3)和平移矩阵t(3*1)

现在开始应用python进行处理，需要的输出文件为MatchPoints.txt、points-1.txt、points-2.txt

需要安装相应的库

```bash
pip install numpy
pip install matplotlib
```

>>>>>>> 3340893e0f457e2dd9ee97650165a8693afebe7a
[p' = R*PT+t](https://medium.com/machine-learning-world/linear-algebra-points-matching-with-svd-in-3d-space-2553173e8fed)

参考svd.py

<<<<<<< HEAD
=======
输出rotation maxtrix、translation maxtrix 和MSE

```cpp
('Rc', matrix([[ 0.45502858,  0.82279156, -0.34053346],
        [-0.86786103,  0.49540269,  0.03732843],
        [ 0.19941471,  0.27855022,  0.93949111]]))
('tc', matrix([[ 0.37559066],
        [-0.47055007],
        [ 0.1718546 ]]))
('RMSE:', 0.27144931727710353)
```

>>>>>>> 3340893e0f457e2dd9ee97650165a8693afebe7a
## 使用R、t将视频1的坐标进行转换

参考transform.py

<<<<<<< HEAD
## 画三维坐标点图，进行比较

参考draw.py
=======
需要修改Rc和Tc矩阵的值，修改为上一步得到的结果

```python
Rc = np.mat( [[ 0.45502858,  0.82279156, -0.34053346],
        [-0.86786103,  0.49540269,  0.03732843],
        [ 0.19941471,  0.27855022,  0.93949111]])

tc = np.mat( [[ 0.37559066],
        [-0.47055007],
        [ 0.1718546 ]])
```

## 画三维坐标点图，进行比较

参考draw.py

可以从各个角度观察转换后两个点集是否重合，以此判断转换矩阵是否合理。
>>>>>>> 3340893e0f457e2dd9ee97650165a8693afebe7a
