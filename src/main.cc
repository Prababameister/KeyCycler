#include "keyboard.hh"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCoreApplication>

#include <iostream>
#include <fstream>

#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

#include <backend.hh>
#include <cycle_list.hh>

CycleList cycleList;
Cycle masterCycle;

Backend back;


int main(int argc, char *argv[]) {
    // Init sequence
    if(!back.exists(CONFIG_DIR "/cycles.json")) {
        std::ofstream file(CONFIG_DIR "/cycles.json");
        file << "{}";
        file.close();
    }

    std::cout << CONFIG_DIR << " here\n";
    back.retrieveCycles(cycleList, CONFIG_DIR "/cycles.json");
    back.retrieveKbLayouts(masterCycle, "/usr/share/X11/xkb/rules/evdev.lst");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cycleList", &cycleList);
    engine.rootContext()->setContextProperty("kbList", &masterCycle);

    QObject::connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, []() {
        back.saveCycles(cycleList, CONFIG_DIR "/cycles.json");
    });

    engine.load(QStringLiteral(PROJECT_HEAD "/qml/main.qml"));

    return app.exec();
}
