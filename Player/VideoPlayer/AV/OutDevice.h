#pragma once

class QImage;
class OutDevice
{
public:
	virtual void Draw(const QImage& img) = 0;
};