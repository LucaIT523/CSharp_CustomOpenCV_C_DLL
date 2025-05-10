# 



<div align="center">
   <h1>CSharp_CustomOpenCV_C_DLL</h1>
</div>



This program demonstrates how to call OpenCV functions using a C++ DLL from C#.

### 1. Core Architecture

<div align="center">
   <img src=https://github.com/LucaIT523/CSharp_CustomOpenCV_C_DLL/blob/main/images/1.png>
</div>





### 2. Key Components

#### 2.1 Interop Structure

```
[StructLayout(LayoutKind.Sequential)]
public struct ST_MyRect {
    public int m_Height;
    public int m_Width;
    public int m_X; 
    public int m_Y;
}

[DllImport(cppDLL, CallingConvention=CallingConvention.StdCall)]
public static extern IntPtr PreProcessImage(/*...*/);
```

- **Memory Alignment**: Original image dimensions adjusted to multiples of 4 (`w_nWidth = (int)(w_nWidth/4)*4`)
- **Native Interop**: Uses sequential layout for struct compatibility
- **Parameter Types**: 15 parameters covering processing configuration

#### 2.2 Image Pipeline

| Stage         | Operation       | Technical Detail                                     |
| ------------- | --------------- | ---------------------------------------------------- |
| 1. Input      | Load & Format   | Converts source image to 24bpp RGB or 8bpp grayscale |
| 2. Locking    | Memory Access   | `LockBits()` with `ImageLockMode.ReadOnly`           |
| 3. Processing | Native Call     | Passes raw pixel data via `Scan0` pointer            |
| 4. Output     | Bitmap Creation | Creates bitmap from unmanaged memory pointer         |

### 3. Processing Parameters

```
int iScaleFactor = 10;         // Image scaling factor (%)
int iErodeValue = 20;          // Morphological erosion strength
int iDilateValue = 30;         // Morphological dilation strength  
int iSmoothValue = 40;         // Smoothing/blur intensity
int iThreshType = 0;           // Threshold type (0=Binary)
int iThreshMinValue = 150;     // Lower threshold bound
int iThreshMaxValue = 255;     // Upper threshold bound
bool IsWhiteOnBlack = true;    // Output polarity
```

### 4. Memory Management

```
csharpCopy// Native memory access pattern
BitmapData imageData = srcImage.LockBits(...);
IntPtr outImage_BitMap = PreProcessImage(imageData.Scan0, ...);
srcImage.UnlockBits(imageData);

// Output bitmap creation
new Bitmap(width, height, stride, format, outImage_BitMap);
```

- **Stride Calculation**: Uses `resizedWidth * channels` for row alignment
- **Pixel Formats**: Supports both 24bpp RGB and 8bpp grayscale
- **Resource Release**: Explicit `PreProcessImage_close()` call

### 5. Potential Issues & Mitigations

#### 5.1 Stability Risks

```
1. **Memory Leaks**: No explicit freeing of `outImage_BitMap`
2. **Alignment Assumption**: Arbitrary division by 4 without verification
3. **Pointer Lifetime**: Native memory ownership unclear
4. **Exception Handling**: Missing error checking for native calls
```

#### 5.2 Suggested Improvements

```
// Memory Management
[StructLayout(LayoutKind.Sequential)]
public struct SizeParams {
    public uint width;
    public uint height;
}

// Enhanced Error Handling
[DllImport(cppDLL)]
public static extern int GetLastError();

// Async Pattern
public static extern Task<IntPtr> PreProcessImageAsync(...);
```

### 6. Native Function Speculation

Based on parameters, the C++ `PreProcessImage` likely implements:

```
1. ROI cropping (via ST_MyRect)
2. Image scaling (iScaleFactor)
3. Morphological operations (erode/dilate)
4. Smoothing filter (iSmoothValue)
5. Thresholding (iThreshType/Min/Max)
6. Color inversion (IsWhiteOnBlack)
7. Memory reallocation (resizedWidth/Height)
```

### 7. Execution Characteristics

```
input Requirements: 
- JPEG images with width/height >4 pixels
- Either 24bpp RGB or 8bpp grayscale

Output Behavior:
- Saves processed image as cs_test.jpg
- Console logging of resized dimensions
- Final "test ended." confirmation

Memory Footprint: 
- ~2-3× original image size (input+output buffers)
- Additional DLL runtime overhead
```

This implementation demonstrates a typical C#/C++ interop pattern for performance-critical image processing tasks. While functional for basic scenarios, it would benefit from enhanced memory management and error handling for production use.



### **Contact Us**

For any inquiries or questions, please contact us.

telegram : @topdev1012

email :  skymorning523@gmail.com

Teams :  https://teams.live.com/l/invite/FEA2FDDFSy11sfuegI