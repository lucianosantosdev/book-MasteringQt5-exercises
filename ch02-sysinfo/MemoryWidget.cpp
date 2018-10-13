#include "MemoryWidget.h"
#include "SysInfo.h"

#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

const int CHART_X_RANGE_MAX = 50;
const int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget* parent)
  : SysInfoWidget(parent)
  , m_series(new QLineSeries(this))
  , m_pointPositionX(0)
{
  QPen pen(COLOR_DARK_GREEN);
  pen.setWidth(PEN_WIDTH);

  QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
  gradient.setColorAt(1.0, COLOR_DARK_GREEN);
  gradient.setColorAt(0.0, COLOR_LIGHT_GREEN);
  gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

  QAreaSeries* areaSeries = new QAreaSeries(m_series);
  areaSeries->setPen(pen);
  areaSeries->setBrush(gradient);

  QChart* chart = chartView().chart();
  chart->addSeries(areaSeries);
  chart->setTitle("Memory used");
  chart->createDefaultAxes();
  chart->axes()[0]->setVisible(false);
  chart->axes()[0]->setRange(0, CHART_X_RANGE_MAX);
  chart->axes()[1]->setRange(0, 100);
}

void
MemoryWidget::updateSeries()
{
  double memoryUsed = SysInfo::instance().memoryUsed();

  m_series->append(m_pointPositionX++, memoryUsed);

  if (m_series->count() > CHART_X_RANGE_MAX) {
    QChart* chart = chartView().chart();
    chart->scroll(chart->plotArea().width() / CHART_X_RANGE_MAX, 0);
    m_series->remove(0);
  }
}
