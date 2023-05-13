#include <core/core.hpp>
#include <core/logger.hpp>

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;

class TestCore
{
public:
    void runInstanceExample()
    {
        auto ev1    = Engine               ();    //!< Simple - safe & Static Singleton Pattern (Limited Only once) - safe
        auto ev2    = createEngineObject   ();    //!< Smart Pointer (Perfect RAII) - safe
        auto ev3    = safeEngine           ();    //!< Optional (Safe mode) - safe
        auto *ev4   = new Engine           ();    //!< Raw Pointer (Classic pointer to the engine) - unsafe

        if(ev1.instance().initialize())
        {
            if(ev3.has_value())
                std::cout << "Copyright:" << ev3->copyright() << std::endl;
        }

        Log(ev1.instance().translator()->translate("en_US","account","recent_activity").defaultValue(), LoggerType::Info);
        Log(ev1.instance().translator()->translate("fa_IR","account","recent_activity").defaultValue(), LoggerType::Info);
    }
};
