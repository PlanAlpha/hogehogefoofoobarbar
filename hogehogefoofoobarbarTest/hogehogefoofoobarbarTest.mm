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
    {
        PAMovingAverage<int16_t, 10> average;
        for (int i = 0; i < 100; i++) {
            switch (arc4random_uniform(3)) {
                case 0:
                    XCTAssertEqual(average.addValue(-1), 0);
                    break;
                    
                case 1:
                    XCTAssertEqual(average.addValue(0), 0);
                    break;
                    
                case 2:
                    XCTAssertEqual(average.addValue(1), 0);
                    break;
                    
                default:
                    XCTAssert(false);
                    break;
            }
        }
    }
    
    {
        PAMovingAverage<float, 10> average;
        for (int i = 0; i < 100; i++) {
            switch (arc4random_uniform(3)) {
                case 0:
                    XCTAssert(fabs(average.addValue(-1)) < 1);
                    break;
                    
                case 1:
                    XCTAssert(fabs(average.addValue(0)) < 1);
                    break;
                    
                case 2:
                    XCTAssert(fabs(average.addValue(1)) < 1);
                    break;
                    
                default:
                    XCTAssert(false);
                    break;
            }
        }
    }
}

@end
