#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <QObject>

class Requirement : public QObject {
  Q_OBJECT
public:
  explicit Requirement(int questionID, int responseID,
                       QObject *parent = nullptr);

public:
  int questionID() const;
  int responseID() const;

private:
  int questionID_;
  int responseID_;
};

#endif // REQUIREMENT_H
