#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include "AVPlayer.h"

namespace balsampear
{
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
		void play();

	private:
		QWidget fullWidget_;
		QVBoxLayout layout_;
		QWidget* playArea_;
		QPushButton button_;

		QTimer timer;
	};
}


