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
/// @ingroup API_EXPOSURE
/// \~chinese
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
/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设定LUT动态生成模式下的Gamma值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iGamma     要设定的Gamma值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)。
iGamma: 0-250

```

### 设定对比度:

```cpp
/// @ingroup API_ENHANCE
/// \~chinese
/// \brief 设定LUT动态生成模式下的对比度值。
/// \param [in] hCamera 相机的句柄。
/// \param [in] iContrast  设定的对比度值。
/// \return 成功返回 CAMERA_STATUS_SUCCESS(0)
MVSDK_API CameraSdkStatus __stdcall CameraSetContrast(
    CameraHandle    hCamera, 
    int             iContrast
);
iContrast: 0-200
```

### 设置分辨率：

```cpp
/// @ingroup API_ROI
/// \~chinese
/// \brief 设置预览的分辨率。
/// \param [in] hCamera 相机的句柄。
/// \param [in] pImageResolution 新分辨率。
MVSDK_API CameraSdkStatus __stdcall CameraSetImageResolution(
    CameraHandle            hCamera, 
    tSdkImageResolution*    pImageResolution
);

typedef struct
{
  INT     iIndex;				///< \~chinese 索引号，[0,N]表示预设的分辨率(N 为预设分辨率的最大个数，一般不超过20),OXFF 表示自定义分辨率(ROI) \~english Index number, [0, N] indicates the preset resolution (N is the maximum number of preset resolutions, generally no more than 20), OXFF indicates custom resolution (ROI)
  char    acDescription[32];	///< \~chinese 该分辨率的描述信息。仅预设分辨率时该信息有效。自定义分辨率可忽略该信息 \~english The description of the resolution. This information is valid only when the resolution is preset. Custom resolution ignores this information
  UINT    uBinSumMode;			///< \~chinese BIN(求和)的模式,范围不能超过tSdkResolutionRange.uBinSumModeMask \~english The BIN (sum) mode cannot exceed the tSdkResolutionRange.uBinSumModeMask
  UINT    uBinAverageMode;		///< \~chinese BIN(求均值)的模式,范围不能超过tSdkResolutionRange.uBinAverageModeMask \~english BIN (average) mode, the range cannot exceed tSdkResolutionRange.uBinAverageModeMask 
  UINT    uSkipMode;			///< \~chinese 是否SKIP的尺寸，为0表示禁止SKIP模式，范围不能超过tSdkResolutionRange.uSkipModeMask \~english Whether the SKIP size is 0 indicates that the SKIP mode is disabled and the range cannot exceed the tSdkResolutionRange.uSkipModeMask
  UINT    uResampleMask;		///< \~chinese 硬件重采样的掩码 \~english Hardware resampling mask
  INT     iHOffsetFOV;			///< \~chinese 采集视场相对于Sensor最大视场左上角的水平偏移 \~english The horizontal offset of the acquisition field of view relative to the top left corner of the Sensor's largest field of view
  INT     iVOffsetFOV;			///< \~chinese 采集视场相对于Sensor最大视场左上角的垂直偏移 \~english The vertical offset of the acquisition field of view relative to the upper left corner of the Sensor's largest field of view
  INT     iWidthFOV;			///< \~chinese 采集视场的宽度 \~english The width of the field of view
  INT     iHeightFOV;			///< \~chinese 采集视场的高度 \~english The height of the field of view
  INT     iWidth;				///< \~chinese 相机最终输出的图像的宽度 \~english The width of the final output image of the camera
  INT     iHeight;				///< \~chinese 相机最终输出的图像的高度 \~english The height of the final output image of the camera
  INT     iWidthZoomHd;			///< \~chinese 硬件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0. \~english The width of the hardware zoom, resolution that does not require this operation, this variable is set to 0.
  INT     iHeightZoomHd;		///< \~chinese 硬件缩放的高度,不需要进行此操作的分辨率，此变量设置为0. \~english The height of the hardware zoom, resolution that does not require this operation, this variable is set to 0.
  INT     iWidthZoomSw;			///< \~chinese 软件缩放的宽度,不需要进行此操作的分辨率，此变量设置为0. \~english The width of the software's zoom, which does not require the resolution of this operation, this variable is set to 0.
  INT     iHeightZoomSw;		///< \~chinese 软件缩放的高度,不需要进行此操作的分辨率，此变量设置为0. \~english The height of the software's zoom, which does not require the resolution of this operation, this variable is set to 0.
} tSdkImageResolution;

设置分辨率前先调用CameraGetImageResolution来获取当前的分辨率信息
tSdkImageResolution sImageSize;
CameraGetImageResolution(m_hCamera,&sImageSize)
```

