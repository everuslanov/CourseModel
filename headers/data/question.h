#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>

class Response;

class Question : public QObject {
  Q_OBJECT
public:
  explicit Question(const QString &title, const QString &text,
                    QList<QSharedPointer<Response>> responses, int id,
                    QVariantMap nextQuestions, QObject *parent = nullptr);

public:
  void appendResponse(QSharedPointer<Response> response);

  QList<QSharedPointer<Response>> responses() const;
  QString title() const;
  QString text() const;
  int id() const;
  QVariantMap nextQuestions() const;

private:
  QString title_;
  QString text_;
  QList<QSharedPointer<Response>> responses_;
  int id_;
  QVariantMap nextQuestions_;
};

#endif // QUESTION_H
