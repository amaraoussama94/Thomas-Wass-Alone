#pragma once
#include <iostream>
#include <fstream>
#include <string>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
public:
    static void log(const std::string& message, LogLevel level = LogLevel::INFO) {
        std::ofstream logFile("debug.log", std::ios::app);
        if (!logFile) return;

        switch (level) {
            case LogLevel::INFO: logFile << "[INFO] "; break;
            case LogLevel::WARNING: logFile << "[WARNING] "; break;
            case LogLevel::ERROR: logFile << "[ERROR] "; break;
        }
        logFile << message << std::endl;
        logFile.close();
    }
};
