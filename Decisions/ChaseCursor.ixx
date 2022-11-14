module;

#include <string>

export module ChaseCursor;

import UpdateInfo;
import Decision;

using namespace std;

namespace Roarsome::Descisions
{
	export class ChaseCursor : public Decision
	{
	private:
		double _speed;

	protected:
		virtual wstring GetName();
		double GetSpeed(double direction);

	public:
		ChaseCursor()
		{
			_speed = 30;
		}

		virtual DecisionResult Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo);
	};

	wstring ChaseCursor::GetName()
	{
		return L"ChaseCursor";
	}

	DecisionResult ChaseCursor::Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo)
	{
		double vx = updateInfo->CursorPoint.x - creaturePosition.x;
		double vy = updateInfo->CursorPoint.y - creaturePosition.y;

		double distancex = updateInfo->totalSeconds() * GetSpeed(vx);
		double distancey = updateInfo->totalSeconds() * GetSpeed(vy);

		DecisionResult result { };
		result.position.x = creaturePosition.x + (vx > 0 ? distancex : -distancex);
		result.position.y = creaturePosition.y + (vy > 0 ? distancey : -distancey);

		return result;
	}

	double ChaseCursor::GetSpeed(double direction)
	{
		if (direction < 0)
		{
			direction = direction*-1;
		}
		return (direction / 2.0);
	}
}