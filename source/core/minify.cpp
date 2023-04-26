#include "minify.hpp"

CELL_NAMESPACE_BEGIN(Cell)

Minify::Minify()
{
    m_minifyStruct = new MinifyStruct();
}

Minify::~Minify()
{
    __cell_safe_delete(m_minifyStruct);
}

CELL_NAMESPACE_END
