#include "headers/decisionsparser.h"
#include "headers/data/decision.h"
#include "headers/data/question.h"
#include "headers/data/requirement.h"
#include "headers/data/response.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSharedPointer>

DecisionsParser::DecisionsParser(const QString &decisionsPath, QObject *parent)
    : QObject(parent), decisionsPath_(decisionsPath) {}

bool DecisionsParser::parseQND() {
  QFile decisionFile(decisionsPath_);

  if (!decisionFile.open(QIODevice::ReadOnly))
    return false;

  QString strReply = (QString)decisionFile.readAll();

  QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
  QJsonObject jsonObject = jsonResponse.object();
  QJsonArray jsonQuestionsArray = jsonObject["questions"].toArray();
  QJsonArray jsonDecisionsArray = jsonObject["decisions"].toArray();

  parseQuestions(jsonQuestionsArray);
  parseDecisions(jsonDecisionsArray);

  return true;
}

QList<QSharedPointer<Decision>> DecisionsParser::decisions() const {
  return decisions_;
}

QList<QSharedPointer<Question>> DecisionsParser::questions() const {
  return questions_;
}

void DecisionsParser::parseQuestions(const QJsonArray &jsonArray) {
  foreach (const QJsonValue &value, jsonArray) {
    QJsonObject obj = value.toObject();

    auto question = QSharedPointer<Question>::create(
        obj["title"].toString(), obj["text"].toString(),
        QList<QSharedPointer<Response>>{}, obj["id"].toInt(),
        obj["next"].toObject().toVariantMap());

    auto responses = obj["responses"].toArray();

    foreach (const QJsonValue &respValue, responses) {
      QJsonObject respObj = respValue.toObject();
      question->appendResponse(QSharedPointer<Response>::create(
          respObj["text"].toString(), respObj["id"].toInt(), question->id()));
    }

    questions_.append(std::move(question));
  }
}

void DecisionsParser::parseDecisions(const QJsonArray &jsonArray) {
  foreach (const QJsonValue &value, jsonArray) {
    QJsonObject obj = value.toObject();

    auto requirementsArray = obj["requirements"].toArray();
    QList<QSharedPointer<Requirement>> requirements;
    foreach (const QJsonValue &reqValue, requirementsArray) {
      QJsonObject reqObj = reqValue.toObject();
      requirements.append(QSharedPointer<Requirement>::create(
          reqObj["question_id"].toInt(), reqObj["response_id"].toInt()));
    }

    auto decisionsObj = obj["decision"].toObject();

    decisions_.append(QSharedPointer<Decision>::create(
        decisionsObj["subwoofer"].toString(), decisionsObj["head"].toString(),
        decisionsObj["front"].toString(), decisionsObj["summary"].toDouble(),
        std::move(requirements), decisionsObj["power"].toString()));
  }
}
