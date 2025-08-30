/**
 * @file logger.hpp
 * @brief Simple logging utility for debugging purposes
 *  @date 2025-06-15
 * @version 1.0
 * @author Oussama amara
 */
#pragma once
#include <iostream>
#include <fstream>
#include <string>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
public:
    static void Log(const std::string& module, const std::string& message, LogLevel level = LogLevel::INFO) {
        std::ofstream logFile("debug.log", std::ios::app);
        if (!logFile) return;

        switch (level) {
            case LogLevel::INFO: logFile << "[INFO] "; break;
            case LogLevel::WARNING: logFile << "[WARNING] "; break;
            case LogLevel::ERROR: logFile << "[ERROR] "; break;
        }
        logFile << "[" << module << "] " << message << std::endl;
        logFile.close();
    }

};
