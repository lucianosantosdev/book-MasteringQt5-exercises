#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "SysInfoWidget.h"

namespace QtCharts {
class QPieSeries;
}

class CpuWidget : public SysInfoWidget
{
  Q_OBJECT
public:
  explicit CpuWidget(QWidget* parent = nullptr);

protected slots:
  void updateSeries() override;

private:
  QtCharts::QPieSeries* m_series;
};

#endif // CPUWIDGET_H
