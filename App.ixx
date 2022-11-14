module;

#include <windows.h>
#include <gdiplus.h>
#include <chrono>

export module App;

import Creature;

namespace Roarsome
{
	export class App
	{
	private:
		HWND _hwnd;
		Roarsome::Creature* _ctr;
		std::chrono::steady_clock::time_point _startFrameTime;
		int _frameDurationInMS;
		bool _shouldExit;
		ULONG_PTR gdiplusToken;

		Gdiplus::Bitmap* _buffers[2];

	public:
		App(HWND hwnd);
		~App();

		void Initialise();
		void Update();
		void Draw();

		bool ShouldExit();
		void Exit();
	};


	App::App(HWND hwnd)
	{
		_hwnd = hwnd;
		_ctr = nullptr;
		_shouldExit = false;
	}

	App::~App()
	{
		if (_ctr != nullptr)
		{
			delete _ctr;
			_ctr = nullptr;
		}

		delete _buffers[0];
		delete _buffers[1];

		Gdiplus::GdiplusShutdown(gdiplusToken);
	}

	void App::Initialise()
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		_startFrameTime = std::chrono::high_resolution_clock::now();
		_frameDurationInMS = 0;
		_ctr = new Roarsome::Creature();
		_ctr->SetupResources();

		RECT windowRect;
		GetClientRect(_hwnd, &windowRect);

		_buffers[0] = new Gdiplus::Bitmap(windowRect.right, windowRect.bottom, PixelFormat32bppPARGB);
		_buffers[1] = new Gdiplus::Bitmap(windowRect.right, windowRect.bottom, PixelFormat32bppPARGB);
	}

	void App::Update()
	{
		auto endFrameTime = std::chrono::high_resolution_clock::now();
		_frameDurationInMS = std::chrono::duration_cast<std::chrono::milliseconds>(endFrameTime - _startFrameTime).count();

		auto updateInfo = Roarsome::UpdateInfo();
		updateInfo.MillisecondsSinceLastUpdate = _frameDurationInMS;

		_ctr->Update(&updateInfo);

		_startFrameTime = endFrameTime;
	}

	void App::Draw()
	{
		Gdiplus::Graphics gfxCurrent(_hwnd);
		gfxCurrent.DrawImage(_buffers[0], 0, 0);
		gfxCurrent.Flush();


		Gdiplus::Graphics gfxNext(_buffers[1]);
		gfxNext.Clear(Gdiplus::Color::Black);
		_ctr->Draw(&gfxNext);

		gfxNext.Flush();

		auto a = _buffers[0];
		auto b = _buffers[1];
		_buffers[0] = b;
		_buffers[1] = a;

		
	}

	bool App::ShouldExit()
	{
		return _shouldExit;
	}

	void App::Exit()
	{
		_shouldExit = true;
	}
}