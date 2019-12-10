#pragma once
#include "QWidget"
#include "PlayPauseButton.h"
#include "StopButton.h"
namespace balsampear
{
	class ControlWidget:public QWidget
	{
		Q_OBJECT
	public:
		explicit ControlWidget(QWidget* parant = nullptr);
		virtual ~ControlWidget();
		void setPlayingStatus(bool _val);

	signals:
		void checkChangePlayStatus();
		void stopPlay();
	protected:
		virtual void paintEvent(QPaintEvent* event);

	private:
		PlayPauseButton playButton_;
		StopButton stopButton_;
	};
}