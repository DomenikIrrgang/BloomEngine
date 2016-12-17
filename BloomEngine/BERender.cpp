#include "BERender.h"
#include <math.h>
#include "Plane.h"

Render defaultRender;

typedef struct Square
{
	Vector a;
	Vector b;
	Vector c;
	Vector d;
	Vector e;
	Vector f;
	Vector g;
	Vector h;
	Vector center;
	real32 rotation;

	Square()
	{
		rotation = 0;
	}

	Square(Vector a, Vector b)
	{
		this->a = a;
		this->b = b;
		calculatePositions();
		rotation = 0;
	}

	Square(Vector a, Vector b, Vector c, Vector d, real32 rotation)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->rotation = rotation;
		center = a + ((b - a) * 0.5f);
	}
	
	void rotate(Vector angle, real32 degree)
	{
		a = angle + a.Rotate(angle, degree);
		b = angle + b.Rotate(angle, degree);
		c = angle + c.Rotate(angle, degree);
		d = angle + d.Rotate(angle, degree);
		e = angle + e.Rotate(angle, degree);
		f = angle + f.Rotate(angle, degree);
		g = angle + g.Rotate(angle, degree);
		h = angle + h.Rotate(angle, degree);
		center = a + ((f - a) * 0.5f);
	}

	void calculatePositions()
	{
		this->c = Vector(a.x, b.y, a.z);
		this->d = Vector(b.x, a.y, b.z);
		this->e = Vector(a.x, a.y, 100);
		this->f = Vector(b.x, b.y, 100);
		this->g = Vector(c.x, c.y, 100);
		this->h = Vector(d.x, d.y, 100);
		center = a + ((b - a) * 0.5f);
	}

	Square transform(Vector position)
	{
		Square tmp = Square(a + position, b + position, c + position, d + position, rotation);
		return tmp;
	}

} Square;

typedef struct Color
{
	uint8 blue;
	uint8 green;
	uint8 red;
	uint8 alpha;

	Color(uint8 blue, uint8 green, uint8 red, uint8 alpha)
	{
		this->blue = blue;
		this->red = red;
		this->green = green;
		this->alpha = alpha;
	}
} Color;

void InitRender(Render* render)
{
	render->screenBuffer.memory = 0;
	render->screenBuffer.bytesPerPixel = 4;
	render->screenBuffer.info.bmiHeader.biSize = sizeof(render->screenBuffer.info.bmiHeader);
	render->screenBuffer.info.bmiHeader.biPlanes = 1;
	render->screenBuffer.info.bmiHeader.biBitCount = 32;
	render->screenBuffer.info.bmiHeader.biCompression = BI_RGB;
	render->screenBuffer.info.bmiHeader.biSizeImage = 0;
	render->screenBuffer.info.bmiHeader.biXPelsPerMeter = 0;
	render->screenBuffer.info.bmiHeader.biYPelsPerMeter = 0;
}

void ResizeDIBSection(Render* render, int32 width, int32 height)
{
	if (render->screenBuffer.memory)
	{
		VirtualFree(render->screenBuffer.memory, 0, MEM_RELEASE);
	}

	render->screenBuffer.info.bmiHeader.biWidth = width;
	render->screenBuffer.info.bmiHeader.biHeight = height;
	render->screenBuffer.width = width;
	render->screenBuffer.height = height;
	render->screenBuffer.pitch = render->screenBuffer.width * render->screenBuffer.bytesPerPixel;
	render->screenBuffer.memory = VirtualAlloc(0, render->screenBuffer.bytesPerPixel * width * height, MEM_COMMIT, PAGE_READWRITE);
	render->screenBuffer.width = width;
	render->screenBuffer.height = height;
}

void RenderClientArea(Render* render, WindowSize windowSize, HDC context)
{
	StretchDIBits(context, 0, 0, windowSize.width, windowSize.height, 0, 0, render->screenBuffer.width, render->screenBuffer.height, render->screenBuffer.memory, &(render->screenBuffer.info), DIB_RGB_COLORS, SRCCOPY);
}


void DrawPixel(Render* render, Color color, int32 x, int32 y)
{
	int32 yPitch = render->screenBuffer.pitch * y;
	int32 xPitch = sizeof(uint8) * 4 * x;
	uint8* row = (uint8*)render->screenBuffer.memory + yPitch + xPitch;
	if (x >= 0 && x < render->screenBuffer.width && y >= 0 && y < render->screenBuffer.height)
	{
		*row = color.blue;
		row++;
		*row = color.green;
		row++;
		*row = color.red;
		row++;
		*row = color.alpha;
	}
}

