#pragma once
#include <cstddef>
#include <vector>
#include <memory>

using Byte = unsigned char;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using uint64 = unsigned long long;
namespace balsampear
{
	class Frame
	{
	public:

		Frame();
		virtual ~Frame();
		const Byte* data() const;
		void setTimeStampMsec(uint64 t);
		uint64 getTimeStampMsec()const;
		void setDuration(uint64 t);
		uint64 getDuration();
		void allocMemory(size_t size);
		void setEof(bool _val);
		bool eof();
	protected:
		class DataManager
		{
		public:
			DataManager();
			~DataManager();
			void allocMemory(size_t size);
			const Byte* data() const;
		private:
			Byte* d_;
		};
		shared_ptr<DataManager> data_;
		uint64 timestamp_msec_;
		uint64 duration_;
		bool eof_;
	};
}


