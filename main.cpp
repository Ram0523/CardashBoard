#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



// #include <gtest/gtest.h>


// int main(int argc,char **argv){
//     testing::InitGoogleTest(&argc,argv);
//     return RUN_ALL_TESTS();
// }
