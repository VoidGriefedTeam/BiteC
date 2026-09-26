#include <linker.hpp>

void Linker::linlink(const std::filesystem::path& outputPath,
        const std::filesystem::path& objectPath,
        const std::filesystem::path& runtime)
{
    const auto bin = runtime / "bin";
    const auto sysroot = runtime / "sysroot";

    const auto lld =
        bin / "ld.lld.exe";

    const auto lib =
        sysroot / "usr" / "lib" / "x86_64-linux-gnu";

    const auto lib64 =
        sysroot / "lib64";

    const auto crt1 =
        lib / "crt1.o";

    const auto crti =
        lib / "crti.o";

    const auto crtn =
        lib / "crtn.o";

    std::vector<std::string> args;

    args.push_back(lld.string());

    args.push_back("--sysroot=" + sysroot.string());

    args.push_back("-m");
    args.push_back("elf_x86_64");

    args.push_back("-dynamic-linker");
    args.push_back("/lib64/ld-linux-x86-64.so.2");

    args.push_back("-L" + lib64.string());

    args.push_back("-o");
    args.push_back(outputPath.string());

    args.push_back(crt1.string());
    args.push_back(crti.string());

    args.push_back(objectPath.string());

    args.push_back("-L" + lib.string());

    args.push_back("-lc");

    args.push_back(crtn.string());

    std::vector<const char*> argv;

    for (const auto& arg : args)
    {
        argv.push_back(arg.c_str());
    }

    argv.push_back(nullptr);

    verbose(
        "Linker: {}\n",
        lld.string()
    );

    int result = _spawnv(
        _P_WAIT,
        lld.string().c_str(),
        argv.data()
    );

    if (result != 0)
    {
        fmt::print(
            fg(fmt::terminal_color::red),
            "Linking failed ❌\n"
        );

        std::exit(78);
    }

    verbose(
        fg(fmt::terminal_color::green),
        "Linked: {}\n",
        outputPath.string()
    );

    return;
}