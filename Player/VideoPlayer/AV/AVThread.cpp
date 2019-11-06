#include "stdafx.h"
#include "AVThread.h"
#include "Task.h"


AVThread::AVThread()
	:task_(nullptr),
	pause_(false),
	exit_(false)
{

}

void AVThread::run()
{
	for (;;)
	{
		if (exit_)
		{
			break;
		}

		if (isPauseOrStop())
		{
			usleep(100);
			continue;
		}

		task_->Execute();
	}
}

void AVThread::StopTask()
{
	if (task_)
	{
		task_->End();
	}
}
