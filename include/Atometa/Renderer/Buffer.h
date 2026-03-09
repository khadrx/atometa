#pragma once

#include "Atometa/Core/Core.h"
#include <cstdint>   // uint32_t — required for GCC/Clang
#include <vector>

namespace Atometa {

    enum class BufferUsage { Static, Dynamic, Stream };

    // ── Vertex Buffer ─────────────────────────────────────────────────────
    class VertexBuffer {
    public:
        VertexBuffer(const void* data, uint32_t size,
                     BufferUsage usage = BufferUsage::Static);
        ~VertexBuffer();

        void Bind()   const;
        void Unbind() const;

        void SetData(const void* data, uint32_t size);

        uint32_t GetRendererID() const { return m_RendererID; }

    private:
        uint32_t m_RendererID = 0;
    };

    // ── Index Buffer ──────────────────────────────────────────────────────
    class IndexBuffer {
    public:
        IndexBuffer(const uint32_t* indices, uint32_t count,
                    BufferUsage usage = BufferUsage::Static);
        ~IndexBuffer();

        void Bind()   const;
        void Unbind() const;

        void SetData(const uint32_t* indices, uint32_t count);

        uint32_t GetCount()      const { return m_Count; }
        uint32_t GetRendererID() const { return m_RendererID; }

    private:
        uint32_t m_RendererID = 0;
        uint32_t m_Count      = 0;
    };

} // namespace Atometa