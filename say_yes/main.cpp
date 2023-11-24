#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtGlobal>
#include <QQuickStyle>

#include "settingsmanager.h"
#include "questionreader.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");

    QuestionReader questionReader;
    const auto paragraphs = questionReader.getChangingParagraphs();
    const auto question = questionReader.getQuestion();

    SettingsManager settings;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("paragraphs", paragraphs);
    engine.rootContext()->setContextProperty("question", question);
    engine.rootContext()->setContextProperty("settings", &settings);

    QUrl url;
    if (settings.alreadyChoseOnce())
    {
        url.setUrl(QStringLiteral("qrc:/AlreadyChosen.qml"));
    }
    else
    {
        url.setUrl(QStringLiteral("qrc:/Question.qml"));
    }

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
