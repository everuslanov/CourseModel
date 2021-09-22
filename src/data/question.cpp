#include "headers/data/question.h"
#include "headers/data/response.h"

Question::Question(const QString &title, const QString &text,
                   QList<QSharedPointer<Response>> responses, int id,
                   QVariantMap nextQuestions, QObject *parent)
    : QObject(parent), title_(title), text_(text),
      responses_(std::move(responses)), id_(id), nextQuestions_(nextQuestions) {
}

void Question::appendResponse(QSharedPointer<Response> response) {
  responses_.append(std::move(response));
}

QList<QSharedPointer<Response>> Question::responses() const {
  return responses_;
}

QString Question::title() const { return title_; }

QString Question::text() const { return text_; }

int Question::id() const { return id_; }

QVariantMap Question::nextQuestions() const { return nextQuestions_; }
