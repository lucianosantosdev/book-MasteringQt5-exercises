#include "CpuWidget.h"
#include "SysInfo.h"

#include <QtCharts/QPieSeries>
#include <QtDebug>
using namespace QtCharts;

const qreal CHART_HOLE_SIZE = 0.35;

CpuWidget::CpuWidget(QWidget* parent)
  : SysInfoWidget(parent)
  , m_series(new QPieSeries(this))
{
  m_series->setHoleSize(CHART_HOLE_SIZE);

  QChart* chart = chartView().chart();
  chart->addSeries(m_series);
  chart->setTitle("CPU average load");
  chart->legend()->setVisible(true);

  SysInfo::instance().init();
}

void
CpuWidget::updateSeries()
{
  double cpuLoadAverage = SysInfo::instance().cpuLoadAverage();

  m_series->clear();

  QPieSlice* loadSlice = m_series->append("CPU Load", cpuLoadAverage);
  loadSlice->setColor(COLOR_DARK_GREEN);
  QPieSlice* freeSlice = m_series->append("CPU Free", 100.0 - cpuLoadAverage);
  freeSlice->setColor(COLOR_LIGHT_GREEN);
}
