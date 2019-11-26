#include "Parser.h"

#pragma warning(disable: 4819)
extern "C"
{
#include "libavformat/avformat.h"
}

Parser::Parser()
{
	av_register_all();
}
