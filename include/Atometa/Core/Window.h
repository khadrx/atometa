#pragma once

#include "Atometa/Core/Core.h"
#include <cstdint>    // uint32_t
#include <string>
#include <functional>

struct GLFWwindow;

namespace Atometa {

    struct WindowProperties {
        std::string Title;
        uint32_t    Width;
        uint32_t    Height;
        bool        VSync;
        std::string IconPath;

        explicit WindowProperties(const std::string& title    = "Atometa",
                                  uint32_t           width    = 1600,
                                  uint32_t           height   = 900,
                                  bool               vsync    = true,
                                  const std::string& iconPath = "")
            : Title(title), Width(width), Height(height),
              VSync(vsync), IconPath(iconPath) {}
    };

    class Window {
    public:
        explicit Window(const WindowProperties& props);
        ~Window();

        void OnUpdate();
        bool ShouldClose() const;

        uint32_t GetWidth()       const { return m_Data.Width; }
        uint32_t GetHeight()      const { return m_Data.Height; }
        float    GetAspectRatio() const { return (float)m_Data.Width / (float)m_Data.Height; }
        bool     IsVSync()        const { return m_Data.VSync; }

        void SetVSync(bool enabled);

        // Declared here so Window.cpp definition matches
        void SetWindowIcon(const std::string& iconPath);

        GLFWwindow* GetNativeWindow() const { return m_Window; }

    private:
        void Init(const WindowProperties& props);
        void Shutdown();

        GLFWwindow* m_Window = nullptr;

        struct WindowData {
            std::string Title;
            uint32_t    Width  = 1600;
            uint32_t    Height = 900;
            bool        VSync  = true;
        } m_Data;
    };

} // namespace Atometa