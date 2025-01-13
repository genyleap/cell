//! Cell's Engine.
#if __has_include(<cell/core>)
#   include <cell/core>
#else
#   error "Cell's engine was not found!"
#endif

//! Cell's Dynamics (Moduels/Plugins).
#if __has_include(<cell/dynamics>)
#   include <cell/dynamics>
#else
#   error "Cell's dynamics was not found!"
#endif

#include <cell/modules/built-in/network>
#include <cell/modules/built-in/hardware>
#include <cell/modules/built-in/ai>

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn::Network::WebServer;

auto main() -> int {

    System::DeveloperMode::IsEnable = {true};
    // Initialize the engine
    auto engineController = Cell::System::EngineController();
    auto& engine = engineController.getEngine();

    if (engine.start()) {

    }
}
