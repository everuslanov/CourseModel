#ifndef PAGE_H
#define PAGE_H

#include <QAbstractListModel>
#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>

#include "response.h"

class ResponseModel;
class Question;

class Page : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString title READ title FINAL)
  Q_PROPERTY(QString textQuestion READ textQuestion FINAL)
  Q_PROPERTY(ResponseModel *responses READ responses FINAL)
  Q_PROPERTY(int id READ id FINAL)
  Q_PROPERTY(QVariantMap nextQuestions READ nextQuestions FINAL)
public:
  explicit Page(QSharedPointer<Question> question, QObject *parent = nullptr);

public:
  QString title() const;
  QString textQuestion() const;
  ResponseModel *responses() const;
  int id() const;
  QVariantMap nextQuestions() const;

private:
  QSharedPointer<Question> question_;
  QSharedPointer<ResponseModel> responseModel_;
  QVariantMap nextQuestions_;
};
Q_DECLARE_METATYPE(Page *);

#endif // PAGE_H
