#if __has_include("tableanalyzer.hpp")
#   include "tableanalyzer.hpp"
#else
#   error "Cell's tableanalyzer was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief Constructs an abstract TableDataAnalyzer.
 */
TableDataAnalyzer::TableDataAnalyzer()
{
}

/*!
 * \brief Destroys the TableDataAnalyzer.
 */
TableDataAnalyzer::~TableDataAnalyzer()
{
}

CELL_NAMESPACE_END
