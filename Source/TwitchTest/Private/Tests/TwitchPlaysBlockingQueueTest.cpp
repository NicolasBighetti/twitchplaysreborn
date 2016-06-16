#include "TwitchPlaysAPI.h"
#include "AutomationTest.h"
#include "BlockingQueue.h"
#include "AssertionMacros.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TwitchPlaysBlockingQueueTest, "TwitchPlays.BlockingQueueTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter);

// Running test
bool TwitchPlaysBlockingQueueTest::RunTest(const FString& Parameters)
{
	BlockingQueue<int>* q = new BlockingQueue<int>();
	int32 val = 42;

	q->push(val);
	int32 test = q->pop();

	//Test val afther a pop
	TWITCH_CHECK(test == val, "Error on pop()");

	//Test IsEmpty
	TWITCH_CHECK(q->IsEmpty(), "Error on IsEmpty()");

	//Test clear
	q->clear();
	TWITCH_CHECK(q->IsEmpty(), "Error on clear()");
	
    return true;
}
