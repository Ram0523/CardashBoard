#include "api.h"
#include "mainwindow.h"
#include <gtest/gtest.h>
#include <QSignalSpy>
using namespace :: testing;

// sumtest::sumtest() {}


TEST(gettingvalues,WhenKMValueCalledThenReturnCorrectValue){
    api* obj=new api;

    const int x=obj->GetTotalKm();
    const int val=25;
    EXPECT_EQ(val,x);
}

TEST(gettingvalues,WhenEngineHoursValueCalledThenReturnCorrectValue){
    api* obj=new api;

    const int x=obj->GetEngineHours();
    const int val=25;
    EXPECT_EQ(val,x);
}

TEST(gettingvalues,WhenKmEngineHoursFuelValueUpdatedThenReturnCorrectValue){
    api* obj=new api;

    const bool x=obj->UpdateKmEngine(80,20,10);
    EXPECT_TRUE(x);
}



// Test case to verify signal emission
TEST(SignalTest, LastUserSignalTest)
{
    MainWindow* obj=new MainWindow;
    api* ap=new api;

    // Create a signal spy to monitor the signal
    QSignalSpy spy(obj, &MainWindow::LastUserSignal);

    // Emit the signal
    obj->LastUserSignal(ap->GetLastUserPrefrence());

    // Verify that the signal was emitted with the correct argument
    ASSERT_EQ(spy.count(), 9); // Check that the signal was emitted once
    //QList<QVariant> arguments = spy.takeFirst();
   // ASSERT_EQ(arguments.at(0).toInt(), ap->GetLastUserPrefrence()); // Check the value emitted
}

// TEST(sumtest,WhenOneValueIsZeroThenReturnMaxValue){
//     sum obj;

//     const int x=obj.getvalue(0,4);
//     const int val=4;
//     EXPECT_EQ(val,x);
// }
