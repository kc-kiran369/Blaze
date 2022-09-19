#ifndef MATH_F_H
#define MATH_F_H

namespace Blaze
{
	namespace Math
	{
		class Mathf
		{
		public:
			template<typename T>
			static T max(T v1, T v2);

			template<typename T>
			static T min(T v1, T v2);
		};

		template<typename T>
		static inline T Mathf::max(T v1, T v2)
		{
			return (v1 > v2 ? v1 : v2);
		}
		template<typename T>
		static inline T Mathf::min(T v1, T v2)
		{
			return (v1 > v2 ? v2 : v1);
		}
	}
}
#endif // !MATH_H