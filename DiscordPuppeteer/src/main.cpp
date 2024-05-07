#include <iostream>

#include "EnviroumentFile.h"

#include "dpp/dpp.h"

int main() {
    EnviroumentFile env;
    std::cout << env["CLIENTID"] << "\n";

    dpp::cluster bot(env["TOKEN"]);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            std::vector<dpp::slashcommand> commands{
                {"ping", "pong!", bot.me.id}
            };
            bot.global_bulk_command_create(commands);
        }
    });

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            std::cout << "pong!\n";
            event.reply("pong!");
            
        }
        //return dpp::task_dummy();
    });

    bot.start(dpp::st_wait);

}
