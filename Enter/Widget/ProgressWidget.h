#pragma once
#include "QWidget"

namespace balsampear
{
	class ControlWidget;
	class ProgressWidget : public QWidget
	{
		Q_OBJECT
	public:
		explicit ProgressWidget(QWidget* parent = nullptr);
		~ProgressWidget();

		void setPlayProgress(double progress);

	protected:
		virtual void paintEvent(QPaintEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);

	protected:
		ControlWidget* controlWidget_;
		double progress_;
	};
}
