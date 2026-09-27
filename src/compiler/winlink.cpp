#include <linker.hpp>

void Linker::winlink(const std::filesystem::path& outputPath
    ,const std::filesystem::path& objectPath,
     const std::filesystem::path& runtime)
{
    const auto bin = runtime / "bin";
        const auto lib = runtime / "lib";

        const auto lld =
            bin / "ld.lld.exe";

        const auto crt2 =
            lib / "crt2.o";

        const auto crtbegin =
            lib / "crtbegin.o";

        const auto crtend =
            lib / "crtend.o";

        const auto builtins =
            lib / "libclang_rt.builtins-x86_64.a";

        std::vector<std::string> args;

        args.push_back(lld.string());
        args.push_back("-m");
        args.push_back("i386pep");
        args.push_back("-Bdynamic");

        args.push_back("-o");
        args.push_back(outputPath.string());

        args.push_back(crt2.string());
        args.push_back(crtbegin.string());

        args.push_back("-L" + lib.string());

        args.push_back(objectPath.string());

        args.push_back("-lmingw32");

        args.push_back(builtins.string());

        args.push_back("-lunwind");
        args.push_back("-lmoldname");
        args.push_back("-lmingwex");
        args.push_back("-lmsvcrt");
        args.push_back("-ladvapi32");
        args.push_back("-lshell32");
        args.push_back("-luser32");
        args.push_back("-lkernel32");

        args.push_back(crtend.string());

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

        if (!std::filesystem::exists(lld))
        {
            fmt::print(
                fg(fmt::terminal_color::red),
                "Linker not found: {}\n",
                lld.string()
            );

            std::exit(78);
        }

        verbose(
            "Running linker:\n"
        );

        for (const auto& arg : args)
        {
            verbose("{} ", arg);
        }

        verbose("\n");

        int result = _spawnv(
            _P_WAIT,
            lld.string().c_str(),
            argv.data()
        );

        if (result == -1)
        {
            fmt::print(
                fg(fmt::terminal_color::red),
                "Failed to start linker ❌\n"
            );

            fmt::print(
                "errno: {}\n",
                errno
            );

            std::exit(78);
        }

        if (result != 0)
        {
            fmt::print(
                fg(fmt::terminal_color::red),
                "Linking failed ❌\n"
            );

            fmt::print(
                "ld.lld exit code: {}\n",
                result
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