void DrawLine(Render* render, Color color, Vector source, Vector target)
{
	int32 yPitch = render->screenBuffer.pitch * source.y;
	uint8* row = (uint8*)render->screenBuffer.memory + yPitch;
	Vector direction = target - source;
	Vector nDirection = direction.Normalized();
	for (int index = 0; index < direction.Length(); index++)
	{
		Vector point = source + (nDirection * (real32) index);
		point.Convert2D();
		int32 x = (int32)point.x, y = (int32)point.y;
		DrawPixel(render, color, x, y);
	}
}

void ClearScreen(Render* render)
{
	memset(render->screenBuffer.memory, 0, render->screenBuffer.width * render->screenBuffer.height * render->screenBuffer.bytesPerPixel);
}

extern real32 cameraPositionX = 50.0f;
extern real32 cameraPositionY = 20.0f;

void RenderGradient(Render* render, int32 xOffset, int32 yOffset)
{
	local Square squares[10];
	local bool created = false;
	local int32 test = 0;
	local int32 direction = 1;
	local int32 limit = 0;
	local real32 scaling = 1.0f;
	local real32 scalingDirection = -0.01f;

	Plane plane = PlaneFromPointCoords(Vector(100, 100, 1), Vector(200, 100, 1), Vector(100, 200, 1));
	ClearScreen(render);

	for (int32 i = 0; i < 10; i++)
	{
		if (!created)
		{
			Vector start = Vector(rand() % 2000,rand() % 1100, 1);
			int32 width = rand() % 100 + 50;
			int32 height = rand() % 100 + 50;
			squares[i] = Square(start, Vector(start.x + width, start.y + height, 1));
			//squares[i] = Square(Vector(100, 100, 1), Vector(200, 200, 1));
			//squares[i].rotate(Vector(0, 0, 1), rand() % 90);
		}
		//squares[i].rotate(Vector(render->screenBuffer.width / 2, render->screenBuffer.height / 2,1), test / 2);
		//squares[i].rotate(squares[i].center, test * 2);
		Square square = squares[i];//.transform(Vector(0, 0, 0));
		//Matrix translationMatrix = TranslationMatrix(Vector(20, 0, 0));
		//Matrix scalingMatrix = ScalingMatrix(Vector(1, 1, 1-scaling));
		Matrix rotationMatrix = RoationMatrixAxis(Vector(0.1, 0.1, 0.1), scaling);
		//Matrix cameraMatrix = CameraMatrix(Vector(cameraPositionX, cameraPositionY, -10), Vector(cameraPositionX, cameraPositionY, -9), Vector(0, 1, 0));
		Matrix matrix = rotationMatrix;
								  
		square.a = TransformCoordinates(square.a, matrix, NULL);
		square.b = TransformCoordinates(square.b, matrix, NULL);
		square.c = TransformCoordinates(square.c, matrix, NULL);
		square.d = TransformCoordinates(square.d, matrix, NULL);
		square.e = TransformCoordinates(square.e, matrix, NULL);
		square.f = TransformCoordinates(square.f, matrix, NULL);
		square.g = TransformCoordinates(square.g, matrix, NULL);
		square.h = TransformCoordinates(square.h, matrix, NULL);


		DrawLine(render, Color(255, 0, 0, 0), square.a, square.c);
		DrawLine(render, Color(255, 0, 0, 0), square.c, square.b);
		DrawLine(render, Color(255, 0, 0, 0), square.b, square.d);
		DrawLine(render, Color(255, 0, 0, 0), square.d, square.a);

		DrawLine(render, Color(255, 0, 0, 0), square.a, square.e);
		DrawLine(render, Color(255, 0, 0, 0), square.b, square.f);
		DrawLine(render, Color(255, 0, 0, 0), square.c, square.g);
		DrawLine(render, Color(255, 0, 0, 0), square.d, square.h);

		DrawLine(render, Color(255, 0, 0, 0), square.e, square.g);
		DrawLine(render, Color(255, 0, 0, 0), square.g, square.f);
		DrawLine(render, Color(255, 0, 0, 0), square.f, square.h);
		DrawLine(render, Color(255, 0, 0, 0), square.h, square.e);
	}
	created = true;
	limit++;
	test += direction;
	scaling += scalingDirection;

	if (scaling >= 3.0f)
	{
		scalingDirection = -0.01f;
	}

	if (scaling <= 0.0f)
	{
		scalingDirection = 0.01f;
	}

	if (test == 2)
	{
		direction = -1;
	}
	if (test == 0)
	{
		direction = 1;
	}

}