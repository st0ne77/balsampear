#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include "AVPlayer.h"

namespace balsampear
{
	class ControlWidget;
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget* parent = 0);
		~MainWindow();
		AVPlayer player_;
	protected:
		virtual void closeEvent(QCloseEvent* event);

	public slots:
		void updateVideo();
		void changePlayStatus();
		void stopPlay();

	private:
		void sourceEndCallBack();

	private:
		QWidget fullWidget_;
		QVBoxLayout layout_;
		QWidget* playArea_;
		ControlWidget* control_;

		QTimer timer;
	};
}


