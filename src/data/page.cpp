#include "headers/data/page.h"
#include "headers/data/question.h"
#include "headers/models/responsemodel.h"

Page::Page(QSharedPointer<Question> question, QObject *parent)
    : QObject(parent), question_(question),
      responseModel_(
          QSharedPointer<ResponseModel>::create(question->responses())) {}

QString Page::title() const { return question_->title(); }

QString Page::textQuestion() const { return question_->text(); }

ResponseModel *Page::responses() const { return responseModel_.data(); }

int Page::id() const { return question_->id(); }

QVariantMap Page::nextQuestions() const { return question_->nextQuestions(); }
