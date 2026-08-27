// The UCRT64 raylib static archive was compiled against GLFW as a DLL.  This
// bridge maps those import-pointer symbols to the static GLFW implementation,
// so GameClient.exe remains a single distributable executable.
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

extern "C"
{
#define GLFW_IMPORT(name) void* __imp_##name = reinterpret_cast<void*>(name)

GLFW_IMPORT(glfwCreateStandardCursor);
GLFW_IMPORT(glfwCreateWindow);
GLFW_IMPORT(glfwDefaultWindowHints);
GLFW_IMPORT(glfwDestroyWindow);
GLFW_IMPORT(glfwFocusWindow);
GLFW_IMPORT(glfwGetClipboardString);
GLFW_IMPORT(glfwGetError);
GLFW_IMPORT(glfwGetFramebufferSize);
GLFW_IMPORT(glfwGetGamepadState);
GLFW_IMPORT(glfwGetJoystickName);
GLFW_IMPORT(glfwGetKeyName);
GLFW_IMPORT(glfwGetKeyScancode);
GLFW_IMPORT(glfwGetMonitorName);
GLFW_IMPORT(glfwGetMonitorPhysicalSize);
GLFW_IMPORT(glfwGetMonitorPos);
GLFW_IMPORT(glfwGetMonitors);
GLFW_IMPORT(glfwGetMonitorWorkarea);
GLFW_IMPORT(glfwGetPlatform);
GLFW_IMPORT(glfwGetPrimaryMonitor);
GLFW_IMPORT(glfwGetProcAddress);
GLFW_IMPORT(glfwGetTime);
GLFW_IMPORT(glfwGetVideoMode);
GLFW_IMPORT(glfwGetVideoModes);
GLFW_IMPORT(glfwGetWin32Window);
GLFW_IMPORT(glfwGetWindowAttrib);
GLFW_IMPORT(glfwGetWindowContentScale);
GLFW_IMPORT(glfwGetWindowMonitor);
GLFW_IMPORT(glfwGetWindowPos);
GLFW_IMPORT(glfwHideWindow);
GLFW_IMPORT(glfwIconifyWindow);
GLFW_IMPORT(glfwInit);
GLFW_IMPORT(glfwJoystickPresent);
GLFW_IMPORT(glfwMakeContextCurrent);
GLFW_IMPORT(glfwMaximizeWindow);
GLFW_IMPORT(glfwPollEvents);
GLFW_IMPORT(glfwRawMouseMotionSupported);
GLFW_IMPORT(glfwRestoreWindow);
GLFW_IMPORT(glfwSetCharCallback);
GLFW_IMPORT(glfwSetClipboardString);
GLFW_IMPORT(glfwSetCursor);
GLFW_IMPORT(glfwSetCursorEnterCallback);
GLFW_IMPORT(glfwSetCursorPos);
GLFW_IMPORT(glfwSetCursorPosCallback);
GLFW_IMPORT(glfwSetDropCallback);
GLFW_IMPORT(glfwSetErrorCallback);
GLFW_IMPORT(glfwSetInputMode);
GLFW_IMPORT(glfwSetJoystickCallback);
GLFW_IMPORT(glfwSetKeyCallback);
GLFW_IMPORT(glfwSetMouseButtonCallback);
GLFW_IMPORT(glfwSetScrollCallback);
GLFW_IMPORT(glfwSetWindowAttrib);
GLFW_IMPORT(glfwSetWindowContentScaleCallback);
GLFW_IMPORT(glfwSetWindowFocusCallback);
GLFW_IMPORT(glfwSetWindowIcon);
GLFW_IMPORT(glfwSetWindowIconifyCallback);
GLFW_IMPORT(glfwSetWindowMaximizeCallback);
GLFW_IMPORT(glfwSetWindowMonitor);
GLFW_IMPORT(glfwSetWindowOpacity);
GLFW_IMPORT(glfwSetWindowPos);
GLFW_IMPORT(glfwSetWindowPosCallback);
GLFW_IMPORT(glfwSetWindowShouldClose);
GLFW_IMPORT(glfwSetWindowSize);
GLFW_IMPORT(glfwSetWindowSizeCallback);
GLFW_IMPORT(glfwSetWindowSizeLimits);
GLFW_IMPORT(glfwSetWindowTitle);
GLFW_IMPORT(glfwShowWindow);
GLFW_IMPORT(glfwSwapBuffers);
GLFW_IMPORT(glfwSwapInterval);
GLFW_IMPORT(glfwTerminate);
GLFW_IMPORT(glfwUpdateGamepadMappings);
GLFW_IMPORT(glfwWaitEvents);
GLFW_IMPORT(glfwWindowHint);
GLFW_IMPORT(glfwWindowShouldClose);
}
