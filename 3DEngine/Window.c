#include "Window.h"
#include <windows.h>
#include "LogManager.h"

static char* backBuffer;
static char* frontBuffer;
static HDC dc;
static int width;
static int height;
static BITMAPINFO bitmapinfo;

static void createBitmapInfo()
{
	// fill struct with correct values
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biWidth = width;
	bitmapinfo.bmiHeader.biHeight = -height;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biBitCount = 24;
	bitmapinfo.bmiHeader.biCompression = BI_RGB;
	bitmapinfo.bmiHeader.biSizeImage = 0;
	bitmapinfo.bmiHeader.biXPelsPerMeter = 10000;
	bitmapinfo.bmiHeader.biYPelsPerMeter = 10000;
	bitmapinfo.bmiHeader.biClrUsed = 0;
	bitmapinfo.bmiHeader.biClrImportant = 0;
}

static int initBuffers()
{
	backBuffer = (char*)malloc(sizeof(char) * 3 * width*height);
	if (!backBuffer)
		return 0;
	frontBuffer = (char*)malloc(sizeof(char) * 3 * width*height);
	if (!frontBuffer)
		return 0;

	return 1;
}

int winInit(int screenWidth, int screenHeight)
{
	// get connecion with console window
	HWND hwnd = GetConsoleWindow();
	dc = GetDC(hwnd);

	width = screenWidth;
	height = screenHeight;
	createBitmapInfo();

	if(!initBuffers())
	{
		logs("can't create window buffers");
		return 0;
	}

	return 1;
}

int winGetBuffer(void** buffer)
{
	*buffer = backBuffer;
	return 1;
}

int winSwapBuffers()
{
	void* temp = backBuffer;
	backBuffer = frontBuffer;
	frontBuffer = temp;

	return 1;
}

int winRender()
{
	if(!SetDIBitsToDevice(dc, 20, 0, width, height, 0, 0, 0, height, frontBuffer, &bitmapinfo, DIB_PAL_COLORS))
	{
		logs("Error with setting window buffer to device");
		return 0;
	}

	return 1;
}

void winShutdown()
{
	free(backBuffer);
	free(frontBuffer);
}
