#ifndef UI_H
#define UI_H

#include <QObject>

class Ui : public QObject {
  Q_OBJECT
  Q_PROPERTY(double ratio READ ratio NOTIFY ratioChanged)
  Q_PROPERTY(double ratioFont READ ratioFont NOTIFY ratioFontChanged)

public:
  explicit Ui(QObject *parent = nullptr);

public:
  double ratio() const;
  double ratioFont() const;

signals:
  void ratioFontChanged();
  void ratioChanged();

private:
  double ratio_font_;
  double ratio_;
};

#endif // UI_H
