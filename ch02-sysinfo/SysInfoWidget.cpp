#include "SysInfoWidget.h"

#include <QVBoxLayout>

using namespace QtCharts;
SysInfoWidget::SysInfoWidget(QWidget* parent,
                             int startDelayMs,
                             int updateSeriesDelayMs)
  : QWidget(parent)
  , m_chartView(this)
{
  m_refreshTimer.setInterval(updateSeriesDelayMs);
  connect(
    &m_refreshTimer, &QTimer::timeout, this, &SysInfoWidget::updateSeries);
  QTimer::singleShot(startDelayMs, [this] { m_refreshTimer.start(); });

  m_chartView.setRenderHint(QPainter::Antialiasing);
  m_chartView.chart()->legend()->setVisible(false);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(&m_chartView);
  setLayout(layout);
}

QtCharts::QChartView&
SysInfoWidget::chartView()
{
  return m_chartView;
}
