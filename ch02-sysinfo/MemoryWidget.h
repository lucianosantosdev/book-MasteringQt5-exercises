#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include "SysInfoWidget.h"

#include <QWidget>

namespace QtCharts {
class QLineSeries;
}

class MemoryWidget : public SysInfoWidget
{
  Q_OBJECT
public:
  explicit MemoryWidget(QWidget* parent = nullptr);

protected slots:
  void updateSeries() override;

private:
  QtCharts::QLineSeries* m_series;
  qint64 m_pointPositionX;
};

#endif // MEMORYWIDGET_H
