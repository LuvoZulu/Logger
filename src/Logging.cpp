#include "Logging.h"


namespace apex
{
    // Configuration constants
    static constexpr size_t MAX_FILE_SIZE = 1024 * 1024 * 5;  // 5MB
    static constexpr size_t MAX_FILES = 3;
    static constexpr size_t ASYNC_QUEUE_SIZE = 8192;
    static constexpr size_t ASYNC_THREAD_COUNT = 1;

    Logging::Logging(const std::string& name)
    {
        try {
            // Ensure log directory exists
            std::filesystem::create_directories("./logs");

            // Initialize async logging if not already done
            if (!spdlog::get("async_tp")) {
                spdlog::init_thread_pool(ASYNC_QUEUE_SIZE, ASYNC_THREAD_COUNT);
            }

            // Create console logger
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern("%^[%^%l%$] [%n] [%Y-%m-%d %H:%M:%S.%e] %v");

            // Create rotating file logger
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                "./logs/" + name + ".log", MAX_FILE_SIZE, MAX_FILES);
            file_sink->set_pattern("[%^%l%$] [%n] [%Y-%m-%d %H:%M:%S.%e] %v");

            // Create loggers with both sinks
            std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };

            console_logger_ = std::make_shared<spdlog::async_logger>(
                name , console_sink, spdlog::thread_pool(),
                spdlog::async_overflow_policy::block);

            file_logger_ = std::make_shared<spdlog::async_logger>(
                name + "_file", file_sink, spdlog::thread_pool(),
                spdlog::async_overflow_policy::block);

            // Set default log level
            console_logger_->set_level(spdlog::level::info);
            file_logger_->set_level(spdlog::level::debug);  // File gets more detail

            // Register loggers
            spdlog::register_logger(console_logger_);
            spdlog::register_logger(file_logger_);

        }
        catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "Log initialization failed: " << ex.what() << std::endl;
            throw;
        }
    }

    Logging& Logging::getInstance()
    {
        static Logging instance("Apex-Engine");
        return instance;
    }

    spdlog::level::level_enum Logging::convertLogLevel(LogLevel level)
    {
        switch (level) {
        case LogLevel::TRACE:    return spdlog::level::trace;
        case LogLevel::DEBUG:    return spdlog::level::debug;
        case LogLevel::INFO:     return spdlog::level::info;
        case LogLevel::WARN:     return spdlog::level::warn;
        case LogLevel::ERRO:    return spdlog::level::err;
        case LogLevel::CRITICAL: return spdlog::level::critical;
        default:                 return spdlog::level::info;
        }
    }

    void Logging::flush()
    {
        if (console_logger_) {
            console_logger_->flush();
        }
        if (file_logger_) {
            file_logger_->flush();
        }
    }

    void Logging::log(LogLevel level, const std::string& message)
    {
        if (!console_logger_ || !file_logger_) {
            std::cerr << "Logger not initialized: " << message << std::endl;
            return;
        }

        const auto spdlog_level = convertLogLevel(level);

        // Log to both loggers at the specified level
        console_logger_->log(spdlog_level, message);
        file_logger_->log(spdlog_level, message);
    }

    void Logging::trace(const std::string& message)
    {
        if (console_logger_ && file_logger_) {
            console_logger_->trace(message);
            file_logger_->trace(message);
        }
    }

    void Logging::debug(const std::string& message)
    {
        if (console_logger_ && file_logger_) {
            console_logger_->debug(message);
            file_logger_->debug(message);
        }
    }

    void Logging::info(const std::string& message)
    {
        if (console_logger_ && file_logger_) {
            console_logger_->info(message);
            file_logger_->info(message);
        }
    }

    void Logging::warn(const std::string& message)
    {
        if (console_logger_ && file_logger_) {
            console_logger_->warn(message);
            file_logger_->warn(message);
        }
    }

    void Logging::error(const std::string& message)
    {
        if (console_logger_ && file_logger_) {
            console_logger_->error(message);
            file_logger_->error(message);
        }
    }

    void Logging::critical(const std::string& message)
    {
        if (console_logger_ && file_logger_) {
            console_logger_->critical(message);
            file_logger_->critical(message);
        }
    }
}