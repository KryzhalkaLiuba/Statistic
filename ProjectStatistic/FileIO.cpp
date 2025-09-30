#include "FileIO.h"

void FileIO::open(const std::ios_base::openmode inputOutputMode) noexcept(false) {

	if (this->inputOutputMode == inputOutputMode) {
		return;
	}

	close();
	this->inputOutputMode = inputOutputMode;
	fileStream.open(fileName_, inputOutputMode);

	if (fileStream.fail()) {
		throw OpenCloseException("File couldn't be open");
	}
}

FileIO::FileIO(const std::string& fileName) {
	this->fileName_ = fileName;
}

bool FileIO::endOfFile() const {
	return fileStream.eof();
}

void FileIO::close() {
	if (fileStream.is_open()) {
		fileStream.close();
	}
}

bool FileIO::getline(std::string& s) {
	open(std::ios::in);
	if (std::getline(fileStream, s)) {
		return true;
	}
	return false;
}

void FileIO::write(const std::string& contentToWrite, bool appendContent) {

	if (appendContent) { open(std::ios::out | std::ios::in | std::ios::app); }
	else { open(std::ios::out | std::ios::in | std::ios::trunc); }

	fileStream << contentToWrite;
}

void FileIO::saveTextTo(const std::string& fileName, const std::string& text) {
	FileIO fileToWrite(fileName);
	fileToWrite.open(std::ios::out);
	fileToWrite.write(text);
}

FileIO::~FileIO() {
	close();
}