#pragma once


class Task
{
public:
	Task() :end_(false){}
	virtual void Execute() = 0;
	inline void End() { end_ = true; }
protected:
	bool end_;
private:
	Q_DISABLE_COPY(Task)
};