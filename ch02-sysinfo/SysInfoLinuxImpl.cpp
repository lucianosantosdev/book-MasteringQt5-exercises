#include "SysInfoLinuxImpl.h"

#include <sys/sysinfo.h>
#include <sys/types.h>

#include <QFile>

SysInfoLinuxImpl::SysInfoLinuxImpl()
  : SysInfo()
  , m_cpuLoadLastValues()
{}

void
SysInfoLinuxImpl::init()
{
  m_cpuLoadLastValues = cpuRawData();
}

double
SysInfoLinuxImpl::cpuLoadAverage()
{
  QVector<qulonglong> firstSample = m_cpuLoadLastValues;
  QVector<qulonglong> secondSample = cpuRawData();
  m_cpuLoadLastValues = secondSample;

  double overrall = (secondSample[0] - firstSample[0]) +
                    (secondSample[1] - firstSample[1]) +
                    (secondSample[2] - firstSample[2]);

  double total = overrall + (secondSample[3] - firstSample[3]);
  double percent = (overrall / total) * 100.0;
  return qBound(0.0, percent, 100.0);
}

double
SysInfoLinuxImpl::memoryUsed()
{
  struct sysinfo memInfo;
  sysinfo(&memInfo);

  qulonglong totalMemory = memInfo.totalram;
  totalMemory += memInfo.totalswap;
  totalMemory *= memInfo.mem_unit;

  qulonglong totalMemoryUsed = memInfo.totalram - memInfo.freeram;
  totalMemoryUsed += memInfo.totalswap - memInfo.freeswap;
  totalMemory *= memInfo.mem_unit;

  double percent = (double)totalMemoryUsed / (double)totalMemory * 100.0;
  return qBound(0.0, percent, 100.0);
}

QVector<qulonglong>
SysInfoLinuxImpl::cpuRawData()
{
  QFile file("/proc/stat");
  file.open(QIODevice::ReadOnly);

  QByteArray line = file.readLine();
  file.close();

  qulonglong totalUser = 0, totalUserNice = 0, totalSystem = 0, totalIdle = 0;

  std::sscanf(line.data(),
              "cpu %llu %llu %llu %llu",
              &totalUser,
              &totalUserNice,
              &totalSystem,
              &totalIdle);

  QVector<qulonglong> rawData;
  rawData.append(totalUser);
  rawData.append(totalUserNice);
  rawData.append(totalSystem);
  rawData.append(totalIdle);

  return rawData;
}
