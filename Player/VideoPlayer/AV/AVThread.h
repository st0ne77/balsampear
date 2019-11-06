#pragma once
#include "qglobal.h"
#include <QThread>
class Task;
class AVThread: public QThread
{
public:
	AVThread();
	virtual void run();
	inline void Start() { pause_ = false; }
	inline void Start(Task* task) {task_ = task; pause_ = false;}
	inline void Pause() { pause_ = true; }
	inline void Stop() { StopTask(); task_ = nullptr; }
	inline void Exit() { StopTask(); exit_ = true; }
	inline bool isPause() { return pause_; }
	inline bool isStop() { return task_ == nullptr; }
	inline bool isPauseOrStop() { return pause_ || !task_; }

private:
	void StopTask();
private:
	Q_DISABLE_COPY(AVThread)
	Task* task_;
	bool pause_;
	bool exit_;
};