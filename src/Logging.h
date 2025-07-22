#pragma once
#include "ILogger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>

// Format of all the Error Messages in this application when Trace is turned on
//"[LOG TYPE] [Summarized Message]\n"
//"Reason      : {}\n"
//"Suggestion  : Suggested Fix"
//"Context     : Function: {}, File: {}, Line: {}\n",
//SDL_GetError(), __funct__ ,__FILE__ ,__LINE__,

namespace apex
{
    using LoggerPtr = std::shared_ptr<spdlog::logger>;

    class Logging : public ILogger
    {
    private:
        LoggerPtr console_logger_;
        LoggerPtr file_logger_;

        spdlog::level::level_enum convertLogLevel(LogLevel level);
        void flush();

    public:
        Logging() = default;
        explicit Logging(const std::string& name);

        void log(LogLevel level, const std::string& message) override;
        void trace(const std::string& message) override;
        void debug(const std::string& message) override;
        void info(const std::string& message) override;
        void warn(const std::string& message) override;
        void error(const std::string& message) override;
        void critical(const std::string& message) override;

        
        static Logging& getInstance();

        Logging(const Logging&) = delete;
        Logging& operator=(const Logging&) = delete;
        Logging(Logging&&) = delete;
        Logging& operator=(Logging&&) = delete;

        ~Logging() override {
            flush();
        }
    };
}

// Simple logging format
#define AP_LOG_TRACE1(msg)    apex::Logging::getInstance().trace(msg)
#define AP_LOG_DEBUG1(msg)    apex::Logging::getInstance().debug(msg)
#define AP_LOG_INFO1(msg)     apex::Logging::getInstance().info(msg)
#define AP_LOG_WARN1(msg)     apex::Logging::getInstance().warn(msg)
#define AP_LOG_ERROR1(msg)    apex::Logging::getInstance().error(msg)
#define AP_LOG_CRITICAL1(msg) apex::Logging::getInstance().critical(msg)

// Preferred logging format
#define AP_LOG_TRACE(message,reason, suggested_fix, function, file, line) \
        std::string msg = message + STRING("\nReason      : ") + reason + "\n" \
                         "Suggestion  : " + suggested_fix + "\n" \
                         "Context     : Function: " + STRING(function) + " File: " + STRING(file) + " Line: " + std::to_string(line) + "\n"; \
        apex::Logging::getInstance().trace(msg) \

#define AP_LOG_INFO(message,reason, suggested_fix, function, file, line) \
        std::string msg = message + STRING(STRING("\nReason      : ")) + reason + "\n" \
                         "Suggestion  : " + suggested_fix + "\n" \
                         "Context     : Function: " + STRING(function) + " File: " + STRING(file) + " Line: " + std::to_string(line) + "\n"; \
        apex::Logging::getInstance().info(msg) \

#define AP_LOG_DEBUG(message,reason, suggested_fix, function, file, line) \
        std::string msg = message + STRING("\nReason      : ") + reason + "\n" \
                         "Suggestion  : " + suggested_fix + "\n" \
                         "Context     : Function: " + STRING(function) + " File: " + STRING(file) + " Line: " + std::to_string(line) + "\n"; \
        apex::Logging::getInstance().debug(msg) \

#define AP_LOG_WARN(message,reason, suggested_fix, function, file, line) \
        std::string msg = message + STRING("\nReason      : ") + reason + "\n" \
                         "Suggestion  : " + suggested_fix + "\n" \
                         "Context     : Function: " + STRING(function) + " File: " + STRING(file) + " Line: " + std::to_string(line) + "\n"; \
        apex::Logging::getInstance().warn(msg) \

#define AP_LOG_ERROR(message,reason, suggested_fix, function, file, line) \
        std::string msg = message + STRING("\nReason      : ") + reason + "\n" \
                         "Suggestion  : " + suggested_fix + "\n" \
                         "Context     : Function: " + STRING(function) + " File: " + STRING(file) + " Line: " + std::to_string(line) + "\n"; \
        apex::Logging::getInstance().error(msg) \

#define AP_LOG_CRITICAL(message,reason, suggested_fix, function, file, line) \
        std::string msg = message + STRING("\nReason      : ") + reason + "\n" \
                         "Suggestion  : " + suggested_fix + "\n" \
                         "Context     : Function: " + STRING(function) + " File: " + STRING(file) + " Line: " + std::to_string(line) + "\n"; \
        apex::Logging::getInstance().critical(msg) \

#define AP_LOG_TRACE_FMT(fmt, ...)    apex::Logging::getInstance().trace(fmt::format(fmt, __VA_ARGS__))
#define AP_LOG_DEBUG_FMT(fmt, ...)    apex::Logging::getInstance().debug(fmt::format(fmt, __VA_ARGS__))
#define AP_LOG_INFO_FMT(fmt, ...)     apex::Logging::getInstance().info(fmt::format(fmt, __VA_ARGS__))
#define AP_LOG_WARN_FMT(fmt, ...)     apex::Logging::getInstance().warn(fmt::format(fmt, __VA_ARGS__))
#define AP_LOG_ERROR_FMT(fmt, ...)    apex::Logging::getInstance().error(fmt::format(fmt, __VA_ARGS__))
#define AP_LOG_CRITICAL_FMT(fmt, ...) apex::Logging::getInstance().critical(fmt::format(fmt, __VA_ARGS__))