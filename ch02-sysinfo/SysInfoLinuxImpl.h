#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include "SysInfo.h"

#include <QVector>
#include <QtGlobal>

class SysInfoLinuxImpl : public SysInfo
{
public:
  SysInfoLinuxImpl();

  // SysInfo interface
public:
  void init() override;
  double cpuLoadAverage() override;
  double memoryUsed() override;

private:
  QVector<qulonglong> cpuRawData();
  QVector<qulonglong> m_cpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
