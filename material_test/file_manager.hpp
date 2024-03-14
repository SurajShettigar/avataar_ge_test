#ifndef MATERIAL_TEST_FILE_MANAGER_HPP
#define MATERIAL_TEST_FILE_MANAGER_HPP

#include <filesystem>
#include <fstream>


typedef std::filesystem::path Filepath;
typedef std::ifstream FileStream;

static inline bool fileExists(const Filepath &filepath) {
    return std::filesystem::exists(filepath);
}

static inline std::string getFilename(const Filepath &filepath) {
    return filepath.filename().string();
}

static inline std::string getExtension(const Filepath &filepath) {
    const std::string ext = filepath.extension().string();
    return ext.empty() ? ext : ext.substr(1, ext.size());
}

static inline Filepath getAbsoluteFilepath(const Filepath &filepath) {
    return std::filesystem::absolute(filepath);
}

static inline size_t getFileSize(const Filepath &filepath) {
    return std::filesystem::file_size(filepath);
}

static inline FileStream openFileToRead(const Filepath &filepath, bool is_binary = false,
                                        bool seek_to_eof = true) {
    std::ifstream::openmode mode =
            (is_binary ? std::ios::binary : 0) | (seek_to_eof ? std::ios::ate : 0);
    return std::ifstream(filepath.string(), mode);
}

static inline void closeFile(FileStream &stream) { stream.close(); }

static inline void readFileChunk(FileStream &stream, size_t offset,
                                 size_t chunk_size, char *data) {
    stream.seekg(static_cast<std::ifstream::off_type>(offset), std::ios::beg);
    stream.read(data, static_cast<std::streamsize>(chunk_size));
}

static inline size_t readFile(const Filepath &filepath, bool is_binary, char *data) {
    if (!fileExists(filepath)) return 0;

    std::ifstream stream = openFileToRead(filepath, is_binary);
    size_t size = stream.tellg();
    if (data == nullptr) return size;

    readFileChunk(stream, 0, size, data);
    closeFile(stream);
    return size;
}

#endif  // MATERIAL_TEST_FILE_MANAGER_HPP
