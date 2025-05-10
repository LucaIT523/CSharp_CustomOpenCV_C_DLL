using System;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;

namespace ConsoleApp_Test
{
    internal class Program
    {

        public struct ST_MyRect
        {
            public int m_Height;
            public int m_Width;
            public int m_X;
            public int m_Y;
        };

        public const string cppDLL = "MyTest.dll";

        [DllImport(cppDLL, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr PreProcessImage(IntPtr imageData, int width, int height, int channels, ref uint resizedWidth, ref uint resizedHeight, ST_MyRect rect, int iScaleFactor, int iErodeValue, int iDilateValue, int iSmoothValue, int iThreshType, int iThreshMinValue, int iThreshMaxValue, bool p_bState);

        [DllImport(cppDLL, CallingConvention = CallingConvention.StdCall)]
        public static extern void PreProcessImage_close();

        static void Main(string[] args)
        {
            try
            {
                //. 
                string w_ImgPath = "test1.jpg";
                Bitmap tempImg = new Bitmap(w_ImgPath);
                int w_nWidth = tempImg.Width;
                int w_nHeight = tempImg.Height;
                w_nWidth = (int)(w_nWidth / 4) * 4;
                w_nHeight = (int)(w_nHeight / 4) * 4;
                Bitmap srcImage = new Bitmap(w_nWidth, w_nHeight, PixelFormat.Format24bppRgb);
                using (Graphics g = Graphics.FromImage(srcImage))
                {
                    g.DrawImage(tempImg, 0, 0, w_nWidth, w_nHeight);
                }
                int w_nChanels = 3;
                if (srcImage.PixelFormat == PixelFormat.Format24bppRgb)
                {
                    w_nChanels = 3;
                }
                else if (srcImage.PixelFormat == PixelFormat.Format8bppIndexed)
                {
                    w_nChanels = 1;
                }

                uint resizedWidth = 0;
                uint resizedHeight = 0;

                ST_MyRect w_rect;
                w_rect.m_Height = 10;
                w_rect.m_Width = 20;
                w_rect.m_X = 30;
                w_rect.m_Y = 40;

                //. 
                int iScaleFactor = 10;
                int iErodeValue = 20;
                int iDilateValue = 30;
                int iSmoothValue = 40;
                int iThreshType = 0; //. THRESH_BINARY
                int iThreshMinValue = 150;
                int iThreshMaxValue = 255;
                bool IsWhiteOnBlack = true;

                //. 
                BitmapData imageData = srcImage.LockBits(new Rectangle(0, 0, srcImage.Width, srcImage.Height), ImageLockMode.ReadOnly, srcImage.PixelFormat);
                IntPtr outImage_BitMap = PreProcessImage(imageData.Scan0, w_nWidth, w_nHeight, w_nChanels, ref resizedWidth, ref resizedHeight, w_rect, iScaleFactor, iErodeValue, iDilateValue, iSmoothValue, iThreshType, iThreshMinValue, iThreshMaxValue, IsWhiteOnBlack);
                srcImage.UnlockBits(imageData);

                if (outImage_BitMap.ToInt64() == 0)
                {
                    Console.WriteLine($"outImage_BitMap Null");

                }
                else
                {
                    Console.WriteLine($"resized size : {resizedWidth} x {resizedHeight}");

                    if (w_nChanels == 3)
                    {
                        Bitmap outImage = new Bitmap((int)resizedWidth, (int)resizedHeight, (int)resizedWidth * w_nChanels, PixelFormat.Format24bppRgb, outImage_BitMap);
                        outImage.Save("cs_test.jpg");

                    }
                    else if (w_nChanels == 1)
                    {
                        Bitmap outImage = new Bitmap((int)resizedWidth, (int)resizedHeight, (int)resizedWidth * w_nChanels, PixelFormat.Format8bppIndexed, outImage_BitMap);
                        outImage.Save("cs_test.jpg");
                    }

                    //.
                    PreProcessImage_close();
                }
            }
            finally
            {
                //.
                Console.WriteLine("test ended.");

            }

        }
    }
}
