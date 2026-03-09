#pragma once

#include "Buffer.h"
#include <cstdint>   // uint32_t
#include <string>    // std::string — must be included before use in structs
#include <vector>
#include <memory>

namespace Atometa {

    enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
            default:                     return 0;
        }
    }

    struct VertexBufferElement {
        std::string    Name;
        ShaderDataType Type        = ShaderDataType::None;
        uint32_t       Size        = 0;
        uint32_t       Offset      = 0;
        bool           Normalized  = false;

        VertexBufferElement() = default;
        VertexBufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type),
              Size(ShaderDataTypeSize(type)), Offset(0),
              Normalized(normalized) {}

        uint32_t GetComponentCount() const {
            switch (Type) {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3;
                case ShaderDataType::Mat4:   return 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
                default:                     return 0;
            }
        }
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout() = default;
        VertexBufferLayout(std::initializer_list<VertexBufferElement> elements)
            : m_Elements(elements) { CalculateOffsetsAndStride(); }

        const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
        uint32_t GetStride() const { return m_Stride; }

        std::vector<VertexBufferElement>::iterator       begin()       { return m_Elements.begin(); }
        std::vector<VertexBufferElement>::iterator       end()         { return m_Elements.end(); }
        std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<VertexBufferElement>::const_iterator end()   const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.Offset  = offset;
                offset         += element.Size;
                m_Stride       += element.Size;
            }
        }

        std::vector<VertexBufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind()   const;
        void Unbind() const;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb,
                             const VertexBufferLayout& layout);
        void SetIndexBuffer (const std::shared_ptr<IndexBuffer>&  ib);

        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
        uint32_t GetRendererID() const { return m_RendererID; }

    private:
        uint32_t m_RendererID          = 0;
        uint32_t m_VertexBufferIndex   = 0;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer>               m_IndexBuffer;
    };

} // namespace Atometa