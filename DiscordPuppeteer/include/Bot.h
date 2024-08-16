#pragma once
#include <functional>

#pragma warning( push )
#pragma warning(disable : 4251)
#include "dpp/dpp.h"
#pragma warning( pop )

class Bot {
public:
    /// <summary>
    /// Initialize bot, inserting a token defined in EnviroumentFile in "TOKEN" field
    /// </summary>
    /// <param name="log"></param>
    /// <returns>returns if the bot ran before init() call. True, when bot is running</returns>
    bool init(const bool log = false);

    /// <summary>
    /// Adds a slash command for the Bot and in your discord server command "/(your command)". It initialize tools for embeding any slash commands in the first call of the function
    /// </summary>
    /// <param name="info">information about the command and in-server description</param>
    /// <param name="callback">calls the function when the command matches</param>
    void addSlashCommand(const dpp::slashcommand& info, const std::function<void(const dpp::slashcommand_t&)>& callback);

    /// <summary>
    /// Starting a bot. The function should be called at last
    /// </summary>
    /// <param name="run_forever">define bot's behaviour during the runtime</param>
    void run(bool run_forever = dpp::st_wait);

    /// <summary>
    /// Gives you the control with the bot cluster. Don't dare you!
    /// </summary>
    inline dpp::cluster* getBotInstance() { return mBot; }

    /// <summary>
    /// Terminates bot, allowing to re-activate. The function is automatically called at the end of runtime
    /// </summary>
    void terminate();
    ~Bot() {
        terminate();
    }

    /// <summary>
    /// Static function for making the instance created once
    /// </summary>
    /// <returns>Instance of Bot class</returns>
    inline static Bot& getInstance() { return mInstance; }
private:
    static Bot mInstance;

    // necessary for re-initialize bot with a new token or with other parameters
    dpp::cluster* mBot = nullptr;

    // they're pointers, because they're optional
    std::vector<dpp::slashcommand>* mSlashCommands = nullptr;
    std::vector<std::function<void(const dpp::slashcommand_t&)>>* mSlashCallbacks = nullptr;

    Bot() = default;
};

