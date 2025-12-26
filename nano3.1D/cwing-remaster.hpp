#pragma once
#include <windows.h>
#include <functional>
#include <string>

namespace cwing {

struct Window {
    HWND hwnd = nullptr;
    HINSTANCE hInst = nullptr;
    std::wstring title = L"Cwing Window";
    int width = 800;
    int height = 600;

    std::function<void(HDC)> on_paint;          // callback WM_PAINT
    std::function<void(MSG&)> on_message;       // callback do loop
    std::function<void(int, int)> on_resize;    // callback de resize (largura, altura)
    std::function<void()> on_loop;              // callback por frame

    bool create(HINSTANCE inst, const std::wstring& t = L"Cwing Window",
                int w = 800, int h = 600)
    {
        hInst = inst;
        title = t;
        width = w;
        height = h;

        WNDCLASS wc{};
        wc.lpfnWndProc = [](HWND h, UINT m, WPARAM w, LPARAM l) -> LRESULT {
            Window* win = nullptr;
            if (m == WM_NCCREATE) {
                CREATESTRUCT* cs = (CREATESTRUCT*)l;
                win = (Window*)cs->lpCreateParams;
                SetWindowLongPtr(h, GWLP_USERDATA, (LONG_PTR)win);
                win->hwnd = h;
            } else {
                win = (Window*)GetWindowLongPtr(h, GWLP_USERDATA);
            }

            if (!win) return DefWindowProc(h,m,w,l);

            switch (m) {
                case WM_PAINT:
                    if (win->on_paint) {
                        PAINTSTRUCT ps;
                        HDC hdc = BeginPaint(h, &ps);
                        win->on_paint(hdc);
                        EndPaint(h, &ps);
                    }
                    return 0;

                case WM_SIZE:
                    win->width = LOWORD(1);
                    win->height = HIWORD(1);
                    if (win->on_resize)
                        win->on_resize(win->width, win->height);
                    return 0;

                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;
            }

            return DefWindowProc(h,m,w,l);
        };

        wc.hInstance = hInst;
        wc.lpszClassName = L"CwingRemasterClass";
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        RegisterClass(&wc);

        hwnd = CreateWindow(
            wc.lpszClassName,
            title.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT,
            width, height,
            nullptr, nullptr, hInst, this
        );

        return hwnd != nullptr;
    }

    void set_title(const std::wstring& t) {
        title = t;
        if (hwnd) SetWindowText(hwnd, title.c_str());
    }

    void show(int cmd = SW_SHOW) {
        if (hwnd) ShowWindow(hwnd, cmd);
    }

    void loop() {
        MSG msg{};
        while (true) {
            while (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) return;
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (on_message) on_message(msg);
            }

            if (on_loop) on_loop();
        }
    }
};

} // namespace cwing
