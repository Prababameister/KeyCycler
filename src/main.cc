#include <exception>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>

#include <iostream>
#include <fstream>
#include <filesystem>

#include <cycle.hh>

std::vector<Cycle> cycles;

int init_backend() {
    std::ifstream file(CONFIG_DIR "/cycles.json");
    if(!file.is_open()) {
        try {
            std::filesystem::copy_file(PROJECT_HEAD "/resources/cycles.scaffold.json",
                                       CONFIG_DIR "/cycles.json",
                                       std::filesystem::copy_options::overwrite_existing);
        } catch (std::exception& e) {
            std::cout << e.what();
        }

        file.open(CONFIG_DIR "/cycles.json");
    }

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;

    std::string errs;
    if(!Json::parseFromStream(builder, file, &root, &errs)) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return 1;
    }

    Json::Value raw_cycles = root["cycles"];
    cycles.resize(raw_cycles.size());
    for (int i = 0; i < raw_cycles.size(); ++i) {
        for (int j = 0; j < raw_cycles[i]["keyboards"].size(); ++j) {
            Json::Value& kb = raw_cycles[i]["keyboards"][j];
            cycles[i].add_keyboard(kb["full"].asString(), kb["abbrev"].asString());
        }
        cycles[i].set_current(raw_cycles[i]["current_kb"].asInt());
    }

    return 0;
}

int main(int argc, char *argv[]) {
    // Init sequence
    std::cout << init_backend();

    for (Cycle& cyc : cycles) {
        std::cout << "Current kb: " << cyc.get_current() << "\n";
        for(int i = 0; i < cyc.get_cycle_size(); ++i) {
            Cycle::Keyboard* kb = cyc.get_keyboard_layout(i);
            std::cout << "KB " << i << ": " << kb->abbrev << " - " << kb->full << "\n";
        }
    }

    // QGuiApplication app(argc, argv);

    // QQmlApplicationEngine engine;
    // const QUrl url(QStringLiteral(PROJECT_HEAD "/qml/main.qml"));
    // engine.load(url);

    // return app.exec();
}
