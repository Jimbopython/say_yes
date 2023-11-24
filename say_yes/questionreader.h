#pragma once

#include <QObject>
#include <QJsonObject>

class QuestionReader : public QObject
{
    Q_OBJECT

    QStringList m_changingParagraphs;
    QString m_question;

    void readChangingParagraphs(const QJsonObject& jsonObject);

    void readQuestion(const QJsonObject& jsonObject);
public:
    QuestionReader();
    QStringList getChangingParagraphs();

    QString getQuestion();
};
