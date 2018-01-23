#pragma once
#include "Basic.h"
#include "AtomicInt.h"

namespace vl
{
	class Variant:
		public Object
	{
		public:
			enum Type
			{
				Invalid = 0,
				
				Bool = 1,
				Int = 2,
				UInt = 3,
				LongLong = 4,
				ULongLong = 5,
				Double = 6,
				Char = 7,
				Map = 8,
				List = 9,
				String = 10,
				StringList = 11,
				ByteArray = 12,
				BitArray = 13,
				Date = 14,
				Time = 15,
				DateTime = 16,
				Url = 17,
				Locale = 18,
				Rect = 19,
				RectF = 20,
				Size = 21,
				SizeF = 22,
				Line = 23,
				LineF = 24,
				Point = 25,
				PointF = 26,
				RegExp = 27,
				Hash = 28,
				EasingCurve = 29,
				LastCoreType = EasingCurve,
				
				// value 62 is internally reserved
				Font = 64,
				Pixmap = 65,
				Brush = 66,
				Color = 67,
				Palette = 68,
				Icon = 69,
				Image = 70,
				Polygon = 71,
				Region = 72,
				Bitmap = 73,
				Cursor = 74,
				SizePolicy = 75,
				KeySequence = 76,
				Pen = 77,
				TextLength = 78,
				TextFormat = 79,
				Matrix = 80,
				Transform = 81,
				Matrix4x4 = 82,
				Vector2D = 83,
				Vector3D = 84,
				Vector4D = 85,
				Quaternion = 86,
				LastGuiType = Quaternion,
				
				UserType = 127,
#ifdef QT3_SUPPORT
				IconSet = Icon,
				CString = ByteArray,
				PointArray = Polygon,
#endif
				LastType = 0xffffffff // need this so that gcc >= 3.4 allocates 32 bits for Type
			};
		public:
			inline Variant() {};
			~Variant();
			Variant(const Variant& other);
			
			
			struct PrivateShared
			{
				inline PrivateShared(void* v) : ptr(v), ref(1) { };		//未写虚析构，释放内存时，需要static_cast转换类型
				void* ptr;
				AtomicInt ref;
			};
			
			struct Private
			{
				inline Private() : type(Invalid), is_shared(false), is_null(true)
				{
					data.ptr = 0;
				}
				inline Private(const Private& other)
					: data(other.data), type(other.type),
					  is_shared(other.is_shared), is_null(other.is_null)
				{}
				union Data
					{
					  char c;
					  int i;
					  vuint u;
					  bool b;
					  double d;
					  float f;
					  // 					qreal real;
					  long long ll;
					  unsigned long long ull;
					  Object* o;
					  void* ptr;
					  PrivateShared* shared;
					} data;
				vuint type : 30;
				vuint is_shared : 1;
				vuint is_null : 1;
			};
			
			
	};
	
}
