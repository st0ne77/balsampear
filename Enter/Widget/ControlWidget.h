#pragma once
#include "QWidget"
#include "PlayPauseButton.h"
#include "StopButton.h"
#include "ProgressWidget.h"
namespace balsampear
{
	class ControlWidget:public QWidget
	{
		Q_OBJECT
	public:
		explicit ControlWidget(QWidget* parant = nullptr);
		virtual ~ControlWidget();
		void setPlayingStatus(bool _val);
		void setPlayProgress(double d);
	signals:
		void checkChangePlayStatus();
		void stopPlay();
		void seekProgress(double);
	protected:
		virtual void paintEvent(QPaintEvent* event);

	private:
		ProgressWidget progress_;
		PlayPauseButton playButton_;
		StopButton stopButton_;
	};
}