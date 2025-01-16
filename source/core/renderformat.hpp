/*!
 * @file        renderformat.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Renderer system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       16 Jan 2025
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef RENDERFORMAT_HPP
#define RENDERFORMAT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::System)

/**
 * @enum RenderFormat
 * @brief Defines the supported rendering formats.
 */
enum class RenderFormat
{
    // Basic Formats

    HTML,      //!< Render as HTML.
    QML,       //!< Render as QML.
    XHTML,     //!< Render as XHTML.
    JSON,      //!< Render as JSON.
    XML,       //!< Render as XML.
    PDF,       //!< Render as PDF.
    Markdown,  //!< Render as Markdown.

    // UI Frameworks

    React,     //!< Render as React components.
    Vue,       //!< Render as Vue components.
    Angular,   //!< Render as Angular templates.
    Flutter,   //!< Render as Flutter widgets.

    // Data Formats

    YAML,      //!< Render as YAML.
    CSV,       //!< Render as CSV.
    Protobuf,  //!< Render as Protocol Buffers.

    // Graphics and Visualization

    SVG,       //!< Render as Scalable Vector Graphics.
    Canvas,    //!< Render as HTML5 Canvas commands.
    OpenGL,    //!< Render as OpenGL commands.
    WebGPU,    //!< Render as WebGPU commands.

    // Documentation

    LaTeX,     //!< Render as LaTeX.
    AsciiDoc,  //!< Render as AsciiDoc.

    // Serialization

    BSON,        //!< Render as Binary JSON.
    MessagePack, //!< Render as MessagePack.

    // Custom Formats

    CustomBinary, //!< Render as a custom binary format.
    CustomText    //!< Render as a custom text-based format.
};

CELL_NAMESPACE_END

#endif // RENDERFORMAT_HPP
