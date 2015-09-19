#import <XCTest/XCTest.h>
#import "PAMovingAverage.h"

@interface hogehogefoofoobarbarTest : XCTestCase

@end

@implementation hogehogefoofoobarbarTest

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testMovingAverage
{
    PAMovingAverage<int16_t, 10> average;
    average.initialize(0);
    XCTAssertEqual(average.addValue(0), 0);
    XCTAssertEqual(average.addValue(0), 0);
    XCTAssertEqual(average.addValue(0), 0);
}

@end
