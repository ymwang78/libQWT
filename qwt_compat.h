#pragma once

#include <QDateTime>
#include <QTimeZone>

// QWT compatibility macros for QDateTime deprecated functions in Qt6
// This file provides compatibility fixes for Windows compilation issues

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

// Helper class for QDateTime compatibility
class QwtDateTimeCompat
{
public:
    // Replacement for deprecated setOffsetFromUtc
    static void setOffsetFromUtc(QDateTime& dt, int offsetSeconds)
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        QTimeZone tz = QTimeZone::fromSecondsAheadOfUtc(offsetSeconds);
        dt.setTimeZone(tz);
#else
        // For Qt6.0-6.4, use the deprecated function with warning suppression
        #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable: 4996)
        #endif
        dt.setOffsetFromUtc(offsetSeconds);
        #ifdef _MSC_VER
        #pragma warning(pop)
        #endif
#endif
    }

    // Replacement for deprecated QDateTime constructor with Qt::TimeSpec
    static QDateTime createDateTime(const QDate& date, const QTime& time, Qt::TimeSpec spec = Qt::LocalTime)
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        if (spec == Qt::UTC) {
            return QDateTime(date, time, QTimeZone::UTC);
        } else if (spec == Qt::LocalTime) {
            return QDateTime(date, time, QTimeZone::systemTimeZone());
        } else {
            return QDateTime(date, time, QTimeZone::systemTimeZone());
        }
#else
        // For Qt6.0-6.4, use the deprecated constructor with warning suppression
        #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable: 4996)
        #endif
        QDateTime dt(date, time, spec);
        #ifdef _MSC_VER
        #pragma warning(pop)
        #endif
        return dt;
#endif
    }

    // Replacement for deprecated toTimeSpec
    static QDateTime toTimeSpec(const QDateTime& dt, Qt::TimeSpec spec)
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        if (spec == Qt::UTC) {
            return dt.toTimeZone(QTimeZone::UTC);
        } else if (spec == Qt::LocalTime) {
            return dt.toTimeZone(QTimeZone::systemTimeZone());
        } else {
            return dt;
        }
#else
        // For Qt6.0-6.4, use the deprecated function with warning suppression
        #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable: 4996)
        #endif
        QDateTime result = dt.toTimeSpec(spec);
        #ifdef _MSC_VER
        #pragma warning(pop)
        #endif
        return result;
#endif
    }

    // Replacement for deprecated setTimeSpec
    static void setTimeSpec(QDateTime& dt, Qt::TimeSpec spec)
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        if (spec == Qt::UTC) {
            dt.setTimeZone(QTimeZone::UTC);
        } else if (spec == Qt::LocalTime) {
            dt.setTimeZone(QTimeZone::systemTimeZone());
        }
#else
        // For Qt6.0-6.4, use the deprecated function with warning suppression
        #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable: 4996)
        #endif
        dt.setTimeSpec(spec);
        #ifdef _MSC_VER
        #pragma warning(pop)
        #endif
#endif
    }
};

// Convenience macros for easy replacement
#define QWT_DATETIME_SET_OFFSET_FROM_UTC(dt, offset) QwtDateTimeCompat::setOffsetFromUtc(dt, offset)
#define QWT_DATETIME_CREATE(date, time, spec) QwtDateTimeCompat::createDateTime(date, time, spec)
#define QWT_DATETIME_TO_TIME_SPEC(dt, spec) QwtDateTimeCompat::toTimeSpec(dt, spec)
#define QWT_DATETIME_SET_TIME_SPEC(dt, spec) QwtDateTimeCompat::setTimeSpec(dt, spec)

#else

// For Qt5 and earlier, use the original functions
#define QWT_DATETIME_SET_OFFSET_FROM_UTC(dt, offset) dt.setOffsetFromUtc(offset)
#define QWT_DATETIME_CREATE(date, time, spec) QDateTime(date, time, spec)
#define QWT_DATETIME_TO_TIME_SPEC(dt, spec) dt.toTimeSpec(spec)
#define QWT_DATETIME_SET_TIME_SPEC(dt, spec) dt.setTimeSpec(spec)

#endif // QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)