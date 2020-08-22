- 变动：
  - 根据ipad修改了app的布局，根据模拟器的效果来看，iphone应该也可以正常使用
  - 一次拍摄操作采集的所有文件（彩色图-png格式，深度图-png格式+bin格式），都存放在一个文件夹下面，以第一张图片的时间命名
  - 保留“multi depth”功能的前提下，增加了“Keep Save”功能，也就是开启后按“Photo”按钮会一直拍照，直到再一次按“Photo”按钮才会停下
  - 源码中的改动几乎都集中在`CameraViewController.swift`，代码附近带有“**楚门**”字样的都是我添加、修改的，所有**中文注释**也都是我加的
  - 增加了.bin格式的深度文件的可视化工具，放在`./VisualizationTool`下面
  
- 使用方法：
  - **单拍模式**：一次只拍一张。在app打开的初始状态下（“Depth”开关打开），按下底部的“photo”按钮开始拍照，拍一张后就会停止。
  - **multi depth模式**：即连续拍摄固定数量的图片。在app打开的初始状态下（“Depth”开关打开），打开”Multi Depth“开关，操作“➖➕”按钮调整旁边的数字，然后按下底部的“photo”按钮开始拍照，拍照数量到达要求后会停止拍照。拍照数量=“➖➕”按钮旁边的数字*10。
  - **Keep Save模式**：即连续拍照。在app打开的初始状态下（“Depth”开关打开），打开”Keep Save“开关，按下底部的“photo”按钮开始连续拍照，直到第二次按下“photo”按钮时拍照才会停止
  - **depth格式选择**：默认将一张depth同时保存bin和jpeg两种格式，可以通过`Depth->bin`和`Depth->png`两个开关来选择要保存的格式。
  - **深度图可视化**：将app保存的.bin文件(可以包含文件夹or其他文件，可视化工具会筛选出.bin文件的)从ipad/iphone导出后，存放在`./VisualizationTool/binfile`下面(里面已经放了一些文件/文件夹，当作示例)，然后运行camke工程，.bin文件会被读取然后根据最大、最小值归一化到0-255后保存为.png，存在`./VisualizationTool/pngfile`下面
  - **相机内参**：每次拍摄，都会在采集第一张图片的时候在xcode的输出界面现实相机内参。考虑到相机内参不变，我已经将其复制到`camera_intrinsic.txt`里面了

- 注意：
  - 单拍模式下，也会按照时间命名的文件夹存放
  - ”Keep Save“开关与”Multi Depth“开关（还有“➖➕”按钮）不能同时使用，因为它们是两种不同的拍照模式。使用其中一种的时候，另一种会被关闭并且禁用
  - 拍照的时候“photo”按钮下面会显示图片五个位置（中间、左上、右上、左下、右下）的深度值（单位mm）和当前已经拍照数量
  - 保存.bin格式的depth速度比保存.png格式的depth和rgb慢很多
  - `LiveDepth-iphone.rar`为我拿到的最原始的代码，可以用于对比修改



以下是原始的README.md文件
# AVCamPhotoFilter

Using AV Foundation to capture photos with image processing.

## Overview

AVCamPhotoFilter demonstrates how to use AV Foundation's capture API to draw a live camera preview and capture photos with image processing (filtering) applied.

Two "rosy" filters are provided: one is implemented using Core Image, and the other is implemented as a Metal shader. A horizontal swipe on the camera preview switches between the filters.

On devices that support depth map delivery, AVCamPhotoFilter provides depth data visualization (via a Metal shader). When depth visualization is enabled, a slider enables crossfading between video and depth visualization.

AVCamPhotoFilter also shows how to properly propagate sample buffer attachments and attributes, including EXIF metadata and color space information (e.g. wide gamut).

## Requirements

### Build

Xcode 9.0 or later; iOS 11.0 SDK or later.

- Note: **AVCamPhotoFilter can only be built for an actual iOS device, not for the simulator.**

### Runtime

iOS 11.0 or later

- Note: **AVCamPhotoFilter can only be run on an actual iOS device, not on the simulator.**
