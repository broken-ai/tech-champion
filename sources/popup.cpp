/**

Opens a simple window with the given message

*/
const bool openMessageBox(const std::string &message,
                          const sf::Color &bgColor=sf::Color(15, 188, 249, 255),
                          const sf::Color &fontColor=sf::Color::Black)
{
    const int charSize = 14;
    const int windowWidth = charSize * message.length() / 2 + charSize * 2;
    const int windowHeight = charSize * 5;

    sf::RenderWindow msgWindow(sf::VideoMode(windowWidth, windowHeight), "Tech Champion", sf::Style::Close);
    msgWindow.setFramerateLimit(24);
    msgWindow.resetGLStates();

    sf::Event event;
    sf::Text messageText(message, *GAME_FONT, charSize);
    GUI::SimpleButton okButton(10, (int) (windowHeight - charSize * 1.5), 27, charSize, "Ok");

    okButton.label.setCharacterSize(charSize);
    okButton.label.setColor(fontColor);
    messageText.setColor(fontColor);
    messageText.setPosition((int) (windowWidth / 2 - message.length() * charSize / 4), (int) (charSize / 2));

    while (msgWindow.isOpen()) {
        while (msgWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                msgWindow.close();
            }
        }
        msgWindow.clear(bgColor);

        // Handle ok button press
        if (okButton.state == GUI::STATE::RELEASED) {
            okButton.state = GUI::STATE::NORMAL;
            return true;
        }

        msgWindow.draw(messageText);
        okButton.updateAndDraw(&msgWindow);
        msgWindow.display();
    }

    return false;
}
