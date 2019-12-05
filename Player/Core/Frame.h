#pragma once
#include <cstddef>
#include <vector>
#include <memory>

using Byte = unsigned char;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
namespace PlayerCore
{
	class Frame
	{
	public:
		class Content
		{
		public:
			vector<Byte> data_;
		};

		Frame();
		virtual ~Frame();
		vector<Byte> data() const;

	protected:
		Frame(weak_ptr<Content> content);
		shared_ptr<Content> content_;
	};
}


