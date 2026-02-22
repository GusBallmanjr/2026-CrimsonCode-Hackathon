/*
 Project: Hackathon — File Drop Interface
 Authors: Gus Ballman, Jameson Scott
 File:    main.cpp

 Summary:
     Implements a Windows-integrated drag‑and‑drop system inside an SFML 3.0.2
     application. The program creates a graphical window with a designated drop
     zone where users can drag .txt files from the operating system. A custom
     Win32 window procedure intercepts WM_DROPFILES messages and forwards the
     dropped file path into the SFML event loop. The UI highlights the drop box
     on hover and reports whether the file was dropped inside or outside the
     target region.

 Major Components: (Written by Copilot)
     + Win32 Drop Handler:
         A custom WndProc (FileDropWndProc) receives WM_DROPFILES and extracts
         the file path using DragQueryFileA. The result is stored in a global
         buffer for retrieval inside the SFML loop.

     + SFML Window + Native Handle:
         SFML 3.0.2 exposes getNativeHandle(), allowing the program to attach
         the custom Win32 callback and enable DragAcceptFiles().

     + Drop Box UI:
         A simple, clean rectangle rendered with SFML shapes. The box changes
         color on hover to provide visual feedback and acts as the target region
         for file‑drop detection.

     + Event Loop:
         Uses SFML’s modern event API (event->is<sf::Event::Closed>()) to
         process window events while polling for dropped files and updating the
         UI.

 Notes:
     This implementation avoids SFML text/font dependencies for maximum
     compatibility with SFML 3.0.2 and focuses on a minimal, stable, and
     platform‑integrated drag‑and‑drop workflow.
*/

#include "Hackathon.hpp"

std::string gDroppedFile;

// Win32 callback to catch file drops
LRESULT CALLBACK FileDropWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DROPFILES)
    {
        HDROP hDrop = (HDROP)wParam;

        char filePath[MAX_PATH];
        DragQueryFileA(hDrop, 0, filePath, MAX_PATH);

        gDroppedFile = filePath;

        DragFinish(hDrop);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int gui_interface()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Encrypt");

    HWND hwnd = (HWND)window.getNativeHandle();
    DragAcceptFiles(hwnd, TRUE);
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)FileDropWndProc);

    sf::RectangleShape dropBox;
    dropBox.setSize(sf::Vector2f(300.f, 200.f));
    dropBox.setPosition(sf::Vector2f(350.f, 300.f));
    dropBox.setFillColor(sf::Color(60, 60, 60));
    dropBox.setOutlineThickness(6.f);
    dropBox.setOutlineColor(sf::Color(150, 150, 150));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Hover highlight
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(hwnd, &p);
        sf::Vector2f mousePos((float)p.x, (float)p.y);

        if (dropBox.getGlobalBounds().contains(mousePos))
        {
            dropBox.setFillColor(sf::Color(80, 80, 110));
            dropBox.setOutlineColor(sf::Color(180, 180, 255));
        }
        else
        {
            dropBox.setFillColor(sf::Color(60, 60, 60));
            dropBox.setOutlineColor(sf::Color(150, 150, 150));
        }

        // File drop
        if (!gDroppedFile.empty())
        {
            if (dropBox.getGlobalBounds().contains(mousePos))
                std::cout << "Dropped into box: " << gDroppedFile << std::endl;
            else
                std::cout << "Dropped outside box: " << gDroppedFile << std::endl;

            gDroppedFile.clear();
        }

        window.clear(sf::Color(20, 20, 20));
        window.draw(dropBox);
        window.display();
    }

    return 0;
}

int terminal_interface(int argc, char* argv[]) {

  return 0;
}

int main(int argc, char* argv[]) {
  if (argv[1] == "--gui-interface") {
    gui_interface();
  }
  else {
    terminal_interface(argc, argv);
  }

  return 0;
}
