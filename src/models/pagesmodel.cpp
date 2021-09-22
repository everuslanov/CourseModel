#include "headers/models/pagesmodel.h"
#include "headers/data/page.h"
#include "headers/data/question.h"
#include "headers/models/responsemodel.h"

PagesModel::PagesModel(QObject *parent)
    : QAbstractListModel(parent), pages_({}) {}

QVariant PagesModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  const int row = index.row();

  if (auto page = pages_.value(row).data()) {
    switch (role) {
    case Roles::Title:
      return page->title();
    case Roles::TextQuestion:
      return page->textQuestion();
    case Roles::Id:
      return page->id();
    case Roles::Responses:
      return QVariant::fromValue(static_cast<QObject *>(page->responses()));
    }
  }

  return QVariant();
}

int PagesModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return pages_.size();
}

QHash<int, QByteArray> PagesModel::roleNames() const {
  return QHash<int, QByteArray>{{Title, "title"},
                                {TextQuestion, "textQuestion"},
                                {Responses, "responses"},
                                {Id, "Id"}};
}

Page *PagesModel::rootPage() const { return pages_.first().data(); }

Page *PagesModel::page(int pageID) const {
  for (auto page : pages_) {
    if (page->id() == pageID)
      return page.data();
  }

  return nullptr;
}

void PagesModel::createPages(QList<QSharedPointer<Question>> questions) {
  for (auto &&question : questions) {
    pages_ << QSharedPointer<Page>::create(question);
  }
}
