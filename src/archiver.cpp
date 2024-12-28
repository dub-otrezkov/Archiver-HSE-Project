#include <iostream>

#include "archive.h"
#include "utilities.h"
#include "dearchive.h"

int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            throw std::logic_error("invalid args. run 'archiver -h' to see documentation\n");
        }
        std::string command = std::string(*(argv + 1));
        if (command == "-h") {
            std::cout << "run 'archiver -h' to see documentation\n";
            std::cout << "run 'archiver -c archive_name file1 [file2 ...]' to archive file1, [file2 ...] into "
                         "'archive_name'\n";
            std::cout << "run 'archiver -d archive_name' to dearchivate 'archive_name'\n";
        } else if (command == "-c") {
            if (argc < 4) {
                throw std::logic_error("invalid args. run 'archiver -h' to see documentation\n");
            }
            std::vector<const char*> files_to_archive;
            for (int file_index = 3; file_index < argc; ++file_index) {
                files_to_archive.push_back(*(argv + file_index));
            }

            Archive(*(argv + 2), files_to_archive);
        } else if (command == "-d") {
            if (argc != 3) {
                throw std::logic_error("invalid args. run 'archiver -h' to see documentation\n");
            } else {
                Dearchive(*(argv + 2));
            }
        } else {
            throw std::logic_error("invalid args. run 'archiver -h' to see documentation\n");
        }

        return 0;
    } catch (std::runtime_error& err) {
        std::cout << "error occured: " << err.what() << "\n";
        return ArchiverFailedCode;
    } catch (std::logic_error& err) {
        std::cout << "error occured: " << err.what() << "\n";
        return ArchiverFailedCode;
    }
}
