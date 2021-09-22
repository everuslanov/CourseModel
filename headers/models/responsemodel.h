#ifndef RESPONSEMODEL_H
#define RESPONSEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

class Response;

class ResponseModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum Roles { Text = Qt::UserRole + 1, Id };
  explicit ResponseModel(QList<QSharedPointer<Response>> responses,
                         QObject *parent = nullptr);

public:
  QVariant data(const QModelIndex &index, int role) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QHash<int, QByteArray> roleNames() const override;

private:
  QList<QSharedPointer<Response>> responses_;
};
Q_DECLARE_METATYPE(QAbstractListModel *)

#endif // RESPONSEMODEL_H
