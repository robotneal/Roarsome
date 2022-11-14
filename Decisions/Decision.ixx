module;

#include <string>

export module Decision;

import UpdateInfo;

using namespace std;

namespace Roarsome::Descisions
{
	export struct DecisionResult
	{
		ScreenPoint position;
	};

	export class Decision
	{
	private:

	protected:
		virtual wstring GetName() = 0;

	public:
		Decision()
		{
		}

		virtual DecisionResult Update(ScreenPoint creaturePosition, UpdateInfo* updateInfo) = 0;
	};
}