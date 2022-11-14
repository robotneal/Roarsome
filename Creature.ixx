module;

#include <windows.h>
#include <gdiplus.h>
#include <string>

export module Creature;

import UpdateInfo;
import Decision;
import Wander;

using namespace std;
using namespace Roarsome::Descisions;

namespace Roarsome
{
	export class Creature
	{
	private:
		wstring _name;
		ScreenPoint _position;
		Decision* _currentDescision;
		Gdiplus::Bitmap* _bmp;

	protected:
		virtual void SetName();

	public:
		Creature();
		~Creature();

		void SetupResources();
		void Update(UpdateInfo* updateInfo);
		void Draw(Gdiplus::Graphics* gfx);
	};

	Creature::Creature()
	{
		this->SetName();
		_bmp = nullptr;
		_currentDescision = nullptr;

		_position.x = 50;
		_position.y = 50;
	}

	Creature::~Creature()
	{
		if (_bmp != nullptr)
		{
			delete _bmp;
			_bmp = nullptr;
		}

		if (_currentDescision != nullptr)
		{
			delete _currentDescision;
			_currentDescision = nullptr;
		}
	}

	void Creature::SetName()
	{
		this->_name = L"Roar";
	}

	void Creature::SetupResources()
	{
		_bmp = new Gdiplus::Bitmap(L"Images\\Roar.png");
	}

	void Creature::Update(UpdateInfo* updateInfo)
	{
		if (_currentDescision == nullptr)
		{
			_currentDescision = new Roarsome::Descisions::Wander();
		}

		auto result = _currentDescision->Update(_position, updateInfo);
		_position.x = result.position.x;
		_position.y = result.position.y;
	}

	void Creature::Draw(Gdiplus::Graphics* gfx)
	{
		gfx->DrawImage(_bmp, (int)_position.x, (int)_position.y, 50, 50);
	}
}