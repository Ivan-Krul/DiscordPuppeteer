#include "Bot.h"
#include "EnviroumentFile.h"

Bot Bot::mInstance;

bool Bot::init(const bool log) {
    EnviroumentFile env;

    if (mBot != nullptr) return true;

    mBot = new dpp::cluster(env["TOKEN"]);

    if (mBot && log) mBot->on_log(dpp::utility::cout_logger());

    return false;
}

void Bot::addSlashCommand(const dpp::slashcommand& info, const std::function<void(const dpp::slashcommand_t&)>& callback) {
    if (mSlashCommands == nullptr) {
        mSlashCommands = new std::vector<dpp::slashcommand>();
        mSlashCallbacks = new std::vector<std::function<void(const dpp::slashcommand_t&)>>();

        mBot->on_slashcommand([=](const dpp::slashcommand_t& event) {
            for (size_t c = 0; c < mSlashCommands->size(); c++) {
                if (event.command.get_command_name() == (*mSlashCommands)[c].name) {
                    std::cout << "Called: " << event.command.get_command_name() << '\n';
                    (*mSlashCallbacks)[c](event);
                    break;
                }

                if (c == mSlashCommands->size() - 1) {
                    std::cout << "Command wasn't found ;-;\n";
                    event.reply("Command wasn't found ;-;");
                }
            }
        });
    }

    mSlashCommands->push_back(info);
    mSlashCallbacks->push_back(callback);
}

void Bot::run(bool run_forever) {
    mBot->on_ready([=](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            // init here
            mBot->global_bulk_command_create(*mSlashCommands);
        }
    });

    mBot->start(run_forever);
}

void Bot::terminate() {
    if (mSlashCommands) {
        delete mSlashCommands, mSlashCallbacks;
        mSlashCommands = nullptr;
        mSlashCallbacks = nullptr;
    }

    delete mBot;
    mBot = nullptr;
}
