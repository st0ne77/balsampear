#include "mainwindow.h"
#include "AVParser.h"


using namespace std;
using PlayerCore::AVParser;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Video Player 0.1");
    resize(800, 600);
    
    
    AVParser parser;
    parser.setFile("E:\\Project\\TestFile\\video.mp4");
    parser.parse();
}

MainWindow::~MainWindow()
{
}

