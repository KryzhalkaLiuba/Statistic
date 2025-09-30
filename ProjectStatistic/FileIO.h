#pragma once
#include <fstream>
#include <string>

class FileIO {
public:

	struct OpenCloseException : public std::runtime_error {
		OpenCloseException() :runtime_error("error") {}
		OpenCloseException(const std::string& message) :runtime_error(message.c_str()) {}
	};

private:

	std::fstream fileStream;
	std::ios_base::openmode inputOutputMode;
	std::string fileName_;

	void open(const std::ios_base::openmode inputOutputMode) noexcept(false);

public:
	FileIO(const std::string& fileName);

	bool endOfFile() const;

	void close();

	void write(const std::string& contentToWrite, bool appendContent = true);

	bool getline(std::string& s);

	static void saveTextTo(const std::string& fileName, const std::string& text);

	~FileIO();
};




