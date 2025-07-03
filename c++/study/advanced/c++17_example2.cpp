#include <iostream>
#include <tuple>
#include <optional>
#include <variant>
#include <any>
#include <string_view>
#include <vector>
#include <algorithm>
#include <execution>
#include <filesystem>
#include <mutex>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void create_and_write_file(const fs::path& filepath) {
    std::ofstream file(filepath);
    if (file) {
        file << "Hello, std::filesystem!";
        std::cout << "File created: " << filepath << "\n";
    }
    else {
        std::cerr << "Failed to create file: " << filepath << "\n";
    }
}

void display_file_info(const fs::path& filepath) {
    if (fs::exists(filepath)) {
        std::cout << "File: " << filepath << "\n";
        std::cout << "Size: " << fs::file_size(filepath) << " bytes\n";
        std::cout << "Last modified: " << fs::last_write_time(filepath).time_since_epoch().count() << "\n";
        std::cout << "Is regular file: " << fs::is_regular_file(filepath) << "\n";
    }
    else {
        std::cerr << "File does not exist: " << filepath << "\n";
    }
}

void list_directory(const fs::path& dirpath) {
    if (fs::exists(dirpath) && fs::is_directory(dirpath)) {
        std::cout << "Contents of " << dirpath << ":\n";
        for (const auto& entry : fs::directory_iterator(dirpath)) {
            std::cout << "  " << entry.path() << "\n";
        }
    }
    else {
        std::cerr << "Directory does not exist: " << dirpath << "\n";
    }
}

void copy_and_move_file(const fs::path& src, const fs::path& dest) {
    try {
        fs::copy(src, dest, fs::copy_options::overwrite_existing);
        std::cout << "Copied " << src << " to " << dest << "\n";
        fs::rename(dest, dest.parent_path() / "moved_file.txt");
        std::cout << "Moved to " << (dest.parent_path() / "moved_file.txt") << "\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

void create_link(const fs::path& target, const fs::path& link) {
    try {
        fs::create_symlink(target, link);
        std::cout << "Symlink created: " << link << " -> " << target << "\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

void check_space(const fs::path& dirpath) {
    auto space = fs::space(dirpath);
    std::cout << "Free space in " << dirpath << ": " << space.free / (1024 * 1024) << " MB\n";
}

void remove_file_or_directory(const fs::path& path) {
    if (fs::remove_all(path)) {
        std::cout << "Deleted: " << path << "\n";
    }
    else {
        std::cerr << "Failed to delete: " << path << "\n";
    }
}

int test_filesystem_all() {
    fs::path test_dir = "test_dir";
    fs::path test_file = test_dir / "test.txt";
    fs::path copy_file = test_dir / "copy.txt";
    fs::path symlink_path = test_dir / "symlink.txt";

    fs::create_directory(test_dir);
    create_and_write_file(test_file);
    display_file_info(test_file);
    list_directory(test_dir);
    copy_and_move_file(test_file, copy_file);
    create_link(test_file, symlink_path);
    check_space(test_dir);
    remove_file_or_directory(test_dir);
    return 0;
}

inline constexpr int inlineVar = 42;

int main() {
    // 1. Structured Bindings
    std::tuple<int, double, std::string> myTuple = { 10, 3.14, "Hello" };
    auto [intVal, doubleVal, strVal] = myTuple;
    std::cout << "Structured Bindings: " << intVal << ", " << doubleVal << ", " << strVal << std::endl;

    // 2. If and Switch with Initializers
    if (auto result = intVal * 2; result > 0) {
        std::cout << "If with initializer: " << result << std::endl;
    }

    // 3. Inline Variables (Demonstrated with a header, but shown as a concept here)
    std::cout << "Inline Variable: " << inlineVar << std::endl;

    // 4. constexpr Lambda Expressions
    constexpr auto square = [](int x) constexpr { return x * x; };
    constexpr int squared = square(5);
    std::cout << "constexpr Lambda: " << squared << std::endl;

    // 5. Fold Expressions
    auto sum = [](auto... args) { return (args + ...); };
    std::cout << "Fold Expression: " << sum(1, 2, 3, 4) << std::endl;

    // 6. Template Argument Deduction for Class Templates
    std::pair myPair(10, 3.14);
    std::cout << "Template Deduction: " << myPair.first << ", " << myPair.second << std::endl;

    // 7. Guaranteed Copy Elision (Demonstrated conceptually, as it's compiler-driven)
    // (This is hard to show simply, but elision happens in many return cases now)

    // 8. [[maybe_unused]] Attribute
    [[maybe_unused]] int unusedVar = 0;

    // 9. [[fallthrough]] Attribute
    int switchVal = 1;
    switch (switchVal) {
    case 1:
        std::cout << "Switch case 1" << std::endl;
        [[fallthrough]];
    case 2:
        std::cout << "Switch case 2" << std::endl;
        break;
    default:
        std::cout << "Default" << std::endl;
    }

    // 10. [[nodiscard]] Attribute
    [[nodiscard]] auto createValue = []() { return 123; };
    createValue(); // Compiler warning if not used.

    // 11. std::optional
    std::optional<int> optVal = 5;
    std::cout << "Optional: " << optVal.value_or(0) << std::endl;

    // 12. std::variant
    std::variant<int, std::string> varVal = "Variant string";
    if (std::holds_alternative<std::string>(varVal)) {
        std::cout << "Variant: " << std::get<std::string>(varVal) << std::endl;
    }

    // 13. std::any
    std::any anyVal = 123.45;
    std::cout << "Any: " << std::any_cast<double>(anyVal) << std::endl;

    // 14. std::string_view
    std::string_view view = "String View";
    std::cout << "String View: " << view << std::endl;

    // 15. Parallel Algorithms
    std::vector<int> vec = { 5, 2, 8, 1, 9 };
    std::sort(std::execution::par, vec.begin(), vec.end());
    std::cout << "Parallel Sort: ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 16. Filesystem Library
    fs::path currentPath = fs::current_path();
    std::cout << "Current Path: " << currentPath << std::endl;

    // 17. std::scoped_lock
    std::mutex mutex1, mutex2;
    {
        std::scoped_lock lock(mutex1, mutex2);
        std::cout << "Scoped Lock acquired" << std::endl;
    }

    //18. std::clamp
    int myValue = 10;
    int clampedValue = std::clamp(myValue, 0, 5);
    std::cout << "Clamped value: " << clampedValue << std::endl;

    //19. std::as_const
    std::string mutableString = "Hello";
    const std::string& constString = std::as_const(mutableString);
    std::cout << "as_const example: " << constString << std::endl;

    return test_filesystem_all();
}