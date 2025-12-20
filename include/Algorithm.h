#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Algorithm {
public:
    Algorithm() = default;
    virtual ~Algorithm() = default;

    virtual std::string name() const = 0;
    virtual fs::path folder() const = 0;
    static bool alias(const std::string alg);

    // User input, setup, etc.
    virtual void configure() = 0;

    virtual bool loadFile(const fs::path &file) = 0;
    virtual void run() = 0;

    virtual std::string results() const = 0;
};
