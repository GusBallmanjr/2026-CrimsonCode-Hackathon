#include "Hackathon.hpp"
#include "Password.hpp"
#include "EncryptionBox.hpp"
#include "DecryptionBox.hpp"
#include "HashFunction.hpp"

static std::string droppedFile = "";
static int16_t D = 0;
static int16_t E = 0;
static int offset = 0;
static bool passwordConfirmed = false;
static WNDPROC originalWndProc = nullptr;

LRESULT CALLBACK FileDropWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DROPFILES)
    {
        HDROP hDrop = (HDROP)wParam;

        char filePath[MAX_PATH];
        DragQueryFileA(hDrop, 0, filePath, MAX_PATH);

        droppedFile = filePath;

        DragFinish(hDrop);
        return 0;
    }

    return CallWindowProc(originalWndProc, hwnd, msg, wParam, lParam);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "OGRE Encryption");
    float centerX = 500.f;

    Password passwordBox;
    EncryptionBox encryptBox;
    DecryptionBox decryptBox;

    EnDe selection = NEITHER;

    D = GenerateD();
    E = generateE(D, 5);

    HWND hwnd = (HWND)window.getNativeHandle();
    DragAcceptFiles(hwnd, TRUE);
    originalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)FileDropWndProc);

    sf::Font font("C:/Windows/Fonts/arial.ttf");

    sf::Text title(font, "OGRE Encryption", 60);
    title.setFillColor(sf::Color::Black);
    title.setPosition({ centerX - title.getLocalBounds().size.x / 2.f, 40.f });

    sf::RectangleShape dropBox({ 350.f, 220.f });
    dropBox.setPosition({ centerX - 175.f, 330.f });
    dropBox.setFillColor(sf::Color(60, 60, 60));
    dropBox.setOutlineThickness(6.f);
    dropBox.setOutlineColor(sf::Color(150, 150, 150));

    sf::RectangleShape fileIcon({ 70.f, 90.f });
    fileIcon.setFillColor(sf::Color(230, 230, 255));
    fileIcon.setOutlineThickness(3.f);
    fileIcon.setOutlineColor(sf::Color(150, 150, 200));
    fileIcon.setPosition({ centerX - 35.f, 360.f });

    sf::Text fileLabel(font, "", 22);
    fileLabel.setFillColor(sf::Color(230, 230, 230));

    bool fileVisible = false;
    bool fileEncrypted = false;
    std::string selectedFile = "";

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // --- Password typing ---
            if (event->is<sf::Event::TextEntered>())
            {
                if (passwordBox.getPasswordActive())
                {
                    uint32_t u = event->getIf<sf::Event::TextEntered>()->unicode;

                    if (u == 8)
                    {
                        std::string t = passwordBox.getPasswordText();
                        if (!t.empty())
                        {
                            t.pop_back();
                            passwordBox.setPasswordText(t);
                        }
                    }
                    else if (u >= 32 && u < 127)
                    {
                        std::string t = passwordBox.getPasswordText();
                        if (t == "Enter Password")
                            t.clear();
                        t.push_back((char)u);
                        passwordBox.setPasswordText(t);
                    }
                }
            }

            // --- Enter key confirms password ---
            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;

                if (key == sf::Keyboard::Key::Enter && passwordBox.getPasswordActive())
                {
                    std::string pwd = passwordBox.getPasswordText();
                    if (!pwd.empty() && pwd != "Enter Password")
                    {
                        std::string hash = hashPassword(pwd);
                        offset = hashToPrime(hash);
                        passwordConfirmed = true;
                        passwordBox.setPasswordActive(false);
                        passwordBox.setOutlineColor(sf::Color(150, 150, 150));
                    }
                }
            }

            // --- Mouse clicks ---
            if (event->is<sf::Event::MouseButtonPressed>() &&
                event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                // Password box
                if (passwordBox.getGlobalBounds().contains(mouse))
                {
                    passwordBox.setPasswordActive(true);
                    passwordBox.clicked();
                    if (passwordBox.getPasswordText() == "Enter Password")
                        passwordBox.setPasswordText("");
                    passwordConfirmed = false;
                }
                else
                {
                    passwordBox.setPasswordActive(false);
                    passwordBox.setFillColor(sf::Color(230, 230, 230));
                    passwordBox.setOutlineColor(sf::Color(150, 150, 150));
                }

                // Encrypt button
                if (encryptBox.getGlobalBounds().contains(mouse))
                {
                    selection = ENCRYPT;

                    if (passwordConfirmed && !selectedFile.empty())
                    {
                        EncryptFinal(selectedFile, offset, E);
                        fileEncrypted = true;
                    }
                }

                // Decrypt button
                if (decryptBox.getGlobalBounds().contains(mouse))
                {
                    selection = DECRYPT;

                    if (passwordConfirmed && !selectedFile.empty())
                    {
                        DecryptFinal(selectedFile, offset);
                        fileEncrypted = false;
                    }
                }
            }

            // --- Button visual state ---
            switch (selection)
            {
            case ENCRYPT:
                encryptBox.clicked();
                decryptBox.notClicked();
                break;
            case DECRYPT:
                decryptBox.clicked();
                encryptBox.notClicked();
                break;
            case NEITHER:
                encryptBox.notClicked();
                decryptBox.notClicked();
                break;
            }
        }

        // --- Drop box hover ---
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (dropBox.getGlobalBounds().contains(mouse))
        {
            dropBox.setFillColor(sf::Color(80, 80, 110));
            dropBox.setOutlineColor(sf::Color(180, 180, 255));
        }
        else
        {
            dropBox.setFillColor(sf::Color(60, 60, 60));
            dropBox.setOutlineColor(sf::Color(150, 150, 150));
        }

        // --- File dropped ---
        if (!droppedFile.empty())
        {
            selectedFile = droppedFile;
            std::string name = selectedFile.substr(selectedFile.find_last_of("\\/") + 1);
            fileLabel.setString(name);

            sf::FloatRect bounds = fileLabel.getLocalBounds();
            fileLabel.setPosition({ centerX - bounds.size.x / 2.f, 470.f });

            fileVisible = true;
            fileEncrypted = false;
            droppedFile.clear();
        }

        // --- Draw ---
        window.clear(sf::Color{ 135, 206, 235 });

        window.draw(title);
        window.draw(passwordBox);
        window.draw(dropBox);
        window.draw(encryptBox);
        window.draw(decryptBox);
        window.draw(encryptBox.encryptText);
        window.draw(decryptBox.decryptText);
        window.draw(passwordBox.passwordLabel);

        if (fileVisible)
        {
            window.draw(fileIcon);
            window.draw(fileLabel);
        }

        window.display();
    }

    return 0;
}