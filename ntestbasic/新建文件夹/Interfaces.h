/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
Stream::Interfaces

Interfaces:
	IStream							£ºÁ÷
***********************************************************************/

// #ifndef VCZH_STREAM_INTERFACES
// #define VCZH_STREAM_INTERFACES
#pragma once

#include "Basic.h"
#include "String.h"
#include "List.h"
// #include "../Collections/Dictionary.h"

		/// <summary>
		/// Interface for streams. Stream functions are grouped into 5 categories:
		/// 1) Feature testing functions.
		/// 2) Read functions, available only if [M:vl.stream.IStream.CanRead] returns true.
		/// 3) Peek functions, available only if [M:vl.stream.IStream.CanPeek] returns true.
		/// 4) Write functions, available only if [M:vl.stream.IStream.CanWrite] returns true.
		/// 5) Seek functions, available only if [M:vl.stream.IStream.CanSeek] returns true.
		/// 6) Size functions, available only if [M:vl.stream.IStream.IsLimited] returns true. But there are still some streams knows that the content is limited, but the size is unknown. In this case, [M:vl.stream.IStream.Size] will return -1.
		/// </summary>
		class IStream : public virtual Interface
		{
		public:
			/// <summary>Test if the stream is readable.</summary>
			/// <returns>Returns true if the stream is readable.</returns>
			virtual bool					CanRead()const=0;
			/// <summary>Test if the stream is writable.</summary>
			/// <returns>Returns true if the stream is writable.</returns>
			virtual bool					CanWrite()const=0;
			/// <summary>Test if the stream is seekable.</summary>
			/// <returns>Returns true if the stream is seekable.</returns>
			virtual bool					CanSeek()const=0;
			/// <summary>Test if the stream is peekable.</summary>
			/// <returns>Returns true if the stream is peekable.</returns>
			virtual bool					CanPeek()const=0;
			/// <summary>Test if the content of the stream is limited. A writable stream can also be limited, it means that you can only write a limited content to the stream.</summary>
			/// <returns>Returns true if the content of the stream is limited.</returns>
			virtual bool					IsLimited()const=0;
			/// <summary>Test if the stream is available. For example, if you create a readable [T:vl.stream.FileStream] giving a wrong file name, it will be unavailable.</summary>
			/// <returns>Returns true if the stream is available.</returns>
			virtual bool					IsAvailable()const=0;
			/// <summary>Close the stream.</summary>
			virtual void					Close()=0;
			/// <summary>Get the current position in the stream.</summary>
			/// <returns>The position in the stream. Returns -1 if the stream is not available.</returns>
			virtual pos_t					Position()const=0;
			/// <summary>Get the size of the content..</summary>
			/// <returns>The size of the content. Returns -1 if the size is unknown or the stream is not available.</returns>
			virtual pos_t					Size()const=0;
			/// <summary>Step forward or backward from the current position. Will throw exception if the stream is not seekable or not available.</summary>
			/// <param name="_size">The length of the step.</param>
			virtual void					Seek(pos_t _size)=0;
			/// <summary>Step fowward from the beginning. Will throw exception if the stream is not seekable or not available.</summary>
			/// <param name="_size">The length of the step.</param>
			virtual void					SeekFromBegin(pos_t _size)=0;
			/// <summary>Step backward from the end. Will throw exception if the stream is not seekable or not available.</summary>
			/// <param name="_size">The length of the step.</param>
			virtual void					SeekFromEnd(pos_t _size)=0;
			/// <summary>Read from the current position and step forward. Will throw exception if the stream is not readable or not available.</summary>
			/// <returns>Returns the actual size of the content that is read. Returns 0 indicates that the stream reaches the end if the stream is limited.</returns>
			/// <param name="_buffer">A buffer to store the content.</param>
			/// <param name="_size">The size of the content that is expected to read.</param>
			virtual int					Read(void* _buffer, int _size)=0;
			/// <summary>Write to the current position and step forward. Will throw exception if the stream is not writable or not available.</summary>
			/// <returns>Returns the actual size of the content that is written. Returns 0 indicates that the stream reaches the end if the stream is limited.</returns>
			/// <param name="_buffer">A buffer storing the content to write.</param>
			/// <param name="_size">The size of the content that is expected to write.</param>
			virtual int					Write(void* _buffer, int _size)=0;
			/// <summary>Read from the current position but not step forward. Will throw exception if the stream is not peekable or not available.</summary>
			/// <returns>Returns the actual size of the content that is read. Returns 0 indicates that the stream reaches the end if the stream is limited.</returns>
			/// <param name="_buffer">A buffer to store the content.</param>
			/// <param name="_size">The size of the content that is expected to peek.</param>
			virtual int					Peek(void* _buffer, int _size)=0;
		};

		/// <summary>Encoder interface. This interface defines a writable transformation from one stream to another stream. You can create a [T:vl.stream.EncoderStream] after you have an encoder.</summary>
		class IEncoder : public Interface
		{
		public:
			/// <summary>Set a target writable stream. The <see cref="Write"/> function will transform the content and write to this tream.</summary>
			/// <param name="_stream">The target writable stream.</param>
			virtual void					Setup(IStream* _stream)=0;
			/// <summary>Stop the transformation, ensuring all written content is transformed to the target stream.</summary>
			virtual	void					Close()=0;
			/// <summary>Transform content and write to the target stream. This function may cache something to increase performance, so it cannot expect that all transformed content will be written to the target stream immediately.</summary>
			/// <returns>Returns the actual size of the content before transforming that is written. The content is treated as being written even it is cached and not actually write to the target stream.</returns>
			/// <param name="_buffer">A buffer storing the content to write.</param>
			/// <param name="_size">The size of the content that is expected to write.</param>
			virtual int					Write(void* _buffer, int _size)=0;
		};
		
		/// <summary>Decoder interface. This interface defines a readable transformation from one stream to another stream. You can create a [T:vl.stream.DecoderStream] after you have an decoder.</summary>
		class IDecoder : public Interface
		{
		public:
			/// <summary>Set a target readable stream. The <see cref="Read"/> function will read from this tream and transform the content.</summary>
			/// <param name="_stream">The target readable stream.</param>
			virtual void					Setup(IStream* _stream)=0;
			/// <summary>Stop the transformation.</summary>
			virtual	void					Close()=0;
			/// <summary>Read from the target stream and transform the content.</summary>
			/// <returns>Returns the actual size of the content after transforming that is read.</returns>
			/// <param name="_buffer">A buffer to store the content.</param>
			/// <param name="_size">The size of the content that is expected to read.</param>
			virtual int					Read(void* _buffer, int _size)=0;
		};


		/// <summary>Enumerator.</summary>
		/// <typeparam name="T">Type of the elements in the enumerator.</typeparam>
		template<typename T>
		class IEnumerator : public virtual Interface
		{
		public:
			typedef T									ElementType;

			/// <summary>Copy the enumerator with the current state.</summary>
			/// <returns>The copied enumerator.</returns>
			virtual IEnumerator<T>*						Clone()const = 0;
			/// <summary>Get the reference to the current element in the enumerator.</summary>
			/// <returns>The reference to the current element.</returns>
			virtual const T&							Current()const = 0;
			/// <summary>Get the position of the current element in the enumerator.</summary>
			/// <returns>The position of the current element.</returns>
			virtual vint								Index()const = 0;
			/// <summary>Step forward.</summary>
			/// <returns>Returns false if the enumerator reaches the end.</returns>
			virtual bool								Next() = 0;
			/// <summary>Reset the enumerator.</summary>
			virtual void								Reset() = 0;

			virtual bool								Evaluated()const { return false; }
		};

		/// <summary>Enumerable.</summary>
		/// <typeparam name="T">Type of the elements in the enumerator.</typeparam>
		template<typename T>
		class IEnumerable : public virtual Interface
		{
		public:
			typedef T									ElementType;

			/// <summary>Create an enumerator. [M:vl.collections.IEnumerator`1.Next] should be called to get the first element.</summary>
			/// <returns>The enumerator.</returns>
			virtual IEnumerator<T>*						CreateEnumerator()const = 0;
		};

		template<typename T>
		struct RandomAccessable
		{
			static const bool							CanRead = false;
			static const bool							CanResize = false;
		};

		template<typename T>
		struct RandomAccess
		{
			static vint GetCount(const T& t)
			{
				return t.Count();
			}

			static const typename T::ElementType& GetValue(const T& t, vint index)
			{
				return t.Get(index);
			}

			static void SetCount(T& t, vint count)
			{
				t.Resize(count);
			}

			static void SetValue(T& t, vint index, const typename T::ElementType& value)
			{
				t.Set(index, value);
			}

			static void AppendValue(T& t, const typename T::ElementType& value)
			{
				t.Add(value);
			}
		};