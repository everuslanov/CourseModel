#include "headers/data/decision.h"
#include "headers/data/requirement.h"

Decision::Decision(const QString &subwoofer, const QString &head,
                   const QString &front, double summary,
                   QList<QSharedPointer<Requirement>> requirements,
                   const QString &power, QObject *parent)
    : QObject(parent), subwoofer_(subwoofer), head_(head), front_(front),
      summary_(summary), requirements_(std::move(requirements)), power_(power) {
}

QList<QSharedPointer<Requirement>> Decision::requirements() const {
  return requirements_;
}

QString Decision::subwoofer() const { return subwoofer_; }

QString Decision::head() const { return head_; }

QString Decision::front() const { return front_; }

QString Decision::power() const { return power_; }

double Decision::summary() const { return summary_; }
