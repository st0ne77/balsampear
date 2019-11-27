#include "AVDecoder.h"

AVDecoder::AVDecoder()
    :codecCtx_(nullptr)
{
}

AVDecoder::~AVDecoder()
{
    // TODO : implement
}

void AVDecoder::setCodecContext(AVCodecContext* codecCtx)
{
    codecCtx_ = codecCtx;
}