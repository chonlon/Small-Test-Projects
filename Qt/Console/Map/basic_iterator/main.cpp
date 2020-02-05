#include <QtCore/QCoreApplication>
#include <QMap>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    QMap<QString, QMap<int, int>> cam_results;
    cam_results.insert("Cam1",
                       {{1, 1}, {2, 2}, {3, 0}});
    cam_results.insert("Cam2",
                       {{1, 0}, {2, 0}, {3, 1}});

    cam_results.find("Cam1").value().remove(2);

    return a.exec();
}
