#include <linker.hpp>

void Linker::link(const std::string& outputFile)
            {
                std::filesystem::path path(outputFile);
                path.replace_extension(".exe");
                fmt::print("Linking {}\n", outputFile);
                std::string command = "lld-link \"" + outputFile +
                                      "\" /subsystem:console /defaultlib:libcmt /out:\"" +
                                      path.string() + "\"";
                int result = std::system(command.c_str());
                
                if (result != 0)
                {
                    fmt::print(
                        fg(fmt::color::red),
                        "Linking failed ❌\n"
                    );

                    std::exit(78);
                }
                fmt::print(
                fg(fmt::color::green),
                "Linked: {}\n",
                path.string()
                );

            }