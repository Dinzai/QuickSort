/*

Open Source !

I hereby grant permision to anyone to use this file/code for any purposes

Wrote by Brett Rogers

Inspiration and psudo-code -> Coding Trains Quick Sort


This uses SFML to draw to the window
Written on Linux, away from my Windows Computer   

:'(



*/


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

#define windowWidth 800
#define windowHeight 600
namespace Dinzai {
struct Sort {

  Sort() {}

  void Swap(std::vector<int> &array, int a, int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
  }

  int Partition(std::vector<int> &array, int start, int end) {
    int pivotIndex = start;
    int pivotValue = array[end];
    for (int i = start; i < end; i++) {
      if (array[i] < pivotValue) {
        Swap(array, i, pivotIndex);
        pivotIndex++;
      }
    }
    Swap(array, pivotIndex, end);
    return pivotIndex;
  }

  void QuickSort(std::vector<int> &array, int start, int end) {

    if (start >= end) {
      return;
    }
    int index = Partition(array, start, end);
    QuickSort(array, start, index - 1);
    QuickSort(array, index + 1, end);
  }
};

struct Data {

  Data() {}

  ~Data() {}

  void GenerateRandomNumbers(int amount) {
    for (int i = 0; i < amount; i++) {
      int random = 10 + (rand() % (100 - 10 + 1));
      listOfNumbers.push_back(random);
    }
  }

  void PrintList() {
    for (int i : listOfNumbers) {
      std::cout << i << '\n';
    }
  }

  void SortList() {
    int end = listOfNumbers.size() - 1;
    sort.QuickSort(listOfNumbers, 0, end);
  }

  std::vector<int> listOfNumbers;
  Sort sort;
};

struct Graph {

  Graph(int amount) {
    data = new Data();
    data->GenerateRandomNumbers(amount);
  }

  void MakeTower() {

    for (int i = 0; i < data->listOfNumbers.size(); i++) {

      int height = data->listOfNumbers[i];
      iD.push_back(height);
      offset = (windowWidth / data->listOfNumbers.size()) * 0.1;
      float positionX = startPosition + (i * width * offset);
      float positionY = windowHeight - 200;
      sf::RectangleShape tempShape;
      tempShape.setOutlineThickness(1);
      tempShape.setOutlineColor(sf::Color::Black);
      tempShape.setSize(sf::Vector2f(
          width, -height)); //- height allows offset from 'ground', to look
                            // correct, basically, flips the image
      tempShape.setFillColor(sf::Color::Red);
      tempShape.setPosition(sf::Vector2f(positionX, positionY));
      shapes.push_back(tempShape);
    }
  }

  void DrawTower(sf::RenderWindow &window) {
    for (sf::RectangleShape shape : shapes) {
      window.draw(shape);
    }
  }

  Data *data;

  int startPosition = 2;
  int width = 10;
  float offset = 0;

  std::vector<int> iD; // vlaues, the heights

  std::vector<sf::RectangleShape> shapes;
};

struct Screen {

  Screen() : window(sf::VideoMode(windowWidth, windowHeight), "Quick Sort") {
    g = new Graph(0);
  }

  void GenerateGraph(int amount) {

    g = new Graph(amount);
    // g->data->SortList();
    g->MakeTower();
  }

  void DrawGraph() { g->DrawTower(window); }

  void UserInput() {
    if (canMake) {
      int amount = 0;
      std::cin >> amount;
      GenerateGraph(amount);
      canMake = false;
    }

    if (canSort) {
      g->data->SortList();
      std::vector<int> tempList;
      tempList = g->data->listOfNumbers;
      g->data->listOfNumbers.clear();
      g->shapes.clear();
      g->data->listOfNumbers = tempList;
      g->MakeTower();
      canSort = false;
    }
  }

  void Run() {

    while (window.isOpen()) {

      deltaTime = mainClock.getElapsedTime();

      UserInput();
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            canMake = true;
          }
        }

        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            canSort = true;
          }
        }
      }

      mainClock.restart();

      window.clear(sf::Color::Cyan);
      DrawGraph();
      window.display();
    }
  }

  Graph *g;

  bool canMake = false;

  bool canSort = false;

  sf::RenderWindow window;
  sf::Clock mainClock;
  sf::Time deltaTime;
  sf::Event event;
};
} 
