/*
 * Copyright (c) 2020-2021. demo Software Ltd. All rights reserved.
 *
 * Author:     xxxxxx <xxxxxx@163.com>
 *
 * Maintainer: xxxxxx <xxxxxx@163.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <iostream>
#include <string>

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QMutex>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
// 专门对SQL语句操作的类
#include <QSqlQuery>

using namespace std;

bool dirExists(const QString &path)
{
    QFileInfo fs(path);
    return fs.exists() && fs.isDir() ? true : false;
}

void Qsqltest()
{
    const QString dbPath = "/deepin/linglong/layers/";
    //添加数据库驱动，并指定连接名称linglong_package_connection
    QSqlDatabase dbConn;
    if (QSqlDatabase::contains("linglong_package_connection")) {
        dbConn = QSqlDatabase::database("linglong_package_connection");
    } else {
        dbConn = QSqlDatabase::addDatabase("QSQLITE", "linglong_package_connection");
        dbConn.setDatabaseName(dbPath + "AppInstalledInfo.db");
    }
    if (!dbConn.open()) {
        qCritical() << "open DB failed";
        return;
    }

    qInfo() << "db status:" << dbConn.isOpen();

    QString createSql = "CREATE TABLE IF NOT EXISTS student(\
         ID INTEGER PRIMARY KEY AUTOINCREMENT,\
         name VARCHAR(32) NOT NULL,\
         sex CHAR(10),\
         score INTEGER\
         )";
    QSqlQuery sql_query(createSql, dbConn);
    //sql_query.prepare(dbConn, createSql);
    if (!sql_query.exec()) {
        qInfo() << "Error: Fail to create table." << sql_query.lastError();
    } else {
        qInfo() << "Table created success";
    }
    // 增
    QString insertSql = "INSERT INTO student(name,sex,score) VALUES('zhangsan', '男','78')";
    sql_query.prepare(insertSql);
    if (!sql_query.exec()) {
        qInfo() << "Error: Fail to exec sql:" << insertSql << ", error:" << sql_query.lastError();
        return;
    }

    insertSql = "INSERT INTO student(name,sex,score) VALUES('lili', '女','80')";
    sql_query.prepare(insertSql);
    if (!sql_query.exec()) {
        qInfo() << "Error: Fail to exec sql:" << insertSql << ", error:" << sql_query.lastError();
        return;
    }

    insertSql = "INSERT INTO student(name,sex,score) VALUES('wangwu', '男','85')";
    sql_query.prepare(insertSql);
    if (!sql_query.exec()) {
        qInfo() << "Error: Fail to exec sql:" << insertSql << ", error:" << sql_query.lastError();
        return;
    }
    // 改
    QString updateSql = "update student set score=81,sex='女' where name='wangwu'";
    sql_query.prepare(updateSql);
    if (!sql_query.exec()) {
        qInfo() << "Error: Fail to exec sql:" << updateSql << ", error:" << sql_query.lastError();
        return;
    }
    // 删
    QString delSql = "delete from student where name = 'lili'";
    sql_query.prepare(delSql);
    if (!sql_query.exec()) {
        qInfo() << "Error: Fail to exec sql:" << delSql << ", error:" << sql_query.lastError();
        return;
    }
    // 查
    QString select_sql = "select * from student";
    if (!sql_query.exec(select_sql)) {
        qInfo() << sql_query.lastError();
        return;
    } else {
        while (sql_query.next()) {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            qInfo() << QString("id:%1 name:%2").arg(id).arg(name);
        }
    }
    //关闭数据库
    dbConn.close();
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch (type) {
    case QtDebugMsg:
        text = QString("[Debug]");
        break;
    case QtInfoMsg:
        text = QString("[Info]");
        break;
    case QtWarningMsg:
        text = QString("[Warning]");
        break;
    case QtCriticalMsg:
        text = QString("[Critical]");
        break;
    case QtFatalMsg:
        text = QString("[Fatal]");
    }

    QString context_info =
        QString("[File:%1 Line:%2 Func:%3]").arg(QString(context.file)).arg(context.line).arg(context.function);

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    QString current_date = QString("%1").arg(current_date_time);

    QString message = QString("%1 %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(msg);

    QFile file("/tmp/ll-debug/ostreehelp_log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << message << "\n";
    file.flush();
    file.close();
    mutex.unlock();
}

int main(int argc, char **argv)
{
    if (dirExists("/tmp/ll-debug")) {
        qInstallMessageHandler(outputMessage);
    } else {
        qSetMessagePattern(
            "%{time yyyy-MM-dd hh:mm:ss.zzz} [%{type}] [File:%{file} Line:%{line} Function:%{function}] %{message}");
    }
    Qsqltest();
}
