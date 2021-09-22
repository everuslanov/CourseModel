#include <QSharedPointer>

#include "headers/data/response.h"
#include "headers/models/responsemodel.h"

ResponseModel::ResponseModel(QList<QSharedPointer<Response>> responses,
                             QObject *parent)
    : QAbstractListModel(parent), responses_(std::move(responses)) {}

QVariant ResponseModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  const int row = index.row();

  if (auto response = responses_.value(row).data()) {
    switch (role) {
    case Roles::Text:
      return response->text();
    case Roles::Id:
      return response->id();
    }
  }

  return QVariant();
}

int ResponseModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return responses_.size();
}

QHash<int, QByteArray> ResponseModel::roleNames() const {
  return QHash<int, QByteArray>{{Text, "text"}, {Id, "id"}};
}
