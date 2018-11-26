#include "Graphics.h"

#pragma comment(lib, "d2d1")

Graphics::Graphics(){
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics(){
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle){
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(), 
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK) return false;
	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	return true; 
}

void Graphics::clearScreen(float r, float g, float b){
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::drawCircle(float x, float y, float radius, float r, float g, float b, float a){
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x,y),radius,radius),brush,3.0f);
}

void Graphics::drawLine(float x, float y, float x2, float y2, float r, float g, float b, float a){
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawLine(D2D1::Point2F(x, y), D2D1::Point2F(x2, y2), brush);
}

void Graphics::drawRect(float x, float y, float x2, float y2, float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawRectangle(D2D1::RectF(x, y, x2, y2), brush);
}