#include <iostream>
#include <lodepng.h>
#include <vector>
#include <cstdint>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

void decodeFromPng(std::vector<unsigned char>& image, const char* filename, unsigned height, unsigned width) {
    /*
     * Функция для чтения png файла
     */
    std::vector<unsigned char> png;
    //load and decode
    unsigned error = lodepng::load_file(png, filename);
    if(!error) error = lodepng::decode(image, width, height, png);

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ... 
}

void getBlueChannel(const std::vector<unsigned char>& image, int** arr, int rows, int cols) {
    /*
     * Функция, которая выделяет синий канал из одномерного вектора и
     * заполняет им двумерный массив
     */
    for (int i = 2, j = 0, k = 0; i < image.size(); i += 4, ++k) {
        if (k == cols) {
            k = 0; // обнуляем номер столбца
            ++j; // увеличиваем номер строки
        }
        arr[j][k] = int(image[i]);
    }
}
void printArray(int** arr, int rows, int cols) { 
    /*
     * Функция для вывода массива в консоль
     */
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            std::cout << arr[i][j] << " ";
        std::cout << endl;    
    }
}

void drawPath(const vector<int>& path, vector<unsigned char>& image, int rows, int cols, const char* output_file) {
    int i = 0, j = -1;
    int previousPoint = -1;
    for (auto& e : path) {
        if (previousPoint == e)
            ++i;
        else
            j = e;
        previousPoint = e;
        // draw red path R = 255, G = 0, B = 0
        int index = (i*cols + j)*4;
        image[index] = (unsigned char)255;
        image[++index] = (unsigned char)0;
        image[++index] = (unsigned char)0;
    }


    
    //Encode the image
    unsigned error = lodepng::encode(output_file, image, cols, rows);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}



void findOptimalPath(int** arr, vector<int>& path, int x_i, int x_f, int rows, int cols) {
    //--------------------------------------------------------------------------------
    //arr - массив с пикселями картинки, path - вектор переданный по ссылке, в который мы должны используя push_back записать путь. 
    //Принцип записи пути следующий - записывается номер столбца пути(столбцы нумеруются с 0), 
    //первый элемент path это номер столбца x_s, последний элемент - номер столбца x_f. 
    //Длина пути - будет равняться длине массива path. 
    struct Point
    {
      int own_cost;
      int path_cost =  std::numeric_limits<int>::max();
      bool visited = false;
      int previous_i = -1;
      int previous_j = -1;
    };

    Point** P = new Point* [rows];
    for (int row = 0; row < rows; ++row)
        P[row] = new Point [cols];

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j)
        {
            P[i][j].own_cost = arr[i][j] + 1;
            P[i][j].visited = false;
        }

    }


    P[0][x_i].path_cost = 0;
    int visited_number =  0;


    while (visited_number < rows * cols)
    {
        int min_path_cost = std::numeric_limits<int>::max();

        int I = -10; int J = -10;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {

                if (!(P[i][j].visited)) 
                {
                    if (P[i][j].path_cost < min_path_cost) 
                    {
                        I = i;
                        J = j;
                        min_path_cost = P[i][j].path_cost;
                    }

                }
            }
        }

        if (I < rows - 1)
        {
            if (P[I + 1][J].path_cost > P[I][J].path_cost + P[I][J].own_cost)
            {
                if (P[I + 1][J].visited)
                    visited_number--;
                  
                P[I + 1][J].path_cost = P[I][J].path_cost + P[I][J].own_cost;
                P[I + 1][J].visited = false;
                P[I + 1][J].previous_i= I;
                P[I + 1][J].previous_j= J;
                
            }
        }


        
        if(J < cols - 1)
        {
            if (P[I][J + 1].path_cost > P[I][J].path_cost + P[I][J].own_cost)
            {
                if (P[I][J + 1].visited)
                    visited_number--;
                  
                P[I][J + 1].path_cost = P[I][J].path_cost + P[I][J].own_cost;
                P[I][J + 1].visited = false;
                P[I][J + 1].previous_i= I;
                P[I][J + 1].previous_j= J;
                
            }
        }

        if(J > 0)
        {
            if (P[I][J - 1].path_cost > P[I][J].path_cost + P[I][J].own_cost)
            {
                if (P[I][J - 1].visited)
                    visited_number--;
        
                P[I][J - 1].path_cost = P[I][J].path_cost + P[I][J].own_cost;
                P[I][J - 1].visited = false;
                P[I][J - 1].previous_i= I;
                P[I][J - 1].previous_j= J;
                
            }
        }
        P[I][J].visited = true;
        visited_number++;
    }

    int I_now = rows - 1; int J_now = x_f;
    
    while (I_now != 0 || J_now != x_i) {
        //std::cout << I_now << " " << J_now <<endl<< "Previous:" << P[I_now][J_now].previous_i << " " <<  P[I_now][J_now].previous_j << endl;
        path.push_back(J_now);

        int x = I_now; int y = J_now;

        I_now = P[x][y].previous_i ;
        J_now = P[x][y].previous_j ;
    }

    path.push_back(J_now);
    // Переворачиваем путь, чтобы стартовать из начала
    std::reverse(path.begin(), path.end());
    
    for (int row = 0; row < rows; ++row )
        delete[] P[row];
    delete P;

}

int main(int argc, char* argv[]) {
    
    if (argc != 7) {
        cerr << "Wrong input arguments" << endl;
        return -1;
    }
    int rows = stoi(argv[2]), cols = stoi(argv[3]); // определение строк и столбцов как у матрицы в математике
    int x_i = stoi(argv[4]), x_f = stoi(argv[5]);
    char *input_file = argv[1], *output_file = argv[6];
    // читаем png изображение
    std::vector<unsigned char> image; // vector to store value of pixels with all 4 channels RGBA
    decodeFromPng(image, input_file, rows, cols); // read png file
    
    // способ 3 стр. 115 создания двумерного массива
    // выделяем память
    
    int** arr = new int*[rows];
    for (int row = 0; row < rows; ++row )
        arr[row] = new int[cols];

    // инициализируем выделенный массив arr синим каналом нашего изображения
    getBlueChannel(image, arr, rows, cols);  

    // можно опционально выводить массив в консоль для отладки 
    printArray(arr, rows, cols);  
    
    //функцию ниже вам нужно реализовать
    //-----------------------------------------------------------------------------
    vector<int> path;  // вектор к которому нужно делать push_back для добавления точек пути 
    findOptimalPath(arr, path, x_i, x_f, rows, cols);
   //------------------------------------------------------------------------------



    // далее можно отрисовать path используя фукцию ниже
    drawPath(path, image, rows, cols, output_file);

    // очищаем память
    for (int row = 0; row < rows; ++row )
        delete[] arr[row];
    delete arr;
    getchar();
}

