#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>

std::vector<sf::RectangleShape> createMainRectangles(){
    std::vector<sf::RectangleShape> rects;

    //control rectangles
    sf::RectangleShape controlRect(sf::Vector2f(150.f,150.f));
    controlRect.setOrigin(controlRect.getSize() / 2.f);
    controlRect.setFillColor(sf::Color::Transparent);

    sf::RectangleShape gameArea(sf::Vector2f(450.f,450.f));
    gameArea.setOrigin(gameArea.getSize() / 2.f);
    gameArea.setFillColor(sf::Color::Transparent);
    gameArea.setPosition(300.f,300.f);
    rects.push_back(gameArea);

    controlRect.setPosition(150.f,150.f);
    rects.push_back(controlRect);
    controlRect.setPosition(300.f,150.f);
    rects.push_back(controlRect);
    controlRect.setPosition(450.f,150.f);
    rects.push_back(controlRect);

    controlRect.setPosition(150.f,300.f);
    rects.push_back(controlRect);
    controlRect.setPosition(300.f,300.f);
    rects.push_back(controlRect);
    controlRect.setPosition(450.f,300.f);
    rects.push_back(controlRect);

    controlRect.setPosition(150.f,450.f);
    rects.push_back(controlRect);
    controlRect.setPosition(300.f,450.f);
    rects.push_back(controlRect);
    controlRect.setPosition(450.f,450.f);
    rects.push_back(controlRect);

    sf::RectangleShape rect(sf::Vector2f(450.f,5.f));
    rect.setFillColor(sf::Color::White);
    rect.setOrigin(rect.getSize() / 2.f);

    //horizontal lines
    rect.setPosition(300.f, 225.f);
    rects.push_back(rect);
    
    rect.setPosition(300.f, 370.f);
    rects.push_back(rect);

    //vertical lines
    rect.setRotation(90.f);
    rect.setPosition(225.f,300.f);
    rects.push_back(rect);

    rect.setPosition(375.f,300.f);
    rects.push_back(rect);

    return rects;
}

std::vector<sf::RectangleShape> createX(float x, float y){
    sf::RectangleShape rect1(sf::Vector2f(100.f, 15.f));
    rect1.setFillColor(sf::Color::Red);
    rect1.setOrigin(rect1.getSize() / 2.f);
    rect1.setPosition(x, y);
    rect1.setRotation(45.f);

    sf::RectangleShape rect2(sf::Vector2f(100.f, 15.f));
    rect2.setFillColor(sf::Color::Red);
    rect2.setOrigin(rect2.getSize() / 2.f);
    rect2.setPosition(x, y);
    rect2.setRotation(-45.f);
    
    std::vector<sf::RectangleShape> xRectangles;
    xRectangles.push_back(rect1);
    xRectangles.push_back(rect2);
    
    return xRectangles;

}
sf::CircleShape createCircle(float x, float y){
    sf::CircleShape circle(50.f);
    circle.setPointCount(200);
    circle.setPosition(x,y);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setOutlineColor(sf::Color::Red);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(7.5);

    return circle;
}

bool boundControl(sf::RenderWindow& window, sf::RectangleShape& rect, sf::Vector2i& pixelPos){
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    if(rect.getGlobalBounds().contains(worldPos)) return true;
    else return false;
}

int containerControl(sf::RenderWindow& window, sf::Vector2i& pixelPos, std::vector<sf::RectangleShape>& mainRectangles){
    for(int i = 1; i <= 9; i++){
        if(boundControl(window, mainRectangles[i], pixelPos)){
            //std::cout << i << std::endl;
            return i-1;
        }
    }
    return -1;
}

int checkWin(int gameTable[9], int index, int player, std::vector<sf::RectangleShape>& rects){
    int line = index / 3; // 0,1,2
    int column = index % 3; // 0,1,2
    sf::RectangleShape rect(sf::Vector2f(550.f,10.f));
    rect.setFillColor(sf::Color::Blue);
    rect.setOrigin(rect.getSize() / 2.f);
    if(index % 2 == 0){    
        int cross; // 0,1,"2" if both(if index = 4)
        if(index != 4){
            if(index % 4 == 0){
                cross = 0;    
            }
            else if(index % 4 == 2){
                cross = 1;
            }
        }
        else{
            cross = 2;
        }
        switch (cross)
        {
        case 0:
            if(gameTable[0] == player && gameTable[4] == player && gameTable[8] == player){
            rect.setPosition(300.f, 300.f);
            rect.setRotation(45.f);
            rects.push_back(rect);
            return true;
            }
            break;
        case 1:
            if(gameTable[2] == player && gameTable[4] == player && gameTable[6] == player){
                rect.setPosition(300.f, 300.f);
                rect.setRotation(135.f);
                rects.push_back(rect);
                return 1;
            }   
            break;
        case 2:
            if(gameTable[0] == player && gameTable[4] == player && gameTable[8] == player){
                rect.setPosition(300.f, 300.f);
                rect.setRotation(45.f);
                rects.push_back(rect);
                return 1;
            }
            else if(gameTable[2] == player && gameTable[4] == player && gameTable[6] == player){
                rect.setPosition(300.f, 300.f);
                rect.setRotation(135.f);
                rects.push_back(rect);
                return 1;
            }    
            break;
        }
    }
    int win = 1;
    for(int i = line*3; i < line*3+3; i++){
        if(gameTable[i] == player){
            continue;
        }
        else{
            win = 0;
            break;
        }
    }
    if(win == 1){
        rect.setPosition(300.f,(float)((line+1)*150));
        rects.push_back(rect);
        return win;
    }
    else{
        win = 1;
    }
    for(int i = column; i < column+7; i += 3){
        if(gameTable[i] == player){
            continue;
        }
        else{
            win = 0;
            break;
        }
    }
    if(win == 0){
        return win;
    }
    else{
        rect.setPosition(((float)(column+1)*150),300.f);
        rect.setRotation(90.f);
        rects.push_back(rect);
        return win;
    }
}

