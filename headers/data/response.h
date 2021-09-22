#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QSharedPointer>
#include <QtQml>

class Response : public QObject {
  Q_OBJECT
public:
  explicit Response(const QString &text, int id, int questionID,
                    QObject *parent = nullptr);

public:
  QString text() const;
  int id() const;
  int questionID() const;

  static void declareQML() {
    qmlRegisterUncreatableType<Response>(
        "Enums", 1, 0, "Response", "Not creatable as it is an enum type.");
  }

private:
  QString text_;
  int id_;
  int questiondID_;
};

#endif // RESPONSE_H
