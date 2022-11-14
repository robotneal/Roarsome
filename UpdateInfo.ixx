module;

export module UpdateInfo;

namespace Roarsome
{
	export struct ScreenPoint
	{
		double x;
		double y;
	};

	export struct UpdateInfo
	{
		int MillisecondsSinceLastUpdate;
		ScreenPoint CursorPoint;

		double totalSeconds()
		{
			return (double)MillisecondsSinceLastUpdate / 1000.0;
		}
	};
}