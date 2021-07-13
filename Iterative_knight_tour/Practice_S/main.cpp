#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime> 

using namespace std;

// Структура для хранения ходов
struct moveAttempt {
  // Координаты клетки, с которой начинается ход
  int x, y;
  // Номер хода
  int lastStep;
};

int main() {
  // Ввод начальных данных
  int n;
  int startX, startY;
  ifstream inFile("input.txt");
  if (inFile.is_open()) {
      inFile >> n;
      inFile >> startX;
      inFile >> startY;
  } 

  // Стек(или список) ходов
  vector<moveAttempt> movesStack;
  // Массив, хранящий посещенные клетки в данной последовательности ходов
  bool visited[8][8]{};

  // Начальная клетка посещена
  visited[startX][startY] = true;
  // И с нее начинаем ход
  movesStack.push_back({startX, startY, 0});

  ofstream outFile("output.txt");
  if (outFile.is_open()) {
      while (!movesStack.empty()) {
          // Клетка, на которой конь остановился в предыдущем ходу
          moveAttempt currentMove = movesStack.back();

          int currentX = currentMove.x, currentY = currentMove.y;
          if (currentMove.lastStep == 8) { // Если возможные ходы закончились
            // Вернуться на ход назад
              movesStack.pop_back();
              visited[currentX][currentY] = false;
          }
          else {
              int nextX, nextY;
              // Найти координаты следующей клетки
              switch (currentMove.lastStep) {
              case 0:
                  nextX = currentX + 2;
                  nextY = currentY + 1;
                  break;
              case 1:
                  nextX = currentX + 1;
                  nextY = currentY + 2;
                  break;
              case 2:
                  nextX = currentX - 1;
                  nextY = currentY + 2;
                  break;
              case 3:
                  nextX = currentX - 2;
                  nextY = currentY + 1;
                  break;
              case 4:
                  nextX = currentX - 2;
                  nextY = currentY - 1;
                  break;
              case 5:
                  nextX = currentX - 1;
                  nextY = currentY - 2;
                  break;
              case 6:
                  nextX = currentX + 1;
                  nextY = currentY - 2;
                  break;
              case 7:
                  nextX = currentX + 2;
                  nextY = currentY - 1;
                  break;
              default: // Невозможно, но default пусть будет
                  nextX = -1;
                  nextY = -1;
                  break;
              }
              // Если все поле обойдено
              if (movesStack.size() == n * n) {
                  // Проверить, идет ли ход в начальную клетку
                  if (nextX == startX && nextY == startY) {
                      // Если да, тогда задача решена, осталось напечатать последовательность ходов
                      for (int i = 0; i < movesStack.size(); ++i) {
                          int moveX = movesStack[i].x, moveY = movesStack[i].y; 
                          outFile << char(moveX + 'a') << " " << moveY + 1 << endl;
                      }
                      outFile << "время поиска решения " << clock() / 1000.0 << " сек." << endl;
                      return 0;
                  }
              }

              ++movesStack.back().lastStep; // Отметить, что вариант хода сделан
              if (0 <= nextX && nextX < n && 0 <= nextY && nextY < n // Если конь не выходит за границы поля
                  && !visited[nextX][nextY] // И в этой клетке еще не был
                  ) {
                  // Тогда следующий ход делать с указанной клетки
                  movesStack.push_back({ nextX, nextY, 0 });
                  // Указать, что в эту клетку конь уже заходил
                  visited[nextX][nextY] = true;
              }
          }
      }

      outFile << "Такой последовательности ходов нет" << endl;
      outFile << "время поиска решения " << clock() / 1000.0 << " сек." << endl;
      outFile.close();
  }

  inFile.close();
  return 0;
}