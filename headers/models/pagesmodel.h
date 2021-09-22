#ifndef PAGESMODEL_H
#define PAGESMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QSharedPointer>

class Page;
class Question;

class PagesModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(Page *rootPage READ rootPage FINAL)
public:
  enum Roles { Title = Qt::UserRole + 1, TextQuestion, Responses, Id };
  explicit PagesModel(QObject *parent = nullptr);

public:
  QVariant data(const QModelIndex &index, int role) const override;
  int rowCount(const QModelIndex &parent) const override;
  QHash<int, QByteArray> roleNames() const override;

  Page *rootPage() const;
  Q_INVOKABLE Page *page(int pageID) const;

public:
  void createPages(QList<QSharedPointer<Question>> questions);

private:
  QList<QSharedPointer<Page>> pages_;
};

#endif // PAGESMODEL_H
