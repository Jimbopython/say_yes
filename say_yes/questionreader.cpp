#pragma once

#include "questionreader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



void QuestionReader::readChangingParagraphs(const QJsonObject& jsonObject)
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

void QuestionReader::readQuestion(const QJsonObject& jsonObject)
{
    const auto value = jsonObject.value(QString("mainQuestion"));
    if (!value.isString())
    {
        // todo
    }
    m_question = value.toString();
}

QuestionReader::QuestionReader()
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

QStringList QuestionReader::getChangingParagraphs()
{
    return m_changingParagraphs;
}

QString QuestionReader::getQuestion()
{
    return m_question;
}
