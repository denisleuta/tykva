#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cstring> 

constexpr size_t PAGE_SIZE = 4 * 1024; // Размер страницы (4 КБ)

// Функция для чтения памяти с указанным шагом и задержкой
void memoryAccessRead(size_t totalMemoryBytes, unsigned int delayPages) {
    for (size_t offset = 0; offset < totalMemoryBytes; offset += PAGE_SIZE) {
        char* memory = reinterpret_cast<char*>(malloc(PAGE_SIZE)); // Выделение памяти размером PAGE_SIZE

        // "Чтение" из выделенной памяти (заполнение нулями с целью потребления памяти)
        std::memset(memory, 0, PAGE_SIZE);

        // Задержка через определенное количество страниц
        if (offset % (delayPages * PAGE_SIZE) == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Задержка 100 миллисекунд
        }
    }
}

// Функция для записи в память с указанным шагом и задержкой
void memoryAccessWrite(size_t totalMemoryBytes, unsigned int delayPages) {
    for (size_t offset = 0; offset < totalMemoryBytes; offset += PAGE_SIZE) {
        char* memory = reinterpret_cast<char*>(malloc(PAGE_SIZE)); // Выделение памяти размером PAGE_SIZE

        // "Запись" в выделенную память (заполнение данными для потребления памяти)
        std::memset(memory, 'A', PAGE_SIZE);

        // Задержка через определенное количество страниц
        if (offset % (delayPages * PAGE_SIZE) == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Задержка 100 миллисекунд
        }
    }
}

int main() {
    std::string mode;
    std::cout << "Choose mode (read or write): ";
    std::cin >> mode;

    size_t totalMemoryMB;
    std::cout << "Enter total memory (MB): ";
    std::cin >> totalMemoryMB;

    unsigned int delayPages;
    std::cout << "Enter delay pages (each page is 4 KB): ";
    std::cin >> delayPages;

    size_t totalMemoryBytes = totalMemoryMB * 1024 * 1024; // Перевод общего объема памяти из МБ в байты

    if (mode == "read") {
        std::cout << "Memory access (read) with delay..." << std::endl;
        memoryAccessRead(totalMemoryBytes, delayPages);
    }
    else if (mode == "write") {
        std::cout << "Memory access (write) with delay..." << std::endl;
        memoryAccessWrite(totalMemoryBytes, delayPages);
    }
    else {
        std::cerr << "Invalid mode. Please use 'read' or 'write'." << std::endl;
        return 1;
    }

    return 0;
}