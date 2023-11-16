#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtGlobal>

class QuestionReader : public QObject
{
    Q_OBJECT

    QStringList m_changingParagraphs;
    QString m_question;

    void readChangingParagraphs(const QJsonObject& jsonObject)
    {
        const auto value = jsonObject.value(QString("changingParagraphs"));
        if (!value.isArray())
        {
            // todo
        }
        const auto array = value.toArray();
        for (const auto& val : array) {
            m_changingParagraphs.append(val.toString());
        }
    }

    void readQuestion(const QJsonObject& jsonObject)
    {
        const auto value = jsonObject.value(QString("mainQuestion"));
        if (!value.isString())
        {
            // todo
        }
        m_question = value.toString();
    }
public:
    QuestionReader()
    {
        QString val;
        QFile file;

        file.setFileName("test.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = d.object();

        readQuestion(jsonObject);
        readChangingParagraphs(jsonObject);
    }

    QStringList getChangingParagraphs()
    {
        return m_changingParagraphs;
    }

    QString getQuestion()
    {
        return m_question;
    }
};


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QuestionReader questionReader;
    const auto paragraphs = questionReader.getChangingParagraphs();
    const auto question = questionReader.getQuestion();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("paragraphs", paragraphs);
    engine.rootContext()->setContextProperty("question", question);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

#include "main.moc"
