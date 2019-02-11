
#include <windows.h>

#define local_persist static;
#define gloabl_variable static;
#define internal static;

static gloabl_variable running;

LRESULT CALLBACK MainWindowCallBack(
   HWND   Window,
   UINT   Message,
   WPARAM wParam,
   LPARAM lParam
)
{
	LRESULT Result = 0;
 	switch(Message)
 	{
 		case WM_CREATE:
 		{
 			OutputDebugStringA("WM_SIZE\n");
 		}break;
		
		case WM_SIZE:
 		{
 			OutputDebugStringA("WM_SIZE\n");
 		}break;
 		
 		case WM_DESTROY:
 		{
      running = false;
 			OutputDebugStringA("WM_DESTROY\n");
 		}break;

 		case WM_CLOSE:
 		{
      running = false;
 			OutputDebugStringA("WM_CLOSE\n");
 		}break;

 		case WM_ACTIVATEAPP:
 		{
 			OutputDebugStringA("WM_ACTIVATEAPP\n");
 		}break;

 		case WM_PAINT:
 		{
 		  PAINTSTRUCT Paint;
 		  HDC DeviceContext=BeginPaint(Window, &Paint);
 		  int X = Paint.rcPaint.left;
 		  int Y = Paint.rcPaint.top;
 		  int Width = Paint.rcPaint.right - Paint.rcPaint.left;
 		  int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
 		  PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
 		  EndPaint(Window, &Paint);
 		  OutputDebugStringA("WM_PAINT\n");
 		}

 		default:
 		{
 			Result = DefWindowProc(Window, Message, wParam,lParam);
 		}
 		break;
 	}

 	return (Result);
}

int CALLBACK WinMain( 
   HINSTANCE Instance,
   HINSTANCE PrevInstance,
   LPSTR     CommmandLine,
   int       ShowCode
)
{
	
  WNDCLASS WindowClass = {}; 

  WindowClass.style = CS_OWNDC|CS_VREDRAW|CS_HREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallBack;
  WindowClass.hInstance = Instance;
  WindowClass.lpszClassName = "HandeMadeHeroWindowClass";

   if(RegisterClass(&WindowClass))
   {
   	 HWND WindowHandel = CreateWindowExA(
 							0,
  							WindowClass.lpszClassName,
							"HandeMade Hero",
							WS_OVERLAPPEDWINDOW|WS_VISIBLE,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							0,
							0,
							Instance,
							0
							);
   	 if(WindowHandel)
   	 {
      running = true;
   	 	MSG Message;
   	 	while(running)
   	 	{
   	 		BOOL MessageResult = GetMessage(&Message, 0, 0 ,0);
   	 		if(MessageResult > 0)
   	 		{
   	 			TranslateMessage(&Message);
   	 			DispatchMessage(&Message);
   	 		}
   	 		else
   	 		{
   	 			break;
   	 		}
   	 	}
   	}	 
   
   }
   else
   {

   }

  return 0 ;
}