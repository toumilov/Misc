#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <mutex>

#define log_error( format, ... )	Trace::instance().msg( __FILE__, __LINE__, Trace::Level::Error, (format), ## __VA_ARGS__ )
#define log_debug( format, ... )	Trace::instance().msg( __FILE__, __LINE__, Trace::Level::Debug, (format), ## __VA_ARGS__ )

class Trace
{
public:
	enum class Level
	{
		Error,
		Debug
	};

	static Trace& instance();
	void setup( Level lvl );
	void msg( const char *file, unsigned line, Level level, const char *format, ... )
			__attribute__ ((format (printf, 5, 6)));

private:
	Trace();
	std::mutex mtx_;
	Level level_;
};


struct LoggerBase
{
	LoggerBase() {};
	virtual ~LoggerBase() {};
	virtual void log( const std::string &s ) = 0;
};

struct FileLogger : LoggerBase
{
	FileLogger( const std::string &file_name );
	~FileLogger();
	virtual void log( const std::string &s ) override;
private:
	std::ofstream fs;
};
