#pragma once
#include "appch.h"


namespace apex {
    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERRO,
        CRITICAL
    };

    class ILogger {
    public:
        virtual ~ILogger() = default;

        virtual void log(LogLevel level, const std::string& message) = 0;
        virtual void trace(const std::string& message) = 0;
        virtual void debug(const std::string& message) = 0;
        virtual void info(const std::string& message) = 0;
        virtual void warn(const std::string& message) = 0;
        virtual void error(const std::string& message) = 0;
        virtual void critical(const std::string& message) = 0;

        template<typename ...Args>
        void log(LogLevel level,std::string& format, Args&&... args) {
            log(level, formatMessage(format, std::forward<Args>(args)...));
        }
        template<typename ...Args>
        void trace(std::string& format, Args&&... args) {
            trace(formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename ...Args>
        void debug(std::string& format, Args&&... args) {
            debug(formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename ...Args>
        void info(std::string& format, Args&&... args) {
            info(formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename ...Args>
        void warn(std::string& format, Args&&... args) {
            warn(formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename ...Args>
        void error(std::string& format, Args&&... args) {
            error(formatMessage(format, std::forward<Args>(args)...));
        }

        template<typename ...Args>
        void critical(std::string& format, Args&&... args) {
            critical(formatMessage(format, std::forward<Args>(args)...));
        }

    protected:
        template<typename... Args>
        std::string formatMessage(const std::string& format, Args&&... args) {
            return format;
        }

    };
};