int main(){
    sf::RenderWindow window(sf::VideoMode(600,800), "Tic Tac Toe");
    
    std::vector<sf::RectangleShape> mainRectangles = createMainRectangles();
    //0-> MAIN GAME AREA
    //1,9 -> X-O CONTAINERS
    //10,13 -> VISUAL LINES

    int gameTable[9] = {0};
    //0-> EMPTY
    //1-> X
    //2-> O


    std::vector<sf::CircleShape> circles;
    std::vector<sf::RectangleShape> rectangles;

    int turn = 0;//%0 -> X, %1 -> O
    int gameState = 1;
    int winner = 0; //1 -> X, 2 -> O
    int winCount[3] = {0,0};

    sf::Font font;
    if (!font.loadFromFile("font.ttf")){
        std::cerr << "Font file could not loaded." << std::endl;
        return -1;
    }

    sf::Text mainText;
    mainText.setFont(font);           
    mainText.setString("Turn : X");   
    mainText.setCharacterSize(20);      
    mainText.setFillColor(sf::Color::White);
    mainText.setPosition(75.f, 600.f);

    sf::Text counter[3];
    float gap = 0;
    for(auto& text : counter){
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(450.f, 600.f + gap);
        gap+=50.f;
    }
    counter[0].setString("X wins: 0");
    counter[1].setString("O wins: 0");
    counter[2].setString("  Ties: 0");

    sf::RectangleShape resetButton(sf::Vector2f(100.f, 15.f));

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            //left click
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && gameState){
                sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
                if(boundControl(window, mainRectangles[0], pixelPos)){
                    int index = containerControl(window,pixelPos, mainRectangles);
                    if(gameTable[index] != 0){
                        continue;
                    }

                    int x = mainRectangles[index+1].getPosition().x;
                    int y = mainRectangles[index+1].getPosition().y;
                    if(turn < 9){
                        if(turn % 2 == 0){
                            gameTable[index] = 1;
                            auto vec = createX(x,y);
                            rectangles.push_back(vec[0]);
                            rectangles.push_back(vec[1]);
                            if(checkWin(gameTable, index, 1, rectangles)){
                                winner = 1;
                                gameState = 0;
                                winCount[0]++;
                                counter[0].setString("X wins: " + std::to_string(winCount[0]));
                            }
                            else{
                                mainText.setString("Turn : O");  
                            }
                            turn++;
                        }   
                        else{
                            gameTable[index] = 2;
                            circles.push_back(createCircle(x,y));
                            if(checkWin(gameTable, index, 2, rectangles)){
                                gameState = 0;
                                winner = 2; 
                                winCount[1]++;
                                counter[1].setString("O wins: " + std::to_string(winCount[1]));
                            }
                            else{
                                mainText.setString("Turn : X");
                            }
                            turn++;
                        }
                    }
                    if(turn == 9 || winner != 0){
                        switch (winner)
                        {
                        case 0:
                            std::cout << "Tie!" << std::endl;
                            mainText.setString("Game over. Tie!"); 
                            winCount[2]++;
                            counter[2].setString("   Ties: " + std::to_string(winCount[2]));
                            break;
                        
                        case 1:
                            std::cout << "X player win!" << std::endl;
                            mainText.setString("Game over. X won!"); 
                            break;
                        
                        case 2:
                            std::cout << "O player win!" << std::endl;
                            mainText.setString("Game over. O won!"); 
                            break;
                        
                        default:
                            break;
                        }
                    }
                }                
            }
            //right click
            if(event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Right){
                std::cout << "gameState :" << gameState << std::endl;
                std::cout << "turn :" << turn << std::endl;
                std::cout << "winner :" << winner << std::endl;
            }
            //middle click
            if(event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Middle){      
                    circles.clear();
                    rectangles.clear();
                    gameState = 1;
                    std::memset(gameTable, 0, sizeof(gameTable));
                    turn = 0;
                    winner = 0;
                    mainText.setString("Turn : X"); 
                }
        }
        window.clear(sf::Color::Black);
        for(const auto& rect : mainRectangles){
            window.draw(rect);
        }
        for(const auto& circle : circles){
            window.draw(circle);
        }
        for(const auto& rect : rectangles){
            window.draw(rect);
        }
        for(const auto& text : counter){
            window.draw(text);
        }
        window.draw(mainText);
        
        window.display();
      
    }
    return 0;
}