//
// Created by admin on 2024/7/11.
//

#pragma once

#include "FTypeDef.hpp"

namespace Whale
{
	///
	/// 数学库
	template<class T>
	class WHALE_API TMath
	{
	public:
		
		///
		/// 限制范围
		/// \param x 源值
		/// \param minValue 最小值
		/// \param maxValue 最大值
		/// \returns 结果
		inline static T Clamp(T x, T minValue, T maxValue);
		
		///
		/// 线性插值（限制范围）
		/// \param x 起始
		/// \param y 结束
		/// \param t 因子
		/// \return 结果
		inline static T Lerp(T x, T y, T t);
		
		///
		/// 线性插值（不限制范围）
		/// \param x 起始
		/// \param y 结束
		/// \param t 因子
		/// \return 结果
		inline static T LerpUnclamped(T x, T y, T t);
		
	};
	
	using MathF = TMath<float>;
	using MathD = TMath<double>;
	
	template<class T>
	class WHALE_API TVector2
	{
	public:
		
		// 默认构造函数
		TVector2() : x(T{0}), y(T{0}) {}
		
		// 参数化构造函数
		TVector2(T x, T y, T z) : x(x), y(y) {}
		
		// 向量加法
		TVector2 operator+(const TVector2 &other) const
		{
			return TVector2(x + other.x, y + other.y);
		}
		
		// 向量减法
		TVector2 operator-(const TVector2 &other) const
		{
			return TVector2(x - other.x, y - other.y);
		}
		
		// 向量点乘
		T Dot(const TVector2 &other) const
		{
			return x * other.x + y * other.y;
		}
		
		// 向量长度
		T Length() const
		{
			return sqrt(x * x + y * y);
		}
	
	public:
		
		T x, y;
		
	};
	
	template<class T>
	class WHALE_API TVector3
	{
	public:
		
		// 默认构造函数
		TVector3() : x(T{0}), y(T{0}), z(T{0}) {}
		
		// 参数化构造函数
		TVector3(T x, T y, T z) : x(x), y(y), z(z) {}
		
		// 向量加法
		TVector3 operator+(const TVector3 &other) const
		{
			return TVector3(x + other.x, y + other.y, z + other.z);
		}
		
		// 向量减法
		TVector3 operator-(const TVector3 &other) const
		{
			return TVector3(x - other.x, y - other.y, z - other.z);
		}
		
		// 向量点乘
		T Dot(const TVector3 &other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}
		
		// 向量长度
		T Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}
	
	public:
		
		T x, y, z;
		
	};
	
	template<class T>
	class WHALE_API TVector4
	{
	public:
		
		// 默认构造函数
		TVector4() : x(T{0}), y(T{0}), z(T{0}), w(T{0}) {}
		
		// 参数化构造函数
		TVector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		
		// 向量加法
		TVector4 operator+(const TVector4 &other) const
		{
			return TVector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		
		// 向量减法
		TVector4 operator-(const TVector4 &other) const
		{
			return TVector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}
		
		// 向量点乘
		T Dot(const TVector4 &other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}
		
		// 向量长度
		T Length() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}
	
	public:
		
		T x, y, z, w;
		
	};
	
	using float2 = TVector2<float>;
	using double2 = TVector2<double>;
	
	using float3 = TVector3<float>;
	using double3 = TVector3<double>;
	
	using float4 = TVector4<float>;
	using double4 = TVector4<double>;
	
	template<class T>
	T TMath<T>::LerpUnclamped(T x, T y, T t)
	{
		return x * (T{0} - t) + y * t;
	}
	
	template<class T>
	T TMath<T>::Lerp(T x, T y, T t)
	{
		return LerpUnclamped(x, y, Clamp(t, T{0}, T{1}));
	}
	
	template<class T>
	inline T TMath<T>::Clamp(T x, T minValue, T maxValue)
	{
		return x > maxValue ? maxValue : (x < minValue ? minValue : x);
	}
	
} // Whale
