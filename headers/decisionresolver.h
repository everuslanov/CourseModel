#ifndef DECISIONRESOLVER_H
#define DECISIONRESOLVER_H

#include <QJsonArray>
#include <QObject>
#include <QSharedPointer>

class Decision;
class Response;

class DecisionResolver : public QObject {
  Q_OBJECT
public:
  explicit DecisionResolver(QList<QSharedPointer<Decision>> decisions,
                            QObject *parent = nullptr);

public:
  Q_INVOKABLE Decision *resolveDecision(QJsonArray map) const;

private:
  QList<QSharedPointer<Decision>> decisions_;
};

#endif // DECISIONRESOLVER_H
