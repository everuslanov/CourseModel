#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <QObject>

class Requirement {
public:
  explicit Requirement(int questionID, int responseID);

public:
  int questionID() const;
  int responseID() const;

private:
  int questionID_;
  int responseID_;
};

#endif // REQUIREMENT_H
