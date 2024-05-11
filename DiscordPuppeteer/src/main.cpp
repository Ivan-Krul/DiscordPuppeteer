#include <iostream>
#include <chrono>
#include <thread>

#include "EnviroumentFile.h"

#include "dpp/dpp.h"

int main() {
    EnviroumentFile env;
    std::cout << env["CLIENTID"] << "\n";

    dpp::cluster bot(env["TOKEN"]);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            // init here
            std::vector<dpp::slashcommand> commands{
                {"ping", "pong!", bot.me.id},
                {"return", "return 0 to this crap", bot.me.id}
            };
            bot.global_bulk_command_create(commands);
        }
    });

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        auto time_start = std::chrono::high_resolution_clock::now();
        if (event.command.get_command_name() == "ping") {
            // handle here
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "pong!\n";
            event.reply("pong!");
        }
        if (event.command.get_command_name() == "return") {
            std::cout << "return 0!\n";
            event.reply("return 0;");
            exit(0);
        }
        auto time_stop = std::chrono::high_resolution_clock::now();
        std::cout << "Response duration: " << float(std::chrono::duration_cast<std::chrono::microseconds>(time_stop - time_start).count()) / 1e6 << "s\n";
    });

    bot.on_message_create([&](const dpp::message_create_t& event) {
        if (event.msg.author.id.str() != bot.me.id.str() && event.msg.author.username == "kiwiidevulopir") {
            event.send("Kiwii be like...");
        }
    });

    bot.start(dpp::st_wait);
}
