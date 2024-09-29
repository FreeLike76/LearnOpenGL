#ifndef LOCAL_UTILS_H
#define LOCAL_UTILS_H

namespace Utils
{
	namespace Constants
	{
		namespace Screen
		{
			constexpr int WIDTH = 800;
			constexpr int HEIGHT = 600;
		} // namespace Screen

		namespace Camera
		{
			constexpr float SENSITIVITY = 20.0f;
		} // namespace Camera

		namespace Speed
		{
			constexpr float SLOW = 0.01f;
			constexpr float NORMAL = 0.1f;
			constexpr float FAST = 0.5f;
			constexpr float VERY_FAST = 1.0f;
		} // namespace Speed

	} // namespace Constants

} // namespace Utils

#endif // LOCAL_UTILS_H