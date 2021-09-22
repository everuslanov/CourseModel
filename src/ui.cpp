#include "headers/ui.h"

#include <QGuiApplication>
#include <QRect>
#include <QScreen>

Ui::Ui(QObject *parent) : QObject(parent) {
  qreal refDpi = 216.;
  qreal refHeight = 1776.;
  qreal refWidth = 1080.;
  QRect rect = QGuiApplication::primaryScreen()->geometry();
  qreal height = qMax(rect.width(), rect.height());
  qreal width = qMin(rect.width(), rect.height());
  qreal dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
  ratio_ = qMin(height / refHeight, width / refWidth);
  ratio_font_ = qMin(height * refDpi / (dpi * refHeight),
                     width * refDpi / (dpi * refWidth));
  emit ratioChanged();
  emit ratioFontChanged();
}

double Ui::ratio() const { return ratio_; }

double Ui::ratioFont() const { return ratio_font_; }
