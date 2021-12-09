# 说明

This is a demo for qsqlite.

演示qsqlite 使用，可以使用sqlitebrowser 可视化工具查看sqlite表

sudo apt-get install sqlitebrowser

注意：qsqlite依赖于libqsqlite.so，在debian上面必须安装libqt5sql5-sqlite软件包

否则上报QSqlDatabase: QSQLITE driver not loaded错误

# 使用方式

mkdir build

cd build

rm -rf ./* && cmake .. && make -j

# 运行

./bin/repohelper

# 清理

make clean

# 参考文档

https://stackoverflow.com/questions/9078531/qsqlqueryprepare-database-not-open

https://www.cnblogs.com/xia-weiwen/archive/2017/05/04/6806709.html

https://github.com/hqh2010/Sqlite3Demo
