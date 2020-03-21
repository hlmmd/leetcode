# orbslam2

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

