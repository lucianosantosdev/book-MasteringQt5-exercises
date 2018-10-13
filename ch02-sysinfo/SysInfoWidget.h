#ifndef SYSINFOWIDGET_H
#define SYSINFOWIDGET_H

#include <QTimer>
#include <QWidget>
#include <QtCharts/QChartView>

const int COLOR_DARK_GREEN = 0x20ff9f;
const int COLOR_LIGHT_GREEN = 0xbeffdf;

class SysInfoWidget : public QWidget
{
  Q_OBJECT
public:
  explicit SysInfoWidget(QWidget* parent = nullptr,
                         int startDelayMs = 500,
                         int updateSeriesDelayMs = 500);

protected:
  QtCharts::QChartView& chartView();

protected slots:
  virtual void updateSeries() = 0;

private:
  QTimer m_refreshTimer;
  QtCharts::QChartView m_chartView;
};

#endif // SYSINFOWIDGET_H
