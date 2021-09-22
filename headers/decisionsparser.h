#ifndef DECISIONSPARSER_H
#define DECISIONSPARSER_H

#include <QFile>
#include <QObject>
#include <QSharedPointer>

class Decision;
class Question;

class DecisionsParser : public QObject {
  Q_OBJECT
public:
  explicit DecisionsParser(const QString &decisionsPath,
                           QObject *parent = nullptr);

public:
  bool parseQND();

  QList<QSharedPointer<Decision>> decisions() const;
  QList<QSharedPointer<Question>> questions() const;

private:
  void parseQuestions(const QJsonArray &jsonArray);
  void parseDecisions(const QJsonArray &jsonArray);

private:
  QString decisionsPath_;
  QList<QSharedPointer<Decision>> decisions_;
  QList<QSharedPointer<Question>> questions_;
};

#endif // DECISIONSPARSER_H
