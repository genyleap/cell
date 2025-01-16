/*!
 * @file        renderer.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Renderer system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       16 Jan 2025
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#if __has_include("renderformat.hpp")
#   include "renderformat.hpp"
#else
#   error "Cell's "renderformat.hpp" was not found!"
#endif

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::System)


/**
 * @class Renderer
 * @brief Abstract interface for rendering components in the Cell engine.
 *
 * This class defines the contract for rendering any component in the engine.
 */
class Renderer {
public:
    __cell_virtual ~Renderer() = default;

    /**
     * @brief Render a component in the specified format.
     * @param data The data required to render the component.
     * @param format The desired rendering format.
     * @return A generic result (e.g., std::string, std::vector<uint8_t>, etc.).
     */
    __cell_virtual std::any render(const void* data, RenderFormat format) const = 0;
};

CELL_NAMESPACE_END

#endif  // RENDERER_HPP
