# MindVision

### 设置增益：

```cpp
MVSDK_API  CameraSetAnalogGain(CameraHandle hCamera, INT iAnalogGain);
/// \brief 设置相机的图像模拟增益值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iAnalogGain 设定的模拟增益值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。
iAnalogGain取值： 1-255
```

### 设置曝光：

```cpp
MVSDK_API CameraSdkStatus __stdcall CameraSetExposureTime(
    CameraHandle    hCamera, 
    double          fExposureTime
);
/// \brief 设置曝光时间。单位为微秒。
/// \param [in] hCamera 相机的句柄。
/// \param [in] fExposureTime 曝光时间，单位微秒。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。
fExposureTime:0-13925,单位us
由整数（1-1048565）乘上一个double m_fExpLineTime(13.279352) 得到

```

### 设定伽马值：

```cpp
MVSDK_API CameraSdkStatus __stdcall CameraSetGamma(
    CameraHandle    hCamera, 
    int             iGamma
);
/// \brief 设定LUT动态生成模式下的Gamma值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iGamma     要设定的Gamma值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。
iGamma: 0-250

```

### 设定对比度:

```cpp
MVSDK_API CameraSdkStatus __stdcall CameraSetContrast(
    CameraHandle    hCamera, 
    int             iContrast
);
/// \brief 设定LUT动态生成模式下的对比度值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iContrast  设定的对比度值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)
iContrast: 0-200
```

### 设置分辨率：

```cpp
MVSDK_API CameraSdkStatus __stdcall CameraSetImageResolution(
    CameraHandle            hCamera, 
    tSdkImageResolution*    pImageResolution
);
/// \brief 设置预览的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pImageResolution 新分辨率。

typedef struct
{
  INT     iIndex;				/// 索引号，[0,N]表示预设的分辨率(N 为预设分辨率的最大个数，一般不超过20),OXFF 表示自定义分辨率(ROI) 
  char    acDescription[32];	/// 该分辨率的描述信息。仅预设分辨率时该信息有效。自定义分辨率可忽略该信息 
  UINT    uBinSumMode;			/// BIN(求和)的模式,范围不能超过tSdkResolutionRange.uBinSumModeMask 
  UINT    uBinAverageMode;		/// BIN(求均值)的模式,范围不能超过tSdkResolutionRange.uBinAverageModeMask 
  UINT    uSkipMode;			/// 是否SKIP的尺寸，为0表示禁止SKIP模式，范围不能超过tSdkResolutionRange.uSkipModeMask
  UINT    uResampleMask;		/// 硬件重采样的掩码 
  INT     iHOffsetFOV;			/// 采集视场相对于Sensor最大视场左上角的水平偏移 
  INT     iVOffsetFOV;			/// 采集视场相对于Sensor最大视场左上角的垂直偏移 
  INT     iWidthFOV;			/// 采集视场的宽度 
  INT     iHeightFOV;			/// 采集视场的高度 
  INT     iWidth;				/// 相机最终输出的图像的宽度 
  INT     iHeight;				/// 相机最终输出的图像的高度 
  INT     iWidthZoomHd;			/// 硬件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0. 
  INT     iHeightZoomHd;		/// 硬件缩放的高度,不需要进行此操作的分辨率，此变量设置为0. 
  INT     iWidthZoomSw;			/// 软件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0. 
  INT     iHeightZoomSw;		/// 软件缩放的高度,不需要进行此操作的分辨率，此变量设置为0.
} tSdkImageResolution;

设置分辨率前先调用CameraGetImageResolution来获取当前的分辨率信息
tSdkImageResolution sImageSize;
CameraGetImageResolution(m_hCamera,&sImageSize)
```

