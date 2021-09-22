#ifndef DECISION_H
#define DECISION_H

#include <QObject>
#include <QSharedPointer>

class Requirement;

class Decision : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString subwoofer READ subwoofer CONSTANT)
  Q_PROPERTY(QString head READ head CONSTANT)
  Q_PROPERTY(QString front READ front CONSTANT)
  Q_PROPERTY(QString power READ power CONSTANT)
  Q_PROPERTY(double summary READ summary CONSTANT)
public:
  explicit Decision(const QString &subwoofer, const QString &head,
                    const QString &front, double summary,
                    QList<QSharedPointer<Requirement>> requirements,
                    const QString &power, QObject *parent = nullptr);

public:
  QList<QSharedPointer<Requirement>> requirements() const;

  QString subwoofer() const;
  QString head() const;
  QString front() const;
  QString power() const;
  double summary() const;

private:
  QString subwoofer_;
  QString head_;
  QString front_;
  QString power_;
  double summary_;
  QList<QSharedPointer<Requirement>> requirements_;
};
Q_DECLARE_METATYPE(Decision *)

#endif // DECISION_H
