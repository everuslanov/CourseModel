#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "headers/data/decision.h"
#include "headers/data/page.h"
#include "headers/decisionresolver.h"
#include "headers/decisionsparser.h"
#include "headers/models/pagesmodel.h"
#include "headers/models/responsemodel.h"
#include "headers/ui.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  DecisionsParser parser(qApp->applicationDirPath() + "/decisions.json");
  parser.parseQND();

  Ui screenParams;

  DecisionResolver resolver(parser.decisions());

  PagesModel pages;
  pages.createPages(parser.questions());

  qRegisterMetaType<Page *>();
  qRegisterMetaType<ResponseModel *>();
  qRegisterMetaType<Decision *>();

  QQuickStyle::setStyle("Material");

  qmlRegisterSingletonType(QUrl("qrc:/qml/UI.qml"), "Ui", 1, 0, "Ui");

  engine.rootContext()->setContextProperty("_pagesModel", &pages);
  engine.rootContext()->setContextProperty("_decisionResolver", &resolver);
  engine.rootContext()->setContextProperty("_screenParams", &screenParams);
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

  return app.exec();
}
