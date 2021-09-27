#include "headers/decisionresolver.h"
#include "headers/data/decision.h"
#include "headers/data/requirement.h"
#include "headers/data/response.h"

#include <QJsonObject>

DecisionResolver::DecisionResolver(QList<QSharedPointer<Decision>> decisions,
                                   QObject *parent)
    : QObject(parent), decisions_(std::move(decisions)) {}

Decision *DecisionResolver::resolveDecision(QJsonArray map) const {
  QList<Requirement> responseReqs;
  for (auto value : map) {
    auto obj = value.toObject();
    responseReqs.append(Requirement{obj.keys().first().toInt(),
                                    obj.value(obj.keys().first()).toInt()});
  }

  int success = 0;
  for (auto decision : decisions_) {
    if (decision->requirements().size() != responseReqs.size())
      continue;

    int index = -1;
    for (auto requirement : decision->requirements()) {
      ++index;
      if (requirement->questionID() == responseReqs[index].questionID() &&
          requirement->responseID() == responseReqs[index].responseID()) {
        success++;
      } else {
        continue;
      }
    }
    if (success == decision->requirements().size()) {
      return decision.data();
    }
    success = 0;
  }
  return nullptr;
}
