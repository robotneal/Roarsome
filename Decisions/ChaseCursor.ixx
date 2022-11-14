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

	protected:
		virtual wstring GetName();

	public:
		ChaseCursor()
		{

		}

		virtual DecisionResult Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo);
	};

	wstring ChaseCursor::GetName()
	{
		return L"ChaseCursor";
	}

	DecisionResult ChaseCursor::Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo)
	{
		return DecisionResult();
	}
}