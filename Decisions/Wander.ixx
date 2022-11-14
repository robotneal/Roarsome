module;

#include <string>

export module Wander;

import UpdateInfo;
import Decision;

using namespace std;

namespace Roarsome::Descisions
{
	export class Wander : public Decision
	{
	private:
		double _speed;

	protected:
		virtual wstring GetName();

	public:
		Wander()
		{
			_speed = 12;
		}

		virtual DecisionResult Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo);
	};

	wstring Wander::GetName()
	{
		return L"Wander";
	}

	DecisionResult Wander::Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo)
	{
		DecisionResult result;
		result.position.x = creaturePosition.x + (updateInfo->totalSeconds() * _speed);
		result.position.y = creaturePosition.y + (updateInfo->totalSeconds() * _speed);

		return result;
	}
}