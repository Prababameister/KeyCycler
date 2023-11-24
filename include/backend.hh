#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

#include <cycle_list.hh>

class Backend {
    public:
        Backend();

        void retrieveCycles(CycleList& cycleList, std::string path);
        void saveCycles(CycleList& cycleList, std::string path);

        void retrieveKbLayouts(Cycle& masterCycle, std::string path);

        bool exists(std::string path);
    private:
        std::fstream file;

        Json::CharReaderBuilder builder;
        Json::CharReader* reader;
        Json::StreamWriterBuilder wbuilder;
};
